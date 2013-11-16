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

  $Id: bibedtView.h,v 1.38 2006/06/17 11:43:35 stievie Exp $
*/

// bibedtView.h : Schnittstelle der Klasse CBibedtView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBEDTVIEW_H__9D05F55B_A023_4707_B71D_6218D097E296__INCLUDED_)
#define AFX_BIBEDTVIEW_H__9D05F55B_A023_4707_B71D_6218D097E296__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxpriv.h>

#include "Export.h"
#include "ListViewPrint.h"	// Hinzugefügt von der Klassenansicht
#include "BibedtDoc.h"

#define MISSING_HIGHLIGHT RGB(255, 255, 200)
#define URL_TEXT_COLOR  RGB(0, 0, 255)
#define MISSING_COLOR RGB(160, 5, 5)

class CBibedtView : public CListView
{
protected: // Nur aus Serialisierung erzeugen
	CBibedtView();
	DECLARE_DYNCREATE(CBibedtView)

// Attribute
public:
	CBibedtDoc* GetDocument();

// Operationen
public:
// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBibedtView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	protected:
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void DoMarkMatches();
	BOOL GetFocused(int index);
	int GetPreviousBookmark(int index);
	int GetNextBookmark(int index);
	void ToggleBookmark(int index);
	void ClearBookmarks();
	void SetBookmark(int index, BOOL set = TRUE);
	void SetFocused(int index, BOOL focused);
	void SetColumnValues(int pos, CBibItem* item);
	int GetItemIndex(CBibItem *item);
	int AddItem(int pos, CBibItem *item, BOOL select);
	void DoExport();
	BOOL IsFieldVisible(CString f);
	void SetupColumns();
	int m_CiteFormat;
	void UnselectAll();
	void SetSelected(int index, BOOL selected);
	void AddList(POSITION p, BOOL select);
	BOOL GetSelected(int index);
	CBibItem * GetSelectedItem();
	void SetGridLines(BOOL val);
	void SetRowSelect(BOOL val);
	BOOL Matches(int item);
	void DoSearch();
	void Populate();
	virtual ~CBibedtView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	friend class CPreviewView;

// Generierte Message-Map-Funktionen
protected:
	CListViewPrint m_Print;
	CImageList m_ImageList;
	//{{AFX_MSG(CBibedtView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewGridlines();
	afx_msg void OnUpdateViewGridlines(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopycitation();
	afx_msg void OnUpdateEditCopycitation(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnViewColumns();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchFind(CCmdUI* pCmdUI);
	afx_msg void OnSearchFindnext();
	afx_msg void OnUpdateSearchFindnext(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePrint();
	afx_msg void OnFileExport();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnUpdateSearchTogglebookmark(CCmdUI* pCmdUI);
	afx_msg void OnSearchTogglebookmark();
	afx_msg void OnSearchClearbookmarks();
	afx_msg void OnSearchNextbookmark();
	afx_msg void OnUpdateSearchNextbookmark(CCmdUI* pCmdUI);
	afx_msg void OnSearchPreviousbookmark();
	afx_msg void OnUpdateSearchPreviousbookmark(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchFindduplicate(CCmdUI* pCmdUI);
	afx_msg void OnSearchFindduplicate();
	afx_msg void OnSearchFind();
	afx_msg void OnUpdateSearchClearbookmarks(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRecordGeneratekey();
	afx_msg void OnUpdateRecordGeneratekey(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_SearchRegExpr;
	CMenu m_PopupMenu;
	CImageList m_SortIndicator;
	BOOL m_Updating;
	void SortList(int col);
	BOOL m_SearchMatchCase;
	BOOL m_SortAsc;
	int m_SortCol;
	BOOL m_SearchSelOnly;
	BOOL m_SearchWholeWords;
	CString m_SearchText;
	CString m_SearchFields;
	static int CALLBACK ListViewSortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

#ifndef _DEBUG  // Testversion in bibedtView.cpp
inline CBibedtDoc* CBibedtView::GetDocument()
   { return (CBibedtDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BIBEDTVIEW_H__9D05F55B_A023_4707_B71D_6218D097E296__INCLUDED_)
