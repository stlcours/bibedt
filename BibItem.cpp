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

  $Id: BibItem.cpp,v 1.52 2006/08/13 18:03:29 stievie Exp $
*/

// BibItem.cpp: Implementierung der Klasse CBibItem.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BibItem.h"
#include "Coding.h"
#include "bibedt.h"
#include "BibDef.h"
#include "RegExp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibItem::CBibItem(CObList *owner)
{
	m_Owner = owner;
	m_Key.Empty();
	m_Type.Empty();
	m_Data = 0;
	m_Filtered = FALSE;
	m_Matched = TRUE;
	m_Bookmarked = FALSE;
	m_CrossRefed = FALSE;
}

CBibItem::~CBibItem()
{
}

void CBibItem::SetKey(CString key)
{
	if (m_Key.Compare(key) != 0) {
		m_Key = key;
		CFieldList::SetModified(TRUE);
	}
}

void CBibItem::SetType(CString value)
{
	if (!IsType(value)) {
		m_Type = value;
		CFieldList::SetModified(TRUE);
	}
}

void CBibItem::SetValue(CString value)
{
	if (m_Value.Compare(value) != 0) {
		m_Value = value;
		CFieldList::SetModified(TRUE);
	}
}

void CBibItem::SaveToFile(CBibWriter* file)
{
	try {
		xString* str = xsNew();
		GetSource(str);
		file->WriteLn(xsValue(str));
		xsDelete(str);
	} catch (CFileException ex) {
		ex.ReportError();
	}
}

void CBibItem::LoadFromFile(CBibReader *file)
{
	xString* tmp = xsNew();
	m_Type.Empty();
	m_Key.Empty();
	Clear();
	_TUCHAR c = 0;
	int br = 0;
	if (!file->Read(&c, sizeof(_TUCHAR)) || c != _T('@'))
		return;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
			case _T('{'):
				// This was the type: @type
				xsTerminate(tmp);
				m_Type = CString(xsValue(tmp));
				if (IsType(STR_STRING)) {
					ParseString(file);
					goto leave;
				} else if (IsType(STR_PREAMBLE)) {
					ParsePreamble(file);
					goto leave;
				} else if (IsType(STR_COMMENT)) {
					ParseComment(file);
					goto leave;
				}
				br++;
				xsClear(tmp);
				break;
			case _T(','):
				xsTerminate(tmp);
				m_Key = CString(xsValue(tmp));
				CFieldList::LoadFromFile(file);
				goto leave;
			case _T('@'):
				file->Seek(-1, CFile::current); 
				goto leave;
			case _T('}'):
				br--;
				if (br == 0)
					goto leave;
				break;
			case _T('\0'):
			case _T(' '):
			case _T('\r'):
			case _T('\f'):
			case _T('\n'):
			case _T('\t'):
				break;
			default: 
				xsPut(tmp, c);
				break;
		}
	}
leave:
	xsDelete(tmp);
}

void CBibItem::ParseString(CBibReader *file)
{
	// @STRING{ name = "value"}
	// name -> m_Key
	// value -> m_Value
	CCoding *cc = ((CBibedtApp*)AfxGetApp())->m_Coding;
	xString* tmp = xsNew();
	m_Key.Empty();
	m_Value.Empty();
	_TUCHAR c = 0;
	BOOL openq = FALSE;
	BOOL escape = FALSE;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
		case _T('='):
			if (!openq) {
				xsTerminate(tmp);
				m_Key = CString(xsValue(tmp));
				xsClear(tmp);
			} else
				xsPut(tmp, c);
			escape = FALSE;
			break;
		case _T('\\'):
			escape = !escape;
			xsPut(tmp, c);
			break;
		case _T('"'):
			if (!escape)
				openq = !openq;
			else
				xsPut(tmp, c);
			if (!openq)	{
				xsTerminate(tmp);
				m_Value = cc->Decode(xsValue(tmp));
				xsClear(tmp);
			}
			escape = FALSE;
			break;
		case _T('}'):
			if (!openq) {
				goto leave;
			} else
				xsPut(tmp, c);
			escape = FALSE;
			break;
		case _T(' '):
		case _T('\r'):
		case _T('\f'):
		case _T('\n'):
		case _T('\t'):
			if (openq)
				xsPut(tmp, c);
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

void CBibItem::ParsePreamble(CBibReader *file)
{
	// @preamble{"foo bar"}
	// foo bar -> m_Value
	xString* tmp = xsNew();
	m_Key.Empty();
	m_Value.Empty();
	_TUCHAR c = 0;
	BOOL quote = FALSE;
	BOOL escape = FALSE;
	int brack = 1;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
		case _T('}'):
			brack--;
			if (!brack) {
				xsTerminate(tmp);
				m_Value = CString(xsValue(tmp));
				xsClear(tmp);
				goto leave;
			} else
				xsPut(tmp, c);
			escape = FALSE;
			break;
		case _T('{'):
			xsPut(tmp, c);
			brack++;
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
		default:
			xsPut(tmp, c);
			escape = FALSE;
			break;
		}
	}
leave:
	xsDelete(tmp);
}

void CBibItem::ParseComment(CBibReader *file)
{
	// @COMMENT{You may put a comment in a `comment' command,
	//   the way you would with SCRIBE.}
	xString* tmp = xsNew();
	m_Key.Empty();
	m_Value.Empty();
	// this gets only called when @comment{ was found, so we have already a bracket
	int brack = 1;
	_TUCHAR c = 0;
	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
		case _T('{'):
			if (brack > 0)
				xsPut(tmp, c);
			brack++;
			break;
		case _T('}'):
			brack--;
			if (brack == 0) {
				xsTerminate(tmp);
				m_Value = CString(xsValue(tmp));
				goto leave;
			} else
				xsPut(tmp, c);
			break;
		case _T(','):
			xsTerminate(tmp);
			if (xsICompareS(tmp, STR_FILTER) == 0) {
				// Filter:
				// @comment{__filter__,
				//   name1={field=condition},
				//   ...
				// }
				m_Key = CString(xsValue(tmp));
				// Filter have the same syntax as ordinary items.
				CFieldList::LoadFromFile(file);
				goto leave;
			} else
				xsPut(tmp, c);
			break;
		default:
			xsPut(tmp, c);
			break;
		}
	}
leave:
	xsDelete(tmp);
}

/**
 * Return TRUE when this item is of a certain type
 */
BOOL CBibItem::IsType(CString s)
{
	return (!m_Type.IsEmpty() && m_Type.CompareNoCase(s) == 0);
}

void CBibItem::Assign(CBibItem *src)
{
	SetKey(src->m_Key);
	SetType(src->m_Type);
	SetValue(src->m_Value);
	m_Bookmarked = src->m_Bookmarked;
	m_Data = src->m_Data;
	m_Filtered = src->m_Filtered;
	m_Matched = src->m_Matched;
	CFieldList::Assign(src);
}

CString CBibItem::GetSource()
{
	xString* src = xsNew();
	GetSource(src);
	CString res(xsValue(src));
	xsDelete(src);
	return res;
}

void CBibItem::GetSource(xString *src)
{
	xsPut(src, _T('@'));
	xsCatS(src, m_Type);
	xsPut(src, _T('{'));
	CCoding *cc = ((CBibedtApp*)AfxGetApp())->m_Coding;
	if (IsType(STR_STRING)) {
		// @STRING{ name = "value"}
		// name -> m_Key
		// value -> m_Value
		xsCatS(src, m_Key);
		xsCatS(src, _T("=\""));
		xsCatS(src, cc->Encode(m_Value));
		xsCatS(src, _T("\"}\r\n"));
	} else if (IsType(STR_PREAMBLE)) {
		// @preamble{"foo bar"}
		// foo bar -> m_Value
		xsCatS(src, m_Value);
		xsCatS(src, _T("}\r\n"));
	} else if (IsType(STR_COMMENT) && m_Key.Compare(STR_FILTER) != 0) {
		// Filters have the usual syntax and must be saved the usual way

		// @comment{"foo bar"}
		// foo bar -> m_Value
		xsCatS(src, m_Value);
		xsCatS(src, _T("}\r\n"));
	} else {
		// An ordinary item
		xsCatS(src, m_Key);
		POSITION h = GetHeadPosition();
		for (int i = 0; i < GetCount(); i++) {
			CField* fi = (CField*)GetNext(h);
			if (fi) {
				xsCatS(src, _T(",\r\n"));
				fi->GetSource(src);
				xsTrimRight(src);
				if (xsRightChar(src) == _T(','))
					src->length--;
			}
			if (h == NULL)
				break;
		}
		xsCatS(src, _T("\r\n}\r\n"));
	}
	xsTerminate(src);
}

void CBibItem::SetSource(CString str)
{
	Clear();
	m_Key.Empty();
	m_Type.Empty();
	m_Value.Empty();
	CBibReader *reader = new CBibReader(str);
	LoadFromFile(reader);
	delete reader;
}

CString CBibItem::GetPrettyString()
{
	CBibDef *def = GetBibDef();
	int i = 1;
	xString* str = xsNew();

	CString format;
	CString tmp;
	CString val;
	CString strField = def->GetOrder(GetType(), i);
	while (!strField.IsEmpty()) {
		CField *fi = Find(strField);
		if (fi && !fi->GetValue().IsEmpty()) {
			if (strField.CompareNoCase(STR_AUTHOR) != 0 && strField.CompareNoCase(STR_EDITOR) != 0)
				val = RemoveGarbage(fi->GetExpandedValue(m_Owner));
			else
				val = FormatAuthors(RemoveGarbage(fi->GetExpandedValue(m_Owner)));
			format = def->GetFormat(GetType(), fi->GetName());
			tmp.Format(format, val);
			xsCatS(str, tmp);
		}
		i++;
		strField = def->GetOrder(GetType(), i);
	}
	xsTrim(str);
	xsTerminate(str);
	CString res(xsValue(str));
	xsDelete(str);
	// non-breaking hyphen, doesn't exist elsewhere
	res.Replace(_T("\"~"), _T("-"));
	return res;
}

void CBibItem::DoQuickSearch(CString str, CString fields, BOOL regexpr)
{
	if (!str.IsEmpty()) {
		m_Matched = !MatchesFields(str, fields, regexpr, FALSE, FALSE, FALSE).IsEmpty();
	} else
		// Searchstring is empty means reset quicksearch, i.e. all are visible
		m_Matched = TRUE;
}

/**
 * Do everything needed so that this item is visible when
 * filtered with filter
 */
void CBibItem::ApplyFilter(CField *filter)
{
	CString fi = filter->GetFilterField();
	CString val = filter->GetFilterCond();
	if (fi.CompareNoCase(STR_KEY) == 0)
		SetKey(val);
	else if (fi.CompareNoCase(STR_TYPE) == 0)
		SetType(val);
	else if (fi.CompareNoCase(STR_VALUE) == 0)
		SetValue(val);
	else {
		CField *ff = Find(fi);
		if (!ff)
			// Add new field
			Add(fi, val);
		else {
			CString cval = ff->GetValue();
			if (cval.IsEmpty())
				// Is the only value
				ff->SetValue(val);
			else
				// Has already a value -> append it
				ff->SetValue(cval + _T(", ") + val);
		}
	}
}

/**
 * Match against filter, sets m_Filtered
 */
void CBibItem::DoFilter(CField *filter)
{
	if (filter) {
		CString fi = filter->GetFilterField();
		CString cond = filter->GetFilterCond();
		m_Filtered = !Matches(cond, fi, FALSE, TRUE, FALSE, FALSE);
	} else
		// Reset;
		m_Filtered = FALSE;
}

BOOL CBibItem::SearchTest(CString str, CString substr, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact)
{
	BOOL res = FALSE;
	if (!casesens) {
		str.MakeLower();
		substr.MakeLower();
	}
	if (!regexp) {
		if (exact) {
			return str.Compare(substr) == 0;
		}
		int pos = -1;
		CString mat;
		CString wsp(WHITESPACE);
		BOOL wsb;
		BOOL wse;
		_TUCHAR c;
		do {
			pos = str.Find(substr, pos+1);
			if (pos != -1 && wholewords) {
				if (pos == 0)
					wsb = TRUE;
				else {
					c = str.GetAt(pos-1);
					wsb = (wsp.Find(c, 0) != -1);
				}
				if (pos + substr.GetLength() == str.GetLength())
					wse = TRUE;
				else {
					c = str.GetAt(pos + substr.GetLength());
					wse = (wsp.Find(c, 0) != -1);
				}
				res = wsb & wse;
			} else {
				res = pos != -1;
				break;
			}
		} while (pos != -1 && !res);
	} else {
		CRegExp regexp(substr);
		if (regexp.m_Error == 0) {
			return regexp.Exec(str);
#ifdef _DEBUG
		} else {
			CString err = regexp.GetErrorString();
			TRACE1("CBibItem::SearchTest(): Regular expression error %s\n", err);
#endif
		}
	}
	return res;
}

BOOL CBibItem::Matches(CString teststr, CString field, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact)
{
	CString str = GetFieldValue(field);
	if (!str.IsEmpty() && !teststr.IsEmpty())
		return SearchTest(str, teststr, regexp, wholewords, casesens, exact);
	else
		return FALSE;
}

/**
 * Returns the first fields that matches
 */
CString CBibItem::MatchesFields(CString str, CString fields, BOOL regexp, BOOL wholewords, BOOL casesens, BOOL exact)
{
	if (!str.IsEmpty()) {
		BOOL searchall = fields.IsEmpty();
		if (!searchall) {
			// Extract fields: field1;field2;
			CString field;
			CStringList lf;
			SplitSepString(fields, &lf);
			POSITION p = lf.GetHeadPosition();
			while (p) {
				field = lf.GetNext(p);
				if (Matches(str, field, regexp, wholewords, casesens, exact))
					return field;
			}
		} else {
			// Search all fields
			// First try key
			if (Matches(str, STR_KEY, regexp, wholewords, casesens, exact))
				return STR_KEY;

			POSITION pos = GetHeadPosition();
			while (pos) {
				CField *pField = (CField*)GetNext(pos);
				if (Matches(str, pField->GetName(), regexp, wholewords, casesens, exact))
					return pField->GetName();
			}
			return _T("");
		}
		return _T("");
	} else
		return _T("");
}

CString CBibItem::GetFieldValue(CString field)
{
	if (field.CompareNoCase(STR_KEY) == 0)
		return m_Key;
	else if (field.CompareNoCase(STR_TYPE) == 0)
		return m_Type;
	else if (field.CompareNoCase(STR_VALUE) == 0)
		return m_Value;
	else {
		CField *f = Find(field);
		if (f)
			return f->GetValue();
		else
			return _T("");
	}
	return _T("");
}

/**
 * Returns the count of missing fields.
 */
DWORD CBibItem::GetMissingFields(CStringList* list /* = NULL */)
{
	if (list)
		list->RemoveAll();
	CBibDef* def = GetBibDef();
	CStringList lst;
	def->GetRequiredFields(m_Type, &lst);
	POSITION p = lst.GetHeadPosition();
	DWORD c = 0;
	CFieldList *refed = GetCorssRefed();
	while (p) {
		CString f = lst.GetNext(p);
		CField* fi = Find(f);
		if (refed && (fi == NULL || fi->GetValue().IsEmpty()))
			fi = refed->Find(f);
		if (!fi || fi->GetValue().IsEmpty()) {
			c++;
			if (list)
				list->AddTail(f);
		}
	}
	return c;
}

BOOL CBibItem::IsRegularItem()
{
	return !(IsType(STR_STRING) || IsType(STR_PREAMBLE) || IsType(STR_COMMENT) || IsType(STR_OPTIONS));
}
