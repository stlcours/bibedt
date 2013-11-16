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

  $Id: BibItem.h,v 1.32 2006/08/13 12:19:50 stievie Exp $
*/

// BibItem.h: Schnittstelle für die Klasse CBibItem.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBITEM_H__D736B45E_C196_4A0E_9769_BFB2F47955B8__INCLUDED_)
#define AFX_BIBITEM_H__D736B45E_C196_4A0E_9769_BFB2F47955B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldList.h"
#include "BibReader.h"
#include "BibWriter.h"
#include "xString.h"

// Special BibItem types
static const TCHAR STR_PREAMBLE[] = _T("preamble");
static const TCHAR STR_STRING[]   = _T("string");
static const TCHAR STR_COMMENT[]  = _T("comment");
static const TCHAR STR_ARTICLE[]  = _T("article");
// Options item in config.bib
static const TCHAR STR_OPTIONS[]  = _T("options");
// The name of the filter item
static const TCHAR STR_FILTER[]   = _T("__filter__");

// Special values of a bib item
static const TCHAR STR_KEY[]      = _T("key");
static const TCHAR STR_VALUE[]    = _T("value");
static const TCHAR STR_TYPE[]     = _T("type");

/**
 * \brief Class representing a bib item.
 */
class CBibItem : public CFieldList 
{
public:
	BOOL IsRegularItem();
	DWORD GetMissingFields(CStringList* list = NULL);
	CString GetFieldValue(CString field);
	CString MatchesFields(CString teststr, CString fields, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact);
	BOOL m_CrossRefed;
	void GetSource(xString* src);
	void ApplyFilter(CField* filter);
	void DoQuickSearch(CString str, CString fields, BOOL regexpr);
	BOOL IsVisible() { return !m_Filtered && m_Matched; }  // Return TRUE when NOT filtered AND matched
	BOOL m_Bookmarked;
	BOOL Matches(CString teststr, CString field, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact);
	static BOOL SearchTest(CString str, CString substr, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact);
	void DoFilter(CField *filter);
	BOOL m_Filtered;
	BOOL m_Matched;
	CString GetPrettyString();
	DWORD m_Data;
	void SetSource(CString str);
	CString GetSource();
	void Assign(CBibItem* src);
	BOOL IsType(CString s);
	void ParseComment(CBibReader* file);
	CString GetValue() const { return m_Value; }
	void SetValue(CString value);
	void ParsePreamble(CBibReader* file);
	void ParseString(CBibReader* file);
	void LoadFromFile(CBibReader* file);
	void SaveToFile(CBibWriter* file);
	void SetType(CString value);
	CString GetType() const { return m_Type; }
	void SetKey(CString key);
	CString GetKey() const { return m_Key; }
	CBibItem(CObList *owner);
	virtual ~CBibItem();
private:
	CString m_Key;
	CString m_Type;
	CString m_Value;
};

#endif // !defined(AFX_BIBITEM_H__D736B45E_C196_4A0E_9769_BFB2F47955B8__INCLUDED_)
