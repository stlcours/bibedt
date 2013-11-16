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

  $Id: Print.h,v 1.4 2005/08/22 23:32:33 stievie Exp $
*/

// Print.h: Schnittstelle für die Klasse CPrint.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINT_H__873718DA_8EDF_48E6_A2D5_648B7C5C9489__INCLUDED_)
#define AFX_PRINT_H__873718DA_8EDF_48E6_A2D5_648B7C5C9489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MARGIN_LEFT     200
#define MARGIN_TOP      200
#define MARGIN_RIGHT    200
#define MARGIN_BOTTOM   250
#define HEADER_LINES      2
#define FOOTER_LINES      2
#define HEADER_LINE_SIZE  5
#define FOOTER_LINE_SIZE  5

enum Units {
	U_PIXEL, U_INCH, U_MM
};

class CPrint  
{
public:
	CPrint();
	virtual ~CPrint();

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

protected:
#ifdef _DEBUG
	void DrawRect(CDC* pDC, CRect rect, COLORREF color);
#endif
	CView* m_View;

	CRect m_rectHeader;
	CRect m_rectFooter;
	CRect m_rectBody;
	CRect m_rectPage;
	CRect m_rectPaper;
	CFont* m_pFontHeader;
	CFont* m_pFontFooter;
	CFont* m_pFontBody;
	CSize m_CharSizeHeader;
	CSize m_CharSizeFooter;
	CSize m_CharSizeBody;
	double m_RatioX; 

	int m_headerHeight;
	int m_headerLines;
	int m_footerHeight;
	int m_footerLines;

	int m_nPageCount;
	BOOL m_PrintSelOnly;

	int m_PixPerInchX;
	int m_PixPerInchY;
	double m_PixPerMMX;
	double m_PixPerMMY;

	double PixToInchY(int val);
	double PixToMMY(int val);
	double PixToMMX(int val);
	double PixToInchX(int val);
	int InchToPixY(double val);
	int InchToPixX(double val);
	int MMToPixY(double val);
	int MMToPixX(double val);
	Units m_MarginUnit;

	virtual void PrintFooter(CDC* pDC, CPrintInfo* pInfo);
	virtual void PrintBody(CDC* pDC, CPrintInfo* pInfo) = 0;
	virtual void PrintHeader(CDC* pDC, CPrintInfo* pInfo);
	virtual CFont* CreateFont(CDC* pDC, CString strName = "", int nPoints = 0, int lfWeight = FW_NORMAL, bool lfItalic = false);

	virtual CRect GetBodyRect();
	virtual CRect GetPaperRect(CDC* pDC);
	virtual CRect GetPageRect();
	virtual CRect GetHeaderRect();
	virtual CRect GetFooterRect();
	virtual CSize GetCharSize(CDC* pDC, CFont* pFont);
	virtual double GetTextRatioX(CDC* pDC);

protected:
	int m_marginLeftPix;
	int m_marginTopPix;
	int m_marginRightPix;
	int m_marginBottomPix;
	double m_MarginLeft;
	double m_MarginTop;
	double m_MarginRight;
	double m_MarginBottom;

public:
	Units GetMarginUnit() const {return m_MarginUnit;}
	void SetMarginUnit(Units unit) {m_MarginUnit = unit;}
	void SetMarginLeft(double leftMargin) {m_MarginLeft = leftMargin;}
	double GetMarginLeft() const {return m_MarginLeft;}
	void SetMarginTop(double topMargin) {m_MarginTop = topMargin;}
	double GetMarginTop() const {return m_MarginTop;}
	void SetMarginRight(double rightMargin) {m_MarginRight = rightMargin;}
	double GetMarginRight() const {return m_MarginRight;}
	void SetMarginBottom(double bottomMargin) {m_MarginBottom = bottomMargin;}
	double GetMarginBottom() const {return m_MarginBottom;}
	void SetHeadLines(int lines){ m_headerLines = lines; }
	int GetHeadLines() const { return m_headerLines; }
	void SetFootLines(int lines) { m_footerLines = lines; }
	int GetFootLines() const { return m_footerLines; }
	void SetView(CView* view){ m_View = view; }
	CView* GetView() { return m_View; }

};

#endif // !defined(AFX_PRINT_H__873718DA_8EDF_48E6_A2D5_648B7C5C9489__INCLUDED_)
