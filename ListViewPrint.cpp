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

  $Id: ListViewPrint.cpp,v 1.30 2006/06/06 18:52:18 stievie Exp $
*/

// Original code found at http://www.codeproject.com/

// ListViewPrint.cpp : implementation of the CListViewPrint class
//

#include "stdafx.h"
#include "bibedtDoc.h"
#include "ListViewPrint.h"
#include "bibedtView.h"
#include "Globals.h"
#include "BibItem.h"
#include "Field.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewPrint construction/destruction

CListViewPrint::CListViewPrint()
{	
	m_pListCtrl = NULL;
	m_Pages = NULL;
}

CListViewPrint::~CListViewPrint()
{
}

/////////////////////////////////////////////////////////////////////////////
// CListViewPrint printing

BOOL CListViewPrint::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CPrint::OnPreparePrinting(pInfo);
}

void CListViewPrint::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CPrint::OnBeginPrinting(pDC, pInfo);
	m_nRowCount = GetRowCount();

	CBibDef *def = GetBibDef();
	m_PrintNumbers = def->GetBoolOption(OP_PRINT_NUM, TRUE);
	m_NumberFormat = def->GetStrOption(OP_NUM_FORMAT, "[%d] ");

	// Calculate Pages
	m_Pages = new CPrintPages();
	CalcPageBreak(pDC);
	m_nPageCount = m_Pages->GetCount();

	// How many pages?
	pInfo->SetMaxPage(m_nPageCount);
}

void CListViewPrint::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	delete m_Pages;
	m_Pages = NULL;
	CPrint::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CListViewPrint helpers

/**
 * \brief Draws the row.
 *
 * \param pDC DC to draw.
 * \param nRow The index of the row.
 */
void CListViewPrint::DrawRow(CDC* pDC, int nRow)
{
	CString strText = GetRowText(nRow);
	CRect rect = GetRowRect(pDC, nRow);
#ifdef _DEBUG
	int bottom = m_rectBody.bottom;
	if (m_CurrentY > bottom)
		TRACE2("Warning: Row exceeds Body, y = %d; height = %d\n", m_CurrentY, bottom);
	DrawRect(pDC, rect, RGB(255, 0, 0));
#endif //_DEBUG
	DrawText(pDC->m_hDC, strText, -1, rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);
	m_CurrentY = rect.bottom;
}
/**
 * \brief Returns the rect of a Row
 *
 * \param pDC A Pointer to CDC object for calcualting the rect.
 * \param nRow The index of the row.
 *
 * \return A CRect with the size of the row:
 */
CRect CListViewPrint::GetRowRect(CDC* pDC, int nRow)
{
	ASSERT(nRow >= 0 && nRow < m_nRowCount);

	CSize charSize = m_CharSizeBody;
	CRect rect = m_rectBody;
	rect.top = m_CurrentY;
	rect.left += CELL_SPACING;
	rect.right -= CELL_SPACING;
	CString strRowText = GetRowText(nRow);
	pDC->DrawText(strRowText, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
	rect.bottom += m_CharSizeBody.cy / 2;
	return rect;
}

/**
 * \brief Returns the text of a row.
 *
 * \param nRow The index of the row.
 *
 * \return The row text.
 */
CString CListViewPrint::GetRowText(int nRow)
{
	ASSERT(nRow >= 0 && nRow < m_nRowCount);
	ASSERT(m_pListCtrl);
	CBibItem *pBibItem = (CBibItem*)m_pListCtrl->GetItemData(nRow);
	ASSERT(pBibItem);

	CString res = _T("");
	if (m_PrintNumbers) {
		res.Format(m_NumberFormat, m_Counter);
	}
	res += pBibItem->GetPrettyString();
	res.Replace(_T("~"), _T(" "));
	return res;
}

/**
 * \brief Return the count of items in the ListView.
 *
 * \return The count of rows in the Listview.
 */
int CListViewPrint::GetRowCount()
{
	ASSERT(m_pListCtrl);
	return m_pListCtrl->GetItemCount();
}

/////////////////////////////////////////////////////////////////////////////
// CListViewPrint printing

void CListViewPrint::PrintBody(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pFontBody && pInfo);

	CFont *pOldFont = pDC->SelectObject(m_pFontBody); 

	CPrintPage *CurPage = m_Pages->GetPage(pInfo->m_nCurPage);
	ASSERT(CurPage);
	int nStartRow = CurPage->m_StartRow;
	int nEndRow = CurPage->m_EndRow;

	m_Counter = CurPage->m_StartLine;
	// Prepare document and print rows
	m_CurrentY = m_rectBody.top;
	for (int i = nStartRow; i < nEndRow; i++) {
		if (PrintRow(i)) {
			DrawRow(pDC, i);
			m_Counter++;
		}
	}

	pDC->SelectObject(pOldFont);
}

void CListViewPrint::SetListCtrl(CListCtrl* pList)
{
	ASSERT(pList != NULL);
	m_pListCtrl = pList;
}

/**
 * \brief Returns the count of pages needed.
 */
int CListViewPrint::GetPageCount() const
{
	ASSERT(m_Pages);
	return m_Pages->GetCount();
}

/**
 * \brief Calculates Page Breaks.
 */
void CListViewPrint::CalcPageBreak(CDC* pDC)
{
	ASSERT(m_Pages);
	CFont *pOldFont = pDC->SelectObject(m_pFontBody); 
	pDC->SelectObject(m_pFontBody);

	m_Counter = 1;
	int nRowCount = GetRowCount();
	int bodyHeight = m_rectBody.Height();
	int nCurRowHeight;
	int nCurHeight = 0;
	CPrintPage *CurPage = NULL;

	for (int i = 0; i < nRowCount; i++) {
		if (PrintRow(i)) {
			if (!CurPage) {
				CurPage = m_Pages->New();
				CurPage->m_StartRow = i;
				CurPage->m_StartLine = m_Counter;
			}
			nCurRowHeight = GetRowRect(pDC, i).Height();
			nCurHeight += nCurRowHeight;
			if (nCurHeight >= bodyHeight) {
				if (nCurHeight > bodyHeight) {
					i--;
					m_Counter--;
					CurPage->m_EndRow = i;
					nCurHeight = nCurRowHeight;
				} else {
					CurPage->m_EndRow = i;
					nCurHeight = 0;
				}
				i--;
				CurPage = NULL;
			} else
				m_Counter++;
		}
	}
	CurPage->m_EndRow = i;
	pDC->SelectObject(pOldFont);
}

/**
 * \brief Returns TRUE when the row should be printed otherwise FALSE.
 */
BOOL CListViewPrint::PrintRow(int nRow)
{
	return !m_PrintSelOnly || GetSelected(nRow);
}

/**
 * \brief Returns TRUE when the row is selected otherwise FALSE.
 *
 * This is needed in case only selection should be printed.
 */
BOOL CListViewPrint::GetSelected(int nRow)
{
	ASSERT(m_pListCtrl);
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = nRow;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (m_pListCtrl->GetItem(&item)) {
		return BIT_SET(item.state, LVIS_SELECTED);
	} else
		return FALSE;
}
