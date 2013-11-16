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

  $Id: PreambleDialog.cpp,v 1.23 2006/06/06 18:52:18 stievie Exp $
*/

// PreambleDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "PreambleDialog.h"
#include "SourceDialog.h"
#include "BibReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreambleDialog 


CPreambleDialog::CPreambleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPreambleDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreambleDialog)
	//}}AFX_DATA_INIT
	m_Selection = -1;
	m_BibList = new CBibList();
}

CPreambleDialog::~CPreambleDialog()
{
	delete m_BibList;
}

void CPreambleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreambleDialog)
	DDX_Control(pDX, IDC_BUTTON_SOURCE, m_BtnSource);
	DDX_Control(pDX, IDC_BUTTON_UNDO, m_BtnUndo);
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_BtnApply);
	DDX_Control(pDX, IDC_BUTTON_FIELDREMOVE, m_BtnRemove);
	DDX_Control(pDX, IDC_LIST_PREAMBLES, m_lvPreambles);
	DDX_Control(pDX, IDC_SCINCTRL, m_ScintillaCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreambleDialog, CDialog)
	//{{AFX_MSG_MAP(CPreambleDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ADDFIELD, OnButtonAddfield)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PREAMBLES, OnClickListPreambles)
	ON_BN_CLICKED(IDC_BUTTON_FIELDREMOVE, OnButtonFieldremove)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, OnButtonSource)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PREAMBLES, OnDblclkListPreambles)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PREAMBLES, OnKeydownListPreambles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CPreambleDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_SOURCE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_ADDFIELD, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_FIELDREMOVE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_APPLY, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_UNDO, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_PREAMBLES, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_SCINCTRL, ANF_TOP | ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPreambleDialog 

void CPreambleDialog::SetBibList(CBibList *value)
{
	POSITION p = value->GetHeadPosition();
	while (p) {
		CBibItem *item = (CBibItem*)value->GetNext(p);
		ASSERT(item);
		if (item->IsType(STR_PREAMBLE))
			// Olny add @preamble items
			m_BibList->New()->Assign(item);
	}
}

BOOL CPreambleDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);
	
	m_ScintillaCtrl.Init();
	m_ScintillaCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_ScintillaCtrl.SetDisplayFolding(FALSE);

	CRect r;
	m_lvPreambles.GetWindowRect(&r);
	DWORD scrl = GetSystemMetrics(SM_CXVSCROLL);
	m_lvPreambles.InsertColumn(0, NULL, LVCFMT_LEFT, r.Width() - scrl - 5);
	DWORD extst = m_lvPreambles.GetExtendedStyle();
	m_lvPreambles.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);

	if (!m_BibList)
		return FALSE;

	POSITION h = m_BibList->GetHeadPosition();
	int item = 0;
	if (h) {
		for (int i = 0; i < m_BibList->GetCount(); i++) {
			CBibItem* bi = (CBibItem*)m_BibList->GetNext(h);
			if (bi) {
				if (bi->IsType(STR_PREAMBLE)) {
					// Add all preambles
					item = m_lvPreambles.InsertItem(item, BeautifyValue(bi->GetValue()), -1);
					m_lvPreambles.SetItemData(item, (DWORD)bi);
				}
			} else
				break;
		}
	}
	Update();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CPreambleDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		m_ScintillaCtrl.GotoPosition(0);

		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("PreambleDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);
	}
}


void CPreambleDialog::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("PreambleDialog"), wp);
	CDialog::OnDestroy();
}

BOOL CPreambleDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
			m_BtnApply.EnableWindow(m_Selection != -1 && m_ScintillaCtrl.GetModify());
			m_BtnUndo.EnableWindow(m_Selection != -1 && m_ScintillaCtrl.GetModify());
			break;
		case SCN_MARGINCLICK:
            m_ScintillaCtrl.DoDefaultFolding(pMsg->margin, pMsg->position);
			break;
		}
		return TRUE;
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CPreambleDialog::OnButtonAddfield() 
{
	Apply();
	CBibItem * item = m_BibList->New();
	item->SetType(STR_PREAMBLE);
	item->SetValue(AfxLoadString(IDS_STRING_NEWPREAMBLE));
	m_Selection = m_lvPreambles.InsertItem(m_lvPreambles.GetItemCount(), item->GetValue(), -1);
	m_lvPreambles.SetItemData(m_Selection, (DWORD)item);
	m_lvPreambles.SetSelectionMark(m_Selection);

	LVITEM lvi;
	lvi.mask = LVIF_STATE;
	lvi.iItem = m_Selection;
	lvi.iSubItem = 0;
	lvi.stateMask = LVIS_SELECTED;
	if (m_lvPreambles.GetItem(&lvi)) {
		SET_BIT(lvi.state, LVIS_SELECTED);
		m_lvPreambles.SetItem(&lvi);
	}

	Update();
	m_ScintillaCtrl.SelectAll();
	m_ScintillaCtrl.SetFocus();
}

void CPreambleDialog::OnClickListPreambles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	Apply();
	m_Selection = m_lvPreambles.GetSelectionMark();
	Update();
	*pResult = 0;
}

void CPreambleDialog::Apply()
{
	if (m_Selection == -1 || !m_ScintillaCtrl.GetModify())
		return;
	CString val;
	m_ScintillaCtrl.GetText(val);
	CBibItem * item = (CBibItem*)m_lvPreambles.GetItemData(m_Selection);
	ASSERT(item);
	item->SetValue(val);
	m_lvPreambles.SetItemText(m_Selection, 0, val);
	m_ScintillaCtrl.SetModify(FALSE);
	m_BtnApply.EnableWindow(FALSE);
	m_BtnUndo.EnableWindow(FALSE);
}

CBibList * CPreambleDialog::GetBibList()
{
	return m_BibList;
}

void CPreambleDialog::OnButtonFieldremove() 
{
	if (m_Selection == -1)
		return;
	CBibItem * item = (CBibItem*)m_lvPreambles.GetItemData(m_Selection);
	ASSERT(item);
	m_BibList->Delete(item);
	m_lvPreambles.DeleteItem(m_Selection);
	m_Selection = -1;
	Update();
}

void CPreambleDialog::Update()
{
	if (m_Selection != -1) {
		CBibItem * item = (CBibItem*)m_lvPreambles.GetItemData(m_Selection);
		ASSERT(item);
		m_ScintillaCtrl.SetText(item->GetValue());
		m_ScintillaCtrl.EnableWindow(TRUE);
	} else {
		m_ScintillaCtrl.SetText(NULL);
		m_ScintillaCtrl.EnableWindow(FALSE);
	}
	m_ScintillaCtrl.SetModify(FALSE);
	m_BtnRemove.EnableWindow(m_Selection != -1);
	m_BtnSource.EnableWindow(m_Selection != -1);
	m_BtnApply.EnableWindow(FALSE);
	m_BtnUndo.EnableWindow(FALSE);
}

void CPreambleDialog::OnButtonApply() 
{
	Apply();	
}

void CPreambleDialog::OnButtonUndo() 
{
	if (m_Selection == -1)
		return;
	CBibItem * item = (CBibItem*)m_lvPreambles.GetItemData(m_Selection);
	ASSERT(item);
	m_ScintillaCtrl.SetText(item->GetValue());
	m_ScintillaCtrl.SetModify(FALSE);
	m_BtnApply.EnableWindow(FALSE);
	m_BtnUndo.EnableWindow(FALSE);
}

void CPreambleDialog::OnOK()
{
	Apply();
	CDialog::OnOK();
}

void CPreambleDialog::OnButtonSource() 
{
	if (m_Selection == -1)
		return;
	CBibItem * item = (CBibItem*)m_lvPreambles.GetItemData(m_Selection);
	ASSERT(item);
	CSourceDialog dlg;
	dlg.SetBibItem(item);
	if (dlg.DoModal() == IDOK && dlg.m_Modified) {
		CBibReader reader(dlg.GetSource());
		item->LoadFromFile(&reader);
		m_lvPreambles.SetItemText(m_Selection, 0, BeautifyValue(item->GetValue()));
		Update();
	}
}

void CPreambleDialog::OnDblclkListPreambles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_Selection != -1)
		OnButtonSource();

	*pResult = 0;
}

void CPreambleDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);
	if (m_lvPreambles) {
		DWORD scrl = GetSystemMetrics(SM_CXVSCROLL);
		m_lvPreambles.GetWindowRect(&r);
		m_lvPreambles.SetColumnWidth(0, r.Width() - scrl - 5);
	}
}

void CPreambleDialog::OnKeydownListPreambles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	switch (pLVKeyDow->wVKey) {
	case VK_DELETE:
		if (m_Selection != -1)
			OnButtonFieldremove();
		break;
	}
	
	*pResult = 0;
}
