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

  $Id: PrintPages.cpp,v 1.7 2005/08/22 23:32:33 stievie Exp $
*/

// PrintPages.cpp: Implementierung der Klasse CPrintPages.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "PrintPages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CPrintPages::CPrintPages()
{

}

CPrintPages::~CPrintPages()
{
	Clear();
}

/**
 * Creates a new CPrintPage object and return ist.
 */
CPrintPage * CPrintPages::New()
{
	CPrintPage *curPage = new CPrintPage;
	AddTail((CObject*)curPage);
	return curPage;
}

/**
 * Return a CPrintPage from its page number
 */
CPrintPage * CPrintPages::GetPage(int nPage) const
{
	POSITION p = FindIndex(nPage-1);
	if (!p)
		return NULL;
	CPrintPage *resPage = (CPrintPage*)GetAt(p);
	return resPage;
}

/**
 * Deletes all pages and clears the list.
 */
void CPrintPages::Clear()
{
	POSITION p = GetTailPosition();
	while (p) {
		CPrintPage *page = (CPrintPage*)GetPrev(p);
		delete page;
	}
	RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CPrintPage

CPrintPage::CPrintPage()
{
	m_StartRow = 0;
	m_EndRow = 0;
}

CPrintPage::~CPrintPage()
{
}
