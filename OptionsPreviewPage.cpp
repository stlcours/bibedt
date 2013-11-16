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

  $Id: OptionsPreviewPage.cpp,v 1.2 2006/08/07 17:45:26 stievie Exp $
*/

// OptionsPreviewPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "MainFrm.h"
#include "OptionsPreviewPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsPreviewPage 

IMPLEMENT_DYNCREATE(COptionsPreviewPage, CPropertyPage)

COptionsPreviewPage::COptionsPreviewPage() : CPropertyPage(COptionsPreviewPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsPreviewPage)
	//}}AFX_DATA_INIT
}

COptionsPreviewPage::~COptionsPreviewPage()
{
}

void COptionsPreviewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPreviewPage)
	DDX_Control(pDX, IDC_COMBO_FNT_SANS, m_cboSans);
	DDX_Control(pDX, IDC_COMBO_FNT_PROP, m_cboProp);
	DDX_Control(pDX, IDC_COMBO_FNT_MONO, m_cboMono);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPreviewPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsPreviewPage)
	ON_CBN_EDITCHANGE(IDC_COMBO_FNT_PROP, OnEditchangeComboFntProp)
	ON_CBN_SELCHANGE(IDC_COMBO_FNT_PROP, OnSelchangeComboFntProp)
	ON_CBN_EDITCHANGE(IDC_COMBO_FNT_MONO, OnEditchangeComboFntProp)
	ON_CBN_SELCHANGE(IDC_COMBO_FNT_MONO, OnSelchangeComboFntProp)
	ON_CBN_EDITCHANGE(IDC_COMBO_FNT_SANS, OnEditchangeComboFntProp)
	ON_CBN_SELCHANGE(IDC_COMBO_FNT_SANS, OnSelchangeComboFntProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsPreviewPage 

BOOL COptionsPreviewPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CDC *pDC = GetDC();
	EnumFonts(pDC->GetSafeHdc(), NULL, (FONTENUMPROC)EnumFontProc, (LPARAM)&m_cboSans);
	CString str;
	for (int i = 0; i < m_cboSans.GetCount(); i++) {
		m_cboSans.GetLBText(i, str);
		m_cboProp.AddString(str);
		m_cboMono.AddString(str);
	}
	m_cboSans.SelectString(-1, m_Options->m_FontSans);
	m_cboProp.SelectString(-1, m_Options->m_FontProp);
	m_cboMono.SelectString(-1, m_Options->m_FontMono);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CALLBACK COptionsPreviewPage::EnumFontProc(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
	((CComboBox *)lpData)->AddString(lplf->lfFaceName);
	return TRUE;
}

BOOL COptionsPreviewPage::OnApply() 
{
	m_cboMono.GetWindowText(m_Options->m_FontMono);
	m_cboProp.GetWindowText(m_Options->m_FontProp);
	m_cboSans.GetWindowText(m_Options->m_FontSans);
	CMainFrame* main = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	main->SendMessageToDescendants(WM_BE_FONT_CHANGED, 0, 0);

	return CPropertyPage::OnApply();
}

void COptionsPreviewPage::OnEditchangeComboFntProp() 
{
	SetModified();
}

void COptionsPreviewPage::OnSelchangeComboFntProp() 
{
	SetModified();
}
