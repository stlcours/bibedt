/*
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie[at]users[dot]sourceforge[dot]net, http://bibedt.sourceforge.net/

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  $Id: FieldList.cpp,v 1.9 2006/08/13 12:19:50 stievie Exp $
*/

// FieldList.cpp: Implementierung der Klasse CFieldList.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "FieldList.h"
#include "Field.h"
#include "BibList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CFieldList::CFieldList()
{
}

CFieldList::~CFieldList()
{
	Clear();
}

CField* CFieldList::Add(CString name, CString value)
{
	CField* i = new CField(this, name, value);
	AddTail((CObject *)i);
	return i;
}

void CFieldList::Delete(CField *f)
{
	POSITION p = CObList::Find((CObject*)f);
	if (p) {
		RemoveAt(p);
		delete f;
	}
}

CField* CFieldList::Find(CString name)
{
	POSITION h = GetHeadPosition();
	while (h) {
		CField* f = (CField*)GetNext(h);
		if (f) {
			if (f->GetName().CompareNoCase(name) == 0)
				return f;
		}
	}
	return NULL;
}

void CFieldList::LoadFromFile(CBibReader *file)
{
	CString tmp;
	_TUCHAR c;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
			case _T('%'):
				// Skip comment
				while (file->Read(&c, 1) && c != _T('\f') && c != _T('\r') && c != _T('\n'));
				break;
			case _T(' '):
			case _T('\f'):
			case _T('\r'):
			case _T('\n'):
			case _T('\t'):
				break;
			case _T('}'):
				return;
			default:
				{
					// one char back
					file->Seek(-1, CFile::current); 
					New()->LoadFromFile(file);
				}
				break;
		}
	}
}

BOOL CFieldList::GetModified()
{
	if (CBibEdtList::GetModified())
		return true;
	POSITION h = GetHeadPosition();
	while (h) {
		CField* fi = (CField*)GetNext(h);
		if (fi && fi->GetModified())
			return TRUE;
	}
	return FALSE;
}

void CFieldList::SetModified(BOOL value)
{
	CBibEdtList::SetModified(value);
	if (!value) {
		// Set everything in this list to FALSE
		POSITION h = GetHeadPosition();
		while (h) {
			CField* fi = (CField*)GetNext(h);
			if (fi) {
				fi->SetModified(FALSE);
			}
		}
	}
}

void CFieldList::Assign(CFieldList *src)
{
	Clear();
	Append(src);
}

void CFieldList::Append(CFieldList *lst)
{
	POSITION h = lst->GetHeadPosition();
	while (h) {
		CField* fi = (CField*)lst->GetNext(h);
		CField* old = Find(fi->GetName());
		if (!old)
			New()->Assign(fi);
		else
			// There is already a Field with the name, just update the value
			old->SetValue(fi->GetValue());
	}
}

void CFieldList::ClearValues()
{
	POSITION h = GetHeadPosition();
	while (h) {
		CField* fi = (CField*)GetNext(h);
		if (fi)
			fi->SetValue(_T(""));
	}
}

void CFieldList::DeleteEmpty()
{
	POSITION h = GetTailPosition();
	while (h) {
		CField* fi = (CField*)GetPrev(h);
		if (fi && fi->GetValue().IsEmpty()) {
			Delete(fi);
		}
	}
}

CField * CFieldList::New()
{
	CField *res = new CField(this);
	AddTail((CObject*)res);
	return res;
}

void CFieldList::Clear()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CField* f = (CField*)GetNext(p);
		delete f;
	}
	RemoveAll();
}

CFieldList * CFieldList::GetCorssRefed()
{
	if (m_Owner == NULL)
		return NULL;
	CField *ref = Find(STR_CROSSREF);
	if (ref != NULL) {
		return ((CBibList*)m_Owner)->Find(ref->GetValue());
	}
	return NULL;
}
