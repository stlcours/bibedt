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

  $Id: BibList.cpp,v 1.44 2006/08/12 16:06:16 stievie Exp $
*/

// BibList.cpp: Implementierung der Klasse CBibList.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "BibList.h"
#include "BibItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibList::CBibList()
{
}

CBibList::~CBibList()
{
	Clear();
}

/**
 * \brief Find an item of type.
 *
 * \param type The type name.
 *
 * \return The first found item if any otherwise NULL.
 */
CBibItem* CBibList::FindType(CString type)
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		if (bi->IsType(type))
			return bi;
	}
	return NULL;
}

int CBibList::KeySortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CBibList *lst = (CBibList*)lParamSort;
	POSITION p = lst->FindIndex(lParam1);
	if (!p)
		return 0;
	CBibItem *bi1 = (CBibItem*)lst->GetAt(p);
	p = lst->FindIndex(lParam2);
	if (!p)
		return 0;
	CBibItem *bi2 = (CBibItem*)lst->GetAt(p);

	// Handle @string{}, @comment{}, @preamble{} differently
	// - Filter should be on top of the file
	// - Preamble should be AFTER strings, so string macros can be used
	// - Strings should be on top of the file
	// - Comments should be where they actually are
	// Only real Bib items should be sorted by their Key

	// Put filter on top of the file
	if (bi1->IsType(STR_COMMENT) && bi1->GetKey().CompareNoCase(STR_FILTER) == 0)
		return -1;
	else if (bi2->IsType(STR_COMMENT) && bi2->GetKey().CompareNoCase(STR_FILTER) == 0)
		return 1;
	// Comments should be where they are
	if (bi1->IsType(STR_COMMENT) || bi2->IsType(STR_COMMENT))
		return 0;
	// Strings should be before preambles
	if (bi1->IsType(STR_PREAMBLE) && bi2->IsType(STR_STRING))
		return 1;
	if (bi1->IsType(STR_STRING) && bi2->IsType(STR_PREAMBLE))
		return -1;
	// Preambles are before real bibitems
	if (bi1->IsType(STR_PREAMBLE) && !bi2->IsType(STR_PREAMBLE))
		return -1;
	if (!bi1->IsType(STR_PREAMBLE) && bi2->IsType(STR_PREAMBLE))
		return 1;
	if (bi1->IsType(STR_PREAMBLE) && bi2->IsType(STR_PREAMBLE))
		return 0;
	// Strings are before real bibitems
	if (bi1->IsType(STR_STRING) && !bi2->IsType(STR_STRING))
		return -1;
	if (!bi1->IsType(STR_STRING) && bi2->IsType(STR_STRING))
		return 1;

	// Ensure that cross-referenced items appear after cross-referencing items	
	CField* crossref = bi1->Find(STR_CROSSREF);
	CBibItem* refed;
	CString crv;
	if (crossref) {
		crv = crossref->GetValue();
		if (!crv.IsEmpty()) {
			refed = lst->Find(crv);
			if (refed)
				refed->m_CrossRefed = TRUE;
		}
	}
	crossref = bi2->Find(STR_CROSSREF);
	if (crossref) {
		crv = crossref->GetValue();
		if (!crv.IsEmpty()) {
			refed = lst->Find(crv);
			if (refed)
				refed->m_CrossRefed = TRUE;
		}
	}
	if (bi1->m_CrossRefed && !bi2->m_CrossRefed)
		return 1;
	else if (bi2->m_CrossRefed && !bi1->m_CrossRefed)
		return -1;
	
	// Reached that, both must be real bibitems -> compare the key
	if (((CBibedtApp*)AfxGetApp())->m_Options->m_SortCaseSensitive)
		return bi1->GetKey().Compare(bi2->GetKey());
	else
		return bi1->GetKey().CompareNoCase(bi2->GetKey());
}

/**
 * Sort the list by key
 */
void CBibList::Sort()
{
	// Sort the file by Key
	QuickSort(0, GetCount()-1, KeySortProc);
}

/**
 * Sort the list with a given sort proc
 */
void CBibList::Sort(PFNLVCOMPARE pfnCompare)
{
	// Sort the file with a specific sort proc
	QuickSort(0, GetCount()-1, pfnCompare);
}

/**
 * \brief Return the modified flag.
 *
 * \return TRUE when the list has been modified otherwise FALSE.
 */
BOOL CBibList::GetModified()
{
	if (CBibEdtList::GetModified())
		return TRUE;
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		if (bi->GetModified())
			return TRUE;
	}
	return FALSE;
}

/**
 * \brief Set modified flag.
 *
 * \param value Indicating the flag state.
 */
void CBibList::SetModified(BOOL value)
{
	CBibEdtList::SetModified(value);
	if (!value) {
		POSITION h = GetHeadPosition();
		while (h) {
			CBibItem* bi = (CBibItem*)GetNext(h);
			bi->SetModified(FALSE);
		}
	}
}

/**
 * \brief Assign another list.
 *
 * Clears all items and adds the items of the list.
 *
 * \param src The source list with the items.
 */
void CBibList::Assign(CBibList *src)
{
	Clear();
	Append(src);
}

/**
 * \brief Appends the items of an exisiting list.
 *
 * \param lst Points to a CBibList with the items to append.
 */
void CBibList::Append(CBibList *lst)
{
	POSITION h = lst->GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)lst->GetNext(h);
		New()->Assign(bi);
	}
}

/**
 * \brief Creates a new CBibItem and appends it.
 *
 * \return The newly created item.
 */
CBibItem * CBibList::New(CBibList *owner /* = NULL */)
{
	CBibItem *res;
	if (owner == NULL)
		res = new CBibItem(this);
	else
		res = new CBibItem(owner);
	AddTail((CObject*)res);
	return res;
}

/**
 * \brief Parse a string and append it.
 *
 * \param file A pointer to a CBibReader object containing the source.
 */
void CBibList::Parse(CBibReader *file)
{
	CString line;
	_TUCHAR c;
	BOOL escape = FALSE;

#ifdef _DEBUG
	DWORD start = GetTickCount();
#endif

	while (file->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
		case _T('\\'):
			escape = !escape;
			break;
		case _T('@'):
			if (!escape) {
				// CBibItem needs the @
				file->Seek(-1, CFile::current);
				New()->LoadFromFile(file);
				break;
			}
		case _T('%'):
			if (!escape) {
				// Skip comment to the end of line
				while (file->Read(&c, 1) && c != 10 && c != 13);
				break;
			}
		case _T(' '):
		case _T('\f'):
		case _T('\r'):
		case _T('\n'):
		case _T('\t'):
			break;
		}
	}

#ifdef _DEBUG
	TRACE1("CBibList::Parse(): Took %d ms\n", GetTickCount() - start);
#endif
}

/**
 * \brief Returns the source.
 *
 * \return The source as CString.
 */
CString CBibList::GetSource()
{
	xString* src = xsNew();
	GetSource(src);
	CString res = CString(xsValue(src));
	xsDelete(src);
	return res;
}

void CBibList::GetSource(xString *src)
{
#ifdef _DEBUG
	DWORD start = GetTickCount();
#endif

	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		bi->GetSource(src);
		xsCatS(src, NL);
	}
	xsTrimRight(src);
	xsTerminate(src);

#ifdef _DEBUG
	TRACE1("CBibList::GetSource(): Took %d ms\n", GetTickCount() - start);
#endif
}

/**
 * \brief Set source string.
 *
 * \param src The string.
 */
void CBibList::SetSource(CString src)
{
	Clear();
	CBibReader *reader = new CBibReader(src);
	Parse(reader);
	delete reader;
}

/**
 * \brief Finds a BibItem by key.
 *
 * \param key The key to find.
 *
 * \return The found item or NULL if not found.
 */
CBibItem * CBibList::Find(CString key)
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (bi->GetKey().CompareNoCase(key) == 0)
			return bi;
	}
	return NULL;
}

/**
 * Return the fist visible item
 */
CBibItem * CBibList::GetFirst()	const
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (bi->IsVisible() && bi->IsRegularItem())
			return bi;
	}
	return NULL;
}

/**
 * Return the count of visible items
 */
int CBibList::GetItemCount() const
{
	int res = 0;
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (bi->IsRegularItem())
			res++;
	}
	return res;
}

/**
 * Return the last visible item
 */
CBibItem * CBibList::GetLast() const
{
	POSITION h = GetTailPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetPrev(h);
		ASSERT(bi);
		if (bi->IsVisible() && bi->IsRegularItem())
			return bi;
	}
	return NULL;
}

/**
 * Return the filter item if any, otherwise NULL
 */
CBibItem * CBibList::GetFilter()
{
	return Find(STR_FILTER);
}

/**
 * Add a filter item
 */
CField * CBibList::AddFilter(CString name, CString cond)
{
	CBibItem *filter = GetFilter();
	if (!filter)
		filter = New();
	CField *flt = filter->New();
	flt->SetName(name);
	flt->SetValue(cond);
	return flt;
}

/**
 * Return previous visible item
 */
CBibItem * CBibList::GetPrevItem(CBibItem *item) const
{
	POSITION p = CObList::Find((CObject*)item);
	GetPrev(p);
	while (p) {
		CBibItem *bi = (CBibItem*)GetPrev(p);
		if (bi->IsVisible() && bi->IsRegularItem())
			return bi;
	}
	return NULL;
}

/**
 * Return next visible item
 */
CBibItem * CBibList::GetNextItem(CBibItem *item) const
{
	POSITION p = CObList::Find((CObject*)item);
	GetNext(p);
	while (p) {
		CBibItem *bi = (CBibItem*)GetNext(p);
		if (bi->IsVisible() && bi->IsRegularItem())
			return bi;
	}
	return NULL;
}

/**
 * Filter the list with filter
 */
void CBibList::DoFilter(CField *filter)
{
	POSITION p = GetHeadPosition();
	while (p) {
		CBibItem *bi = (CBibItem*)GetNext(p);
		if (bi->IsRegularItem())
			bi->DoFilter(filter);
	}
}

/**
 * Quicksearch the file for str in fields
 */
void CBibList::DoQuickSearch(CString str, CString fields, BOOL regexpr)
{
	POSITION p = GetHeadPosition();
	while (p) {
		CBibItem *bi = (CBibItem*)GetNext(p);
		if (bi->IsRegularItem())
			bi->DoQuickSearch(str, fields, regexpr);
	}
}

/**
 * Fill lst with all field names in the list, duplicates are ignored.
 */
void CBibList::GetAllFieldNames(CStringList *lst)
{
	POSITION p = GetHeadPosition();
	while (p) {
		CBibItem *bi = (CBibItem*)GetNext(p);
		if (bi->IsRegularItem()) {
			POSITION pf = bi->GetHeadPosition();
			while (pf) {
				CField *fi = (CField*)bi->GetNext(pf);
				CString fn = fi->GetName();
				fn.MakeLower();
				if (lst->Find(fn) == NULL)
					lst->AddTail(fn);
			}
		}
	}
}

void CBibList::GetAllFieldValues(CString field, CStringList *lst)
{
	lst->RemoveAll();
	if (field.IsEmpty())
		return;

	POSITION p = GetHeadPosition();
	while (p) {
		CBibItem *bi = (CBibItem*)GetNext(p);
		if (bi->IsRegularItem()) {
			CField *fi = bi->Find(field);
			if (fi) {
				CString val = fi->GetValue();
				if (!val.IsEmpty() && lst->Find(val) == NULL)
					lst->AddTail(val);
			}
		}
	}
}

CString CBibList::GenerateKey(CBibItem *item)
{
	return GetNewKey(item, item);
}

CString CBibList::GetNewKey(CBibItem *item1, CBibItem *item2)
{
	// Generate a key like:
	//   author1[+author2][:year][x]
	CExporterList *exlst = ((CBibedtApp*)AfxGetApp())->m_Options->m_ExporterList;
	CExportPreview *exporter = (CExportPreview*)exlst->GetKeygenExporter();
	if (exporter) {
		exporter->SetItem(item1);
		CString key = exporter->GetSource();

		MakeValidKey(&key);
		CString newkey = key;
		_TUCHAR c = _T('a');
		CBibItem *pFindItem;
		// Find unique key with appending a-z
		while ((pFindItem = Find(newkey)) && pFindItem != item2 && c <= _T('z')) {
			if (c == _T('z')) {
				key += _T('a');
				c = _T('a');
			}
			newkey = key;
			newkey += c;
			c++;
		}
		return newkey;
	}
	return _T("");

/*
	// Find author
	CField *pfAuth = (CField*)item1->Find(STR_AUTHOR);
	// If there is not author use editor
	if (!pfAuth || pfAuth->GetValue().IsEmpty())
		pfAuth = (CField*)item1->Find(STR_EDITOR);
	// Is still nothing use organiztation
	if (!pfAuth || pfAuth->GetValue().IsEmpty())
		pfAuth = (CField*)item1->Find(STR_ORGANIZATION);
	if (!pfAuth)
		return _T("");
	CString author = ExtractLastNames(pfAuth->GetValue(), '+');
	if (author.IsEmpty())
		return _T("");
	// Remove dots if any.
	author.Remove('.');
	// Spaces may come from ExtractLastNames
	author.Remove(' ');
	CString year = _T("");
	CField *pfYear = (CField*)item1->Find(STR_YEAR);
	if (pfYear)
		year = pfYear->GetValue();
	CString key = author;
	if (key.IsEmpty())
		return _T("");
	key.MakeLower();
	// Append the year
	if (!year.IsEmpty())
		key += _T(":") + year;

	if (!key.IsEmpty()) {
		MakeValidKey(&key);
		CString newkey = key;
		_TUCHAR c = _T('a');
		CBibItem *pFindItem;
		// Find unique key with appending a-z
		while ((pFindItem = Find(newkey)) && pFindItem != item2 && c <= _T('z')) {
			if (c == _T('z')) {
				key += _T('a');
				c = _T('a');
			}
			newkey = key;
			newkey += c;
			c++;
		}
		return newkey;
	} else
		return _T("");
*/
}

CBibItem * CBibList::FindMacro(CString name)
{
	POSITION h = GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)GetNext(h);
		ASSERT(bi);
		if (bi->IsType(STR_STRING) && bi->GetKey().CompareNoCase(name) == 0) {
			return bi;
		}
	}
	return NULL;
}
