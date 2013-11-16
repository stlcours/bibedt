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

  $Id: CopyCitationDialog.cpp,v 1.9 2006/07/29 11:33:14 stievie Exp $
*/

// CopyCitationDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "CopyCitationDialog.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCopyCitationDialog 


CCopyCitationDialog::CCopyCitationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyCitationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyCitationDialog)
	//}}AFX_DATA_INIT
	m_Keys = new CStringList();
	m_CiteFormat = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("LastCiteFormat"), CITE_CITE);
}


void CCopyCitationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyCitationDialog)
	DDX_Control(pDX, IDC_STATIC_CUSTOM, m_StCustom);
	DDX_Control(pDX, IDC_COMBO_CUSTOM, m_ComboCustom);
	DDX_Control(pDX, IDC_LIST_KEYS, m_ListKeys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopyCitationDialog, CDialog)
	//{{AFX_MSG_MAP(CCopyCitationDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_CITE, OnRadioCite)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioCustom)
	ON_BN_CLICKED(IDC_RADIO_NOCITE, OnRadioNocite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCopyCitationDialog 

void CCopyCitationDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	delete m_Keys;	
}

BOOL CCopyCitationDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// Load combobox with cite strings
	LoadHistory();

	m_ListKeys.ResetContent();
	POSITION p = m_Keys->GetHeadPosition();
	while (p) {
		CString key = m_Keys->GetNext(p);
		int i = m_ListKeys.AddString(key);
		m_ListKeys.SetSel(i, TRUE);
	}
	m_ListKeys.SendMessage(WM_VSCROLL, MAKEWPARAM(SB_TOP, 0), 0);

	CButton *button = NULL;
	switch (m_CiteFormat) {
	case CITE_KEYONLY:
		button = (CButton*)GetDlgItem(IDC_RADIO_KEYONLY);
		break;
	case CITE_CITE:
		button = (CButton*)GetDlgItem(IDC_RADIO_CITE);
		break;
	case CITE_NOCITE:
		button = (CButton*)GetDlgItem(IDC_RADIO_NOCITE);
		break;
	case CITE_CUSTOM:
		button = (CButton*)GetDlgItem(IDC_RADIO_CUSTOM);
		break;
	}
	if (button)
		button->SetCheck(1);
	m_ComboCustom.EnableWindow(m_CiteFormat == CITE_CUSTOM);

	m_ComboCustom.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CCopyCitationDialog::AddKey(CString key)
{
	m_Keys->AddTail(key);
}

CString CCopyCitationDialog::GetCopyString()
{
	return m_CopyString;
}

void CCopyCitationDialog::OnRadioCite() 
{
	UpdateFormat();
	m_ComboCustom.EnableWindow(m_CiteFormat == CITE_CUSTOM);	
}

void CCopyCitationDialog::OnRadioCustom() 
{
	UpdateFormat();
	m_ComboCustom.EnableWindow(m_CiteFormat == CITE_CUSTOM);	
}

void CCopyCitationDialog::OnRadioNocite() 
{
	UpdateFormat();
	m_ComboCustom.EnableWindow(m_CiteFormat == CITE_CUSTOM);	
}

void CCopyCitationDialog::OnOK()
{
	UpdateCopyString();

	CString s;
	m_ComboCustom.GetWindowText(s);
	int i = m_ComboCustom.FindString(0, s);
	if (i != CB_ERR) {
		m_ComboCustom.DeleteString(i);
	}
	m_ComboCustom.InsertString(0, s);
	SaveHistory();
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("LastCiteFormat"), m_CiteFormat);

	CDialog::OnOK();
}

int CCopyCitationDialog::GetCiteFormat()
{
	return m_CiteFormat;
}

void CCopyCitationDialog::SetCiteFormat(int format)
{
	m_CiteFormat = format;
}

void CCopyCitationDialog::UpdateFormat()
{
	m_CiteFormat = -1;
	CButton *button = (CButton*)GetDlgItem(IDC_RADIO_KEYONLY);
	if (button->GetCheck() == 1) {
		m_CiteFormat = CITE_KEYONLY;
	}
	button = (CButton*)GetDlgItem(IDC_RADIO_CITE);
	if (button->GetCheck() == 1) {
		m_CiteFormat = CITE_CITE;
	}
	button = (CButton*)GetDlgItem(IDC_RADIO_NOCITE);
	if (button->GetCheck() == 1) {
		m_CiteFormat = CITE_NOCITE;
	}
	button = (CButton*)GetDlgItem(IDC_RADIO_CUSTOM);
	if (button->GetCheck() == 1) {
		m_CiteFormat = CITE_CUSTOM;
	}
}

CString CCopyCitationDialog::GetFormatString()
{
	UpdateFormat();
	CString res = _T("");
	switch (m_CiteFormat) {
	case CITE_KEYONLY:
		res = _T("%s");
		break;
	case CITE_CITE:
		res = _T("\\cite{%s}");
		break;
	case CITE_NOCITE:
		res = _T("\\nocite{%s}");
		break;
	case CITE_CUSTOM:
		m_ComboCustom.GetWindowText(res);
		break;
	}
	return res;
}

void CCopyCitationDialog::UpdateCopyString()
{
	CString format = GetFormatString();
	if (format.IsEmpty())
		return;
	CString res = _T("");
	int n;
	CString key;
	CString e;
	for (int i = 0; i < m_ListKeys.GetCount(); i++) {
		if (m_ListKeys.GetSel(i) > 0) {
			n = m_ListKeys.GetTextLen(i);
			m_ListKeys.GetText(i, key.GetBuffer(n));
			key.ReleaseBuffer();
			e.Format(format, key);
			res += e + NL;
		}
	}
	if (!res.IsEmpty()) {
		if (res.Right(2).Compare(NL) == 0)
			// delete trailing CrLf
			res.Delete(res.GetLength());
	}
	m_CopyString = res;
}

void CCopyCitationDialog::LoadHistory()
{
	CString his = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("CiteFormats"));
	int p = 0;
	if (!his.IsEmpty()) {
		m_ComboCustom.ResetContent();
		CString s;
		do {
			p = his.Find(_T("\n"), 0);
			if (p != -1) {
				s = his.Mid(0, p);
				m_ComboCustom.AddString(s);
			}
			his.Delete(0, p + 1);
		} while (p != -1);
	}
}

void CCopyCitationDialog::SaveHistory()
{
	CString his;
	CString s;
	int c = min(m_ComboCustom.GetCount(), MAX_HISTORY);
	for (int i = 0; i < c; i++) {
		m_ComboCustom.GetLBText(i, s);
		if (!s.IsEmpty())
			his += s + _T("\n");
	}
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("CiteFormats"), his);
}
