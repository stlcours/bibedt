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

  $Id: HTMLView.h,v 1.11 2006/08/08 21:37:27 stievie Exp $
*/

#if !defined(AFX_HTMLVIEW_H__9C333F2A_9AE6_4AD8_8FB9_D4A4D94AE594__INCLUDED_)
#define AFX_HTMLVIEW_H__9C333F2A_9AE6_4AD8_8FB9_D4A4D94AE594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HTMLView.h : Header-Datei
//

#include "BibedtDoc.h"
#include "htmlviewer.h"
#include "BibItem.h"

struct _SCROLLWINDOW{
	int nXMax;
	int nYMax;
	int nXPos;
	int nYPos;
	int nXSize;
	int nYSize;
	int nXLine;
	int nYLine;
	SIZE s;
	BOOL bChanging;
	HWND hWnd;
	BOOL bCapture;
};

/////////////////////////////////////////////////////////////////////////////
// Ansicht CHTMLView 

class CHTMLView : public CView, CHTMLProgress
{
// CHTMLProgress
public:
	virtual void Reading(BOOL bImage, int nPos, int nSize);
	virtual void LinkClicked(char *szLink, int nLink);
	virtual void SetCursor(BOOL bLink, char *szLink, int nLink);
	virtual void SetTitle(char *szTitle);

	virtual char *ReadHTTPData(char *szUrl,int *pnSize);
	virtual void ImageLoaded(int nDone, int nCount);

	// Control functions, return -1 if no control support.
	virtual int CreateForm(char *szAction, char *szMethod);
	virtual int CreateTextBox(int nSize, int nMaxChar,SIZE scSize,char *szText, BOOL bMultiline,char *szName,int nForm,BOOL bPassword);
	virtual int CreateButton(SIZE scSize,char *szText,char *szName,int nForm);
	virtual int CreateRadio(SIZE scSize,char *szValue,char *szName,int nForm);
	virtual int CreateCheckbox(SIZE scSize,char *szValue,char *szName,int nForm);
	virtual int CreateListbox(SIZE scSize,CHTMLStringTable &stOptions,int nSelected,char *szName,int nForm);
	virtual void MoveControl(int nControlID, POINT pPos);

	virtual void UpdateScreen(RECT &r);

protected:
	CHTMLView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CHTMLView)

// Attribute
public:
	CBibedtDoc* GetDocument();

protected:
	CHTMLViewer *m_pViewer;
	CString m_ActiveUrl;
	CPoint m_pSelectStart;
	CPoint m_pSelectStop;

// Operationen
public:
	void Refresh();
	int SetScrollSize(int nBar, int nSize);
	BOOL ExecLink(CString url);
	void CalcPos();
	void SetText(CString str);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHTMLView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CHTMLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CString m_HTMLSource;
	int ScrollProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CHTMLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdatePreviewCopylink(CCmdUI* pCmdUI);
	afx_msg void OnPreviewCopylink();
	afx_msg void OnUpdatePreviewViewsource(CCmdUI* pCmdUI);
	afx_msg void OnPreviewViewsource();
	afx_msg void OnPreviewCopyhtml();
	afx_msg void OnUpdatePreviewCopyhtml(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bLinkClicked;
	_SCROLLWINDOW **m_ppScrolls;
	int m_nScrolls;
	CMenu m_PopupMenu;
	HCURSOR m_HyperCursor;	
	HBITMAP m_bmBmp;
	int m_MouseWheelScollSize;
	void UpdateItem(CBibItem* item);
};

#ifndef _DEBUG  // Testversion in bibedtView.cpp
inline CBibedtDoc* CHTMLView::GetDocument()
   { return (CBibedtDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HTMLVIEW_H__9C333F2A_9AE6_4AD8_8FB9_D4A4D94AE594__INCLUDED_
