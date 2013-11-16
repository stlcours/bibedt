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

  $Id: FilterDialog.cpp,v 1.9 2006/08/11 09:25:20 stievie Exp $
*/

// FilterDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "FilterDialog.h"
#include "Globals.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFilterDialog 


CFilterDialog::CFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterDialog)
	//}}AFX_DATA_INIT
	m_Filter = new	CBibItem(NULL);
	m_Filter->SetType(STR_COMMENT);
	m_Filter->SetKey(STR_FILTER);
	m_Selected = -1;
	m_Updating = FALSE;
}

CFilterDialog::~CFilterDialog()
{
	delete m_Filter;
}

void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterDialog)
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_BtnDown);
	DDX_Control(pDX, IDC_BUTTON_UP, m_BtnUp);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_BtnRemove);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_BtnEdit);
	DDX_Control(pDX, IDC_LIST_FILTERS, m_lvFields);
	DDX_Control(pDX, IDC_EDIT_COND, m_EditCond);
	DDX_Control(pDX, IDC_EDIT_FIELD, m_EditField);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CFilterDialog)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_FILTERS, OnEndlabeleditListFilters)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FILTERS, OnClickListFilters)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FILTERS, OnItemchangedListFilters)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_FILTERS, OnItemchangingListFilters)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CFilterDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_FILTERS, ANF_TOP | ANF_LEFT | ANF_RIGHT | ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_ADD, ANF_BOTTOM | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_EDIT, ANF_BOTTOM | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_REMOVE, ANF_BOTTOM | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_UP, ANF_BOTTOM | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_DOWN, ANF_BOTTOM | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_FIELD, ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_FIELD, ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_COND, ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_COND, ANF_BOTTOM | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFilterDialog 

BOOL CFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);

	m_lvFields.InsertColumn(0, AfxLoadString(IDS_STRING_NAME), LVCFMT_LEFT, 150);
	m_lvFields.InsertColumn(1, AfxLoadString(IDS_STRING_CONDITION), LVCFMT_LEFT, 350);	
	DWORD extst = m_lvFields.GetExtendedStyle();
	m_lvFields.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);

	POSITION p = m_Filter->GetHeadPosition();
	int i = -1;
	m_Updating = TRUE;
	while (p) {
		CField *flt = (CField*)m_Filter->GetNext(p);
		i = m_lvFields.InsertItem(i+1, flt->GetName());
		m_lvFields.SetItemText(i, 1, flt->GetValue());
		m_lvFields.SetItemData(i, (DWORD)flt);
	}
	m_Updating = FALSE;
	EnableControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CFilterDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void CFilterDialog::SetFilter(CBibItem *filter)
{
	if (filter)
		// Could be NULL if no filters are defined yet.
		m_Filter->Assign(filter);
}

void CFilterDialog::OnEndlabeleditListFilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	if (pDispInfo->item.pszText != NULL) {
		LVFINDINFO info;
		info.flags = LVFI_STRING;
		info.psz = pDispInfo->item.pszText;
		int i = m_lvFields.FindItem(&info);
		if (i == -1) {
			CField *flt = (CField*)m_lvFields.GetItemData(pDispInfo->item.iItem);
			ASSERT(flt);
			flt->SetName(pDispInfo->item.pszText);
			*pResult = 1;
		} else {
			// Already exists
			ShowError(IDS_STRING_FILTEREXISTS);
			m_lvFields.SetFocus();
			CEdit* edt = m_lvFields.EditLabel(pDispInfo->item.iItem);	
			*pResult = 0;
		}
	} else
		*pResult = 0;
}

void CFilterDialog::OnClickListFilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

CBibItem * CFilterDialog::GetFilter()
{
	return m_Filter;
}

void CFilterDialog::OnButtonEdit() 
{
	if (m_Selected == -1)
		return;
	m_lvFields.EnsureVisible(m_Selected, FALSE);
	UINT is = m_lvFields.GetItemState(m_Selected, LVIF_STATE);
	m_lvFields.SetItemState(m_Selected, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_lvFields.SetFocus();
	CEdit* edt = m_lvFields.EditLabel(m_Selected);	
}

void CFilterDialog::EnableControls()
{
	m_BtnEdit.EnableWindow(m_Selected != -1);
	m_BtnRemove.EnableWindow(m_Selected != -1);
	m_BtnUp.EnableWindow(m_Selected > 0);
	m_BtnDown.EnableWindow(m_Selected != -1 && m_Selected < m_lvFields.GetItemCount() - 1);
	m_EditCond.EnableWindow(m_Selected != -1);
	m_EditField.EnableWindow(m_Selected != -1);
}

void CFilterDialog::OnItemchangedListFilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (!m_Updating) {
		if (pNMListView->uChanged == LVIF_STATE) {
			CField *flt;
			if (BIT_SET(pNMListView->uNewState, LVIS_SELECTED)) {
				m_Selected = pNMListView->iItem;
				flt = (CField*)m_lvFields.GetItemData(m_Selected);
				m_EditField.SetWindowText(flt->GetFilterField());
				m_EditCond.SetWindowText(flt->GetFilterCond());
			} else if (BIT_SET(pNMListView->uOldState, LVIS_SELECTED)) {
				Apply();
				m_Selected = -1;
				m_EditField.SetWindowText(NULL);
				m_EditCond.SetWindowText(NULL);
			}
			EnableControls();
		}
	}
	*pResult = 0;
}

void CFilterDialog::OnItemchangingListFilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
}

void CFilterDialog::OnButtonAdd() 
{
	Apply();
	m_EditField.SetWindowText(NULL);
	m_EditCond.SetWindowText(NULL);

	m_Selected = m_lvFields.InsertItem(m_lvFields.GetItemCount(), AfxLoadString(IDS_STRING_NEWFILTER), -1);
	CField *item = m_Filter->New();
	item->SetName(AfxLoadString(IDS_STRING_NEWFILTER));
	m_lvFields.SetItemData(m_Selected, (DWORD)item);
	m_lvFields.EnsureVisible(m_Selected, FALSE);
	UINT is = m_lvFields.GetItemState(m_Selected, LVIF_STATE);
	m_lvFields.SetItemState(m_Selected, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_lvFields.SetFocus();

	CEdit* edt = m_lvFields.EditLabel(m_Selected);
}

void CFilterDialog::OnButtonRemove() 
{
	if (m_Selected == -1)
		return;
	m_Updating = TRUE;
	CField *item = (CField*)m_lvFields.GetItemData(m_Selected);
	ASSERT(item);
	m_Filter->Delete(item);
	m_lvFields.DeleteItem(m_Selected);
	m_Selected = -1;
	m_Updating = FALSE;
	EnableControls();	
}

void CFilterDialog::Apply()
{
	if (m_Selected == -1)
		return;
	CField *flt = (CField*)m_lvFields.GetItemData(m_Selected);
	CString f;
	CString c;
	m_EditField.GetWindowText(f);
	m_EditCond.GetWindowText(c);
	ASSERT(flt);
	flt->SetFilter(f, c);
	m_lvFields.SetItemText(m_Selected, 1, flt->GetValue());
}

void CFilterDialog::OnOK()
{
	Apply();
	CDialog::OnOK();
}
void CFilterDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement("FilterDialog", &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);
	}
}

void CFilterDialog::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement("FilterDialog", wp);
	CDialog::OnDestroy();
}

void CFilterDialog::OnButtonDown() 
{
	int curinx = m_Selected;
	int newinx = m_Selected + 1;
	MoveFilter(curinx, newinx);
}

void CFilterDialog::OnButtonUp() 
{
	int curinx = m_Selected;
	int newinx = m_Selected - 1;
	MoveFilter(curinx, newinx);
}

void CFilterDialog::SetSelected(int index, BOOL selected)
{
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (m_lvFields.GetItem(&item)) {
		if (selected)
			SET_BIT(item.state, LVIS_SELECTED);
		else
			UNSET_BIT(item.state, LVIS_SELECTED);
		m_lvFields.SetItem(&item);
	}
}

void CFilterDialog::MoveFilter(int curinx, int newinx)
{
	m_Filter->Move(curinx, newinx);

	m_Updating = TRUE;

	CField *flt = (CField*)m_lvFields.GetItemData(curinx);
	m_lvFields.DeleteItem(curinx);
	int i = m_lvFields.InsertItem(newinx, flt->GetName());
	m_lvFields.SetItemText(i, 1, flt->GetValue());
	m_lvFields.SetItemData(i, (DWORD)flt);
	m_Selected = i;
	SetSelected(m_Selected, TRUE);

	m_Updating = FALSE;
	EnableControls();	
}
