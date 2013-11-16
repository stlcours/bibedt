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

  $Id: Field.cpp,v 1.20 2006/08/13 12:19:50 stievie Exp $
*/

// Field.cpp: Implementierung der Klasse CField.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Field.h"
#include "Globals.h"
#include "Coding.h"
#include "bibedt.h"
#include "BibedtDoc.h"
#include "BibReader.h"
#include "xString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CField::CField(CObList *owner, CString name, CString value)
{
	m_Owner = owner;
	m_Name = name;
	m_Value = value;
	m_Modified = FALSE;
}

CField::CField(CObList *owner)
{
	m_Owner = owner;
	m_Name.Empty();
	m_Value.Empty();
	m_Modified = FALSE;
}

CField::~CField()
{

}

void CField::SetName(CString name)
{
	if (m_Name.Compare(name) != 0) {
		m_Name = name;
		SetModified(TRUE);
	}
}

void CField::SetValue(CString value)
{
	if (m_Value.Compare(value) != 0) {
		m_Value = value;
		SetModified(TRUE);
	}
}

void CField::SaveToFile(CFile *file)
{
	if (!m_Value.IsEmpty()) {
		xString* str = xsNew();
		GetSource(str);
		file->Write(xsValue(str), xsLen(str));
		xsDelete(str);
	}
}

CString CField::DecodeValue(CString val)
{
	CBibDef* def = GetBibDef();
	if (def && !def->GetConvField(m_Name)) {
		return val;
	} else {
		CCoding *cc = ((CBibedtApp*)AfxGetApp())->m_Coding;
		return cc->Decode(val);
	}
}

void CField::LoadFromFile(CBibReader *file)
{
	xString* tmp = xsNew();
	_TUCHAR c;
	int openpar = 0;
	BOOL quote = FALSE;
	BOOL squote = FALSE;
	BOOL escape = FALSE;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
			case 9:
			case _T(' '):
				if ((openpar || quote) && !xsIsEmpty(tmp) && xsRightChar(tmp) != _T(' ')) {						
					// always use spaces
					xsPut(tmp, _T(' '));
				}
				escape = FALSE;
				break;
			case _T('='):
				if (openpar || quote)
					// inside value
					xsPut(tmp, c);
				else {
					// outside value
					xsTerminate(tmp);
					m_Name = CString(xsValue(tmp));
					xsClear(tmp);
				}
				escape = FALSE;
				break;
			case _T('\\'):
				escape = !escape;
				xsPut(tmp, c);
				break;
			case _T('"'):
				if (!escape)
					quote = !quote;
				xsPut(tmp, c);
				escape = FALSE;
				break;
			case _T('\''):
				if (!escape)
					squote = !squote;
				xsPut(tmp, c);
				escape = FALSE;
				break;
			case _T('{'):
				if (openpar || quote)
					xsPut(tmp, c);
				openpar++;
				escape = FALSE;
				break;
			case _T('}'):
				if (openpar)
					openpar--;
				else {
					// the last field
					file->Seek(-1, CFile::current);
					goto leave;
				}
				if (openpar || quote)
					xsPut(tmp, c);
				if (!openpar && !quote) {
					xsTerminate(tmp);
					m_Value = DecodeValue(CString(xsValue(tmp)));
					xsClear(tmp);
				}
				escape = FALSE;
				break;
			case _T(','):
				if (!openpar && !quote) {
					if (m_Value.IsEmpty()) {
						xsTerminate(tmp);
						m_Value = DecodeValue(CString(xsValue(tmp)));
					}
					goto leave;
				} else
					xsPut(tmp, c);
				escape = FALSE;
				break;
			case 10:
			case 13:
				escape = FALSE;
				break;
			default:
				xsPut(tmp, c);
				escape = FALSE;
				break;
		}
	}
leave:
	xsDelete(tmp);
}

void CField::SetModified(BOOL value)
{
	if (m_Modified != value)
		m_Modified = value;
}

void CField::Assign(CField *src)
{
	SetName(src->m_Name);
	SetValue(src->m_Value);
}


CString CField::GetSource()
{
	if (!m_Value.IsEmpty()) {
		xString* src = xsNew();
		GetSource(src);
		CString res = CString(xsValue(src));
		xsDelete(src);
		return res;
	} else
		return _T("");
}

CString CField::EncodeValue(CString val)
{
	CBibDef* def = GetBibDef();
	if (def && !def->GetConvField(m_Name)) {
		return val;
	} else {
		CCoding *cc = ((CBibedtApp*)AfxGetApp())->m_Coding;
		return cc->Encode(val);
	}
}

void CField::GetSource(xString *src)
{
	if (!m_Value.IsEmpty()) {
		DWORD MaxLine = ((CBibedtApp*)AfxGetApp())->m_Options->m_LineLength - 1;
		_TUCHAR c;

		xString* val = xsNewInitS(EncodeValue(m_Value));
		xsTerminate(val);
		xsCatS(src, _T("  "));
		xsCatS(src, m_Name);
		xsCatS(src, _T("={"));
		DWORD pos = 4 + m_Name.GetLength();
		int length = xsLen(val);
		xsGrow(src, length);
		for (int i = 0; i < length; i++) {
			c = xsChar(val, i);
			pos++;
			if (pos >= MaxLine && c == ' ' && i < length) {
				xsCatS(src, _T("\r\n    "));
				pos = 4;
			} else
				xsPut(src, c);
		}
		xsDelete(val);
		xsPut(src, _T('}'));
		xsTerminate(src);
	}
}

CString CField::GetFilterField()
{
	CString ret = _T("");
	int p = m_Value.Find(_T('='));
	if (p != -1) {
		ret = m_Value.Mid(0, p);
	}

	return ret;
}

CString CField::GetFilterCond()
{
	CString ret = _T("");
	int p = m_Value.Find(_T('='));
	if (p != -1) {
		ret = m_Value.Mid(p+1);
	}

	return ret;
}

void CField::SetFilter(CString field, CString cond)
{
	m_Value.Format(_T("%s=%s"), field, cond);
}

CString CField::GetExpandedValue(CObList *list)
{
	if (list == NULL)
		return _T("");

	CString res;
	// Expand @string
	if (!m_Value.IsEmpty()) {
		CBibItem *m = ((CBibList*)list)->FindMacro(m_Value);
		if (m != NULL)
			res = m->GetValue();
		else
			res = m_Value;
	}

	return res;

/*
	CBibItem *mi;
	CString res = _T("");
	CString macro = _T("");
	DWORD l = val.GetLength();
	DWORD i = 0;
	_TUCHAR c;
	while (i < l) {
		c = val.GetAt(i);
		switch (c) {
		case _T('{'):
			while (i < l) {
				i++;
				if (val.GetAt(i) == _T('}'))
					break;
			}
			break;
		case _T('\"'):
			while (i < l) {
				i++;
				if (val.GetAt(i) == _T('\"'))
					break;
			}
			break;
		case _T('\n'):
		case _T('\r'):
		case _T(' '):
		case _T('\t'):
			mi = ((CBibList*)list)->FindMacro(macro, owner);
			if (mi) {
				res += mi->GetValue();
				res += c;
			} else {
				res += macro;
				res += c;
			}
			macro.Empty();
			break;
		default:
			macro += c;
			break;
		}
		i++;
	}
	
	return res;
*/
}
