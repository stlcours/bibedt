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

  $Id: ListViewPrint.h,v 1.20 2005/08/22 23:32:33 stievie Exp $
*/

// Original code found at http://www.codeproject.com/

// ListViewPrint.h : interface of the CListViewPrint class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ListViewPrint_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_)
#define AFX_ListViewPrint_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrintPages.h"
#include "Print.h"

#define CELL_SPACING  5

/**
 * \brief Class to print and print preview the list.
 *
 * This class does all the print and print previewing work.
 */
class CListViewPrint : public CPrint
{
// Construction
public:
   CListViewPrint();
   virtual ~CListViewPrint();

// Operations
public:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	BOOL m_PrintNumbers;
	int GetPageCount() const;
	CString GetRowText(int nRow);
	void SetListCtrl(CListCtrl* pList);
	int GetRowCount();

protected:
	void DrawRow(CDC* pDC, int nRow);
	virtual void PrintBody(CDC* pDC, CPrintInfo* pInfo);

private:
	CString m_NumberFormat;
	DWORD m_Counter;
	int m_CurrentY;
	BOOL GetSelected(int nRow);
	BOOL PrintRow(int nRow);
	void CalcPageBreak(CDC* pDC);
	CPrintPages* m_Pages;
	CRect GetRowRect(CDC* pDC, int nRow);
	CListCtrl* m_pListCtrl;
	int m_nRowCount;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ListViewPrint_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_)
