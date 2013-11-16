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

  $Id: StringListEx.h,v 1.1 2005/08/26 19:49:49 stievie Exp $
*/

// StringListEx.h: Schnittstelle für die Klasse CStringListEx.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGLISTEX_H__FAF78BF1_9417_443A_B6E8_4997A7DFC085__INCLUDED_)
#define AFX_STRINGLISTEX_H__FAF78BF1_9417_443A_B6E8_4997A7DFC085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringListEx : public CStringList  
{
public:
	void ExchangeItems(int i1, int i2);
	void ExchangeItems(POSITION i1, POSITION i2);
	void Sort();
	CStringListEx();
	virtual ~CStringListEx();

protected:
	void QuickSort(int l, int r, PFNLVCOMPARE pfnCompare);
private:
	static int CALLBACK SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

#endif // !defined(AFX_STRINGLISTEX_H__FAF78BF1_9417_443A_B6E8_4997A7DFC085__INCLUDED_)
