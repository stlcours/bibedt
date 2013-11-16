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

  $Id: Print.cpp,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

// Print.cpp: Implementierung der Klasse CPrint.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Print.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CPrint::CPrint()
{
	// In case of no printers installed this information is used
	m_PixPerInchX = 300;
	m_PixPerInchY = 300;
}

CPrint::~CPrint()
{

}

CRect CPrint::GetPaperRect(CDC* pDC)
{
	ASSERT(pDC != NULL);
	CSize paperSize = CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
	return CRect(0, 0, paperSize.cx, paperSize.cy);
}

CRect CPrint::GetPageRect()
{
	ASSERT(m_rectPaper != CRect(0, 0, 0, 0));
	CRect rect = m_rectPaper;
	rect.DeflateRect(m_marginLeftPix, m_marginTopPix, m_marginRightPix, m_marginBottomPix);
	return rect;
}

CRect CPrint::GetHeaderRect()
{
	ASSERT(m_rectPage != CRect(0, 0, 0, 0));
	CRect rect = m_rectPage;
	CSize charSize = m_CharSizeHeader;
	rect.DeflateRect(0, 0, 0, rect.Height() - m_headerLines * m_CharSizeHeader.cy);
	return rect;
}

CRect CPrint::GetFooterRect()
{
	ASSERT(m_rectPage != CRect(0, 0, 0, 0));
	CRect rect = m_rectPage;
	rect.DeflateRect(0, rect.Height() - m_footerLines * m_CharSizeFooter.cy, 0, 0);
	return rect;
}

CSize CPrint::GetCharSize(CDC* pDC, CFont* pFont)
{
	ASSERT(pDC != NULL && pFont != NULL);
	CFont *pOldFont = pDC->SelectObject(pFont);
	CSize charSize = pDC->GetTextExtent(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ^_0()"), 55);
	charSize.cx /= 55;
	pDC->SelectObject(pOldFont);
	return charSize;
}

double CPrint::GetTextRatioX(CDC* pDC)
{
	ASSERT(pDC != NULL);
	ASSERT(m_View);
	CDC* pCurrentDC = m_View->GetDC();
	TEXTMETRIC tmSrc;
	pCurrentDC->GetTextMetrics(&tmSrc);
	m_View->ReleaseDC(pCurrentDC);
	return ((double)m_CharSizeBody.cx) / ((double)tmSrc.tmAveCharWidth);
}

CFont* CPrint::CreateFont(CDC* pDC, CString strName, int nPoints, int lfWeight, bool lfItalic)
{
	ASSERT(pDC && m_View);   
	CDC* pCurrentDC = m_View->GetDC();
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	TEXTMETRIC tm;
	
	pCurrentDC->GetTextMetrics(&tm);
	CFont* pFont = new CFont();
	CSize PaperPixelsPerInch(
		pDC->GetDeviceCaps(LOGPIXELSX), 
		pDC->GetDeviceCaps(LOGPIXELSY));
	CSize ScreenPixelsPerInch(
		pCurrentDC->GetDeviceCaps(LOGPIXELSX), 
		pCurrentDC->GetDeviceCaps(LOGPIXELSY));
	if (nPoints == 0)
		nPoints = MulDiv((tm.tmHeight - tm.tmInternalLeading), 72, ScreenPixelsPerInch.cy);
	lf.lfWeight = lfWeight;
	lf.lfItalic = lfItalic;
	lf.lfHeight = -MulDiv(nPoints, PaperPixelsPerInch.cy, 72);  
	if (!strName.IsEmpty())
		_tcscpy(lf.lfFaceName, strName);  
	m_View->ReleaseDC(pCurrentDC);
	BOOL bResult = pFont->CreateFontIndirect(&lf);
	ASSERT(bResult == TRUE);
	return pFont;
}

BOOL CPrint::OnPreparePrinting(CPrintInfo* pInfo)
{
	UNUSED_ALWAYS(pInfo);
	m_RatioX = 0; 
	m_rectPaper  = CRect(0,0,0,0);
	m_rectPage   = CRect(0,0,0,0);
	m_rectHeader = CRect(0,0,0,0);
	m_rectFooter = CRect(0,0,0,0);
	m_rectBody   = CRect(0,0,0,0);
	m_pFontHeader = NULL;
	m_pFontFooter = NULL;
	m_pFontBody   = NULL;
	m_CharSizeHeader = CSize(0,0);
	m_CharSizeFooter = CSize(0,0);
	m_CharSizeBody   = CSize(0,0);
	m_MarginUnit = U_PIXEL;
	m_MarginLeft   = MARGIN_LEFT;
	m_MarginTop    = MARGIN_TOP;
	m_MarginRight  = MARGIN_RIGHT;
	m_MarginBottom = MARGIN_BOTTOM;
	m_headerHeight = 0;
	m_footerHeight = 0;
	m_headerLines = HEADER_LINES;
	m_footerLines = FOOTER_LINES;
	m_nPageCount = 0;
	return TRUE;
}

void CPrint::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{   
	// Create fonts
	ASSERT(pDC != NULL && pInfo != NULL);

	m_pFontHeader = CreateFont(pDC,_T("Arial"), 12, FW_BOLD);
	m_pFontFooter = CreateFont(pDC,_T("Arial"), 10);
	m_pFontBody   = CreateFont(pDC,_T("Times New Roman"), 10);

	// Calculate Margins
	m_PixPerInchX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_PixPerInchY = pDC->GetDeviceCaps(LOGPIXELSY);
	m_PixPerMMX	= m_PixPerInchX / 25.4;
	m_PixPerMMY	= m_PixPerInchY / 25.4;
	switch (m_MarginUnit) {
	case U_PIXEL:
		m_marginLeftPix = (int)m_MarginLeft;
		m_marginTopPix = (int)m_MarginTop;
		m_marginRightPix = (int)m_MarginRight;
		m_marginBottomPix = (int)m_MarginBottom;
		break;
	case U_INCH:
		m_marginLeftPix = InchToPixX(m_MarginLeft);
		m_marginTopPix = InchToPixY(m_MarginTop);
		m_marginRightPix = InchToPixX(m_MarginRight);
		m_marginBottomPix = InchToPixY(m_MarginBottom);
		break;
	case U_MM:
		m_marginLeftPix = MMToPixX(m_MarginLeft);
		m_marginTopPix = MMToPixY(m_MarginTop);
		m_marginRightPix = MMToPixX(m_MarginRight);
		m_marginBottomPix = MMToPixY(m_MarginBottom);
		break;
	}

	// Calculate character size
	m_CharSizeHeader = GetCharSize(pDC, m_pFontHeader);
	m_CharSizeFooter = GetCharSize(pDC, m_pFontFooter);
	m_CharSizeBody   = GetCharSize(pDC, m_pFontBody);

	// Prepare layout 
	m_rectPaper  = GetPaperRect(pDC);
	m_rectPage   = GetPageRect();
	m_rectHeader = GetHeaderRect();
	m_rectFooter = GetFooterRect();
	m_rectBody = GetBodyRect();

	m_PrintSelOnly = pInfo->m_pPD->PrintSelection();
}

void CPrint::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
#ifdef _DEBUG
	DrawRect(pDC, m_rectPaper, RGB(0,0,0));
	DrawRect(pDC, m_rectPage, RGB(0,0,255));
#endif
	PrintHeader(pDC, pInfo);
	PrintBody(pDC, pInfo);
	PrintFooter(pDC, pInfo);
}

void CPrint::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	delete m_pFontHeader;
	delete m_pFontFooter;
	delete m_pFontBody;
}

/**
 * \brief Returns the rect of the body.
 */
CRect CPrint::GetBodyRect()
{
	ASSERT(m_rectPage != CRect(0,0,0,0));
	ASSERT(m_rectHeader != CRect(0,0,0,0));
	ASSERT(m_rectFooter != CRect(0,0,0,0));
	CRect rectPage = m_rectPage;
	CRect rectHead = m_rectHeader;
	CRect rectFoot = m_rectFooter;
	rectPage.DeflateRect(0, rectHead.Height(), 0, rectFoot.Height());
	return rectPage;
}

#ifdef _DEBUG
void CPrint::DrawRect(CDC* pDC, CRect rect, COLORREF color)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldPen);
}
#endif //_DEBUG

void CPrint::PrintHeader(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pFontHeader && pInfo);
	UNUSED_ALWAYS(pInfo);
	CFont *pOldFont = pDC->SelectObject(m_pFontHeader);

#ifdef _DEBUG
	DrawRect(pDC, m_rectHeader, RGB(0, 255, 0));
#endif

	// Create black brush
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// Draw line
	CRect rectLine = m_rectHeader;
	rectLine.top += m_CharSizeHeader.cy * 3 / 2;
	rectLine.bottom = rectLine.top + HEADER_LINE_SIZE;
	pDC->FillRect(&rectLine, &brush);
	pDC->SelectObject(pOldBrush);

	// Draw "Document"
	CRect rectHeader = m_rectHeader;
	rectHeader.bottom = rectHeader.top + m_CharSizeHeader.cy;
	pDC->DrawText(m_View->GetDocument()->GetTitle(), rectHeader, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_NOCLIP);   
	pDC->SelectObject(pOldFont);
}

void CPrint::PrintFooter(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pFontFooter != NULL && pInfo != NULL);
	CFont *pOldFont = pDC->SelectObject(m_pFontFooter);

#ifdef _DEBUG
	DrawRect(pDC, m_rectFooter, RGB(0, 255, 0));
#endif

	// Create black brush
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// Draw line
	CRect rectLine = m_rectFooter;
	rectLine.top += m_CharSizeHeader.cy * (1 / 2);
	rectLine.bottom = rectLine.top + HEADER_LINE_SIZE;
	pDC->FillRect(&rectLine, &brush);
	pDC->SelectObject(pOldBrush);

	// Draw "Pages"
	CString strPages;
	if (m_nPageCount > 0)
		strPages.Format(_T("Page %d of %d"), pInfo->m_nCurPage, m_nPageCount);
	else
		strPages.Format(_T("Page %d"), pInfo->m_nCurPage);
	CRect rectPage = m_rectFooter;
	rectPage.top = rectPage.bottom - m_CharSizeFooter.cy - 20;
	pDC->DrawText(strPages, rectPage, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_NOCLIP);
	pDC->SelectObject(pOldFont);
}

// Conversion from/to Pixel, Millimeters and Inches

int CPrint::MMToPixX(double val)
{
	ASSERT(m_PixPerMMX);
	return (int)(val * (double)m_PixPerMMX);
}

int CPrint::MMToPixY(double val)
{
	ASSERT(m_PixPerMMY);
	return (int)(val * (double)m_PixPerMMY);
}

int CPrint::InchToPixX(double val)
{
	ASSERT(m_PixPerInchX);
	return (int)(val * m_PixPerInchX);
}

int CPrint::InchToPixY(double val)
{
	ASSERT(m_PixPerInchY);
	return (int)(val * m_PixPerInchY);
}

double CPrint::PixToInchX(int val)
{
	ASSERT(m_PixPerInchX);
	return val / m_PixPerInchX;
}

double CPrint::PixToInchY(int val)
{
	ASSERT(m_PixPerInchY);
	return val / m_PixPerInchY;
}

double CPrint::PixToMMX(int val)
{
	ASSERT(m_PixPerMMX);
	return val / m_PixPerMMX;
}

double CPrint::PixToMMY(int val)
{
	ASSERT(m_PixPerMMY);
	return val / m_PixPerMMY;
}
