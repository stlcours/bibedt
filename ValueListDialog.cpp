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

  $Id: ValueListDialog.cpp,v 1.5 2006/08/14 08:08:06 stievie Exp $
*/

// ValueListDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "MainFrm.h"
#include "BibedtView.h"
#include "ValueListDialog.h"
#include "Globals.h"
#include "StringListEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CValueListDialog 


CValueListDialog::CValueListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CValueListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValueListDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	VERIFY(m_PopupMenu.LoadMenu(IDR_MENU_VALUELIST));
	CDialog::Create(IDD_DIALOG_VALUELIST, pParent);
}


void CValueListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValueListDialog)
	DDX_Control(pDX, IDC_LIST_VALUES, m_lvValues);
	DDX_Control(pDX, IDC_COMBO_FIELD, m_cboField);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CValueListDialog, CDialog)
	//{{AFX_MSG_MAP(CValueListDialog)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, OnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_FIELD, OnSelchangeComboField)
	ON_CBN_EDITCHANGE(IDC_COMBO_FIELD, OnEditchangeComboField)
	ON_COMMAND(ID_POPUP_SELECT, OnPopupSelect)
	ON_UPDATE_COMMAND_UI(ID_POPUP_SELECT, OnUpdatePopupSelect)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VALUES, OnDblclkListValues)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CValueListDialog)
	ANCHOR_MAP_ENTRY(IDC_REFRESH, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_COMBO_FIELD, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_VALUES, ANF_TOP | ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CValueListDialog 

BOOL CValueListDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);
	DWORD extst = m_lvValues.GetExtendedStyle();
	m_lvValues.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);
	m_lvValues.InsertColumn(0, AfxLoadString(IDS_COLUMNVALUE_TEXT)); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CValueListDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);
	if (::IsWindow(m_lvValues.m_hWnd)) {
		m_lvValues.GetClientRect(&r);
		m_lvValues.SetColumnWidth(0, r.Width() - 20);
	}
}

void CValueListDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("ValuelistDialog"), wp);	
}

void CValueListDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("ValuelistDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);
		if (::IsWindow(m_lvValues.m_hWnd)) {
			CRect r;
			m_lvValues.GetClientRect(&r);
			m_lvValues.SetColumnWidth(0, r.Width() - 20);
		}

		Refresh();
	}	
}

void CValueListDialog::Refresh()
{
	CWaitCursor wait;
	m_lvValues.DeleteAllItems();
	CStringListEx lst;
	ASSERT(m_BibList);
	m_cboField.GetWindowText(m_CurField);
	POSITION p;
	CString val;
	if (!m_CurField.IsEmpty()) {
		m_BibList->GetAllFieldValues(m_CurField, &lst);
		lst.Sort();
		p = lst.GetHeadPosition();
		while (p) {
			val = lst.GetNext(p);
			m_lvValues.InsertItem(m_lvValues.GetItemCount(), val);
		}
	}
	lst.RemoveAll();
	m_cboField.ResetContent();
	m_BibList->GetAllFieldNames(&lst);
	p = lst.GetHeadPosition();
	lst.Sort();
	while (p) {
		val = lst.GetNext(p);
		m_cboField.AddString(val);
	}
	if (!m_CurField.IsEmpty()) {
		if (m_cboField.SelectString(-1, m_CurField) == CB_ERR) {
			int i = m_cboField.InsertString(0, m_CurField);
			m_cboField.SetCurSel(i);
		}
	}
}

void CValueListDialog::OnRefresh() 
{
	Refresh();
}

void CValueListDialog::OnSelchangeComboField() 
{
}

void CValueListDialog::OnEditchangeComboField() 
{
}

void CValueListDialog::OnPopupSelect() 
{
	SelectMatching();
}

void CValueListDialog::OnUpdatePopupSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_lvValues.GetSelectionMark() != -1);
}

void CValueListDialog::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd->GetSafeHwnd() == m_lvValues.GetSafeHwnd()) {
		CMenu* pPopup = m_PopupMenu.GetSubMenu(0);

		// Update Menuitems
//		AfxGetMainWnd()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopup->m_hMenu, MAKELONG(0, FALSE));
//		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CValueListDialog::SelectMatching()
{
	if (m_CurField.IsEmpty() || m_lvValues.GetSelectionMark() == -1)
		return;
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	CBibedtView *view = dynamic_cast<CBibedtView*>(pFrame->GetActiveView());
	if (!view)
		return;
	CListCtrl *lc = &view->GetListCtrl();
	CString val = m_lvValues.GetItemText(m_lvValues.GetSelectionMark(), 0);
	if (val.IsEmpty())
		return;
	int first = -1;
	view->UnselectAll();
	for (int i = 0; i < lc->GetItemCount(); i++) {
		CBibItem *item = (CBibItem*)(lc->GetItemData(i));
		if (item) {
			if (item->IsRegularItem() && item->Matches(val, m_CurField, FALSE, TRUE, TRUE, TRUE)) {
				view->SetSelected(i, TRUE);
				if (first == -1)
					first = i;
			}
		}
	}
	if (first != -1)
		lc->EnsureVisible(first, FALSE);
}

void CValueListDialog::OnDblclkListValues(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SelectMatching();

	*pResult = 0;
}

