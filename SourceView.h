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

  $Id: SourceView.h,v 1.18 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_SOURCEVIEW_H__BB5AF7E4_EC38_4E20_9648_6E922003EE2E__INCLUDED_)
#define AFX_SOURCEVIEW_H__BB5AF7E4_EC38_4E20_9648_6E922003EE2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceView.h : Header-Datei
//

#include <afxpriv.h>

#include "ScintillaBibWnd.h"
#include "BibedtDoc.h"
#include "ScintillaPrint.h"

/////////////////////////////////////////////////////////////////////////////
// Ansicht CSourceView 

class CSourceView : public CView
{
public:
	CSourceView();           // Dynamische Erstellung verwendet geschützten Konstruktor

protected:
	DECLARE_DYNCREATE(CSourceView)

// Attribute
public:
	CBibedtDoc* GetDocument();

protected:
	CScintillaBibWnd m_wndScintilla;

private:
	CMenu m_PopupMenu;
	BOOL m_Updating;
	BOOL m_Active;
	CScintillaPrint m_Print;

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSourceView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	BOOL GotoItem(CString key);
	void SetText(LPCSTR txt, BOOL maintainpos);
	BOOL m_NeedUpdate;
	virtual ~CSourceView();

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	friend class CPreviewView;

	//{{AFX_MSG(CSourceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchClearbookmarks(CCmdUI* pCmdUI);
	afx_msg void OnSearchClearbookmarks();
	afx_msg void OnSearchNextbookmark();
	afx_msg void OnUpdateSearchNextbookmark(CCmdUI* pCmdUI);
	afx_msg void OnSearchPreviousbookmark();
	afx_msg void OnUpdateSearchPreviousbookmark(CCmdUI* pCmdUI);
	afx_msg void OnSearchTogglebookmark();
	afx_msg void OnUpdateSearchTogglebookmark(CCmdUI* pCmdUI);
	afx_msg void OnSearchFind();
	afx_msg void OnUpdateSearchFind(CCmdUI* pCmdUI);
	afx_msg void OnSearchFindnext();
	afx_msg void OnUpdateSearchFindnext(CCmdUI* pCmdUI);
	afx_msg void OnSearchReplace();
	afx_msg void OnUpdateSearchReplace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrevious(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchGotorecord(CCmdUI* pCmdUI);
	afx_msg void OnSearchGotorecord();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePrint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateSourceviewEdititem(CCmdUI* pCmdUI);
	afx_msg void OnSourceviewEdititem();
	afx_msg void OnPopupCopykey();
	afx_msg void OnUpdatePopupCopykey(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewFoldall();
	afx_msg void OnUpdateViewFoldall(CCmdUI* pCmdUI);
	afx_msg void OnViewExpandall();
	afx_msg void OnUpdateViewExpandall(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in bibedtView.cpp
inline CBibedtDoc* CSourceView::GetDocument()
   { return (CBibedtDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SOURCEVIEW_H__BB5AF7E4_EC38_4E20_9648_6E922003EE2E__INCLUDED_
