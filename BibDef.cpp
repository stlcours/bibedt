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

 $Id: BibDef.cpp,v 1.18 2006/07/29 11:33:14 stievie Exp $
*/
 
// BibDef.cpp: Implementierung der Klasse CBibDef.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "BibDef.h"
#include "bibedt.h"
#include "Options.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibDef::CBibDef()
{
	CFileFind finder;
	CBibedtApp* app = (CBibedtApp*)AfxGetApp();
	CString dfn = app->m_Options->m_TemplateFile;
	if (finder.FindFile(dfn)) {
		finder.Close();
		SetFilename(dfn);
	} else {
		if (SaveRes(dfn)) {
			this->SetFilename(dfn);
		} else {
			CString msg;
			msg.Format(IDS_ERR_NOTEMPLATEFILE, dfn);
			ShowError(msg);
			return;
		}
	}
	Load();
}

/**
 * Load the template file.
 */
BOOL CBibDef::Load()
{
	CFileException ex;
	CFile f;
	BOOL res;
	if (f.Open(m_Filename, CFile::modeRead | CFile::shareDenyWrite, &ex)) {
		res = CBibFile::Load(&f);
		f.Close();
	} else {
		res = FALSE;
		ex.ReportError();
	}
	return res;
}

CBibDef::~CBibDef()
{
}

/**
 * Returns how required the field is
 */
REQUIRED CBibDef::GetRequired(CString type, CString field)
{
	CBibItem* bi = FindType(type);
	if (!bi)
		return R_UNKNOWN;
	CField* fi = bi->Find(field);
	if (!fi)
		return R_UNKNOWN;
	return IsRequired(bi, fi);
}

REQUIRED CBibDef::IsRequired(CBibItem *item, CField *field)
{
	CString val = field->GetValue();
	int p = val.Find(_T(","), 0);
	if (p != -1)
		val.Delete(p, val.GetLength() - p);
	val.TrimLeft();
	val.TrimRight();
	if (val.CompareNoCase(_T("R")) == 0)
		return R_REQUIRED;
	else if (val.CompareNoCase(_T("O")) == 0)
		return R_OPTIONAL;
	else if (val.CompareNoCase(_T("I")) == 0)
		return R_IGNORED;
	return R_UNKNOWN;
}

/**
 * Get a list with all required fields
 */
DWORD CBibDef::GetRequiredFields(CString type, CStringList *lst)
{
	ASSERT(lst);
	lst->RemoveAll();
	CBibItem* item = FindType(type);
	if (!item)
		return 0;
	POSITION p = item->GetHeadPosition();
	while (p) {
		CField* field = (CField*)item->GetNext(p);
		if (IsRequired(item, field) == R_REQUIRED)
			lst->AddTail(field->GetName());
	}
	return lst->GetCount();	
}

/** 
 * Returns the name of the field
 */
CString CBibDef::GetOrder(CString type, int field)
{
	CBibItem* bi = FindType(type);
	if (!bi)
		return _T("");
	POSITION p = bi->GetHeadPosition();
	while (p) {
		CField *fi = (CField*)bi->GetNext(p);
		CString val = fi->GetValue();
		int p = val.Find(_T(","), 0);
		if (p != -1) {
			int p2 = val.Find(_T(","), p+1);
			if (p2 != -1) {
				val = val.Mid(p+1, p2-p-1);
				val.TrimLeft();
				val.TrimRight();
				if (_ttoi(val) == field)
					return fi->GetName();
			}
		}
	}
	return _T("");
}

/**
 * Returns how to format the field
 */
CString CBibDef::GetFormat(CString type, CString field)
{
	CString res = _T("%s");
	CBibItem* bi = FindType(type);
	if (!bi)
		return _T("");
	CField* fi = bi->Find(field);
	if (!fi)
		return _T("");
	CString val = fi->GetValue();
	int p = val.Find(_T(","), 0);
	if (p == -1)
		return res;
	p = val.Find(_T(","), p+1);
	if (p == -1)
		return res;
	val.Delete(0, p+1);
	// after the format
	p = val.Find(_T(","), p+1);
	if (p != -1)
		val.Delete(p, val.GetLength() - p);
	if (val.IsEmpty())
		return res;
	val.TrimLeft();
	val.TrimRight();
	if (val.Left(1) == _T("{") && val.Right(1) == _T("}"))
		val = val.Mid(1, val.GetLength() - 2);
	return val;
}

/**
 * If the template file does not exists extract the resource and save it.
 */
BOOL CBibDef::SaveRes(CString name)
{
	HRSRC hr = FindResource(NULL, _T("BIB_DEF"), _T("BIB"));
	if (hr == NULL)
		return FALSE;
	HGLOBAL hres = LoadResource(NULL, hr);
	if (hres == NULL)
		return FALSE;
	LPVOID lpres = LockResource(hres);
	if (lpres == NULL)
		return FALSE;
	CString strres((LPSTR)lpres);
	try {
		CFile f;
		f.Open(name, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
		f.Write(strres, strres.GetLength());
		f.Close();
		return TRUE;
	} catch (...) {
		return FALSE;
	}
}

/**
 * Returns the ImageIndex of the field
 */
int CBibDef::GetImage(CString type)
{
	CBibItem *item = FindType(type);
	if (!item)
		return -1;
	POSITION p1 = GetHeadPosition();
	int i = 0;
	while (p1) {
		CBibItem *ic = (CBibItem*)GetNext(p1);
		if (ic == item)
			return i;
		i++;
	}
	return -1;
}

/**
 * Return the \@option item
 */
CBibItem * CBibDef::GetOptionsItem() const
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (bi->IsType(STR_OPTIONS))
			return bi;
	}
	return NULL;
}

/**
 * Return default type (for BibItem Dialog)
 */
CBibItem * CBibDef::GetDefault() const
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (!bi->IsType(STR_OPTIONS) && !bi->IsType(STR_COMMENT) && !bi->IsType(STR_STRING) && !bi->IsType(STR_PREAMBLE))
			return bi;
	}
	return NULL;
}

/**
 * Return boolean option from \@option item
 */
BOOL CBibDef::GetBoolOption(CString name, BOOL def)
{
	CBibItem *op = GetOptionsItem();
	if (op) {
		CField *pn = op->Find(name);
		if (pn)
			return pn->GetValue().CompareNoCase(_T("true")) == 0;
	}
	return def;
}

/**
 * Return string option from \@option item
 */
CString CBibDef::GetStrOption(CString name, CString def)
{
	CBibItem *op = GetOptionsItem();
	if (op) {
		CField *pn = op->Find(name);
		if (pn)
			return pn->GetValue();
	}
	return def;
}

/**
 * Return integer option from \@option item
 */
int CBibDef::GetIntOption(CString name, int def)
{
	CBibItem *op = GetOptionsItem();
	if (op) {
		CField *pn = op->Find(name);
		if (pn)
			return _ttoi(pn->GetValue());
	}
	return def;
}

/**
 * Return the font style for a field.
 */
DWORD CBibDef::GetFontStyle(CString type, CString field)
{				 
	DWORD res = 0;
	CBibItem* bi = FindType(type);
	if (!bi)
		return 0;
	CField* fi = bi->Find(field);
	if (!fi)
		return 0;
	CString val = fi->GetValue();
	int p = val.Find(_T(","), 0);
	// 1
	if (p == -1)
		return res;
	// 2
	p = val.Find(_T(","), p+1);
	if (p == -1)
		return res;
	// 4
	p = val.Find(_T(","), p+1);
	if (p == -1)
		return res;

	val.Delete(0, p+1);
	if (val.IsEmpty())
		return res;
	val.TrimLeft();
	val.TrimRight();
	for (int i = 0; i < val.GetLength(); i++) {
		TCHAR c = val.GetAt(i);
		switch (c) {
		case _T('b'):
			res |= FS_BOLD;
			break;
		case _T('i'):
			res |= FS_ITALIC;
			break;
		case _T('u'):
			res |= FS_UNDERLINE;
			break;
		case _T('s'):
			res |= FS_STRIKE;
			break;
		}
	}
	return res;
}

BOOL CBibDef::GetConvField(CString name)
{
	return GetBoolOption(_T("convert_") + name, TRUE);
}
