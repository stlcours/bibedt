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

  $Id: StringListEx.cpp,v 1.1 2005/08/26 19:49:49 stievie Exp $
*/

// StringListEx.cpp: Implementierung der Klasse CStringListEx.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "StringListEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CStringListEx::CStringListEx()
{

}

CStringListEx::~CStringListEx()
{

}

void CStringListEx::Sort()
{
	QuickSort(0, GetCount()-1, SortProc);
}

void CStringListEx::ExchangeItems(int i1, int i2)
{
	POSITION p1 = FindIndex(i1);
	POSITION p2 = FindIndex(i2);
	ExchangeItems(p1, p2);
}

void CStringListEx::ExchangeItems(POSITION i1, POSITION i2)
{
	if (!i1 || !i2)
		return;
	CString str1 = GetAt(i1);
	CString str2 = GetAt(i2);
	SetAt(i1, str2);
	SetAt(i2, str1);
}

void CStringListEx::QuickSort(int l, int r, PFNLVCOMPARE pfnCompare)
{
	int i; int j; int p;
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

int CStringListEx::SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CStringListEx* lst = (CStringListEx*)lParamSort;
	POSITION p = lst->FindIndex(lParam1);
	if (!p)
		return 0;
	CString str1 = lst->GetAt(p);
	p = lst->FindIndex(lParam2);
	if (!p)
		return 0;
	CString str2 = lst->GetAt(p);
	return str1.Compare(str2);
}
