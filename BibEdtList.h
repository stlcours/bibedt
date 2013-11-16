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

  $Id: BibEdtList.h,v 1.7 2006/05/22 18:49:31 stievie Exp $
*/

// BibEdtList.h: Schnittstelle für die Klasse CBibEdtList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBEDTLIST_H__7E19C108_F78B_464B_9193_F25ACD611323__INCLUDED_)
#define AFX_BIBEDTLIST_H__7E19C108_F78B_464B_9193_F25ACD611323__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * A list class that has a modified flag.
 */
class CBibEdtList : public CObList
{
public:
	void Clear();
	void Move(POSITION curpos, POSITION newpos);
	void ExchangeItems(int i1, int i2);
	void ExchangeItems(POSITION i1, POSITION i2);
	void Move(int curindex, int newindex);
	void Delete(CObject* item);
	CObject* RemoveHead();
	CObject* RemoveTail();

	// add before head or after tail
	POSITION AddHead(CObject* newElement);
	POSITION AddTail(CObject* newElement);


	// add another list of elements before head or after tail
	void AddHead(CObList* pNewList);
	void AddTail(CObList* pNewList);

	// remove all elements
	void RemoveAll();

	void SetAt(POSITION pos, CObject* newElement);

	void RemoveAt(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, CObject* newElement);
	POSITION InsertAfter(POSITION position, CObject* newElement);

	virtual void SetModified(BOOL value) { m_Modified = value; }
	virtual BOOL GetModified() { return m_Modified;	}
	CBibEdtList();
	virtual ~CBibEdtList();

protected:
	BOOL m_Modified;
	void QuickSort(int l, int u, PFNLVCOMPARE pfnCompare);
};

#endif // !defined(AFX_BIBEDTLIST_H__7E19C108_F78B_464B_9193_F25ACD611323__INCLUDED_)
