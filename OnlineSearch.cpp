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

  $Id: OnlineSearch.cpp,v 1.24 2006/06/06 18:52:18 stievie Exp $
*/

// OnlineSearch.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OnlineSearch.h"
#include "Globals.h"
#include "BibItem.h"
#include "Field.h"
#include "Options.h"
#include "InputBox.h"
#include "SearchProfilesDialog.h"

#include "YazConn.h"
#include "YazQuery.h"
#include "YazPrefixQuery.h"
#include "YazCCLQuery.h"
#include "YazCQLQuery.h"
#include "YazRecord.h"
#include "YazResultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COnlineSearch 


COnlineSearch::COnlineSearch(CWnd* pParent /*=NULL*/)
	: CDialog(COnlineSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(COnlineSearch)
	//}}AFX_DATA_INIT
	COptions* pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_ProfilesList.Load(pOp->m_SearchProfilesFile);
	m_RecordSyntax = YCSS_XML;
	CDialog::Create(IDD_DIALOG_ONLINESEARCH, pParent);
}


void COnlineSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COnlineSearch)
	DDX_Control(pDX, IDC_CHECK_SAVEPASS, m_chkSavePass);
	DDX_Control(pDX, IDC_SPIN_RECEND, m_spinRecEnd);
	DDX_Control(pDX, IDC_EDIT_RECEND, m_editRecEnd);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_EDIT_RAW, m_editRawData);
	DDX_Control(pDX, IDC_STATIC_RESULTS, m_staticResults);
	DDX_Control(pDX, IDC_SPIN_RECSTART, m_spinRecStart);
	DDX_Control(pDX, IDC_EDIT_RECSTART, m_editRecStart);
	DDX_Control(pDX, IDC_SPIN_PORT, m_spinPort);
	DDX_Control(pDX, IDC_COMBO_PROFILES, m_cboProfiles);
	DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
	DDX_Control(pDX, IDC_EDIT_PROXY, m_editProxy);
	DDX_Control(pDX, IDC_EDIT_PASS, m_editPass);
	DDX_Control(pDX, IDC_EDIT_GROUP, m_editGroup);
	DDX_Control(pDX, IDC_LIST_RESULTS, m_lstResults);
	DDX_Control(pDX, IDC_EDIT_SEARCHFOR, m_editSearchFor);
	DDX_Control(pDX, IDC_EDIT_HOST, m_editHost);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_DATABASE, m_editDatabase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COnlineSearch, CDialog)
	//{{AFX_MSG_MAP(COnlineSearch)
	ON_BN_CLICKED(ID_SEARCH, OnSearch)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_NEWPROFILE, OnButtonNewprofile)
	ON_CBN_SELCHANGE(IDC_COMBO_PROFILES, OnSelchangeComboProfiles)
	ON_BN_CLICKED(IDC_BUTTON_EDITPROFILE, OnButtonEditprofile)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULTS, OnDblclkListResults)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULTS, OnClickListResults)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(ID_CLOSE, OnCloseClick)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(COnlineSearch)
	ANCHOR_MAP_ENTRY(IDC_COMBO_PROFILES, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_NEWPROFILE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_EDITPROFILE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(ID_SEARCH, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(ID_CLOSE, ANF_TOP | ANF_RIGHT)

	ANCHOR_MAP_ENTRY(IDC_STATIC_SERVER, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_HOST, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_HOST, ANF_TOP | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_PORT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_SPIN_PORT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_PORT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_PROXY, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_PROXY, ANF_TOP | ANF_LEFT)

	ANCHOR_MAP_ENTRY(IDC_STATIC_USER, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_USER, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_USERNAME, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_GROUP, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_GROUP, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_PASS, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_PASS, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_CHECK_SAVEPASS, ANF_TOP | ANF_RIGHT)

	ANCHOR_MAP_ENTRY(IDC_STATIC_SEARCH, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_DATABASE, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_DATABASE, ANF_TOP | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_SEARCHFOR, ANF_TOP | ANF_LEFT | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_QUERY, ANF_TOP | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_QT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_RECSTART, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_RECSTART, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_SPIN_RECSTART, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_STATIC_RECEND, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_RECEND, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_SPIN_RECEND, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_NEXT, ANF_TOP | ANF_RIGHT)

	ANCHOR_MAP_ENTRY(IDC_RADIO_QT_PREFIX, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_RADIO_QT_CQL, ANF_TOP | ANF_RIGHT)

	ANCHOR_MAP_ENTRY(IDC_BUTTON_IMPORT, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_RESULTS, ANF_TOP | ANF_RIGHT | ANF_LEFT | ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_EDIT_RAW, ANF_RIGHT | ANF_LEFT | ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_STATIC_RESULTS, ANF_TOP | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COnlineSearch 

void COnlineSearch::OnSearch() 
{
	m_editRecEnd.SetWindowText(_T("10"));
	m_editRecStart.SetWindowText(_T("1"));
	DoSearch();
}

void COnlineSearch::DoSearch()
{
	CWaitCursor wait;

	// Save the infos to the profile
	SaveProfile();

#ifdef _DEBUG
	m_editRawData.Clear();
#endif

	m_lstResults.SetRedraw(FALSE);
	m_lstResults.DeleteAllItems();
	m_staticResults.SetWindowText(AfxLoadString(IDS_STRING_SEARCHRESULT));

	CString str;
	try {
		m_editHost.GetWindowText(str);
		CString port;
		m_editPort.GetWindowText(port);
		CYazConn conn(str, _ttoi(port));
		if (!conn.GetConnected()) {
			// Connection failed
			ShowError(conn.GetLastError());
		} else {
			// Connection established
			conn.SetOption(_T("implementationName"), _T("BibEdt Version ") + CAboutDlg::GetAppVersion());
			m_editUser.GetWindowText(str);
			if (!str.IsEmpty())
				conn.SetOption(_T("user"), str);
			m_editGroup.GetWindowText(str);
			if (!str.IsEmpty())
				conn.SetOption(_T("group"), str);
			m_editPass.GetWindowText(str);
			if (!str.IsEmpty())
				conn.SetOption(_T("password"), str);
			m_editProxy.GetWindowText(str);
			if (!str.IsEmpty())
				conn.SetOption(_T("proxy"), str);
			m_editDatabase.GetWindowText(str);
			if (!str.IsEmpty())
				conn.SetOption(_T("databaseName"), str);
			conn.SetOption(_T("preferredRecordSyntax"), m_RecordSyntax);
//			conn.SetOption(_T("preferredRecordSyntax"), "OPAC");

			m_editSearchFor.GetWindowText(str);
			
			CYazQuery* q = NULL;
			switch (GetQueryType()) {
			case QT_PREFIX:
				q = new CYazPrefixQuery();
				break;
			case QT_CQL:
				q = new CYazCQLQuery();
				break;
			case QT_CCL:
				q = new CYazCCLQuery();
				break;
			default:
				ShowError(IDS_STRING_STRANGEQUERYTYPE);
				return;
			}
			ASSERT(q);
			q->SetQueryString(str);
			CYazResultSet rs = conn.Search(q);

			m_editRecStart.GetWindowText(str);
			int recstart = _ttoi(str);
			m_editRecEnd.GetWindowText(str);
			int recend = _ttoi(str);
			int n = rs.GetCount();
			str.Format(AfxLoadString(IDS_STRING_SEARCHRESULTSNUM), n);
			m_staticResults.SetWindowText(str);
			if (recend > 0)
				n = min(n, recend);
			int ix = -1;
#ifdef _DEBUG
			CFile dbgfile;
			try {
				dbgfile.Open(COptions::AddBackslash(COptions::GetAppPath()) + _T("result.xml"), CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
			} catch (...) {
			}
#endif
			for (int i = recstart - 1; i < n; i++) {
				CYazRecord rec = rs.GetRecord(i);
				CString rawdata = rec.GetRaw();

#ifdef _DEBUG
				try {
					dbgfile.Write(rawdata, rawdata.GetLength());
				} catch (...) {
				}

				int selstart = m_editRawData.GetWindowTextLength();
				m_editRawData.SetSel(selstart, selstart, TRUE);
				m_editRawData.ReplaceSel(rawdata + _T("\r\n"));
#endif

				// Add the item to m_Results list
				CBibItem* item = m_Results.New();
				item->SetType(rec.GetType());
				item->Add(_T("raw"), rawdata);

				str = rec.GetValue(STR_AUTHOR);
				if (!str.IsEmpty())
					item->Add(STR_AUTHOR, str);
				str = rec.GetValue(STR_EDITOR);
				if (!str.IsEmpty())
					item->Add(STR_EDITOR, str);
				str = rec.GetValue(STR_TITLE);
				if (!str.IsEmpty())
					item->Add(STR_TITLE, str);
				str = rec.GetValue(STR_EDITION);
				if (!str.IsEmpty())
					item->Add(STR_EDITION, str);
				str = rec.GetValue(STR_SERIES);
				if (!str.IsEmpty())
					item->Add(STR_SERIES, str);
				str = rec.GetValue(_T("Performer"));
				if (!str.IsEmpty())
					item->Add(_T("Performer"), str);
				str = rec.GetValue(STR_YEAR);
				if (!str.IsEmpty())
					item->Add(STR_YEAR, str);
				str = rec.GetValue(_T("ISBN"));
				if (!str.IsEmpty())
					item->Add(_T("ISBN"), str);
				str = rec.GetValue(_T("Topic"));
				if (!str.IsEmpty())
					item->Add(_T("Topic"), str);
				str = rec.GetValue(_T("Contents"));
				if (!str.IsEmpty())
					item->Add(_T("Contents"), str);

				// Add it to the listview
				CField* field = item->Find(STR_AUTHOR);
				if (!field)
					field = item->Find(STR_EDITOR);
				if (!field)
					field = item->Find(_T("Performer"));
				if (field)
					ix = m_lstResults.InsertItem(ix+1, field->GetValue(), -1);
				else
					ix = m_lstResults.InsertItem(ix+1, NULL, -1);
				m_lstResults.SetItemData(ix, (DWORD)item);
				field = item->Find(STR_TITLE);
				if (field)
					m_lstResults.SetItemText(ix, 1, field->GetValue());
				field = item->Find(STR_YEAR);
				if (field)
					m_lstResults.SetItemText(ix, 2, field->GetValue());
			}

			delete q;

#ifdef _DEBUG
			try {
				dbgfile.Close();
			} catch (...) {
			}
#endif
		} // if (conn.GetConnected())
	} catch (...) {
		ShowError(IDS_STRING_YAZEXCEPTION);
	}
	m_lstResults.SetRedraw();
	m_staticResults.Invalidate();
}

BOOL COnlineSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON_ONLINESEARCH);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);

	// SHRT_MAX = 32767 also maximum number of ports
	m_spinPort.SetRange(1, SHRT_MAX);
	m_spinRecStart.SetRange(1, SHRT_MAX);
	m_spinRecEnd.SetRange(0, SHRT_MAX);
	SetQueryType(QT_PREFIX);

	DWORD extst = m_lstResults.GetExtendedStyle();
	m_lstResults.SetExtendedStyle(extst | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);
	m_lstResults.InsertColumn(0, _T("Author/Editor"), LVCFMT_LEFT, AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col1"), 200));
	m_lstResults.InsertColumn(1, _T("Title"), LVCFMT_LEFT, AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col2"), 300));
	m_lstResults.InsertColumn(2, _T("Year"), LVCFMT_LEFT, AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col3"), 50));

	m_editRecEnd.SetWindowText(_T("10"));
	m_editRecStart.SetWindowText(_T("1"));

#ifdef _DEBUG
	// Set some default values
	m_editHost.SetWindowText(_T("z3950.loc.gov"));
	m_editPort.SetWindowText(_T("7090"));
	m_editDatabase.SetWindowText(_T("Voyager"));
	// The ISBN number, isn't it?
	m_editSearchFor.SetWindowText(_T("@attr 1=7 0253333490"));
#endif

	// Add profiles
	UpdateProfileList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void COnlineSearch::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void COnlineSearch::OnButtonImport() 
{
	ASSERT(m_BibList);
	for (int i = 0; i < m_lstResults.GetItemCount(); i++) {
		if (GetSelected(i)) {
			CBibItem* item = (CBibItem*)m_lstResults.GetItemData(i);
			ASSERT(item);
			CBibItem* newitem = m_BibList->New();
			newitem->Assign(item);
			// Delete raw field
			CField* rf = newitem->Find(_T("raw"));
			if (rf)
				newitem->Delete(rf);
			newitem->SetKey(m_BibList->GenerateKey(newitem));
			m_Document->UpdateAllViews(NULL, UR_RECADDED, newitem);
		}
	}
	if (m_Document->GetSelected() == NULL) {
		// Select one
		m_Document->SetSelected(m_BibList->GetFirst());
		if (m_Document->GetSelected() != NULL)
			m_Document->UpdateAllViews(NULL, UR_SELECTED, m_Document->GetSelected());
	}
}

QUERY_TYPE COnlineSearch::GetQueryType()
{
	CButton* qt = (CButton*)GetDlgItem(IDC_RADIO_QT_PREFIX);
	if (qt->GetCheck())
		return QT_PREFIX;
	qt = (CButton*)GetDlgItem(IDC_RADIO_QT_CQL);
	if (qt->GetCheck())
		return QT_CQL;
	return QT_UNKNOWN;
}

void COnlineSearch::SetQueryType(QUERY_TYPE q)
{
	CButton* qt = NULL;
	switch (q) {
	case QT_PREFIX:
		qt = (CButton*)GetDlgItem(IDC_RADIO_QT_PREFIX);
		qt->SetCheck(TRUE);
		qt = (CButton*)GetDlgItem(IDC_RADIO_QT_CQL);
		qt->SetCheck(FALSE);
		break;
	case QT_CQL:
		qt = (CButton*)GetDlgItem(IDC_RADIO_QT_PREFIX);
		qt->SetCheck(FALSE);
		qt = (CButton*)GetDlgItem(IDC_RADIO_QT_CQL);
		qt->SetCheck(TRUE);
		break;
	}
}

BOOL COnlineSearch::GetSelected(int i)
{
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = i;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (m_lstResults.GetItem(&item)) {
		return BIT_SET(item.state, LVIS_SELECTED);
	} else
		return FALSE;
}

void COnlineSearch::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("OnlineSearchDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);

		// Give the query textbox the focus
		m_editSearchFor.SetFocus();
	}
}

void COnlineSearch::OnDestroy() 
{
	COptions* pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_ProfilesList.Save(pOp->m_SearchProfilesFile);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col1"), m_lstResults.GetColumnWidth(0));
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col2"), m_lstResults.GetColumnWidth(1));
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("OnlineSearch.lv.col3"), m_lstResults.GetColumnWidth(2));

	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("OnlineSearchDialog"), wp);
	if (m_Document->m_OnlineSearchDialog != NULL) {
		m_Document->m_OnlineSearchDialog = NULL;
	}

	CDialog::OnDestroy();
}

void COnlineSearch::OnButtonNewprofile() 
{
	CInputBox dlg;
	dlg.SetCaption(AfxLoadString(IDS_STRING_NEWPROFCAP));
	dlg.SetPrompt(AfxLoadString(IDS_STRING_NEWPROFPROMPT));
	if (dlg.DoModal() == IDOK && !dlg.m_strText.IsEmpty()) {
		CString name = dlg.m_strText;
		CSearchProfile* profile = m_ProfilesList.New(name);
		int i = m_cboProfiles.AddString(name);
		m_cboProfiles.SetItemDataPtr(i, profile);
		m_cboProfiles.SetCurSel(i);
		OnSelchangeComboProfiles();
		m_editHost.SetFocus();
	}
}

void COnlineSearch::OnSelchangeComboProfiles() 
{
	int sel = m_cboProfiles.GetCurSel();
	if (sel == -1)
		return;
	CSearchProfile* profile = (CSearchProfile*)m_cboProfiles.GetItemDataPtr(sel);
	if (profile == NULL)
		return;

	m_editHost.SetWindowText(profile->m_Host);
	CString s;
	s.Format(_T("%d"), profile->m_Port);
	m_editPort.SetWindowText(s);
	m_editProxy.SetWindowText(profile->m_Proxy);
	m_editUser.SetWindowText(profile->m_User);
	m_editGroup.SetWindowText(profile->m_Group);
	m_editPass.SetWindowText(profile->m_Password);
	m_chkSavePass.SetCheck(profile->m_SavePass);
	m_editDatabase.SetWindowText(profile->m_Database);
	SetQueryType(profile->m_QueryType);
}

void COnlineSearch::SaveProfile()
{
	int sel = m_cboProfiles.GetCurSel();
	if (sel == -1)
		return;
	CSearchProfile* profile = (CSearchProfile*)m_cboProfiles.GetItemDataPtr(sel);
	if (profile == NULL)
		return;

	CString s;
	m_editHost.GetWindowText(s);
	profile->m_Host = s;
	m_editPort.GetWindowText(s);
	profile->m_Port = _ttoi(s);
	m_editProxy.GetWindowText(s);
	profile->m_Proxy = s;
	m_editUser.GetWindowText(s);
	profile->m_User = s;
	m_editGroup.GetWindowText(s);
	profile->m_Group = s;
	m_editDatabase.GetWindowText(s);
	profile->m_Database = s;
	profile->m_QueryType = GetQueryType();
	m_editPass.GetWindowText(s);
	profile->m_Password = s;
	int i = m_chkSavePass.GetCheck();
	profile->m_SavePass = (BOOL)i;
}

void COnlineSearch::OnButtonEditprofile() 
{
	CSearchProfilesDialog dlg;
	dlg.SetProfiles(&m_ProfilesList);
	if (dlg.DoModal() == IDOK) {
		m_ProfilesList.Assign(&dlg.m_Profiles);
		UpdateProfileList();
	}
}

void COnlineSearch::UpdateProfileList()
{
	m_cboProfiles.ResetContent();
	POSITION p = m_ProfilesList.GetHeadPosition();
	while (p) {
		CSearchProfile* prof = (CSearchProfile*)m_ProfilesList.GetNext(p);
		int i = m_cboProfiles.AddString(prof->m_Name);
		m_cboProfiles.SetItemDataPtr(i, prof);
	}
	if (m_cboProfiles.GetCount() > 0) {
		m_cboProfiles.SetCurSel(0);
		OnSelchangeComboProfiles();
	}
}

void COnlineSearch::OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_lstResults.GetSelectedCount() > 0)
		OnButtonImport();	
	*pResult = 0;
}

void COnlineSearch::OnClickListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_btnImport.EnableWindow(m_lstResults.GetSelectedCount() > 0);	
	*pResult = 0;
}

void COnlineSearch::OnButtonNext() 
{
	CString str;
	m_editRecEnd.GetWindowText(str);
	int i = _ttoi(str) + 1;
	CString str2;
	m_editRecStart.GetWindowText(str2);
	int i2 = _ttoi(str2);
	str.Format(_T("%d"), i);
	m_editRecStart.SetWindowText(str);
	i = i + (i-i2) - 1;
	str.Format(_T("%d"), i);
	m_editRecEnd.SetWindowText(str);
	DoSearch();
}

void COnlineSearch::OnCloseClick() 
{
	SendMessage(WM_CLOSE, 0, 0);	
}

void COnlineSearch::OnButtonHelp() 
{
	CString f = COptions::FindFile(YAZ_MANUAL);
	if (f.IsEmpty())
		f = YAZ_MANUAL_URL;
	ShellExecute(0, _T("open"), f, NULL, NULL, SW_NORMAL);
}
