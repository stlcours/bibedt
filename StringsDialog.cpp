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

  $Id: StringsDialog.cpp,v 1.21 2006/08/10 18:51:15 stievie Exp $
*/

// StringsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "StringsDialog.h"
#include "BibList.h"
#include "SourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CStringsDialog 


CStringsDialog::CStringsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStringsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStringsDialog)
	//}}AFX_DATA_INIT
	m_TmpList = new CBibList();
	m_Selected = -1;
}

CStringsDialog::~CStringsDialog()
{
	delete m_TmpList;
}

void CStringsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStringsDialog)
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_BtnApply);
	DDX_Control(pDX, IDC_BUTTON_UNDO, m_BtnUndo);
	DDX_Control(pDX, IDC_BUTTON_SOURCE, m_BtnSource);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_BtnRemove);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_BtnEdit);
	DDX_Control(pDX, IDC_LIST_STRINGS, m_ListStrings);
	DDX_Control(pDX, IDC_SCINCTRL, m_ScintillaCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStringsDialog, CDialog)
	//{{AFX_MSG_MAP(CStringsDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STRINGS, OnClickListStrings)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_STRINGS, OnDeleteitemListStrings)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_STRINGS, OnEndlabeleditListStrings)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_STRINGS, OnInsertitemListStrings)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, OnButtonSource)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STRINGS, OnDblclkListStrings)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnButtonUndo)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_STRINGS, OnKeydownListStrings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CStringsDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_SOURCE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_ADD, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_EDIT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_REMOVE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_APPLY, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_UNDO, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_STRINGS, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_SCINCTRL, ANF_TOP | ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CStringsDialog 

void CStringsDialog::SetBibList(CBibList *value)
{
	m_BibList = value;
	POSITION p = value->GetHeadPosition();
	while (p) {
		CBibItem *item = (CBibItem*)value->GetNext(p);
		ASSERT(item);
		if (item->IsType(STR_STRING)) {
			m_TmpList->New()->Assign(item);
		}
	}
}

BOOL CStringsDialog::OnInitDialog() 
{
	if (!m_BibList)
		return FALSE;

	CDialog::OnInitDialog();
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);

	m_ScintillaCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_ScintillaCtrl.Init();
	m_ScintillaCtrl.SetDisplayFolding(FALSE);
	m_ScintillaCtrl.SetDisplayLinenumbers(FALSE);
	m_ScintillaCtrl.SetDisplaySelection(TRUE);
	m_ScintillaCtrl.SetLexer(SCLEX_NULL);

	CString col;
	col.LoadString(IDS_STRING_NAME);
	m_ListStrings.InsertColumn(0, col, LVCFMT_LEFT, 200);
	col.LoadString(IDS_STRING_VALUE);
	m_ListStrings.InsertColumn(1, col, LVCFMT_LEFT, 400);	
	DWORD extst = m_ListStrings.GetExtendedStyle();
	m_ListStrings.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);

	Populate();
	Update();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CStringsDialog::OnClickListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	Apply();
	m_Selected = pNMListView->iItem;
	Update();
	
	*pResult = 0;
}

void CStringsDialog::OnButtonAdd() 
{
	m_Selected = m_ListStrings.InsertItem(m_ListStrings.GetItemCount(), STR_NEWSTRING, -1);
	CBibItem *item = m_TmpList->New();
	item->SetType(STR_STRING);
	item->SetKey(STR_NEWSTRING);
	m_ListStrings.SetItemData(m_Selected, (DWORD)item);
	m_ListStrings.EnsureVisible(m_Selected, FALSE);
	UINT is = m_ListStrings.GetItemState(m_Selected, LVIF_STATE);
	m_ListStrings.SetItemState(m_Selected, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_ListStrings.SetFocus();
	Update();

	CEdit* edt = m_ListStrings.EditLabel(m_Selected);
}

void CStringsDialog::OnButtonEdit() 
{
	if (m_Selected == -1)
		return;
	m_ListStrings.EnsureVisible(m_Selected, FALSE);
	UINT is = m_ListStrings.GetItemState(m_Selected, LVIF_STATE);
	m_ListStrings.SetItemState(m_Selected, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_ListStrings.SetFocus();
	CEdit* edt = m_ListStrings.EditLabel(m_Selected);
}

void CStringsDialog::OnButtonRemove() 
{
	if (m_Selected == -1)
		return;
	CBibItem *item = (CBibItem*)m_ListStrings.GetItemData(m_Selected);
	ASSERT(item);
	m_TmpList->Delete(item);
	m_ListStrings.DeleteItem(m_Selected);
	m_Selected = -1;
	Update();
}

void CStringsDialog::Populate()
{
	m_Updating = TRUE;
	m_ListStrings.DeleteAllItems();
	POSITION h = m_TmpList->GetHeadPosition();
	int i = 0;
	while (h) {
		CBibItem* bi = (CBibItem*)m_TmpList->GetNext(h);
		if (bi) {
			if (bi->IsType(STR_STRING)) {
				i = m_ListStrings.InsertItem(i+1, bi->GetKey(), -1);
				m_ListStrings.SetItemText(i, 1, BeautifyValue(bi->GetValue()));
				m_ListStrings.SetItemData(i, (DWORD)bi);
			}
		}
	}
	m_Updating = FALSE;
}

void CStringsDialog::OnDeleteitemListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_Updating) {
	}

	*pResult = 0;
}

void CStringsDialog::OnEndlabeleditListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if (!m_Updating) {
		if (pDispInfo->item.pszText != NULL) {
			int i = pDispInfo->item.iItem;
			CBibItem *item = (CBibItem*)m_ListStrings.GetItemData(i);
			ASSERT(item);
			item->SetKey(pDispInfo->item.pszText);
			*pResult = 1;
		} else
			*pResult = 0;
	} else
		*pResult = 0;
}

void CStringsDialog::OnInsertitemListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_Updating) {
	}
	
	*pResult = 0;
}

void CStringsDialog::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("StringsDialog"), wp);
	CDialog::OnDestroy();
}

void CStringsDialog::Update()
{
	if (m_Selected != -1) {
		CBibItem* bi = (CBibItem*)m_ListStrings.GetItemData(m_Selected);
		ASSERT(bi);
		m_ScintillaCtrl.SetText(bi->GetValue());
		m_ScintillaCtrl.EnableWindow(TRUE);
	} else {
		m_ScintillaCtrl.SetText(NULL);
		m_ScintillaCtrl.EnableWindow(FALSE);
	}
	m_ScintillaCtrl.SetModify(FALSE);
	m_BtnApply.EnableWindow(FALSE);
	m_BtnUndo.EnableWindow(FALSE);
	m_BtnEdit.EnableWindow(m_Selected != -1);
	m_BtnRemove.EnableWindow(m_Selected != -1);
	m_BtnSource.EnableWindow(m_Selected != -1);
}

void CStringsDialog::OnButtonSource() 
{
	if (m_Selected == -1)
		return;
	CBibItem * item = (CBibItem*)m_ListStrings.GetItemData(m_Selected);
	ASSERT(item);
	CSourceDialog dlg;
	dlg.SetBibItem(item);
	if (dlg.DoModal() == IDOK && dlg.m_Modified) {
		CBibReader reader(dlg.GetSource());
		item->LoadFromFile(&reader);
		m_ListStrings.SetItemText(m_Selected, 0, item->GetKey());
		m_ListStrings.SetItemText(m_Selected, 1, BeautifyValue(item->GetValue()));
		Update();
	}
}

BOOL CStringsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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
		case SCN_MODIFIED:
			m_BtnApply.EnableWindow(m_Selected != -1 && m_ScintillaCtrl.GetModify());
			m_BtnUndo.EnableWindow(m_Selected != -1 && m_ScintillaCtrl.GetModify());
			break;
		}
		return TRUE;
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CStringsDialog::OnDblclkListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_Selected != -1)
		OnButtonSource();
	*pResult = 0;
}

void CStringsDialog::Apply()
{
	if (m_Selected == -1 || !m_ScintillaCtrl.GetModify())
		return;
	CBibItem *item = (CBibItem*)m_ListStrings.GetItemData(m_Selected);
	ASSERT(item);
	item->SetValue(m_ScintillaCtrl.GetText());
	m_ListStrings.SetItemText(m_Selected, 1, BeautifyValue(item->GetValue()));
}

CBibList * CStringsDialog::GetBibList()
{
	return m_TmpList;
}

void CStringsDialog::OnOK()
{
	Apply();
	CDialog::OnOK();
}

void CStringsDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void CStringsDialog::OnButtonUndo() 
{
	if (m_Selected == -1)
		return;
	CBibItem * item = (CBibItem*)m_ListStrings.GetItemData(m_Selected);
	ASSERT(item);
	m_ScintillaCtrl.SetText(item->GetValue());
	m_ScintillaCtrl.SetModify(FALSE);
	m_BtnApply.EnableWindow(FALSE);
	m_BtnUndo.EnableWindow(FALSE);	
}

void CStringsDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("StringsDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);
	}
}

void CStringsDialog::OnKeydownListStrings(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	switch (pLVKeyDow->wVKey) {
	case VK_DELETE:
		// Delete key -> delete selected
		if (m_Selected != -1)
			OnButtonRemove();
		break;
	}
	
	*pResult = 0;
}
