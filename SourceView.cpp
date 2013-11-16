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

  $Id: SourceView.cpp,v 1.40 2006/05/25 11:26:49 stievie Exp $
*/

// SourceView.cpp: Implementierungsdatei
//

#include <afxpriv.h>
#include "stdafx.h"
#include "bibedt.h"
#include "MainFrm.h"
#include "SourceView.h"
#include "FindDialog.h"
#include "ReplaceDialog.h"
#include "LexBib.h"
#include "xString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceView

IMPLEMENT_DYNCREATE(CSourceView, CView)

CSourceView::CSourceView()
{
	m_Active = FALSE;
	m_NeedUpdate = FALSE;
	m_Updating = FALSE;
	VERIFY(m_PopupMenu.LoadMenu(IDR_MENU_SOURCEVIEW));
}

CSourceView::~CSourceView()
{
}


BEGIN_MESSAGE_MAP(CSourceView, CView)
	//{{AFX_MSG_MAP(CSourceView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_WM_PAINT()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_CLEARBOOKMARKS, OnUpdateSearchClearbookmarks)
	ON_COMMAND(ID_SEARCH_CLEARBOOKMARKS, OnSearchClearbookmarks)
	ON_COMMAND(ID_SEARCH_NEXTBOOKMARK, OnSearchNextbookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_NEXTBOOKMARK, OnUpdateSearchNextbookmark)
	ON_COMMAND(ID_SEARCH_PREVIOUSBOOKMARK, OnSearchPreviousbookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_PREVIOUSBOOKMARK, OnUpdateSearchPreviousbookmark)
	ON_COMMAND(ID_SEARCH_TOGGLEBOOKMARK, OnSearchTogglebookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_TOGGLEBOOKMARK, OnUpdateSearchTogglebookmark)
	ON_COMMAND(ID_SEARCH_FIND, OnSearchFind)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND, OnUpdateSearchFind)
	ON_COMMAND(ID_SEARCH_FINDNEXT, OnSearchFindnext)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FINDNEXT, OnUpdateSearchFindnext)
	ON_COMMAND(ID_SEARCH_REPLACE, OnSearchReplace)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_REPLACE, OnUpdateSearchReplace)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREVIOUS, OnUpdateRecordPrevious)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_GOTORECORD, OnUpdateSearchGotorecord)
	ON_COMMAND(ID_SEARCH_GOTORECORD, OnSearchGotorecord)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_EDITITEM, OnUpdateSourceviewEdititem)
	ON_COMMAND(ID_SOURCEVIEW_EDITITEM, OnSourceviewEdititem)
	ON_COMMAND(ID_POPUP_COPYKEY, OnPopupCopykey)
	ON_UPDATE_COMMAND_UI(ID_POPUP_COPYKEY, OnUpdatePopupCopykey)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_FOLDALL, OnViewFoldall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDALL, OnUpdateViewFoldall)
	ON_COMMAND(ID_VIEW_EXPANDALL, OnViewExpandall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EXPANDALL, OnUpdateViewExpandall)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_SOURCEVIEW_COPY, OnEditCopy)
	ON_COMMAND(ID_SOURCEVIEW_CUT, OnEditCut)
	ON_COMMAND(ID_SOURCEVIEW_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_SOURCEVIEW_PASTE, OnEditPaste)
	ON_COMMAND(ID_SOURCEVIEW_REDO, OnEditRedo)
	ON_COMMAND(ID_SOURCEVIEW_SELECTALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_SOURCEVIEW_SELECTALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_SOURCEVIEW_UNDO, OnEditUndo)
	ON_COMMAND(ID_POPUP_FIND, OnSearchFind)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FIND, OnUpdateSearchFind)
	ON_COMMAND(ID_POPUP_TOGGLEBOOKMARK, OnSearchTogglebookmark)
	ON_UPDATE_COMMAND_UI(ID_POPUP_TOGGLEBOOKMARK, OnUpdateSearchTogglebookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CSourceView 

void CSourceView::OnDraw(CDC* pDC)
{
	ASSERT(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CSourceView

#ifdef _DEBUG
void CSourceView::AssertValid() const
{
	CView::AssertValid();
}

void CSourceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBibedtDoc* CSourceView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBibedtDoc)));
	return (CBibedtDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSourceView 


int CSourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndScintilla.Create(_T("Scintilla"), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 10000)) {   
		LPVOID lpMsgBuf;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
		// Write to stderr
		TRACE (_T("%s\n"), (LPCTSTR)lpMsgBuf);
		// Free the buffer.
		LocalFree(lpMsgBuf);
		return -1;
	}
	m_wndScintilla.Init();
	m_wndScintilla.SetDisplaySelection(TRUE);
	m_wndScintilla.SetWrap(SC_WRAP_WORD);
	m_wndScintilla.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_wndScintilla.SetRightEdge(pOp->m_LineLength);
	m_wndScintilla.SendMessage(SCI_USEPOPUP, 0, 0);
	
	return 0;
}

void CSourceView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndScintilla.GetSafeHwnd())
		m_wndScintilla.MoveWindow(0, 0, cx, cy);
}

void CSourceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint) {
	case UR_RECREMOVED:
	case UR_RECADDED:
	case UR_RECEDITED:
	case UR_RECSRCEDITED:
	case UR_OPENFILE:
	case UR_APPENDFILE:
	case UR_SORTED:
	case UR_FLTEDITED:
	case UR_STREDITED:
	case UR_PREEDITED:
	case UR_PASTE:
		if (m_Active) {
			xString* str = xsNew();
			GetDocument()->m_BibFile->GetSource(str);			
			SetText(xsValue(str), TRUE);
			xsDelete(str);
			m_NeedUpdate = FALSE;
		} else
			m_NeedUpdate = TRUE;
		break;
	case UR_NEWFILE:
		if (m_Active) {
			SetText(NULL, FALSE);	
			m_NeedUpdate = FALSE;
		} else
			m_NeedUpdate = TRUE;
		break;
	case UR_SAVINGFILE:
	case UR_SAVEVIEWS:
		if (m_wndScintilla.GetModify()) {
			CString str;
			m_wndScintilla.GetText(str);
			GetDocument()->SetSource(str);
			GetDocument()->UpdateAllViews(this, UR_SRCEDITED, GetDocument()->GetSelected());
			m_wndScintilla.SetModify(FALSE);
			m_NeedUpdate = FALSE;
		}
		break;
	}
}

void CSourceView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCanCut());	
}

void CSourceView::OnEditCut() 
{
	m_wndScintilla.Cut();	
}

void CSourceView::OnEditCopy() 
{
	m_wndScintilla.Copy();	
}

void CSourceView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCanCut());
}

void CSourceView::OnEditPaste() 
{
	m_wndScintilla.Paste();	
}

void CSourceView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCanPaste());
}

void CSourceView::OnEditDelete() 
{
	m_wndScintilla.Clear();	
}

void CSourceView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());	
}

void CSourceView::OnEditSelectAll() 
{
	m_wndScintilla.SelectAll();
}

void CSourceView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());	
}

void CSourceView::OnEditUndo() 
{
	m_wndScintilla.Undo();	
}

void CSourceView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCanUndo());	
}

void CSourceView::OnEditRedo() 
{
	m_wndScintilla.Redo();	
}

void CSourceView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCanRedo());	
}

void CSourceView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Print.OnEndPrinting(pDC, pInfo);
}

void CSourceView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Print.OnBeginPrinting(pDC, pInfo);
}

void CSourceView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Print.OnPrepareDC(pDC, pInfo);
}

void CSourceView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Print.OnPrint(pDC, pInfo);
}

BOOL CSourceView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	m_Print.OnPreparePrinting(pInfo);
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_Print.SetMarginUnit(pOp->m_PrintUnits);
	m_Print.SetMarginLeft(pOp->m_MarginLeft);
	m_Print.SetMarginTop(pOp->m_MarginTop);
	m_Print.SetMarginRight(pOp->m_MarginRight);
	m_Print.SetMarginBottom(pOp->m_MarginBottom);

	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CSourceView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate) {
		if (pActivateView != pDeactiveView) {
			if (m_NeedUpdate) {
				xString* str = xsNew();
				GetDocument()->m_BibFile->GetSource(str);
				SetText(xsValue(str), GetDocument()->GetSelected() != NULL);
				xsDelete(str);
				m_NeedUpdate = FALSE;
			}
			COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
			if (pOp->m_ScrollToSelected && GetDocument()->GetSelected()) {
				m_wndScintilla.GotoItem(GetDocument()->GetSelected()->GetKey());
			}
		}
	} else {
		if (pActivateView != NULL             // Maybe closing
			&& pActivateView != this          // Only if the active view is not this one
			&& m_wndScintilla.GetModify()) {  // Only if the text has changed
			CString txt;
			m_wndScintilla.GetText(txt);
			GetDocument()->SetSource(txt);
			GetDocument()->UpdateAllViews(this, UR_SRCEDITED, GetDocument()->GetSelected());
			m_wndScintilla.SetModify(FALSE);
		}
	}
	m_Active = bActivate;
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

BOOL CSourceView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR *phDR;
	phDR = (NMHDR*)lParam;
	// does notification come from my scintilla window?
	if (phDR != NULL && phDR->hwndFrom == m_wndScintilla.m_hWnd) {
		SCNotification *pMsg = (SCNotification*)lParam;
		switch (phDR->code) {
		case SCN_UPDATEUI:
			m_wndScintilla.UpdateUI();
			break;
		case SCN_MARGINCLICK:
            m_wndScintilla.DoDefaultFolding(pMsg->margin, pMsg->position);
			break;
		case SCN_MODIFIED:
			if (!m_Updating && 
				(BIT_SET(pMsg->modificationType, SC_MOD_INSERTTEXT) ||
				BIT_SET(pMsg->modificationType, SC_MOD_DELETETEXT) ||
				BIT_SET(pMsg->modificationType, SC_MULTISTEPUNDOREDO) ||
				BIT_SET(pMsg->modificationType, SC_LASTSTEPINUNDOREDO) ||
				BIT_SET(pMsg->modificationType, SC_MULTILINEUNDOREDO)))
			{
				GetDocument()->SetModifiedFlag(GetDocument()->IsModified() || m_wndScintilla.GetModify());
			}
			break;
		case SCN_CHARADDED:
			// Replace special characters
			COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
			if (pOp->m_ReplaceSpecialChar && m_wndScintilla.GetCurrentStyle() == SCE_L_DEFAULT) {
				CCodingTeX* coding = ((CBibedtApp*)AfxGetApp())->m_Coding;
				CString enc = coding->GetString((UCHAR)pMsg->ch);
				if (!enc.IsEmpty()) {
					m_wndScintilla.SendMessage(SCI_DELETEBACK);
					m_wndScintilla.SetSelectedText(enc.GetBuffer(enc.GetLength()+1));
				}
			}
			break;
		}
		// No one else will handle that
		return TRUE;
	}

	return CView::OnNotify(wParam, lParam, pResult);
}

void CSourceView::OnPaint() 
{
	Default();
	
	// Kein Aufruf von CView::OnPaint() für Zeichnungsnachrichten
}

void CSourceView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());
}

void CSourceView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());
}

void CSourceView::OnUpdateSearchClearbookmarks(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CSourceView::OnSearchClearbookmarks() 
{
	m_wndScintilla.ClearBookmarks();	
}

void CSourceView::OnSearchNextbookmark() 
{
	if (!m_wndScintilla.FindNextBookmark())
		MessageBeep(MB_ICONEXCLAMATION);
}

void CSourceView::OnUpdateSearchNextbookmark(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CSourceView::OnSearchPreviousbookmark() 
{
	if (!m_wndScintilla.FindPreviousBookmark())
		MessageBeep(MB_ICONEXCLAMATION);
}

void CSourceView::OnUpdateSearchPreviousbookmark(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CSourceView::OnSearchTogglebookmark() 
{
	m_wndScintilla.ToogleBookmark(m_wndScintilla.GetCurrentLine());		
}

void CSourceView::OnUpdateSearchTogglebookmark(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CSourceView::OnSearchFind() 
{
	CFindDialog dlg;
	dlg.m_MatchCase = m_wndScintilla.m_MatchCase;
	dlg.m_RegExpr = m_wndScintilla.m_RegExpr;
	dlg.m_WholeWords = m_wndScintilla.m_WholeWords;
	dlg.m_Backward = m_wndScintilla.m_SearchBackward;
	CString txt = m_wndScintilla.GetSelectedText();
	if (!txt.IsEmpty())
		dlg.m_SearchText = m_wndScintilla.GetSelectedText();
	else if (!m_wndScintilla.m_FindText.IsEmpty())
		dlg.m_SearchText = m_wndScintilla.m_FindText;
	int res = dlg.DoModal();
	if (!dlg.m_SearchText.IsEmpty()) {
		if (res == IDOK) {
			m_wndScintilla.m_MatchCase = dlg.m_MatchCase;
			m_wndScintilla.m_RegExpr = dlg.m_RegExpr;
			m_wndScintilla.m_WholeWords = dlg.m_WholeWords;
			m_wndScintilla.m_SearchBackward = dlg.m_Backward;
			if (!m_wndScintilla.SearchText(dlg.m_SearchText))
				MessageBeep(MB_ICONEXCLAMATION);
		} else if (res = IDC_BUTTON_MARK) {
			m_wndScintilla.m_MatchCase = dlg.m_MatchCase;
			m_wndScintilla.m_RegExpr = dlg.m_RegExpr;
			m_wndScintilla.m_WholeWords = dlg.m_WholeWords;
			m_wndScintilla.m_SearchBackward = dlg.m_Backward;
			if (!m_wndScintilla.MarkMatches(dlg.m_SearchText))
				MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void CSourceView::OnUpdateSearchFind(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());	
}

void CSourceView::OnSearchFindnext() 
{
	if (!m_wndScintilla.FindNext())
		MessageBeep(MB_ICONEXCLAMATION);
}

void CSourceView::OnUpdateSearchFindnext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText() && !m_wndScintilla.m_FindText.IsEmpty());
}

void CSourceView::OnSearchReplace() 
{
	CReplaceDialog dlg;
	dlg.m_MatchCase = m_wndScintilla.m_MatchCase;
	dlg.m_RegExpr = m_wndScintilla.m_RegExpr;
	dlg.m_WholeWords = m_wndScintilla.m_WholeWords;
	dlg.m_SearchText = m_wndScintilla.GetSelectedText();
	dlg.SetEditor(&m_wndScintilla);
	if (dlg.DoModal() == IDOK) {
		// Nothing to do here
	}
}

void CSourceView::OnUpdateSearchReplace(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());	
}

void CSourceView::OnUpdateRecordFirst(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CSourceView::OnUpdateRecordPrevious(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CSourceView::OnUpdateRecordNext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CSourceView::OnUpdateRecordLast(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CSourceView::SetText(LPCSTR txt, BOOL maintainpos)
{
	m_Updating = TRUE;
	long curpos;
	int curline;
	if (maintainpos) {
		curpos = m_wndScintilla.GetCurrentPosition();
		curline = m_wndScintilla.GetFirstVisibleLine();
	}
	m_wndScintilla.SetText(txt);
	m_wndScintilla.Colourise(0);
	m_wndScintilla.FoldItem(STR_FILTER);		
	if (maintainpos) {
		m_wndScintilla.Scoll(0, curline);
		m_wndScintilla.GotoPosition(curpos);
	}
	m_wndScintilla.SetModify(FALSE);
	m_Updating = FALSE;
}

void CSourceView::OnUpdateSearchGotorecord(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetSelected() != NULL);
}

void CSourceView::OnSearchGotorecord() 
{
	m_wndScintilla.GotoItem(GetDocument()->GetSelected()->GetKey());
}

void CSourceView::OnFilePrintPreview() 
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.

	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	// The the pane to hide
	CMainFrame *mf = (CMainFrame*)AfxGetApp()->GetMainWnd();
	TVisualObject *vo = mf->m_Framework.GetActivePane();
	CWnd *parent = vo->GetParentWnd();
	pState->nIDMainPane = parent->GetDlgCtrlID();

	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.

	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this,
							RUNTIME_CLASS(CPreviewView), pState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case

		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
	}
}

void CSourceView::OnFilePrint() 
{
	CView::OnFilePrint();	
}

void CSourceView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	m_Print.SetScintilla(&m_wndScintilla);
	m_Print.SetView(this);
}

void CSourceView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu* pPopup = m_PopupMenu.GetSubMenu(0);
	// Update Menuitems
	AfxGetMainWnd()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopup->m_hMenu, MAKELONG(0, FALSE));
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CSourceView::OnUpdateSourceviewEdititem(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCurrentStyle() == SCE_BIB_KEY);
}

void CSourceView::OnSourceviewEdititem() 
{
	CString key = m_wndScintilla.GetCurrentKey();
	if (!key.IsEmpty()) {
		if (key.CompareNoCase(STR_FILTER) == 0) {
			// It is the filter item -> show filter dialog
			GetDocument()->EditFilter();
		} else {
			// It is another item -> switch to record view
			CBibItem *bib = GetDocument()->m_BibFile->Find(key);
			if (bib) {
				GetDocument()->SetSelected(bib);
				GetDocument()->UpdateAllViews(this, UR_SELECTED, bib);
				GetDocument()->ActivateView(VIEW_RECORD);
			} else
				MessageBeep(MB_ICONEXCLAMATION);
		}
	} else
		MessageBeep(MB_ICONEXCLAMATION);
}

void CSourceView::OnPopupCopykey() 
{
	CString key = m_wndScintilla.GetCurrentKey();
	if (!key.IsEmpty()) {
		ClipBrdPutData(this, key, CB_TEXT, TRUE);
	} else
		MessageBeep(MB_ICONEXCLAMATION);
}

void CSourceView::OnUpdatePopupCopykey(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetCurrentStyle() == SCE_BIB_KEY);
}

void CSourceView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// Tell Scintilla that is has the focus, it'll show then the Caret
	m_wndScintilla.SetFocus();	
}

void CSourceView::OnViewFoldall() 
{
	m_wndScintilla.FoldAll();
}

void CSourceView::OnUpdateViewFoldall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());
}

void CSourceView::OnViewExpandall() 
{
	m_wndScintilla.ExpandAll();
}

void CSourceView::OnUpdateViewExpandall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndScintilla.GetHasText());
}

BOOL CSourceView::GotoItem(CString key)
{
	return m_wndScintilla.GotoItem(key);
}