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

  $Id: BibList.h,v 1.22 2006/08/11 11:56:01 stievie Exp $
*/

// BibList.h: Schnittstelle für die Klasse CBibList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBLIST_H__2E1F0C4F_A9E7_420F_8057_9C6F9E1F56EA__INCLUDED_)
#define AFX_BIBLIST_H__2E1F0C4F_A9E7_420F_8057_9C6F9E1F56EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibItem.h"	// Hinzugefügt von der Klassenansicht
#include "BibEdtList.h"

class CBibList : public CBibEdtList 
{
public:
	CBibItem * FindMacro(CString name);
	CString GetNewKey(CBibItem* item1, CBibItem* item2);
	CString GenerateKey(CBibItem *item);
	void GetAllFieldValues(CString field, CStringList* lst);
	void GetSource(xString* src);
	void GetAllFieldNames(CStringList* lst);
	void DoQuickSearch(CString str, CString fields, BOOL regexpr);
	void DoFilter(CField* filter);
	CBibItem * GetNextItem(CBibItem *item) const;
	CBibItem * GetPrevItem(CBibItem *item) const;
	CField * AddFilter(CString name, CString cond);
	CBibItem * GetFilter();
	CBibItem * GetLast() const;
	int GetItemCount() const;
	CBibItem * GetFirst() const;
	CBibItem * Find(CString key);
	void SetSource(CString src);
	CString GetSource();
	void Parse(CBibReader *file);
	CBibItem * New(CBibList *owner = NULL);
	void Append(CBibList *lst);
	static int CALLBACK KeySortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void Assign(CBibList* src);
	void Sort();
	void Sort(PFNLVCOMPARE pfnCompare);
	CBibItem* FindType(CString type);
	CBibList();
	virtual ~CBibList();
	virtual void SetModified(BOOL value);
	virtual BOOL GetModified();
};

#endif // !defined(AFX_BIBLIST_H__2E1F0C4F_A9E7_420F_8057_9C6F9E1F56EA__INCLUDED_)
