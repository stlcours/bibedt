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

  $Id: FindDialog.cpp,v 1.11 2006/06/06 18:52:18 stievie Exp $
*/

// FindDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "FindDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDialog 


CFindDialog::CFindDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDialog)
	m_MatchCase = FALSE;
	m_WholeWords = FALSE;
	m_RegExpr = FALSE;
	//}}AFX_DATA_INIT
	m_Backward = FALSE;
}


void CFindDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDialog)
	DDX_Control(pDX, IDC_BUTTON_MARK, m_BtnMark);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDC_COMBO_TEXT, m_cboText);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_MatchCase);
	DDX_Check(pDX, IDC_CHECK_WHOLEWORDS, m_WholeWords);
	DDX_Check(pDX, IDC_CHECK_REGEXPR, m_RegExpr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDialog)
	ON_BN_CLICKED(IDC_BUTTON_MARK, OnButtonMark)
	ON_CBN_EDITCHANGE(IDC_COMBO_TEXT, OnEditchangeComboText)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXT, OnSelchangeComboText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFindDialog 

void CFindDialog::OnOK()
{
	Update();
	CDialog::OnOK();
}

BOOL CFindDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CButton *button;
	if (m_Backward)
		button = (CButton*)GetDlgItem(IDC_RADIO_UP);
	else
		button = (CButton*)GetDlgItem(IDC_RADIO_DOWN);
	button->SetCheck(1);
	LoadHistory();
	if (!m_SearchText.IsEmpty())
		m_cboText.SetWindowText(m_SearchText);
	OnEditchangeComboText();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CFindDialog::LoadHistory()
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

void CFindDialog::SaveHistory()
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

void CFindDialog::OnButtonMark() 
{
	UpdateData();
	Update();
	EndDialog(IDC_BUTTON_MARK);	
}

void CFindDialog::Update()
{
	CButton *button = (CButton*)GetDlgItem(IDC_RADIO_UP);
	m_Backward = (button->GetCheck() == 1);
	m_cboText.GetWindowText(m_SearchText);
	int i = m_cboText.FindString(0, m_SearchText);
	if (i != CB_ERR) {
		m_cboText.DeleteString(i);
	}
	m_cboText.InsertString(0, m_SearchText);
	SaveHistory();
}

void CFindDialog::OnEditchangeComboText() 
{
	m_BtnOk.EnableWindow(m_cboText.GetWindowTextLength());
	m_BtnMark.EnableWindow(m_cboText.GetWindowTextLength());
}

void CFindDialog::OnSelchangeComboText() 
{
	int i = m_cboText.SendMessage(CB_GETCURSEL, 0, 0);
	int len = 0;
	if (i != -1)
		len = m_cboText.SendMessage(CB_GETLBTEXTLEN, i, 0);
	m_BtnOk.EnableWindow(len > 0);	
	m_BtnMark.EnableWindow(len > 0);	
}
