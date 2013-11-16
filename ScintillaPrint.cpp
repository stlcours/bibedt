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

  $Id: ScintillaPrint.cpp,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

// ScintillaPrint.cpp: Implementierung der Klasse CScintillaPrint.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ScintillaPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CScintillaPrint::CScintillaPrint()
{

}

CScintillaPrint::~CScintillaPrint()
{

}

BOOL CScintillaPrint::OnPreparePrinting(CPrintInfo* pInfo)
{
	//Determine if we should allow selection printing

	long nStartChar = m_Scintilla->GetSelectionStart();
	long nEndChar = m_Scintilla->GetSelectionEnd();
	if (nStartChar != nEndChar)
	{
		// Enable the Selection button
		pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;

		// Check the Selection button
		pInfo->m_pPD->m_pd.Flags |= PD_SELECTION;
	}
	return CPrint::OnPreparePrinting(pInfo);
}

void CScintillaPrint::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CPrint::OnBeginPrinting(pDC, pInfo);

	//initialize page start vector
	ASSERT(m_aPageStart.GetSize() == 0);
	if (pInfo->m_pPD->PrintSelection())
		m_aPageStart.Add(m_Scintilla->GetSelectionStart());
	else
		m_aPageStart.Add(0);
	ASSERT(m_aPageStart.GetSize() > 0);
	m_nPageCount = 0;
}

void CScintillaPrint::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_Scintilla->FormatRange(NULL, FALSE);
	m_aPageStart.RemoveAll();
	CPrint::OnEndPrinting(pDC, pInfo);
}

void CScintillaPrint::PrintBody(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(pInfo != NULL);
	ASSERT(pInfo->m_bContinuePrinting);

	UINT nPage = pInfo->m_nCurPage;
	ASSERT(nPage <= (UINT) m_aPageStart.GetSize());
	int nIndex = m_aPageStart[nPage-1];

	//Determine where we should end the printing
	int nEndPrint = 0;
	if (pInfo->m_pPD->PrintSelection())
		nEndPrint = m_Scintilla->GetSelectionEnd();
	else
		nEndPrint = m_Scintilla->GetTextLength();

	//print as much as possible in the current page.
	nIndex = PrintPage(pDC, pInfo, nIndex, nEndPrint);
	if (nIndex >= nEndPrint)
	{
		TRACE0("End of Document\n");
		pInfo->SetMaxPage(nPage);
	}

	//update pagination information for page just printed
	if (nPage == (UINT) m_aPageStart.GetSize())
	{
		if (nIndex < nEndPrint)
			m_aPageStart.Add(nIndex);
	}
	else
	{
		ASSERT(nPage+1 <= (UINT) m_aPageStart.GetSize());
		ASSERT(nIndex == m_aPageStart[nPage+1-1]);
	}
}

BOOL CScintillaPrint::PaginateTo(CDC *pDC, CPrintInfo *pInfo)
{
	CRect rectSave = pInfo->m_rectDraw;
	UINT nPageSave = pInfo->m_nCurPage;
	ASSERT(nPageSave > 1);
	ASSERT(nPageSave >= (UINT) m_aPageStart.GetSize());
	VERIFY(pDC->SaveDC() != 0);
	pDC->IntersectClipRect(0, 0, 0, 0);
	pInfo->m_nCurPage = m_aPageStart.GetSize();
	while (pInfo->m_nCurPage < nPageSave) {
		ASSERT(pInfo->m_nCurPage == (UINT) m_aPageStart.GetSize());
		OnPrepareDC(pDC, pInfo);
		ASSERT(pInfo->m_bContinuePrinting);
		pInfo->m_rectDraw.SetRect(0, 0,	pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
		OnPrint(pDC, pInfo);
		if (pInfo->m_nCurPage == (UINT) m_aPageStart.GetSize())
			break;
		++pInfo->m_nCurPage;
	}
	BOOL bResult = pInfo->m_nCurPage == nPageSave;
	pDC->RestoreDC(-1);
	pInfo->m_nCurPage = nPageSave;
	pInfo->m_rectDraw = rectSave;
	return bResult;
}

void CScintillaPrint::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	//Validate our parameters
	ASSERT(pInfo != NULL);

	if (pInfo->m_nCurPage <= pInfo->GetMaxPage()) {
		if ((pInfo->m_nCurPage > (UINT)m_aPageStart.GetSize()) && !PaginateTo(pDC, pInfo)) {
			//can't paginate to that page, thus cannot print it.
			pInfo->m_bContinuePrinting = FALSE;
		}
	} else {
		//Reached the max page to print
		pInfo->m_bContinuePrinting = FALSE;
	}
}

long CScintillaPrint::PrintPage(CDC *pDC, CPrintInfo *pInfo, long nIndexStart, long nIndexStop)
{
	RangeToFormat rfPrint;
	rfPrint.hdc = pDC->m_hDC;
	rfPrint.hdcTarget = pDC->m_hAttribDC;

	//Take into account the specified margins
	CRect rMargins;
	rMargins = CRect(m_marginLeftPix, m_marginTopPix, m_marginRightPix, m_marginBottomPix);

	//We take the page size from the pInfo member variable (decrement the right and
	//bottom values by 1 to suit Scintilla)
	rfPrint.rcPage.left = m_rectPaper.left;
	rfPrint.rcPage.top = m_rectPaper.top;
	rfPrint.rcPage.right = m_rectPaper.right;
	rfPrint.rcPage.bottom = m_rectPaper.bottom;

	//Fill in the area to print
	rfPrint.rc.left = m_rectBody.left;
	rfPrint.rc.top = m_rectBody.top;
	rfPrint.rc.right = m_rectBody.right;
	rfPrint.rc.bottom = m_rectBody.bottom;

	//Fill in the text to print
	rfPrint.chrg.cpMin = nIndexStart;
	rfPrint.chrg.cpMax = nIndexStop;

	//Finally ask the control to print the text
	return m_Scintilla->FormatRange(TRUE, &rfPrint);
}

