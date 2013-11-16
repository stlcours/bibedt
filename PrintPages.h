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

  $Id: PrintPages.h,v 1.10 2006/04/23 21:49:36 stievie Exp $
*/

// PrintPages.h: Schnittstelle für die Klasse CPrintPages.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTPAGES_H__8C743A8D_87A9_4957_ABEA_8F0FA6F175BC__INCLUDED_)
#define AFX_PRINTPAGES_H__8C743A8D_87A9_4957_ABEA_8F0FA6F175BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * \brief This class represents a page to be printed.
 */
class CPrintPage
{
public:
	CPrintPage();
	~CPrintPage();

public:
	int m_StartRow;
	int m_EndRow;
	int m_StartLine;
	int GetRowsOnPage() const { return m_EndRow - m_StartRow; }
};

/**
 * \brief This class is a list to hold all pages to be printed.
 */
class CPrintPages : public CObList  
{
public:
	void Clear();
	CPrintPage * GetPage(int nPage) const;
	CPrintPage * New();
	CPrintPages();
	virtual ~CPrintPages();

};

#endif // !defined(AFX_PRINTPAGES_H__8C743A8D_87A9_4957_ABEA_8F0FA6F175BC__INCLUDED_)
