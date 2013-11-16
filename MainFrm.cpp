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

  $Id: MainFrm.cpp,v 1.54 2006/07/29 11:33:14 stievie Exp $
*/

// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "bibedt.h"

#include "MainFrm.h"
#include "ListViewPrint.h"
#include "Options.h"
#include "bibedtDoc.h"
#include "bibedtView.h"
#include "bibedtView.h"
#include "SourceView.h"
#include "BibitemView.h"
#include "HTMLView.h"
#include "Field.h"
#include "BibItem.h"
#include "xString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_RECCOUNT, OnUpdateKeyIndicator)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_HELP_CHANGELOG, OnHelpChangelog)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBARS_FILTER, OnUpdateViewToolbarsFilter)
	ON_COMMAND(ID_VIEW_TOOLBARS_FILTER, OnViewToolbarsFilter)
	ON_COMMAND(ID_VIEW_TOOLBARS_QUICKSEARCH, OnViewToolbarsQuicksearch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBARS_QUICKSEARCH, OnUpdateViewToolbarsQuicksearch)
	ON_COMMAND(ID_HELP_MANUAL, OnHelpManual)
	ON_COMMAND(ID_VIEW_TOOLBARS_CUSTOMIZE, OnViewToolbarsCustomize)
	ON_COMMAND(ID_VIEW_LISTVIEW, OnViewListview)
	ON_COMMAND(ID_VIEW_SOURCEVIEW, OnViewSourceview)
	ON_COMMAND(ID_VIEW_RECORD, OnViewRecord)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RECORD, OnUpdateViewRecord)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LISTVIEW, OnUpdateViewListview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SOURCEVIEW, OnUpdateViewSourceview)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SELCOUNT, OnUpdateKeyIndicator)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TYPE, OnUpdateKeyIndicator)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOGGLEQUICKSEARCH, OnUpdateViewResetquicksearch)
	ON_COMMAND(ID_VIEW_TOGGLEQUICKSEARCH, OnViewResetquicksearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_RECCOUNT,	// Record count
	ID_INDICATOR_SELCOUNT,	// Selected count
	ID_INDICATOR_TYPE,		// Item type
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create Toolbar\n");
		return -1;      // Fehler bei Erstellung
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create Statusbar\n");
		return -1;      // Fehler bei Erstellung
	}

	if (!m_wndFilter.Create(this, IDD_DIALOGBAR_FILTER_TEMPLATE, WS_CHILD | WS_VISIBLE 
		| CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER, IDD_DIALOGBAR_FILTER))
	{
		TRACE0("Failed to create Dialogbar\n");
		return -1;      // Fehler bei Erstellung
	}

	if (!m_wndQuickSearch.Create(this, IDD_DIALOGBAR_QUICKSEARCH_TEMPLATE, WS_CHILD | WS_VISIBLE 
		| CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER, IDD_DIALOGBAR_QUICKSEARCH))
	{
		TRACE0("Failed to create Dialogbar\n");
		return -1;      // Fehler bei Erstellung
	}
	
	FrameEnableDocking(this, CBRS_ALIGN_ANY);
	m_wndToolBar.SetWindowText(AfxLoadString(IDS_STRING_TBCAPTION_STD));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.SetToolBarInfoForCustomization();
	m_wndToolBar.RestoreState();
	//Delete the button which do not need to shown initially.
	m_wndToolBar.GetToolBarCtrl().DeleteButton(m_wndToolBar.CommandToIndex(ID_RECORD_GENERATEKEY));
	m_wndToolBar.GetToolBarCtrl().DeleteButton(m_wndToolBar.CommandToIndex(ID_SEARCH_REPLACE));
	m_wndToolBar.GetToolBarCtrl().DeleteButton(m_wndToolBar.CommandToIndex(ID_RECORD_SORTED));
	// Mark the default state for reset
	m_wndToolBar.MarkDefaultState();

	m_wndFilter.SetWindowText(AfxLoadString(IDS_STRING_FILTERCAPTION));
	m_wndFilter.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	m_wndQuickSearch.SetWindowText(AfxLoadString(IDS_STRING_QSCAPTION));
	m_wndQuickSearch.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndFilter);
	DockControlBar(&m_wndQuickSearch);

	try {
		LoadBarState(AfxGetApp()->m_pszProfileName);
	} catch (...) {
		// Throws an exception when toolbars have changed
		// just ignore it
	}

	UpdateFilter(NULL);

	CBibedtApp * pApp = (CBibedtApp*)AfxGetApp();
	if (pApp->m_Options->m_WindowPlacement.rcNormalPosition.bottom && 
		pApp->m_Options->m_WindowPlacement.rcNormalPosition.right)
		MoveWindow(&pApp->m_Options->m_WindowPlacement.rcNormalPosition, FALSE);

	return 0;
}

void CMainFrame::OnClose() 
{
	SaveBarState(AfxGetApp()->m_pszProfileName);
	m_wndToolBar.SaveState();

	CBibedtApp * pApp = (CBibedtApp*)AfxGetApp();
	// Save window placement
	GetWindowPlacement(&pApp->m_Options->m_WindowPlacement);
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnUpdateKeyIndicator(CCmdUI* pCmdUI)
{
	CString s;
	switch (pCmdUI->m_nID) {
	case ID_INDICATOR_RECCOUNT:
		{
			CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
			if (doc) {
				s.Format(ID_INDICATOR_RECCOUNT, doc->m_BibFile->GetCount());
				pCmdUI->SetText(s);
			}
			break;
		}
	case ID_INDICATOR_TYPE:
		{
			CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
			if (doc) {
				CBibItem *item = doc->GetSelected();
				if (item) {
					s.Format(ID_INDICATOR_TYPE, item->GetType());
					pCmdUI->SetText(s);
				} else 
					pCmdUI->SetText(NULL);
			}
			break;
		}
	case ID_INDICATOR_SELCOUNT:
		{
			// could also be CPreviewView
			CBibedtView *view = dynamic_cast<CBibedtView*>(GetActiveView());
			if (view) {
				CListCtrl *lc = &view->GetListCtrl();
				ASSERT(lc);
				s.Format(ID_INDICATOR_SELCOUNT, lc->GetSelectedCount(), lc->GetItemCount());
				pCmdUI->SetText(s);
			}
			break;
		}
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

void CMainFrame::OnFilePageSetup() 
{
	// TODO: Page Setup Dialog instead of Print Setup dialog
	CPageSetupDialog dlg(PSD_MARGINS | PSD_DEFAULTMINMARGINS, this);

	if (dlg.DoModal() == IDOK) {
	}
}

void CMainFrame::OnHelpManual() 
{
	CString manual = COptions::GetManualFile();
	if (manual.IsEmpty() || (DWORD)ShellExecute(0, _T("open"), manual, NULL, COptions::GetAppPath(), SW_NORMAL) <= HINSTANCE_ERROR) {
		if (MessageBox(AfxLoadString(IDS_STRING_MANUALNOTFOUND), NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
			ShellExecute(0, _T("open"), MANUAL_URL, NULL, NULL, SW_NORMAL);
	}
}

void CMainFrame::OnHelpChangelog() 
{
	ShellExecute(0, _T("open"), COptions::GetChangelogFile(), NULL, COptions::GetAppPath(), SW_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	TVisualObject *pTab = new TVisualObject(VIEW_TAB, _T(""), pContext, RUNTIME_CLASS(TTabWnd), TVisualObject::TOS_TABTOP);

	// 2 rows, 1 col
	TVisualObject *pSplitter = new TVisualObject(VIEW_SPLITTER, _T("List"), 2, 1, pContext);
	int ph = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ListViewHeight"), 200);
	TVisualObject *ViewList = new TVisualObject(VIEW_LIST, 0, 0, pContext, RUNTIME_CLASS(CBibedtView), CSize(0, ph));

	TVisualObject *ViewPreview = new TVisualObject(VIEW_PREVIEW, 1, 0, pContext, RUNTIME_CLASS(CHTMLView), CSize(0, 50));
//	TVisualObject *ViewPreview = new TVisualObject(VIEW_PREVIEW, 1, 0, pContext, RUNTIME_CLASS(CPreView), CSize(0, 50));

	TVisualObject *ViewSource = new TVisualObject(VIEW_SOURCE, _T("Source"), pContext, RUNTIME_CLASS(CSourceView));
	TVisualObject *ViewItem = new TVisualObject(VIEW_RECORD, _T("Record"), pContext, RUNTIME_CLASS(CBibitemView));

	m_Framework.Add(pTab);
	m_Framework.Add(pTab, pSplitter);
	m_Framework.Add(pSplitter, ViewList);
	m_Framework.Add(pSplitter, ViewPreview);
	m_Framework.Add(pTab, ViewSource);
	m_Framework.Add(pTab, ViewItem);
	m_Framework.Create(this);

	return TRUE;
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	m_Framework.Destroy();	
}

BOOL CMainFrame::ActivateView(DWORD dwID)
{
	TVisualObject * v = m_Framework.Get(dwID);
	if (v && v->GetSafeWnd()) {
		m_Framework.SetActivePane(v);
		return TRUE;
	}

	return FALSE;
}

void CMainFrame::EnableView(DWORD dwID, BOOL enable)
{
	TVisualObject * v = m_Framework.Get(dwID);
	if (v && v->GetSafeWnd()) {
		BOOL e;
		m_Framework.IsEnabled(v, e);
		if (e != enable) {
			// Change only if it is not how it should be.
			if (!enable && m_Framework.GetActivePane() == v)
				// if it should be disabled but is active activate the list view.
				ActivateView(VIEW_LIST);
			m_Framework.Enable(v, enable);
			m_Framework.EnableTab(v, enable);
		}
	}
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
		if (doc)
			// There is already a selected item, file loaded from the commandline
			EnableView(VIEW_RECORD, doc->GetSelected() != NULL);
		else
			// No item is selected now -> disable record view.
			EnableView(VIEW_RECORD, FALSE);

		// Set focus to active pane	-> not the filter combo will have the focus
		FocusActiveView();
	}
}

void CMainFrame::OnUpdateViewToolbarsFilter(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndFilter.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnViewToolbarsFilter() 
{
	ShowControlBar(&m_wndFilter, (m_wndFilter.GetStyle() & WS_VISIBLE) == 0, FALSE);
}

void CMainFrame::SelectFilter(CField *filter)
{
	CWnd *cbo = m_wndFilter.GetDlgItem(IDC_COMBO_FILTER);
	int c = cbo->SendMessage(CB_GETCOUNT, 0, 0);
	for (int i = 0; i < c; i++) {
		LONG res = cbo->SendMessage(CB_GETITEMDATA, i, 0);
		if (res != CB_ERR) {
			cbo->SendMessage(CB_SETCURSEL, i, 0);
			break;
		}
	}
}

void CMainFrame::UpdateFilter(CBibItem *filter)
{
	// Is this the only way???
	CWnd *cbo = m_wndFilter.GetDlgItem(IDC_COMBO_FILTER);
	cbo->SendMessage(CB_RESETCONTENT, 0, 0);
	int i = cbo->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)AfxLoadString(IDS_STRING_NOFILTER));
	AppendFilter(filter);
	// Append default filter
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	if (pApp->m_BibDef && pApp->m_BibDef->GetFilter())
		AppendFilter(pApp->m_BibDef->GetFilter());
	cbo->SendMessage(CB_SETCURSEL, 0, 0);
}

void CMainFrame::AppendFilter(CBibItem *filter)
{
	if (filter) {
		CWnd *cbo = m_wndFilter.GetDlgItem(IDC_COMBO_FILTER);
		POSITION p = filter->GetHeadPosition();
		while (p) {
			CField *f = (CField*)filter->GetNext(p);
			ASSERT(f);
			int i = cbo->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)f->GetName());
			cbo->SendMessage(CB_SETITEMDATA, i, (LPARAM)f); 
		}
	}
}

void CMainFrame::SetQuicksearchText(CString str)
{
	CWnd *edit = m_wndQuickSearch.GetDlgItem(IDC_EDIT_QUICKSEARCH);
	edit->SetWindowText(str);
}

void CMainFrame::DoQuicksearch()
{
	CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
	if (doc) {
		CWnd *edit = m_wndQuickSearch.GetDlgItem(IDC_EDIT_QUICKSEARCH);
		CWnd *qscbo = m_wndQuickSearch.GetDlgItem(IDC_COMBO_QS_FIELD);
		CString txt;
		edit->GetWindowText(txt);
		if (!txt.IsEmpty()) {
			CString f;
			if (qscbo) {
				qscbo->GetWindowText(f);
			}
			doc->DoQuickSearch(txt, f, FALSE);
		} else
			doc->DoQuickSearch(_T(""), _T(""), FALSE);
	}
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (!m_wndFilter || !m_wndQuickSearch)
		return CFrameWnd::OnCommand(wParam, lParam);

	CWnd *cbo = m_wndFilter.GetDlgItem(IDC_COMBO_FILTER);
	CWnd *edit = m_wndQuickSearch.GetDlgItem(IDC_EDIT_QUICKSEARCH);
	CWnd *qscbo = m_wndQuickSearch.GetDlgItem(IDC_COMBO_QS_FIELD);
	int i;

	if (lParam == (DWORD)cbo->m_hWnd) {
		// Filter combo
		switch (HIWORD(wParam)) {
		case CBN_SELCHANGE:
			CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
			if (doc) {
				int cursel = cbo->SendMessage(CB_GETCURSEL, 0, 0);
				CField *filter = (CField*)cbo->SendMessage(CB_GETITEMDATA, cursel, 0);
				doc->SetFilter(filter);
				FocusActiveView();
			}
			break;
		}
	} else if (lParam == (DWORD)edit->m_hWnd) {
		// Quicksearch
		switch (HIWORD(wParam)) {
		case EN_CHANGE:
			DoQuicksearch();
			break;
		case EN_SETFOCUS:
			// Got focus -> select all. Why doesn't is select all???
			edit->SendMessage(EM_SETSEL, 0, -1);
			break;
		}
	} else if (lParam == (DWORD)qscbo->m_hWnd) {
		switch (HIWORD(wParam)) {
		case CBN_SELCHANGE:
		case CBN_EDITCHANGE:
			// Repeat quicksearch with new field(s)
			i = qscbo->SendMessage(CB_GETCURSEL, 0, 0);
			if (i != -1) {
				int len = qscbo->SendMessage(CB_GETLBTEXTLEN, i, 0);
				if (i > 0) {
					xString* str = xsNew();
					xsResize(str, len+1);
					qscbo->SendMessage(CB_GETLBTEXT, i, (LPARAM)xsValue(str));
					if (!xsIsEmpty(str)) {
						qscbo->SetWindowText(xsValue(str));
						DoQuicksearch();
					}
					xsDelete(str);
				}
			}
			break;
		}
	}
	
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::FocusActiveView()
{
	// Set focus to active pane	-> not the filter combo will have the focus
	TVisualObject * v = m_Framework.GetActivePane();
	if (v && v->GetSafeWnd())
		v->GetSafeWnd()->SetFocus();
}

void CMainFrame::OnViewToolbarsQuicksearch() 
{
	ShowControlBar(&m_wndQuickSearch, (m_wndQuickSearch.GetStyle() & WS_VISIBLE) == 0, FALSE);
}

void CMainFrame::OnUpdateViewToolbarsQuicksearch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndQuickSearch.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::ResetQuicksearch()
{
	if (!m_wndQuickSearch)
		return;
	CWnd* edit = m_wndQuickSearch.GetDlgItem(IDC_EDIT_QUICKSEARCH);
	ASSERT(edit);
	edit->SetWindowText(NULL);
}

CString CMainFrame::GetQuicksearchFields()
{
	CWnd* edit = m_wndQuickSearch.GetDlgItem(IDC_COMBO_QS_FIELD);
	ASSERT(edit);
	CString res;
	edit->GetWindowText(res);
	return res;
}

void CMainFrame::UpdateQuicksearchFields(CStringList *lst)
{
	if (!m_wndFilter)
		return;
	CWnd *cbo = m_wndQuickSearch.GetDlgItem(IDC_COMBO_QS_FIELD);
	if (!cbo)
		return;
	cbo->SendMessage(CB_RESETCONTENT, 0, 0);
	CBibedtApp * pApp = (CBibedtApp*)AfxGetApp();
	// Add [All Fields]
	cbo->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)AfxLoadString(IDS_STRING_ALLFIELDS));
	// Add default fields
	cbo->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)pApp->m_Options->m_QuickSearchFields);

	if (lst) {
		POSITION p = lst->GetHeadPosition();
		while (p) {
			cbo->SendMessage(CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)lst->GetNext(p));
		}
	}
	// Select the default fields (from Options) has always index 1
	cbo->SendMessage(CB_SETCURSEL, 1, 0);
}

void CMainFrame::OnViewToolbarsCustomize() 
{
	m_wndToolBar.Customize();
}

void CMainFrame::OnViewListview() 
{
	ActivateView(VIEW_LIST);	
}

void CMainFrame::OnViewSourceview() 
{
	ActivateView(VIEW_SOURCE);	
}

void CMainFrame::OnViewRecord() 
{
	ActivateView(VIEW_RECORD);	
}

void CMainFrame::OnUpdateViewRecord(CCmdUI* pCmdUI) 
{
	TVisualObject * v = m_Framework.Get(VIEW_RECORD);
	if (v && v->GetSafeWnd()) {
		BOOL e;
		m_Framework.IsEnabled(v, e);
		pCmdUI->Enable(e);
		pCmdUI->SetCheck(m_Framework.GetActivePane() == v);
	} else {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateViewListview(CCmdUI* pCmdUI) 
{
	TVisualObject * v = m_Framework.Get(VIEW_LIST);
	if (v && v->GetSafeWnd()) {
		pCmdUI->SetCheck(m_Framework.GetActivePane() == v);
	} else {
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateViewSourceview(CCmdUI* pCmdUI) 
{
	TVisualObject * v = m_Framework.Get(VIEW_SOURCE);
	if (v && v->GetSafeWnd()) {
		pCmdUI->SetCheck(m_Framework.GetActivePane() == v);
	} else {
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateViewResetquicksearch(CCmdUI* pCmdUI) 
{
	CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
	if (doc) {
		pCmdUI->Enable(TRUE);
	} else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnViewResetquicksearch() 
{
	CBibedtDoc *doc = dynamic_cast<CBibedtDoc*>(GetActiveDocument());
	if (doc) {
		if (doc->m_QuicksearchString.IsEmpty())
			DoQuicksearch();
		else
			doc->DoQuickSearch(_T(""), _T(""), FALSE);
	}
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) {
	case WM_BE_LANUAGE_CHANGED:
		SendMessageToDescendants(message, 0, 0, TRUE, TRUE);
		break;
	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
}
