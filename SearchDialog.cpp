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

  $Id: SearchDialog.cpp,v 1.12 2006/06/17 11:43:35 stievie Exp $
*/

// SearchDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "SearchDialog.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSearchDialog 


CSearchDialog::CSearchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDialog)
	m_boolMatchBase = FALSE;
	m_boolSelOnly = FALSE;
	m_boolWholeWords = FALSE;
	m_boolRegEx = FALSE;
	m_strSearchFields = _T("");
	//}}AFX_DATA_INIT
	m_SearchText = _T("");
	m_SearchFields = NULL;
}


void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDialog)
	DDX_Control(pDX, IDC_COMBO_FIELDS, m_cboSearchFields);
	DDX_Control(pDX, IDC_BUTTON_SEARCH_MARKALL, m_btnMarkAll);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDC_COMBO_TEXT, m_cboText);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_boolMatchBase);
	DDX_Check(pDX, IDC_CHECK_SELONLY, m_boolSelOnly);
	DDX_Check(pDX, IDC_CHECK_WHOLEWORDS, m_boolWholeWords);
	DDX_Check(pDX, IDC_CHECK_REGEX, m_boolRegEx);
	DDX_CBString(pDX, IDC_COMBO_FIELDS, m_strSearchFields);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
	//{{AFX_MSG_MAP(CSearchDialog)
	ON_CBN_EDITCHANGE(IDC_COMBO_TEXT, OnEditchangeComboText)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXT, OnSelchangeComboText)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_MARKALL, OnButtonSearchMarkall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSearchDialog 

BOOL CSearchDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LoadHistory();
	if (!m_SearchText.IsEmpty())
		m_cboText.SetWindowText(m_SearchText);
	int i = 0;
	i = m_cboSearchFields.AddString(AfxLoadString(IDS_STRING_ALLFIELDS));
	if (!m_strSearchFields.IsEmpty() && m_strSearchFields.CompareNoCase(AfxLoadString(IDS_STRING_ALLFIELDS)) != 0)
		i = m_cboSearchFields.AddString(m_strSearchFields);

	if (m_SearchFields) {
		POSITION p = m_SearchFields->GetHeadPosition();
		while (p) {
			m_cboSearchFields.AddString(m_SearchFields->GetNext(p));
		}
	}
	m_cboSearchFields.SetCurSel(i);
	OnEditchangeComboText();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSearchDialog::Update()
{
	CString s;
	m_cboText.GetWindowText(s);
	if (s.IsEmpty()) {
		ShowError(IDS_STRING_ENTERSTRING);
		m_cboText.SetFocus();
		return;
	}
	m_SearchText = s;
	int i = m_cboText.FindString(0, s);
	if (i != CB_ERR) {
		m_cboText.DeleteString(i);
	}
	m_cboText.InsertString(0, s);
	SaveHistory();
}

void CSearchDialog::OnOK()
{
	Update();
	CDialog::OnOK();
}

void CSearchDialog::LoadHistory()
{
	CString his = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("SearchHistory"));
	int p = 0;
	if (!his.IsEmpty()) {
		CString s;
		do {
			p = his.Find(_T("\n"), 0);
			if (p != -1) {
				s = his.Mid(0, p);
				m_cboText.AddString(s);
			}
			his.Delete(0, p + 1);
		} while (p != -1);
	}
}

void CSearchDialog::SaveHistory()
{
	CString his;
	CString s;
	int c = min(m_cboText.GetCount(), MAX_HISTORY);
	for (int i = 0; i < c; i++) {
		m_cboText.GetLBText(i, s);
		if (!s.IsEmpty())
			his += s + _T("\n");
	}
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("SearchHistory"), his);
}

void CSearchDialog::OnEditchangeComboText() 
{
	m_BtnOk.EnableWindow(m_cboText.GetWindowTextLength());	
	m_btnMarkAll.EnableWindow(m_cboText.GetWindowTextLength());	
}

void CSearchDialog::OnSelchangeComboText() 
{
	int i = m_cboText.SendMessage(CB_GETCURSEL, 0, 0);
	int len = 0;
	if (i != -1)
		len = m_cboText.SendMessage(CB_GETLBTEXTLEN, i, 0);
	m_BtnOk.EnableWindow(len > 0);	
	m_btnMarkAll.EnableWindow(len > 0);
}

void CSearchDialog::OnButtonSearchMarkall() 
{
	UpdateData();
	Update();
	EndDialog(IDC_BUTTON_SEARCH_MARKALL);	
}