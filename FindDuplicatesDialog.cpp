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

  $Id: FindDuplicatesDialog.cpp,v 1.22 2006/06/06 18:52:18 stievie Exp $
*/

// FindDuplicatesDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "FindDuplicatesDialog.h"
#include "BibItem.h"
#include "Field.h"
#include "MainFrm.h"
#include "ProgressDialog.h"
#include "Globals.h"
#include "BibedtView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDuplicatesDialog 


CFindDuplicatesDialog::CFindDuplicatesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDuplicatesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDuplicatesDialog)
	//}}AFX_DATA_INIT
}


void CFindDuplicatesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDuplicatesDialog)
	DDX_Control(pDX, IDC_BUTTON_BOOKMARK, m_BtnBookmark);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_BtnSelect);
	DDX_Control(pDX, IDC_TREE_ITEMS, m_TreeItems);
	DDX_Control(pDX, IDC_SCINCTRL, m_ScintillaCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDuplicatesDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDuplicatesDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ITEMS, OnSelchangedTreeItems)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_ITEMS, OnDblclkTreeItems)
	ON_BN_CLICKED(IDC_BUTTON_BOOKMARK, OnButtonBookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CFindDuplicatesDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_SELECT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_TREE_ITEMS, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_SCINCTRL, ANF_TOP | ANF_BOTTOM | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFindDuplicatesDialog 

void CFindDuplicatesDialog::SetBibList(CBibList *value)
{
	m_BibItems = value;
}

BOOL CFindDuplicatesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);
	
	m_ScintillaCtrl.Init();
	m_ScintillaCtrl.SetWrap(SC_WRAP_WORD);
	m_ScintillaCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_ScintillaCtrl.SetDisplayFolding(FALSE);
	m_ScintillaCtrl.SetDisplayLinenumbers(TRUE);
	m_ScintillaCtrl.SetDisplaySelection(FALSE);
	m_ScintillaCtrl.SetReadOnly(TRUE);
	DWORD col = GetSysColor(COLOR_BTNFACE);
	m_ScintillaCtrl.SetBackground(col);
	m_ScintillaCtrl.SendMessage(SCI_STYLESETBACK, STYLE_BRACELIGHT, BRACE_HIGHLIGHT);
	col = GetSysColor(COLOR_BTNSHADOW);
	m_ScintillaCtrl.SetBackground(STYLE_LINENUMBER, col);

	CWaitCursor wait;
	DoFindDuplicates();
	if (m_DuplicateCount == 0) {
		AfxMessageBox(IDS_STRING_NODUPLICATES, MB_ICONINFORMATION);
		EndDialog(IDOK);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/**
 * Returns the matching field or empty string
 */
CString CFindDuplicatesDialog::GetDuplicateField(CBibItem *bi1, CBibItem *bi2, CStringList *lstfields)
{
	CString mf("");
	CString field;
	POSITION p = lstfields->GetHeadPosition();
	while (p) {
		field = lstfields->GetNext(p);
		CString sstr = bi1->GetFieldValue(field);
		if (bi2->Matches(sstr, field, FALSE, FALSE, m_CaseSens, m_Exact)) {
			if (mf.IsEmpty())
				// only the first
				mf = field;
		} else
			return _T("");
		if (!m_Exact && mf.IsEmpty()) {
			sstr = bi2->GetFieldValue(field);
			if (bi1->Matches(sstr, field, FALSE, FALSE, m_CaseSens, m_Exact)) {
				if (mf.IsEmpty())
					mf = field;
			} else
				return _T("");
		}
	}
	return mf;
}

BOOL CFindDuplicatesDialog::DoFindDuplicates()
{
	CString key;
	CBibItem *bi1;
	CBibItem *bi2;
	int progr = 0;
	POSITION p1 = m_BibItems->GetHeadPosition();
	POSITION p2 = NULL;
	HTREEITEM root = 0;
	HTREEITEM child = 0;
	BOOL found = FALSE;
	CProgressDialog progress;
	progress.m_Min = 0;
	progress.m_Max = m_BibItems->GetCount();
	progress.ShowWindow(SW_NORMAL);
	progress.UpdateWindow();
	BOOL succ = TRUE;
	m_DuplicateCount = 0;
	CStringList fields;
	SplitSepString(m_Fields, &fields);

	for (;;) {
		progress.SetValue(progr++);
		if (progress.m_Cancel) {
			succ = FALSE;
			break;
		}
		if (p1 == NULL)
			break;
		bi1 = (CBibItem*)m_BibItems->GetNext(p1);
		if (!bi1->IsVisible() || bi1->IsType(STR_COMMENT) || bi1->IsType(STR_PREAMBLE))
			continue;
		p2 = p1;
		for (;;) {
			if (!p2)
				break;
			bi2 = (CBibItem*)m_BibItems->GetNext(p2);
			if (!bi2->IsVisible() || bi2->IsType(STR_COMMENT) || bi2->IsType(STR_PREAMBLE))
				continue;
			if (bi1 != bi2) {
				CString mf = GetDuplicateField(bi1, bi2, &fields);
				if (!mf.IsEmpty()) {
					CString mfv = bi1->GetFieldValue(mf);
					root = FindItem(mfv);
					if (root == 0) {
						root = m_TreeItems.InsertItem(mfv, -1, -1);
						if (!bi1->m_Data) {
							child = m_TreeItems.InsertItem(bi1->GetPrettyString(), -1, -1, root);
							m_TreeItems.SetItemData(child, (DWORD)bi1);
							bi1->m_Data = TRUE;
						}
						m_DuplicateCount++;
						found = TRUE;
					}
					if (!bi2->m_Data) {
						child = m_TreeItems.InsertItem(bi2->GetPrettyString(), -1, -1, root);
						m_TreeItems.SetItemData(child, (DWORD)bi2);
						bi2->m_Data = 1;
					}
				}
			}
		}
		if (root)
			m_TreeItems.Expand(root, TVE_EXPAND);
	}
	progress.DestroyWindow();
	m_TreeItems.SendMessage(WM_VSCROLL, MAKEWPARAM(SB_TOP, 0), 0);
	return succ;
}

void CFindDuplicatesDialog::OnSelchangedTreeItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CBibItem *item = (CBibItem*)m_TreeItems.GetItemData(pNMTreeView->itemNew.hItem);
	if (item) {
		CString src;
		src = item->GetSource();
		m_ScintillaCtrl.SetText(src);
	} else {
		m_ScintillaCtrl.SetText(NULL);
	}
	m_BtnSelect.EnableWindow();
	m_BtnBookmark.EnableWindow();

	*pResult = 0;
}

void CFindDuplicatesDialog::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("DuplicatesDialog"), wp);

	POSITION p = m_BibItems->GetHeadPosition();
	CBibItem *bi;
	while (p) {
		bi = (CBibItem*)m_BibItems->GetNext(p);
		bi->m_Data = FALSE;
	}

	CDialog::OnDestroy();
}

void CFindDuplicatesDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("DuplicatesDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);

		CString cap;
		cap.Format(IDS_STRING_DUPLITEMS, m_DuplicateCount);
		SetWindowText(cap);
		m_TreeItems.SetFocus();

	}
}

HTREEITEM CFindDuplicatesDialog::FindItem(CString key)
{
	HTREEITEM hItem = m_TreeItems.GetRootItem();
	while (hItem) {
		CString text = m_TreeItems.GetItemText(hItem);
		if (key.CompareNoCase(text) == 0) {
			return hItem;
		}
		hItem = m_TreeItems.GetNextSiblingItem(hItem);
	}
	return 0;
}

void CFindDuplicatesDialog::SelectOrBookmark(BOOL bookmark)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	CBibedtView *view = dynamic_cast<CBibedtView*>(pFrame->GetActiveView());
	if (!view)
		return;
	CListCtrl *lc = &view->GetListCtrl();
	HTREEITEM hCurSel = m_TreeItems.GetNextItem(TVI_ROOT, TVGN_CARET);
	HTREEITEM hParent = m_TreeItems.GetParentItem(hCurSel);

	view->UnselectAll();
	if (hParent) {
		// Child
		CBibItem *item = dynamic_cast<CBibItem*>((CObject*)m_TreeItems.GetItemData(hCurSel));
		if (!item)
			return;
		for (int i = 0; i < lc->GetItemCount(); i++) {
			CBibItem *citem = (CBibItem*)lc->GetItemData(i);
			if (item == citem) {
				if (bookmark)
					view->SetBookmark(i, TRUE);
				else
					view->SetSelected(i, TRUE);
				lc->EnsureVisible(i, FALSE);
				break;
			}
		}
	} else {
		// Parent
		hCurSel = m_TreeItems.GetChildItem(hCurSel);
		while (hCurSel != NULL) {
			CBibItem *item = dynamic_cast<CBibItem*>((CObject*)m_TreeItems.GetItemData(hCurSel));
			if (item) {
				for (int i = 0; i < lc->GetItemCount(); i++) {
					CBibItem *citem = (CBibItem*)lc->GetItemData(i);
					if (item == citem) {
						if (bookmark)
							view->SetBookmark(i, TRUE);
						else
							view->SetSelected(i, TRUE);
						lc->EnsureVisible(i, FALSE);
						break;
					}
				}
			}
			hCurSel = m_TreeItems.GetNextItem(hCurSel, TVGN_NEXT);
		}
	}
}

void CFindDuplicatesDialog::OnButtonSelect() 
{
	SelectOrBookmark(FALSE);
}

BOOL CFindDuplicatesDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR *phDR;
	phDR = (NMHDR*)lParam;
	// does notification come from my scintilla window?
	if (phDR != NULL && phDR->hwndFrom == m_ScintillaCtrl.m_hWnd) {
		SCNotification *pMsg = (SCNotification*)lParam;
		switch (phDR->code) {
		case SCN_UPDATEUI:
			m_ScintillaCtrl.UpdateUI();
			break;
		}
		return TRUE;
	}
	return CWnd::OnNotify(wParam, lParam, pResult);
}

void CFindDuplicatesDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);
}

void CFindDuplicatesDialog::OnDblclkTreeItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnButtonSelect();
	CDialog::EndDialog(IDOK);

	*pResult = 0;
}

void CFindDuplicatesDialog::OnButtonBookmark() 
{
	SelectOrBookmark(TRUE);	
}
