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

  $Id: LinkStatic.cpp,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

// LinkStatic.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "LinkStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkStatic

CLinkStatic::CLinkStatic()
{
	m_LinkColor = RGB(0, 0 ,255);
	m_HoverColor = RGB(255, 0, 0);
	m_VisitedColor = RGB(40, 130, 20);
	m_MouseOver = FALSE;
	m_Visited = FALSE;
}

CLinkStatic::~CLinkStatic()
{
}


BEGIN_MESSAGE_MAP(CLinkStatic, CStatic)
	//{{AFX_MSG_MAP(CLinkStatic)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CLinkStatic 

void CLinkStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStatic::OnMouseMove(nFlags, point);

	if (m_MouseOver) {
		CRect r;
		GetClientRect(&r);

		//check if the mouse is in the rect
		if (!r.PtInRect(point)) {
			m_MouseOver = FALSE;
			//Release the Mouse capture previously take
			ReleaseCapture();
			RedrawWindow();
			return;
		}
	} else {
		m_MouseOver = TRUE;
		RedrawWindow();
		//capture the mouse
		SetCapture();
	}
}

BOOL CLinkStatic::OpenURL(CString url)
{
	return (DWORD)ShellExecute(NULL, _T("open"), url, NULL, NULL, SW_NORMAL) > HINSTANCE_ERROR;
}

void CLinkStatic::OnClicked() 
{
	if (OpenURL(m_URL))
		m_Visited = TRUE;
}

BOOL CLinkStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(m_HyperCursor);
	
	return TRUE;
}

void CLinkStatic::PreSubclassWindow() 
{
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	LOGFONT sLogFont;
	GetFont()->GetLogFont(&sLogFont);
	sLogFont.lfUnderline = true;
	m_TextFont.CreateFontIndirect(&sLogFont);
	this->SetFont(&m_TextFont, true);
	
	m_HyperCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_LINKHAND);

	CStatic::PreSubclassWindow();
}

HBRUSH CLinkStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if (m_MouseOver){
		if (m_Visited)
			pDC->SetTextColor(m_VisitedColor);
		else
			pDC->SetTextColor(m_HoverColor);
	}else {
		if (m_Visited)
			pDC->SetTextColor(m_VisitedColor);
		else
			pDC->SetTextColor(m_LinkColor);
	}
	pDC->SetBkMode(TRANSPARENT);
	return((HBRUSH)GetStockObject(NULL_BRUSH));
}
