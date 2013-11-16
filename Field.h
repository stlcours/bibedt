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

  $Id: Field.h,v 1.24 2006/08/13 12:19:50 stievie Exp $
*/

// Field.h: Schnittstelle für die Klasse CField.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELD_H__67D27FB7_DB39_4A63_939C_0AC08C043505__INCLUDED_)
#define AFX_FIELD_H__67D27FB7_DB39_4A63_939C_0AC08C043505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibReader.h"
#include "xString.h"

// Special Fields
static const TCHAR STR_AUTHOR[]     = _T("author");
static const TCHAR STR_EDITOR[]     = _T("editor");
static const TCHAR STR_ORGANIZATION[] = _T("organization");
static const TCHAR STR_TITLE[]      = _T("title");
static const TCHAR STR_EDITION[]    = _T("edition");
static const TCHAR STR_SERIES[]     = _T("series");
static const TCHAR STR_BOOKTITLE[]  = _T("booktitle");
static const TCHAR STR_YEAR[]       = _T("year");
static const TCHAR STR_PUBLISHER[]  = _T("publisher");
static const TCHAR STR_ADDRESS[]    = _T("address");
static const TCHAR STR_ABSTRACT[]   = _T("abstract");
// Links, Refs
static const TCHAR STR_URL[]        = _T("URL");
static const TCHAR STR_LOCALURL[]   = _T("Local-Url");
static const TCHAR STR_LOCALREF[]   = _T("Local-Ref");
static const TCHAR STR_CROSSREF[]   = _T("Crossref");
static const TCHAR STR_PDF[]        = _T("pdf");
static const TCHAR STR_PS[]         = _T("ps");
static const TCHAR STR_DOI[]        = _T("doi");

class CField 
{
public:
	CObList *GetOwner() { return m_Owner; }
	CString GetExpandedValue(CObList *list);
	CString EncodeValue(CString val);
	CString DecodeValue(CString val);
	void GetSource(xString* src);
	void SetFilter(CString field, CString cond);
	CString GetFilterCond();
	CString GetFilterField();
	/* Return the field as string */
	CString GetSource();
	void Assign(CField* src);
	void SetModified(BOOL value);
	BOOL GetModified() const { return m_Modified; }
	void LoadFromFile(CBibReader* file);
	void SaveToFile(CFile* file);
	void SetValue(CString value);
	CString GetValue() const { return m_Value; }
	void SetName(CString name);
	CString GetName() const { return m_Name; }
	CField(CObList *owner, CString name, CString value);
	CField(CObList *owner);
	virtual ~CField();

private:
	CString m_Name;
	CString m_Value;
	CObList *m_Owner;
protected:
	BOOL m_Modified;
};

#endif // !defined(AFX_FIELD_H__67D27FB7_DB39_4A63_939C_0AC08C043505__INCLUDED_)
