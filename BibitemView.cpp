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

  $Id: BibitemView.cpp,v 1.67 2006/08/13 12:19:50 stievie Exp $
*/

// BibitemView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "BibitemView.h"
#include "Options.h"
#include "SourceDialog.h"
#include "ExportRTF.h"
#include "KeysDialog.h"
#include "StringListEx.h"
#include "ApplyFilterDialog.h"
#include "FileDialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBibitemView

IMPLEMENT_DYNCREATE(CBibitemView, CFormView)

CBibitemView::CBibitemView()
	: CFormView(CBibitemView::IDD)
{
	//{{AFX_DATA_INIT(CBibitemView)
	//}}AFX_DATA_INIT
	m_SelField = -1;
	m_BibDef = ((CBibedtApp*)AfxGetApp())->m_BibDef;
	m_BibItem = NULL;
	m_Updating = FALSE;
	m_Modified = FALSE;
	m_TmpItem = NULL;
	VERIFY(m_PopupMenu.LoadMenu(IDR_MENU_FIELDLIST));
}

CBibitemView::~CBibitemView()
{
	if (m_TmpItem != NULL)
		delete m_TmpItem;
}

void CBibitemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBibitemView)
	DDX_Control(pDX, IDC_LIST_MISSINGFIELDS, m_lstMissingFields);
	DDX_Control(pDX, IDC_EDIT_KEY, m_EditKey);
	DDX_Control(pDX, IDC_LIST_FIELDS, m_ListFields);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ComboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBibitemView, CFormView)
	//{{AFX_MSG_MAP(CBibitemView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_GEYGENERATE, OnButtonGeygenerate)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FIELDS, OnDblclkListFields)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_FIELDS, OnDeleteitemListFields)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_FIELDS, OnEndlabeleditListFields)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_FIELDS, OnInsertitemListFields)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FIELDS, OnItemchangedListFields)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_FIELDS, OnKeydownListFields)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnItemclickListFields)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_EN_CHANGE(IDC_EDIT_KEY, OnChangeEditKey)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FIELDLIST_POPUP_ADD, OnFieldlistPopupAdd)
	ON_UPDATE_COMMAND_UI(ID_FIELDLIST_POPUP_ADD, OnUpdateFieldlistPopupAdd)
	ON_COMMAND(ID_FIELDLIST_POPUP_REMOVE, OnFieldlistPopupRemove)
	ON_UPDATE_COMMAND_UI(ID_FIELDLIST_POPUP_REMOVE, OnUpdateFieldlistPopupRemove)
	ON_UPDATE_COMMAND_UI(ID_FIELDLIST_POPUP_EDIT, OnUpdateFieldlistPopupEdit)
	ON_COMMAND(ID_FIELDLIST_POPUP_EDIT, OnFieldlistPopupEdit)
	ON_UPDATE_COMMAND_UI(ID_POPUP_BROWSE, OnUpdatePopupBrowse)
	ON_COMMAND(ID_POPUP_BROWSE, OnPopupBrowse)
	ON_UPDATE_COMMAND_UI(ID_POPUP_CROSSREF, OnUpdatePopupCrossref)
	ON_COMMAND(ID_POPUP_CROSSREF, OnPopupCrossref)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_FIELDS, OnBeginlabeleditListFields)
	ON_COMMAND(ID_RECORD_GENERATEKEY, OnRecordGeneratekey)
	ON_LBN_DBLCLK(IDC_LIST_MISSINGFIELDS, OnDblclkListMissingfields)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_FILTER, OnPopupFilter)
	ON_UPDATE_COMMAND_UI(ID_POPUP_FILTER, OnUpdatePopupFilter)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_POPUP_LOCALURL, OnPopupLocalurl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CBibitemView)
	ANCHOR_MAP_ENTRY(IDC_EDIT_KEY, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_GEYGENERATE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_FIELDS, ANF_TOP | ANF_RIGHT | ANF_LEFT | ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_LIST_MISSINGFIELDS, ANF_BOTTOM | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CBibitemView

#ifdef _DEBUG
void CBibitemView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBibitemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CBibedtDoc* CBibitemView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBibedtDoc)));
	return (CBibedtDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CBibitemView 

void CBibitemView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);
}

void CBibitemView::PopulateFields()
{
	// At the moment nothing is selected
	m_SelField = -1;

	BeginUpdate();
	int l = -1, c = -1;
	m_ListFields.GetEditPos(l, c);

	m_ListFields.DeleteAllItems();
	POSITION h = m_TmpItem->GetHeadPosition();
	CField* fi;
	int j = 0;
	for (int i = 0; i < m_TmpItem->GetCount(); i++) {
		fi = (CField*)m_TmpItem->GetNext(h);
		if (fi) {
			j = m_ListFields.InsertItem(j, fi->GetName(), m_BibDef->GetRequired(m_TmpItem->GetType(), fi->GetName()));
			m_ListFields.SetItemText(j, 1, fi->GetValue());
			m_ListFields.SetItemData(j, (DWORD)fi);
		}
		if (h == NULL)
			break;
	}

	// Add all other fields
	CField *finew;
	CBibItem *bi = m_BibDef->FindType(m_TmpItem->GetType());
	if (bi != NULL) {
		h = bi->GetHeadPosition();
		for (i = 0; i < bi->GetCount(); i++) {
			fi = (CField*)bi->GetNext(h);
			if (fi != NULL && m_TmpItem->Find(fi->GetName()) == NULL) {
				finew = m_TmpItem->New();
				finew->SetName(fi->GetName());
				finew->SetModified(FALSE);
				j = m_ListFields.InsertItem(j, finew->GetName(), m_BibDef->GetRequired(m_TmpItem->GetType(), finew->GetName()));
				m_ListFields.SetItemText(j, 1, _T(""));
				m_ListFields.SetItemData(j, (DWORD)finew);
			}
			if (h == NULL)
				break;
		}
	}

	// Sort it
	LVSORTPARAM ss;
	ss.iHeader = 0;
	ss.pListView = &m_ListFields;
	ss.bSortAsc = TRUE;

	// Sort the list
	m_ListFields.SortItems(SortFunc, (LPARAM)&ss);

	m_SortAsc = FALSE;

	// Edit the last cell if any
	if (l > -1 && c > -1) {
		if (l >= m_ListFields.GetItemCount()) {
			m_ListFields.CancelEdit(TRUE);
			m_ListFields.EditSubItem(m_ListFields.GetItemCount()-1, c);
		} else
			m_ListFields.EditSubItem(l, c);
	}

	m_ListFields.UpdateEditor();

	EndUpdate();
}

int CBibitemView::AddField(CString name, CString value, BOOL edit)
{
	BeginUpdate();
	int i = m_ListFields.InsertItem(m_ListFields.GetItemCount(), name, R_UNKNOWN);
	CField *fi = new CField(m_TmpItem);

	fi->SetName(name);
	if (!value.IsEmpty()) {
		m_ListFields.SetItemText(i, 1, value);
		fi->SetValue(value);
	}
	m_TmpItem->AddTail((CObject*)fi);
	m_ListFields.SetItemData(i, (DWORD)fi);
	m_ListFields.EnsureVisible(i, FALSE);
	UINT is = m_ListFields.GetItemState(i, LVIF_STATE);
	m_ListFields.SetItemState(i, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
	m_ListFields.SetFocus();

	EndUpdate();

	if (edit)
		CEdit* edt = m_ListFields.EditSubItem(i, 0);
	return i;
}

int CBibitemView::SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	PLVSORTPARAM ss = (PLVSORTPARAM)lParamSort;
	CString s1;
	CString s2;
	CField* f1 = (CField*)lParam1;
	CField* f2 = (CField*)lParam2;

	switch (ss->iHeader) {
	case 0:
		s1 = f1->GetName();
		s2 = f2->GetName();
		break;
	case 1:
		s1 = f1->GetValue();
		s2 = f2->GetValue();
		break;
	}
	int res;
	if (pOp->m_SortCaseSensitive)
		res = s1.Compare(s2);
	else
		res = s1.CompareNoCase(s2);
	return ss->bSortAsc ? res : -res;
}

void CBibitemView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate) {
		// If in edit mode set back the focus
		CEdit* editor = m_ListFields.GetEditControl();
		if (editor)
			editor->SetFocus();
	} else {
		if (pActivateView != this && m_Modified && GetDocument()->GetSelected()) {
			Apply();
			m_BibItem->Assign(m_TmpItem);
			GetDocument()->UpdateAllViews(this, UR_RECEDITED, m_BibItem);
			SetModified(FALSE);
		}
	}

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CBibitemView::UpdateItem()
{
	m_ListFields.CancelEdit(FALSE);
	if (m_BibItem) {
		m_TmpItem->Assign(m_BibItem);
		m_TmpItem->SetModified(m_BibItem->GetModified());
	} else {
		m_TmpItem->Clear();
		m_TmpItem->SetKey(_T(""));
		m_TmpItem->SetValue(_T(""));
		m_TmpItem->SetModified(FALSE);
	}

	m_ComboType.ResetContent();
	POSITION h = m_BibDef->GetHeadPosition();
	while (h) {
		CBibItem* bi = (CBibItem*)m_BibDef->GetNext(h);
		ASSERT(bi);
		if (bi->IsRegularItem())
			m_ComboType.AddString(bi->GetType());
	}
	int i;

	PopulateFields();
	if (!m_BibItem) {
		m_EditKey.SetWindowText(NULL);
		i = m_ComboType.SelectString(-1, m_BibDef->GetDefault()->GetType());
		if (i == LB_ERR) {
			i = m_ComboType.AddString(m_BibDef->GetDefault()->GetType());
			m_ComboType.SetCurSel(i);
		}
		return;
	}

	i = m_ComboType.SelectString(-1, m_BibItem->GetType());
	if (i == LB_ERR) {
		i = m_ComboType.AddString(m_BibItem->GetType());
		m_ComboType.SetCurSel(i);
	}

	// Missing fields
	UpdateMissing();

	BeginUpdate();
	m_EditKey.SetWindowText(m_BibItem->GetKey());
	EndUpdate();
}

/**
 * Find a Field with name `Local-Url' and append the filename.
 * If no such field exists add one.
 */
void CBibitemView::AddLocalURL(CString url)
{
	CField *fi = m_TmpItem->Find(STR_LOCALURL);
	if (!fi)
		AddField(STR_LOCALURL, url, FALSE);
	else {
		CString val = fi->GetValue();
		if (!val.IsEmpty())
			val += _T("; ") + url;
		else
			val = url;
		fi->SetValue(val);
		for (int i = 0; i < m_ListFields.GetItemCount(); i++) {
			if (m_ListFields.GetItemData(i) == (DWORD)fi) {
				m_ListFields.SetItemText(i, 1, val);
				break;
			}
		}
	}
}

LRESULT CBibitemView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDROP hDrop;
	switch (message) {
	case WM_INITDIALOG:
		InitDialog();
		break;
	case WM_DROPFILES:
		hDrop = (HDROP)wParam;
		TCHAR* filename = new TCHAR[MAX_PATH+1];
		int count = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, MAX_PATH);
		for (int i = 0; i < count; i++) {
			DragQueryFile(hDrop, i, filename, MAX_PATH);
			AddLocalURL(EncodeFilename(filename));
		}
		delete [] filename;
		SetModified(TRUE);
		return 0;
	}
		
	return CFormView::WindowProc(message, wParam, lParam);
}

void CBibitemView::InitDialog()
{
	UpdateData(FALSE);
	InitAnchors();
	m_ComboType.ResetContent();

	m_SelField = -1;

	m_ImageList.Create(IDB_BITMAP_REQUIRED, 16, 6, RGB(255, 0, 255));
	DWORD extst = m_ListFields.GetExtendedStyle();
	m_ListFields.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);
	m_ListFields.SetImageList(&m_ImageList, LVSIL_SMALL);
	CString col;
	col.LoadString(IDS_STRING_FIELD);
	m_ListFields.InsertColumn(0, col, LVCFMT_LEFT, AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ItemView.Col1.Width"), 200));
	col.LoadString(IDS_STRING_VALUE);
	m_ListFields.InsertColumn(1, col, LVCFMT_LEFT, AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ItemView.Col2.Width"), 400));
	m_ListFields.m_DefaultText = AfxLoadString(IDS_STRING_NEWFIELD);
	SetModified(FALSE);
	m_TmpItem = new CBibItem(GetDocument()->m_BibFile);
}

void CBibitemView::OnButtonGeygenerate() 
{
	GenerateKey();
}

void CBibitemView::OnSelchangeComboType() 
{
	CString strType;
	CString k;
	k = m_TmpItem->GetKey();
	m_ComboType.GetWindowText(strType);

	// In case there are added Fields
	CFieldList oldlst;
	oldlst.Assign(m_TmpItem);
	oldlst.DeleteEmpty();

	if (m_NewDialog) {
		CBibItem *bi = m_BibDef->FindType(strType);
		m_TmpItem->Clear();
		if (bi) {
			m_TmpItem->Assign(bi);
			m_TmpItem->ClearValues();
		}
	} else {
		m_TmpItem->Clear();
		m_TmpItem->Assign(m_BibItem);
		m_TmpItem->SetType(strType);
	}
	// Append old Fields
	m_TmpItem->Append(&oldlst);

	m_TmpItem->SetKey(k);

	PopulateFields();
	UpdateMissing();
	if (!m_Updating)
		SetModified(TRUE);
}

void CBibitemView::Apply()
{
	if (m_Modified) {
		CString str;
		m_EditKey.GetWindowText(str);
		m_TmpItem->SetKey(str);
		m_ComboType.GetWindowText(str);
		m_TmpItem->SetType(str);
	}
}

void CBibitemView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint) {
	case UR_NEWFILE:
		m_BibItem = NULL;
		UpdateItem();
		SetModified(FALSE);
		break;
	case UR_RECREMOVED:
		m_BibItem = NULL;
		UpdateItem();
		SetModified(FALSE);
		break;
	case UR_SELECTED:
	case UR_RECADDED:
		if (m_BibItem != pHint) {
			// Added an item -> save the old if changed
			m_ListFields.CancelEdit(FALSE);
			if (m_Modified) {
				if (m_BibItem) {
					Apply();
					m_BibItem->Assign(m_TmpItem);
					GetDocument()->UpdateAllViews(this, UR_RECEDITED, m_BibItem);
				}
			}
			m_BibItem = (CBibItem*)pHint;
			UpdateItem();
			SetModified(FALSE);
		}
		break;
	case UR_SAVINGFILE:
	case UR_SAVEVIEWS:
		if (m_BibItem && m_Modified) {			
			// If modified apply before saving
			m_ListFields.CancelEdit(FALSE);
			Apply();
			m_BibItem->Assign(m_TmpItem);
			GetDocument()->UpdateAllViews(this, UR_RECEDITED, m_BibItem);
			SetModified(FALSE);
		}
		break;
	case UR_RECEDITED:
		if (pSender != this) {
			m_BibItem = (CBibItem*)pHint;
			UpdateItem();
			SetModified(FALSE);
		}
		break;
	case UR_RECSRCEDITED:
	case UR_SRCEDITED:
		m_BibItem = (CBibItem*)pHint;
		UpdateItem();
		SetModified(FALSE);
		break;
	}
}

void CBibitemView::OnDblclkListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_SelField != -1) {
		// Open URL
		CField *fi = (CField*)m_ListFields.GetItemData(m_SelField);
		if (fi) {
			if (!fi->GetValue().IsEmpty() && 
				(fi->GetName().CompareNoCase(STR_LOCALURL) == 0 || 
				fi->GetName().CompareNoCase(STR_URL) == 0)) {
				CString val = fi->GetValue();
				CStringList lst;
				SplitSepString(val, &lst);
				POSITION p = lst.GetHeadPosition();
				while (p) {
					if (ShellExec(lst.GetNext(p))) {
						if (p)
							// Wait some time if there are other files to show
							Sleep(500);
					} else
						MessageBeep(MB_ICONEXCLAMATION);
				}
			} else
				// Or show edit dialog
				OnFieldlistPopupEdit();
		}
	}
	
	*pResult = 0;
}

void CBibitemView::OnDeleteitemListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_Updating) {
		CField* f = (CField*)m_ListFields.GetItemData(pNMListView->iItem);
		m_TmpItem->Delete(f);
		SetModified(TRUE);
	}
	
	*pResult = 0;
}

void CBibitemView::OnEndlabeleditListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (!m_Updating) {
		LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
		if (pDispInfo->item.pszText != NULL) {
			int i = pDispInfo->item.iItem;
			CField* f = (CField*)m_ListFields.GetItemData(i);
			if (pDispInfo->item.iSubItem == 0) {
				// It's the field name
				f->SetName(pDispInfo->item.pszText);
				m_ListFields.SetItem(i, pDispInfo->item.iSubItem, LVIF_IMAGE, NULL, 
					m_BibDef->GetRequired(m_BibItem->GetType(), pDispInfo->item.pszText), 0, 0, 0);
			} else if (pDispInfo->item.iSubItem == 1) {
				// It's the field value
				f->SetValue(pDispInfo->item.pszText);
			}
			m_ListFields.SetItemText(i, pDispInfo->item.iSubItem, pDispInfo->item.pszText);
			UpdateMissing();
			*pResult = 1;
			SetModified(m_Modified || f->GetModified());
		} else
			*pResult = 0;
	} else
		*pResult = 0;
}

void CBibitemView::OnInsertitemListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_Updating) {

		CField* f = new CField(m_TmpItem);
		// Name
		CString tmp = m_ListFields.GetItemText(pNMListView->iItem, 0);
		f->SetName(tmp);
		m_TmpItem->AddTail((CObject*)f);
		m_ListFields.SetItemData(pNMListView->iItem, (DWORD)f);
		SetModified(TRUE);
	}
	
	*pResult = 0;
}

void CBibitemView::OnItemchangedListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (!m_Updating) {
		if (pNMListView->uChanged == LVIF_STATE) {
			if (BIT_SET(pNMListView->uNewState, LVIS_FOCUSED))
				m_SelField = pNMListView->iItem;
			else
				m_SelField = -1;
		}
	}	
	
	*pResult = 0;
}

void CBibitemView::OnKeydownListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	switch (pLVKeyDow->wVKey) {
	case VK_DELETE:
		if (m_SelField != -1)
			DeleteField(m_SelField);
		break;
	}
	
	*pResult = 0;
}

void CBibitemView::OnItemclickListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	LVSORTPARAM ss;
	ss.iHeader = phdn->iItem;
	ss.pListView = &m_ListFields;
	ss.bSortAsc = m_SortAsc;

	m_ListFields.SortItems(SortFunc, (LPARAM)&ss);
	m_SortAsc = !m_SortAsc;
	
	*pResult = 0;
}

void CBibitemView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CBibitemView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CBibitemView::OnChangeEditKey() 
{
	if (!m_Updating)
		SetModified(TRUE);
}

BOOL CBibitemView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	return CFormView::OnNotify(wParam, lParam, pResult);
}

void CBibitemView::SetModified(BOOL val)
{
	if (m_Modified != val) {
		m_Modified = val;
		m_TmpItem->SetModified(val);
		GetDocument()->SetModifiedFlag(GetDocument()->IsModified() || m_Modified);
	}
}

void CBibitemView::OnDestroy() 
{
	if (!m_ListFields)
		return;
	int i;
	i = m_ListFields.GetColumnWidth(0);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ItemView.Col1.Width"), i);
	i = m_ListFields.GetColumnWidth(1);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ItemView.Col2.Width"), i);

	CFormView::OnDestroy();
}

void CBibitemView::OnFieldlistPopupAdd() 
{
 	AddField(AfxLoadString(IDS_STRING_NEWFIELD), _T(""), TRUE);
 	SetModified(TRUE);
}

void CBibitemView::OnUpdateFieldlistPopupAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CBibitemView::OnFieldlistPopupRemove() 
{
	DeleteField(m_SelField);
}

void CBibitemView::OnUpdateFieldlistPopupRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_SelField != -1);
}

void CBibitemView::DeleteField(int nIndex)
{
 	if (nIndex == -1)
 		return;
 	BeginUpdate();
	if (nIndex == m_SelField)
 		m_SelField = -1;
 	CField* fi = (CField*)m_ListFields.GetItemData(nIndex);
 	m_TmpItem->Delete(fi);
 	m_ListFields.DeleteItem(nIndex);
 	if (!(nIndex == 0 && m_ListFields.GetItemCount()))
 		nIndex--;
 	if (nIndex > -1) {
 		m_ListFields.EnsureVisible(nIndex, FALSE);
 		UINT is = m_ListFields.GetItemState(nIndex, LVIF_STATE);
 		m_ListFields.SetItemState(nIndex, is | LVIS_SELECTED | LVIS_FOCUSED, LVIF_STATE);
 		m_ListFields.SetFocus();
 	}
 	EndUpdate();
 	SetModified(TRUE);
}

void CBibitemView::OnUpdateFieldlistPopupEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_SelField != -1);
}

void CBibitemView::OnFieldlistPopupEdit() 
{
	CSourceDialog dlg;
 	CField* fi = (CField*)m_ListFields.GetItemData(m_SelField);
	dlg.SetSource(fi->GetValue());
	if (dlg.DoModal() == IDOK) {
		fi->SetValue(dlg.GetSource());
		SetModified(m_Modified || fi->GetModified());
		m_ListFields.SetItemText(m_SelField, 1, dlg.GetSource());
	}
}

void CBibitemView::OnUpdatePopupBrowse(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_SelField != -1);
}

void CBibitemView::OnPopupBrowse() 
{
	CString f;
	CString fn;
 	CField* fi = (CField*)m_ListFields.GetItemData(m_SelField);
	fn = DecodeFilename(fi->GetValue());
	CFileFind finder;
	if (!finder.FindFile(fn))
		// Dialog will not show when file does not exist
		fn.Empty();
	finder.Close();
	f.Format(_T("%s||"), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(TRUE, NULL, fn, OFN_HIDEREADONLY | OFN_ENABLESIZING, f, this);	
	if (dlg.DoModal() == IDOK) {
		m_ListFields.SetItemText(m_SelField, 1, EncodeFilename(dlg.GetPathName()));
		fi->SetValue(EncodeFilename(dlg.GetPathName()));
		SetModified(fi->GetModified());
	}
}

void CBibitemView::OnUpdatePopupCrossref(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->m_BibFile->GetCount() > 1);
}

void CBibitemView::OnPopupCrossref() 
{
	CKeysDialog dlg;
	dlg.SetBibList(GetDocument()->m_BibFile);
	if (dlg.DoModal() == IDOK) {
		CString key = dlg.m_SelKey;
		if (!key.IsEmpty()) {
			CField *cr = m_TmpItem->Find(STR_CROSSREF);
			if (cr) {
				// Has already crossref field
				cr->SetValue(key);
				int inx = GetItemIndex(cr);
				if (inx != -1)
					m_ListFields.SetItemText(inx, 1, key);
			} else {
				// Add the field
				AddField(STR_CROSSREF, key, FALSE);
			}
			SetModified(TRUE);
		}
	}
}

int CBibitemView::GetItemIndex(CField *item)
{
	for (int i = 0; i < m_ListFields.GetItemCount(); i++) {
		if (m_ListFields.GetItemData(i) == (DWORD)item)
			return i;
	}
	return -1;
}

void CBibitemView::OnBeginlabeleditListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_ListFields.m_AutoComplete.RemoveAll();
	if (pOp->m_AutoCompleteValues && pDispInfo->item.iSubItem == 1) {
		int i = pDispInfo->item.iItem;
		CString field = m_ListFields.GetItemText(i, 0);
		GetDocument()->m_BibFile->GetAllFieldValues(field, &(m_ListFields.m_AutoComplete));
		m_ListFields.m_AutoComplete.Sort();
	}
	*pResult = 0;
}

void CBibitemView::OnRecordGeneratekey() 
{
	GenerateKey();
}

void CBibitemView::GenerateKey()
{
	CString key	= GetDocument()->m_BibFile->GetNewKey(m_TmpItem, m_BibItem);
	if (!key.IsEmpty())
		m_EditKey.SetWindowText(key);
}

void CBibitemView::OnDblclkListMissingfields() 
{
	int sel = m_lstMissingFields.GetCurSel();
	if (sel != -1) {
		CString str;
		m_lstMissingFields.GetText(sel, str);
		LVFINDINFO info;
		info.flags = LVFI_STRING;
		info.psz = str;
		int i = m_ListFields.FindItem(&info);
		if (i != -1) {
			m_ListFields.SetFocus();
			CEdit* edt = m_ListFields.EditSubItem(i, 1);
		}
	}
}

void CBibitemView::UpdateMissing()
{
	m_lstMissingFields.ResetContent();
	CStringList mf;
	if (m_TmpItem->GetMissingFields(&mf)) {
		POSITION p = mf.GetHeadPosition();
		while (p) {
			m_lstMissingFields.AddString(mf.GetNext(p));
		}
		m_lstMissingFields.EnableWindow();
	} else {
		m_lstMissingFields.AddString(AfxLoadString(IDS_STRING_NOMISSING));
		m_lstMissingFields.EnableWindow(FALSE);
	}
}

void CBibitemView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd->GetSafeHwnd() == m_ListFields.GetSafeHwnd()) {
		CMenu* pPopup = m_PopupMenu.GetSubMenu(0);

		// Update Menuitems
		AfxGetMainWnd()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopup->m_hMenu, MAKELONG(0, FALSE));
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CBibitemView::OnPopupFilter() 
{
	CApplyFilterDialog dlg;
	dlg.SetFilter(GetDocument()->m_BibFile->GetFilter());
	if (dlg.DoModal() == IDOK && dlg.m_SelFilter != NULL) {
		m_TmpItem->ApplyFilter(dlg.m_SelFilter);
		SetModified();
		PopulateFields();
	}
}

void CBibitemView::OnUpdatePopupFilter(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->m_BibFile->GetFilter() != NULL);
}

CEdit* CBibitemView::GetFocusEdit()
{
	CWnd* foc = GetFocus();
	CEdit* edit = dynamic_cast<CEdit*>(foc);
	return edit;
}

void CBibitemView::OnEditUndo() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->Undo();
}

void CBibitemView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	pCmdUI->Enable(edit && edit->CanUndo());
}

void CBibitemView::OnEditCut() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->Cut();
}

void CBibitemView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	if (edit) {
		int s, e;
		edit->GetSel(s, e);
		pCmdUI->Enable(edit && s != e);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibitemView::OnEditCopy() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->Copy();
}

void CBibitemView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	if (edit) {
		int s, e;
		edit->GetSel(s, e);
		pCmdUI->Enable(edit && s != e);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibitemView::OnEditPaste() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->Paste();
}

void CBibitemView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	if (edit) {
		CString txt = ClipBrdGetData(this, CB_TEXT);
		pCmdUI->Enable(!txt.IsEmpty());
	} else
		pCmdUI->Enable(FALSE);
}

void CBibitemView::OnEditDelete() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->ReplaceSel(_T(""), TRUE);
}

void CBibitemView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	if (edit) {
		int s, e;
		edit->GetSel(s, e);
		pCmdUI->Enable(edit && s != e);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibitemView::OnEditSelectAll() 
{
	CEdit* edit = GetFocusEdit();
	if (edit)
		edit->SetSel(0, -1);
}

void CBibitemView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	CEdit* edit = GetFocusEdit();
	pCmdUI->Enable(edit && edit->GetWindowTextLength() > 0);
}

void CBibitemView::OnPopupLocalurl() 
{
	CString f, fn;
	f.Format(_T("%s||"), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(TRUE, NULL, fn, OFN_HIDEREADONLY | OFN_ENABLESIZING, f, this);	
	if (dlg.DoModal() == IDOK) {
		CField *fi = m_TmpItem->Find(STR_LOCALURL);
		if (fi == NULL) {
			fi = m_TmpItem->New();
			fi->SetName(STR_LOCALURL);
			fi->SetValue(EncodeFilename(dlg.GetPathName()));
		} else {
			CString val = fi->GetValue();
			if (!val.IsEmpty())
				val += _T("; ") + EncodeFilename(dlg.GetPathName());
			else
				val = EncodeFilename(dlg.GetPathName());
			fi->SetValue(val);
		}
		SetModified();
		PopulateFields();
	}
}
