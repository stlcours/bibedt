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

  $Id: BibEdtList.cpp,v 1.10 2006/07/29 11:33:14 stievie Exp $
*/

// BibEdtList.cpp: Implementierung der Klasse CBibEdtList.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "BibEdtList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibEdtList::CBibEdtList()
{
	m_Modified = FALSE;
}

CBibEdtList::~CBibEdtList()
{ }

CObject* CBibEdtList::RemoveHead()
{
	m_Modified = TRUE;
	return CObList::RemoveHead();
}

CObject* CBibEdtList::RemoveTail()
{
	m_Modified = TRUE;
	return CObList::RemoveTail();
}

POSITION CBibEdtList::AddHead(CObject *newElement)
{
	m_Modified = TRUE;
	return CObList::AddHead(newElement);
}

POSITION CBibEdtList::AddTail(CObject* newElement)
{
	m_Modified = TRUE;
	return CObList::AddTail(newElement);
}

void CBibEdtList::AddHead(CObList* pNewList)
{
	m_Modified = TRUE;
	CObList::AddHead(pNewList);
}

void CBibEdtList::AddTail(CObList* pNewList)
{
	m_Modified = TRUE;
	CObList::AddTail(pNewList);
}

void CBibEdtList::RemoveAll()
{
	m_Modified = TRUE;
	CObList::RemoveAll();
}

void CBibEdtList::SetAt(POSITION pos, CObject* newElement)
{
	m_Modified = TRUE;
	CObList::SetAt(pos, newElement);
}

void CBibEdtList::RemoveAt(POSITION position)
{
	m_Modified = TRUE;
	CObList::RemoveAt(position);
}

POSITION CBibEdtList::InsertBefore(POSITION position, CObject* newElement)
{
	m_Modified = TRUE;
	return CObList::InsertBefore(position, newElement);
}

POSITION CBibEdtList::InsertAfter(POSITION position, CObject* newElement)
{
	m_Modified = TRUE;
	return CObList::InsertAfter(position, newElement);
}

/**
 * Remove item from the list and delete it
 */
void CBibEdtList::Delete(CObject *item)
{
	POSITION p = Find(item, NULL);
	if (p) {
		RemoveAt(p);
		delete item;
	}
}

/**
 * Move an item from curpos to newpos
 */
void CBibEdtList::Move(POSITION curpos, POSITION newpos)
{
	if (curpos == NULL || newpos == NULL)
		return;

	CObject *o = GetAt(curpos);
	if (newpos == GetTailPosition()) {
		RemoveAt(curpos);
		InsertAfter(newpos, o);
	} else {
		InsertBefore(newpos, o);
		RemoveAt(curpos);
	}
	m_Modified = TRUE;
}

/**
 * Move an item from curindex to newindex
 */
void CBibEdtList::Move(int curindex, int newindex)
{
	if (curindex == newindex || newindex < 0 || newindex >= GetCount())
		return;

	POSITION cp = FindIndex(curindex);
	POSITION np;
	if (newindex == GetCount()-1)
		np = GetTailPosition();
	else {
		if (newindex > curindex)
			newindex++;
		np = FindIndex(newindex);
	}
	if (!cp || !np)
		return;
	Move(cp, np);
}

void CBibEdtList::ExchangeItems(int i1, int i2)
{
	POSITION p1 = FindIndex(i1);
	POSITION p2 = FindIndex(i2);
	ExchangeItems(p1, p2);
}

void CBibEdtList::ExchangeItems(POSITION i1, POSITION i2)
{
	if (!i1 || !i2)
		return;
	CObject *bi1 = GetAt(i1);
	CObject *bi2 = GetAt(i2);
	SetAt(i1, bi2);
	SetAt(i2, bi1);
}

void CBibEdtList::QuickSort(int l, int r, PFNLVCOMPARE pfnCompare)
{
	int i, j, p;
	do {
		i = l;
		j = r;
		p = (l + r) >> 1;
		do {
			while (pfnCompare(i, p, (LPARAM)this) < 0)
				i++;
			while (pfnCompare(j, p, (LPARAM)this) > 0)
				j--;

			if (i <= j) {
				ExchangeItems(i, j);
				if (p == i)
					p = j;
				else if (p == j)
					p = i;
				i++;
				j--;
			}
		} while (i <= j);
		if (l < j)
			QuickSort(l, j, pfnCompare);
		l = i;
	} while (i < r);
}

void CBibEdtList::Clear()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CObject* o = GetNext(p);
		ASSERT_VALID(o);
		delete o;
	}
	RemoveAll();
}
