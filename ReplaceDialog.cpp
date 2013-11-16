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

  $Id: ReplaceDialog.cpp,v 1.9 2006/06/06 18:52:18 stievie Exp $
*/

// ReplaceDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "ReplaceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CReplaceDialog 


CReplaceDialog::CReplaceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplaceDialog)
	m_MatchCase = FALSE;
	m_RegExpr = FALSE;
	m_WholeWords = FALSE;
	m_ReplaceText = _T("");
	m_SearchText = _T("");
	m_SelOnly = FALSE;
	//}}AFX_DATA_INIT
}


void CReplaceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceDialog)
	DDX_Control(pDX, IDC_BUTTON_REPLACEALL, m_BtnReplaceAll);
	DDX_Control(pDX, ID_BUTTON_FINDNEXT, m_BtnFind);
	DDX_Control(pDX, IDC_BUTTON_REPLACE, m_btnReplace);
	DDX_Control(pDX, IDC_COMBO_TEXT, m_cboSearchText);
	DDX_Control(pDX, IDC_COMBO_REPLACETEXT, m_cboReplaceText);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_MatchCase);
	DDX_Check(pDX, IDC_CHECK_REGEXPR, m_RegExpr);
	DDX_Check(pDX, IDC_CHECK_WHOLEWORDS, m_WholeWords);
	DDX_CBString(pDX, IDC_COMBO_REPLACETEXT, m_ReplaceText);
	DDX_CBString(pDX, IDC_COMBO_TEXT, m_SearchText);
	DDX_Check(pDX, IDC_CHECK_SELONLY, m_SelOnly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceDialog, CDialog)
	//{{AFX_MSG_MAP(CReplaceDialog)
	ON_BN_CLICKED(ID_BUTTON_FINDNEXT, OnButtonFindnext)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, OnButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_REPLACEALL, OnButtonReplaceall)
	ON_WM_DESTROY()
	ON_CBN_EDITCHANGE(IDC_COMBO_TEXT, OnEditchangeComboText)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXT, OnSelchangeComboText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CReplaceDialog 

BOOL CReplaceDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadHistory(_T("SearchHistory"), &m_cboSearchText);	
	LoadHistory(_T("ReplaceHistory"), &m_cboReplaceText);
	OnEditchangeComboText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CReplaceDialog::SetEditor(CScintillaBibWnd *editor)
{
	m_Editor = editor;
}

void CReplaceDialog::OnButtonFindnext() 
{
	UpdateData();
	m_Editor->m_MatchCase = m_MatchCase;
	m_Editor->m_RegExpr = m_RegExpr;
	m_Editor->m_WholeWords = m_WholeWords;
	if (m_Editor->SearchText(m_SearchText.GetBuffer(m_SearchText.GetLength()+1)))
		m_btnReplace.EnableWindow();
	else {
		m_btnReplace.EnableWindow(FALSE);
		MessageBeep(MB_ICONEXCLAMATION);
	}
}

void CReplaceDialog::OnButtonReplace() 
{
	UpdateData();

	m_Editor->SetSelectedText(m_ReplaceText.GetBuffer(m_ReplaceText.GetLength()+1));
	m_Editor->m_MatchCase = m_MatchCase;
	m_Editor->m_RegExpr = m_RegExpr;
	m_Editor->m_WholeWords = m_WholeWords;
	BOOL found = m_Editor->SearchText(m_SearchText.GetBuffer(m_SearchText.GetLength()+1));
	if (!found) {
		m_btnReplace.EnableWindow(FALSE);
		MessageBeep(MB_ICONEXCLAMATION);
	}
}

void CReplaceDialog::OnButtonReplaceall() 
{
	UpdateData();
	m_Editor->m_MatchCase = m_MatchCase;
	m_Editor->m_RegExpr = m_RegExpr;
	m_Editor->m_WholeWords = m_WholeWords;
	m_Editor->ReplaceAll(m_SearchText.GetBuffer(m_SearchText.GetLength()+1), 
		m_ReplaceText.GetBuffer(m_ReplaceText.GetLength()+1), m_SelOnly);
	EndDialog(IDC_BUTTON_REPLACEALL);
}

void CReplaceDialog::LoadHistory(CString key, CComboBox* cbo)
{
	CString his = AfxGetApp()->GetProfileString(SETTINGS_KEY, key);
	int p = 0;
	if (!his.IsEmpty()) {
		CString s;
		do {
			p = his.Find(_T("\n"), 0);
			if (p != -1) {
				s = his.Mid(0, p);
				cbo->AddString(s);
			}
			his.Delete(0, p + 1);
		} while (p != -1);
	}
}

void CReplaceDialog::SaveHistory(CString key, CComboBox *cbo)
{
	CString his;
	CString s;
	int c = min(cbo->GetCount(), MAX_HISTORY);
	for (int i = 0; i < c; i++) {
		cbo->GetLBText(i, s);
		if (!s.IsEmpty())
			his += s + _T("\n");
	}
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, key, his);
}

void CReplaceDialog::OnDestroy() 
{
	CString s;
	m_cboSearchText.GetWindowText(s);
	int i = m_cboSearchText.FindString(0, s);
	if (i != CB_ERR) {
		m_cboSearchText.DeleteString(i);
	}
	m_cboSearchText.InsertString(0, s);
	SaveHistory(_T("SearchHistory"), &m_cboSearchText);	

	m_cboReplaceText.GetWindowText(s);
	i = m_cboReplaceText.FindString(0, s);
	if (i != CB_ERR) {
		m_cboReplaceText.DeleteString(i);
	}
	m_cboReplaceText.InsertString(0, s);
	SaveHistory(_T("ReplaceHistory"), &m_cboReplaceText);	

	CDialog::OnDestroy();
}

void CReplaceDialog::OnEditchangeComboText() 
{
	m_BtnFind.EnableWindow(m_cboSearchText.GetWindowTextLength());
	m_BtnReplaceAll.EnableWindow(m_cboSearchText.GetWindowTextLength());
}

void CReplaceDialog::OnSelchangeComboText() 
{
	int i = m_cboSearchText.SendMessage(CB_GETCURSEL, 0, 0);
	int len = 0;
	if (i != -1)
		len = m_cboSearchText.SendMessage(CB_GETLBTEXTLEN, i, 0);
	m_BtnFind.EnableWindow(len > 0);	
	m_BtnReplaceAll.EnableWindow(len > 0);	
}
