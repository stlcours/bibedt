/*
  BibEdt
  Copyright (C) 2006, Ascher Stefan. All rights reserved.
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

  $Id: HTMLView.cpp,v 1.14 2006/08/08 21:37:27 stievie Exp $
*/

// HTMLView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "HTMLView.h"
#include "BibReader.h"
#include "Field.h"
#include "Globals.h"
#include "Options.h"
#include "ExportPreview.h"
#include "SourceDialog.h"
#include "SciLexer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTMLView

#define SM_SETSIZE		WM_USER+1	// wParam=x, lParam=y
#define SM_SETXPOS		WM_USER+2	// lParam=xPos
#define SM_SETYPOS		WM_USER+3	// lParam=yPos
#define SM_GETXPOS		WM_USER+4	// returns xPos
#define SM_GETYPOS		WM_USER+5	// returns yPos
#define SM_GETXSIZE		WM_USER+6	// returns xPos
#define SM_GETYSIZE		WM_USER+7	// returns yPos
#define SM_LINSESIZE	WM_USER+8	// wParam=x, lParam=y
#define SN_SCROLLED		WM_USER+9	// Sent when window is scrolled, wParam=x, lParam=y

// CHTMLProgress
void CHTMLView::LinkClicked(char *szLink, int nLink) 
{
	if (!ExecLink(szLink))
		MessageBeep(MB_ICONEXCLAMATION);
	m_pViewer->UpdateLink(nLink);
	InvalidateRect(NULL,FALSE);
}

void CHTMLView::SetCursor(BOOL bLink, char *szLink, int nLink) 
{
	if (m_ActiveUrl.IsEmpty() || m_ActiveUrl.Compare(szLink) != 0) {
		if (szLink != NULL && strlen(szLink) > 0) {
			COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
			m_ActiveUrl = pOp->ResolveDOI(szLink);
		} else 
			m_ActiveUrl.Empty();
		m_pViewer->UpdateLink(nLink);
	}
	m_bLinkClicked = bLink;
	if (bLink) {
		::SetCursor(m_HyperCursor);
		m_pViewer->UpdateLink(nLink);
	} else {
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
}

void CHTMLView::Reading(BOOL bImage, int nPos, int nSize) { }
void CHTMLView::SetTitle(char *szTitle) { }
char *CHTMLView::ReadHTTPData(char *szUrl,int *pnSize) { return 0; }
void CHTMLView::ImageLoaded(int nDone, int nCount) { }
// Control functions, return -1 if no control support.
int CHTMLView::CreateForm(char *szAction, char *szMethod) {	return -1; }
int CHTMLView::CreateTextBox(int nSize, int nMaxChar,SIZE scSize,char *szText, BOOL bMultiline,char *szName,int nForm,BOOL bPassword) {	return -1; }
int CHTMLView::CreateButton(SIZE scSize,char *szText,char *szName,int nForm) { return -1; }
int CHTMLView::CreateRadio(SIZE scSize,char *szValue,char *szName,int nForm) { return -1; }
int CHTMLView::CreateCheckbox(SIZE scSize,char *szValue,char *szName,int nForm) { return -1; }
int CHTMLView::CreateListbox(SIZE scSize,CHTMLStringTable &stOptions,int nSelected,char *szName,int nForm) { return -1; }
void CHTMLView::MoveControl(int nControlID, POINT pPos) { }

void CHTMLView::UpdateScreen(RECT &r)
{
	RECT rI = {r.left-ScrollProc(SM_GETXPOS,0,0),r.top-ScrollProc(SM_GETYPOS,0,0),
		r.right-ScrollProc(SM_GETXPOS,0,0),r.bottom-ScrollProc(SM_GETYPOS,0,0)};
#ifdef _DEBUG
//			AfxTrace("CHTMLView::UpdateScreen() x1 = %d, y1 = %d, x2 = %d, y2 = %d\n", rI.left, rI.top, rI.right, rI.bottom);
#endif
	InvalidateRect(&rI, FALSE);
}

IMPLEMENT_DYNCREATE(CHTMLView, CView)

CHTMLView::CHTMLView()
{
	m_ppScrolls = 0;
	m_nScrolls = 0;
	if (IsNT()) {
		int sl;
		SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &sl, 0);
		m_MouseWheelScollSize = sl;
	} else {
		m_MouseWheelScollSize = 3;
	}
	m_bLinkClicked = FALSE;
	m_HyperCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_LINKHAND);
	VERIFY(m_PopupMenu.LoadMenu(IDR_MENU_PREVIEW));
}

CHTMLView::~CHTMLView()
{
}


BEGIN_MESSAGE_MAP(CHTMLView, CView)
	//{{AFX_MSG_MAP(CHTMLView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_COPYLINK, OnUpdatePreviewCopylink)
	ON_COMMAND(ID_PREVIEW_COPYLINK, OnPreviewCopylink)
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_VIEWSOURCE, OnUpdatePreviewViewsource)
	ON_COMMAND(ID_PREVIEW_VIEWSOURCE, OnPreviewViewsource)
	ON_COMMAND(ID_PREVIEW_COPYHTML, OnPreviewCopyhtml)
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_COPYHTML, OnUpdatePreviewCopyhtml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CHTMLView 

void CHTMLView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CHTMLView

#ifdef _DEBUG
void CHTMLView::AssertValid() const
{
	CView::AssertValid();
}

void CHTMLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBibedtDoc* CHTMLView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBibedtDoc)));
	return (CBibedtDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHTMLView 

int CHTMLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pViewer = new CHTMLViewer(this);
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_pViewer->SetFontFixed(pOp->m_FontMono.GetBuffer(pOp->m_FontMono.GetLength()));
	m_pViewer->SetFontProp(pOp->m_FontProp.GetBuffer(pOp->m_FontProp.GetLength()));
	m_pViewer->SetFontSans(pOp->m_FontSans.GetBuffer(pOp->m_FontSans.GetLength()));
	return 0;
}

void CHTMLView::OnSize(UINT nType, int cx, int cy) 
{
	RECT r;
	GetClientRect(&r);
	if(m_bmBmp)
		DeleteObject(m_bmBmp);
	CDC *hDC = GetDC();
	m_bmBmp = CreateCompatibleBitmap(hDC->m_hDC,r.right,r.bottom);
	ReleaseDC(hDC);
	
	CalcPos();
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

	CView::OnSize(nType, cx, cy);	
}

void CHTMLView::OnPaint() 
{
	CRect r;
	GetClientRect(&r);
	PAINTSTRUCT ps;
	BeginPaint(&ps);
#ifndef _DEBUG
	if(!m_bmBmp)
		m_bmBmp = CreateCompatibleBitmap(ps.hdc, r.right, r.bottom);
	HDC dcBmp = CreateCompatibleDC(ps.hdc);
	HBITMAP bmOld = (HBITMAP)SelectObject(dcBmp, m_bmBmp);
	m_pViewer->Draw(dcBmp, r, ScrollProc(SM_GETXPOS, 0, 0), ScrollProc(SM_GETYPOS, 0, 0));
	BitBlt(ps.hdc,0,0,r.right,r.bottom,dcBmp,0,0,SRCCOPY);
	SelectObject(dcBmp,bmOld);
	DeleteDC(dcBmp);
#else
	m_pViewer->Draw(ps.hdc, r, ScrollProc(SM_GETXPOS, 0, 0), ScrollProc(SM_GETYPOS, 0, 0));
#endif
	EndPaint(&ps);
}

void CHTMLView::OnDestroy() 
{
	for (int i = 0; i < m_nScrolls; i++) {
		delete m_ppScrolls[i];
	}
	free(m_ppScrolls);
	m_nScrolls = 0;
	delete m_pViewer;

	CView::OnDestroy();
}

void CHTMLView::Refresh()
{
	m_pViewer->SetHTML(m_HTMLSource.GetBuffer(m_HTMLSource.GetLength()), NULL, 18, RGB(0,0,0), NULL);

	CRect r;
	GetClientRect(&r);
	SendMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(r.Width(), r.Height()));
}

void CHTMLView::SetText(CString str)
{
	m_HTMLSource = str;
	Refresh();
}

void CHTMLView::CalcPos()
{
	RECT r;
	GetClientRect(&r);
	m_pViewer->CalcPositions(r);
	ScrollProc(SM_SETSIZE, r.right, r.bottom);
}

void CHTMLView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint) {
	case UR_NEWFILE:
		UpdateItem(NULL);
		break;
	case UR_SELECTED:
	case UR_RECEDITED:
	case UR_RECSRCEDITED:
	case UR_SRCEDITED:
		if (pHint == GetDocument()->GetSelected())
			UpdateItem((CBibItem*)pHint);
		break;
	}	
}

void CHTMLView::UpdateItem(CBibItem *item)
{
	if (item) {
		CExporterList *exlst = ((CBibedtApp*)AfxGetApp())->m_Options->m_ExporterList;
		CExportPreview *exporter = (CExportPreview*)exlst->GetPreviewExporter();
		if (exporter) {
			exporter->SetItem(item);
			SetText(exporter->GetSource());
		} else
			SetText(_T(""));
	} else
		SetText(_T(""));
}

void CHTMLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_pViewer->OnMouseOver(point.x + ScrollProc(SM_GETXPOS, 0, 0), point.y + ScrollProc(SM_GETYPOS, 0, 0));

	if (GetCapture() == this && !m_bLinkClicked) {
		RECT r;
		m_pSelectStop = point;
		if (m_pSelectStart.x < m_pSelectStop.x) {
			r.left = m_pSelectStart.x + ScrollProc(SM_GETXPOS,0,0);
			r.right = m_pSelectStop.x + ScrollProc(SM_GETXPOS,0,0);
		} else {
			r.left = m_pSelectStop.x + ScrollProc(SM_GETXPOS,0,0);
			r.right = m_pSelectStart.x + ScrollProc(SM_GETXPOS,0,0);
		}
		if (m_pSelectStart.y < m_pSelectStop.y) {
			r.top = m_pSelectStart.y + ScrollProc(SM_GETYPOS,0,0);
			r.bottom = m_pSelectStop.y + ScrollProc(SM_GETYPOS,0,0);
		} else {
			r.top = m_pSelectStop.y + ScrollProc(SM_GETYPOS,0,0);
			r.bottom = m_pSelectStart.y + ScrollProc(SM_GETYPOS,0,0);
		}
		m_pViewer->Select(r);
		InvalidateRect(NULL, FALSE);

		GetClientRect(&r);
		if (m_pSelectStop.x<r.left) {
			int nOffs = r.left - m_pSelectStop.x;
			if (nOffs > ScrollProc(SM_GETXPOS, 0, 0))
				nOffs = ScrollProc(SM_GETXPOS, 0, 0);
			ScrollProc(SM_SETXPOS, 0, ScrollProc(SM_GETXPOS, 0, 0) - nOffs);
			m_pSelectStart.x += nOffs;
		} else if (m_pSelectStop.x>r.right) {
			int nOffs = m_pSelectStop.x - r.right;
			if (ScrollProc(SM_GETXPOS, 0, 0) + nOffs > ScrollProc(SM_GETXSIZE, 0, 0))
				nOffs = ScrollProc(SM_GETXSIZE, 0, 0) - ScrollProc(SM_GETXPOS, 0, 0);
			ScrollProc(SM_SETXPOS, 0, ScrollProc(SM_GETXPOS, 0, 0) + nOffs);
			m_pSelectStart.x -= nOffs;
		}
		if (m_pSelectStop.y<r.top) {
			int nOffs = r.top - m_pSelectStop.y;
			if (nOffs > ScrollProc(SM_GETYPOS, 0, 0))
				nOffs = ScrollProc(SM_GETYPOS, 0, 0);
			ScrollProc(SM_SETYPOS, 0, ScrollProc(SM_GETYPOS, 0, 0) - nOffs);
			m_pSelectStart.y += nOffs;
		} else if (m_pSelectStop.y > r.bottom) {
			int nOffs = m_pSelectStop.y - r.bottom;
			if (ScrollProc(SM_GETYPOS, 0, 0) + nOffs > ScrollProc(SM_GETYSIZE, 0, 0))
				nOffs = ScrollProc(SM_GETYSIZE, 0, 0) - ScrollProc(SM_GETYPOS, 0, 0);
			ScrollProc(SM_SETYPOS, 0, ScrollProc(SM_GETYPOS, 0, 0) + nOffs);
			m_pSelectStart.y -= nOffs;
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CHTMLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_pViewer->OnMouseClick(point.x + ScrollProc(SM_GETXPOS, 0, 0),point.y + ScrollProc(SM_GETYPOS, 0, 0));
	if (!m_bLinkClicked) {
		m_pSelectStart = point;
		RECT r = {m_pSelectStart.x + ScrollProc(SM_GETXPOS, 0, 0), m_pSelectStart.y + ScrollProc(SM_GETYPOS, 0, 0),
			m_pSelectStart.x + ScrollProc(SM_GETXPOS, 0, 0), m_pSelectStart.y + ScrollProc(SM_GETYPOS, 0, 0)};
		m_pViewer->Select(r);
		InvalidateRect(NULL, FALSE);
	} else {
		m_pSelectStart = point;
		m_pSelectStop = point;
		m_pViewer->Unselect();
		InvalidateRect(NULL, FALSE);
	}
	SetCapture();
	
	CView::OnLButtonDown(nFlags, point);
}

void CHTMLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (GetCapture() == this)
		ReleaseCapture();
	
	CView::OnLButtonUp(nFlags, point);
}

BOOL CHTMLView::ExecLink(CString url)
{
	if (url.Left(strlen(STR_BIBPROTOCOLL)).CompareNoCase(STR_BIBPROTOCOLL) != 0) {
		COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
		url = pOp->ResolveDOI(url);
		return ShellExec(url);
	} else {
		// bib://bibkey
		CString key = url.Mid(strlen(STR_BIBPROTOCOLL));
		return GetDocument()->SetSelected(key);
	}
}

void CHTMLView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pViewer->HasSelection());
}

void CHTMLView::OnEditCopy() 
{
	m_pViewer->CopySelected();
}

void CHTMLView::OnEditSelectAll() 
{
	m_pViewer->SelectAll();
	InvalidateRect(NULL,FALSE);
}

void CHTMLView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pViewer->GetItemsCount());
}

void CHTMLView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu* pPopup = NULL;
	pPopup = m_PopupMenu.GetSubMenu(0);

	if (pPopup != NULL) {
		// Update Menuitems
		AfxGetMainWnd()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopup->m_hMenu, MAKELONG(0, FALSE));
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}	
}

LRESULT CHTMLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) {
	case WM_BE_FONT_CHANGED:
		COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
		m_pViewer->SetFontFixed(pOp->m_FontMono.GetBuffer(pOp->m_FontMono.GetLength()));
		m_pViewer->SetFontProp(pOp->m_FontProp.GetBuffer(pOp->m_FontProp.GetLength()));
		m_pViewer->SetFontSans(pOp->m_FontSans.GetBuffer(pOp->m_FontSans.GetLength()));
		Refresh();
		return 0;
	}
	LRESULT res = CView::WindowProc(message, wParam, lParam);
	ScrollProc(message, wParam, lParam);
	return res;
}

int CHTMLView::ScrollProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	_SCROLLWINDOW *sw;
	SIZE ss, si, thumb;
	RECT r;
	int i=-1, offs, x, y;
	static POINT pStart;

	if (!uMsg && !wParam && !lParam) {
		for (i = 0; i < m_nScrolls; i++)
			delete m_ppScrolls[i];
		free(m_ppScrolls);
		return 0;
	}

	while (uMsg != WM_CREATE && uMsg != WM_DESTROY && uMsg != WM_NCDESTROY) {
		for (i = 0; i < m_nScrolls; i++)
			if (m_ppScrolls[i]->hWnd == m_hWnd) {
				sw = m_ppScrolls[i];
				break;
			}
		if (i == m_nScrolls && uMsg != WM_DESTROY && uMsg != WM_NCDESTROY)
			ScrollProc(WM_CREATE, 0, 0);
		else
			break;
	}
	if ((i == -1 || i == m_nScrolls) && uMsg != WM_CREATE) {
		return 0;
	}

	switch(uMsg) {
	case WM_CREATE:
		i = m_nScrolls++;
		m_ppScrolls = (_SCROLLWINDOW **)realloc(m_ppScrolls, sizeof(_SCROLLWINDOW*) * m_nScrolls);
		m_ppScrolls[i] = new _SCROLLWINDOW;
		memset(m_ppScrolls[i], 0, sizeof(_SCROLLWINDOW));
		m_ppScrolls[i]->hWnd = m_hWnd;
		m_ppScrolls[i]->nXLine = m_ppScrolls[i]->nYLine = 10;
		break;
	case WM_SIZE:
		if(sw->bChanging)
			break;
		sw->bChanging = TRUE;
		si.cx = sw->nXMax;
		si.cy = sw->nYMax;
		thumb.cx = GetSystemMetrics(SM_CXHTHUMB);
		thumb.cy = GetSystemMetrics(SM_CYVTHUMB);
		ss.cx = LOWORD(lParam) - thumb.cy;
		ss.cy = HIWORD(lParam) - thumb.cx;
		for (i = 0; i < 2; i++){
			if (sw->s.cx > ss.cx + thumb.cy) {
				sw->nXMax = sw->s.cx - ss.cx;
			} else {
				sw->nXMax = 0;
			}
			if (sw->s.cy > ss.cy + thumb.cx) {
				sw->nYMax = sw->s.cy - ss.cy;
			} else {
				sw->nYMax = 0;
			}
		}
		if (sw->nXPos > sw->nXMax) {
			SendMessage(WM_HSCROLL, SB_LINEDOWN, 0);
			sw->nXPos = sw->nXMax;
		}
		if (sw->nYPos > sw->nYMax) {
			SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
			sw->nYPos = sw->nYMax;
		}
		if ((si.cx && !sw->nXMax) || (!si.cx && sw->nXMax))
			SetScrollPos(SB_HORZ, 0, TRUE);
		if ((si.cy && !sw->nYMax) || (!si.cy && sw->nYMax))
			SetScrollPos(SB_VERT, 0, TRUE);
		if (sw->s.cx && sw->nXMax)
			sw->nXSize = SetScrollSize(SB_HORZ, (100 * ss.cx) / sw->s.cx);
		else
			sw->nXSize = SetScrollSize(SB_HORZ, 0);
		if (sw->s.cy && sw->nYMax)
			sw->nYSize = SetScrollSize(SB_VERT, (100 * ss.cy) / sw->s.cy);
		else
			sw->nYSize = SetScrollSize(SB_VERT, 0);
		sw->bChanging = FALSE;
		break;
	case SM_SETSIZE:
		sw->s.cx = (int)wParam;
		sw->s.cy = (int)lParam;
		GetClientRect(&r);
		ScrollProc(WM_SIZE, 0, MAKELONG(r.right, r.bottom));
		break;
	case SM_GETXSIZE:
		return sw->nYMax;
	case SM_GETYSIZE:
		return sw->nYMax;
	case WM_HSCROLL:
		if(LOWORD(wParam) == SB_ENDSCROLL || lParam)
			break;
		GetClientRect(&r);
		switch(LOWORD(wParam)){
		case SB_LINEDOWN:
			offs = -sw->nXLine;
			break;
		case SB_LINEUP:
			offs = sw->nXLine;
			break;
		case SB_PAGEDOWN:
			offs = -r.right;
			break;
		case SB_PAGEUP:
			offs = r.right;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			offs=(int)(sw->nXPos - (sw->nXMax * HIWORD(wParam)) / sw->nXSize);
			break;
		}
		if(sw->nXPos - offs < 0)
			offs = sw->nXPos;
		if(sw->nXPos - offs > sw->nXMax)
			offs = sw->nXPos - sw->nXMax;
		sw->nXPos -= offs;
		SendMessage(SN_SCROLLED, (int)offs, 0);
		ScrollWindow((int)offs, 0, NULL, NULL);
		if(sw->nXMax)
			SetScrollPos(SB_HORZ, (int)(sw->nXPos * sw->nXSize / sw->nXMax) + (sw->nXPos > 0), TRUE);
		break;
	case WM_VSCROLL:
		if(LOWORD(wParam) == SB_ENDSCROLL || lParam)
			break;
		GetClientRect(&r);
		switch(LOWORD(wParam)){
		case SB_LINEDOWN:
			offs = -sw->nYLine;
			break;
		case SB_LINEUP:
			offs = sw->nYLine;
			break;
		case SB_PAGEDOWN:
			offs = -r.bottom;
			break;
		case SB_PAGEUP:
			offs = r.bottom;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			offs= (int)(sw->nYPos - (sw->nYMax * HIWORD(wParam)) / sw->nYSize);
			break;
		}
		if(sw->nYPos - offs < 0)
			offs = sw->nYPos;
		if(sw->nYPos - offs > sw->nYMax)
			offs = sw->nYPos - sw->nYMax;
		sw->nYPos -= offs;
		SendMessage(SN_SCROLLED, 0, offs);
		ScrollWindow(0, offs, NULL, NULL);
		if(sw->nYMax)
			SetScrollPos(SB_VERT, (int)(sw->nYPos * sw->nYSize / sw->nYMax) + (sw->nYPos > 0), TRUE);
		break;
	case WM_LBUTTONDOWN:
		pStart.x = (short)LOWORD(lParam);
		pStart.y = (short)HIWORD(lParam);
		SetCapture();
		sw->bCapture = TRUE;
		break;
	case WM_MOUSEMOVE:
		if (GetCapture() != this)
			break;
		if (!sw->bCapture)
			break;
		x = pStart.x - (short)LOWORD(lParam);
		y = pStart.y - (short)HIWORD(lParam);
		if (sw->nXPos + x > sw->nXMax)
			x = sw->nXMax - sw->nXPos;
		else if (sw->nXPos + x < 0)
			x = -sw->nXPos;
		if (sw->nYPos + y > sw->nYMax)
			y = sw->nYMax - sw->nYPos;
		else if (sw->nYPos + y < 0)
			y = -sw->nYPos;
		sw->nXPos += x;
		sw->nYPos += y;
		SendMessage(SN_SCROLLED, -x, -y);
		ScrollWindow( -x, -y, NULL, NULL);
		if (sw->nXMax)
			SetScrollPos(SB_HORZ, (int)(sw->nXPos * sw->nXSize / sw->nXMax) + (sw->nXPos > 0), TRUE);
		if (sw->nYMax)
			SetScrollPos(SB_VERT, (int)(sw->nYPos * sw->nYSize / sw->nYMax) + (sw->nYPos > 0), TRUE);
		pStart.x -= x;
		pStart.y -= y;
		SendMessage(WM_VSCROLL, SB_ENDSCROLL, 0);
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
	case WM_CAPTURECHANGED:
		sw->bCapture = FALSE;
		break;
	case WM_DESTROY:
		for (i = 0; i < m_nScrolls; i++) {
			delete m_ppScrolls[i];
		}
		m_nScrolls = 0;
		delete sw;
		break;
	case 0x020A://WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0) {
			for (i = 0; i < m_MouseWheelScollSize; i++)
				SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
		} else {
			for (i = 0; i < m_MouseWheelScollSize; i++)
				SendMessage(WM_VSCROLL, SB_LINEUP, 0);
		}
		SendMessage(WM_VSCROLL, SB_ENDSCROLL, 0);
		break;
	case SM_GETXPOS:
		if(lParam)
			*((int*)lParam) = sw->nXPos;
		return sw->nXPos;
	case SM_GETYPOS:
		if(lParam)
			*((int*)lParam) = sw->nYPos;
		return sw->nYPos;
	case SM_SETXPOS:
		if(sw->nXSize && sw->nXMax){
			int nPrev = sw->nXPos;
			sw->nXPos = lParam;
			if(sw->nXPos < 0)
				sw->nXPos = 0;
			if(sw->nXPos > sw->nXMax)
				sw->nXPos = sw->nXMax;
			SetScrollPos(SB_HORZ, (int)(sw->nXPos * sw->nXSize / sw->nXMax) + (sw->nXPos > 0), TRUE);
			SendMessage(SN_SCROLLED, nPrev - sw->nXPos, 0);
			ScrollWindow(nPrev - sw->nXPos, 0, NULL, NULL);
			SendMessage(WM_VSCROLL, SB_ENDSCROLL, 0);
		} else {
			SetScrollSize(SB_HORZ, 0);
		}
		break;
	case SM_SETYPOS: 
		if(sw->nYSize && sw->nYMax){
			int nPrev = sw->nYPos;
			sw->nYPos = lParam;
			if(sw->nYPos < 0)
				sw->nYPos = 0;
			if(sw->nYPos > sw->nYMax)
				sw->nYPos = sw->nYMax;
			SetScrollPos(SB_VERT, (int)(sw->nYPos * sw->nYSize / sw->nYMax) + (sw->nYPos > 0), TRUE);
			SendMessage(SN_SCROLLED, 0, nPrev-sw->nYPos);
			ScrollWindow(0, nPrev - sw->nYPos, NULL, NULL);
			SendMessage(WM_VSCROLL, SB_ENDSCROLL, 0);
		} else {
			SetScrollSize(SB_VERT, 0);
		}
		break;
	}
	return 0;
}

int CHTMLView::SetScrollSize(int nBar, int nSize)
{
	SCROLLINFO si = {sizeof(si)};
	if (nSize >= 100)
		nSize = 99;
	else if (nSize < 0)
		nSize = 0;
	if (nSize == 0) {
		si.fMask = SIF_RANGE;
		si.nMin = 0;
		si.nMax = 0;
	} else {
		si.fMask = SIF_PAGE;
		si.nPage = nSize;
	}
	SetScrollInfo(nBar, &si, FALSE);
	return 100 - nSize;
}

void CHTMLView::OnUpdatePreviewCopylink(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_ActiveUrl.IsEmpty());
}

void CHTMLView::OnPreviewCopylink() 
{
	ClipBrdPutData(this, m_ActiveUrl, CB_TEXT, TRUE);
}

void CHTMLView::OnUpdatePreviewViewsource(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_HTMLSource.IsEmpty());
}

void CHTMLView::OnPreviewViewsource() 
{
	CSourceDialog dlg;
	dlg.SetLexer(SCLEX_HTML);
	dlg.SetReadOnly(TRUE);
	dlg.SetSource(m_HTMLSource);
	dlg.DoModal();
}

void CHTMLView::OnPreviewCopyhtml() 
{
	ClipBrdPutData(this, m_HTMLSource, CB_HTML, TRUE);
}

void CHTMLView::OnUpdatePreviewCopyhtml(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_HTMLSource.IsEmpty());
}
