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

  $Id: OptionsGeneralPage.cpp,v 1.14 2006/07/29 11:33:14 stievie Exp $
*/

// OptionsGeneralPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsGeneralPage 

IMPLEMENT_DYNCREATE(COptionsGeneralPage, CPropertyPage)

COptionsGeneralPage::COptionsGeneralPage() : CPropertyPage(COptionsGeneralPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsGeneralPage)
	m_boolBackup = FALSE;
	m_boolShowCiteDlg = FALSE;
	m_boolSortCase = FALSE;
	m_boolSortOnSave = FALSE;
	m_boolTranslate = FALSE;
	m_strCiteFormat = _T("");
	m_intLineLength = 0;
	m_boolOpenLast = FALSE;
	m_strQsFields = _T("");
	m_boolReplaceSpecialChar = FALSE;
	m_boolScrollToSelected = FALSE;
	m_boolAutoCompleteValues = FALSE;
	m_DOIURL = _T("");
	m_boolDisableSave = FALSE;
	//}}AFX_DATA_INIT
}

COptionsGeneralPage::~COptionsGeneralPage()
{
}

void COptionsGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsGeneralPage)
	DDX_Control(pDX, IDC_SPIN_LINELENGTH, m_spnLineLength);
	DDX_Check(pDX, IDC_CHECK_BACKUP, m_boolBackup);
	DDX_Check(pDX, IDC_CHECK_SHOWCITEDLG, m_boolShowCiteDlg);
	DDX_Check(pDX, IDC_CHECK_SORTCASE, m_boolSortCase);
	DDX_Check(pDX, IDC_CHECK_SORTONSAVE, m_boolSortOnSave);
	DDX_Check(pDX, IDC_CHECK_TRANSLATE, m_boolTranslate);
	DDX_Text(pDX, IDC_EDIT_CITEFORMAT, m_strCiteFormat);
	DDX_Text(pDX, IDC_EDIT_LINELENGTH, m_intLineLength);
	DDV_MinMaxInt(pDX, m_intLineLength, 10, 1024);
	DDX_Check(pDX, IDC_CHECK_OPENLAST, m_boolOpenLast);
	DDX_Text(pDX, IDC_EDIT_QSFIELDS, m_strQsFields);
	DDX_Check(pDX, IDC_CHECK_REPLSPECCHAR, m_boolReplaceSpecialChar);
	DDX_Check(pDX, IDC_CHECK_SCOLLSEL, m_boolScrollToSelected);
	DDX_Check(pDX, IDC_CHECK_AUTOCOMPL, m_boolAutoCompleteValues);
	DDX_Text(pDX, IDC_EDIT_DOIURL, m_DOIURL);
	DDX_Check(pDX, IDC_CHECK_NOSAVE, m_boolDisableSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsGeneralPage)
	ON_BN_CLICKED(IDC_CHECK_BACKUP, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_TRANSLATE, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_SORTCASE, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_SORTONSAVE, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_SHOWCITEDLG, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_TRANSLATE, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_OPENLAST, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_REPLSPECCHAR, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_SCOLLSEL, OnCheckBackup)
	ON_BN_CLICKED(IDC_CHECK_AUTOCOMPL, OnCheckBackup)
	ON_EN_CHANGE(IDC_EDIT_CITEFORMAT, OnChangeEditCiteformat)
	ON_EN_CHANGE(IDC_EDIT_LINELENGTH, OnChangeEditCiteformat)
	ON_EN_CHANGE(IDC_EDIT_QSFIELDS, OnChangeEditCiteformat)
	ON_EN_CHANGE(IDC_EDIT_DOIURL, OnChangeEditCiteformat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsGeneralPage 

void COptionsGeneralPage::OnCheckBackup() 
{
	SetModified();	
}

void COptionsGeneralPage::OnChangeEditCiteformat() 
{
	SetModified();	
}

BOOL COptionsGeneralPage::OnApply() 
{
	m_Options->m_Backup = m_boolBackup;
	m_Options->m_AutoCompleteValues = m_boolAutoCompleteValues;
	m_Options->m_OpenLastFile = m_boolOpenLast;
	m_Options->m_ShowCiteDlg = m_boolShowCiteDlg;
	m_Options->m_SortCaseSensitive = m_boolSortCase;
	m_Options->m_SortOnSave = m_boolSortOnSave;
	m_Options->m_TranslateASCII = m_boolTranslate;
	m_Options->m_LineLength = m_intLineLength;
	m_Options->m_CiteFormat = m_strCiteFormat;
	m_Options->m_QuickSearchFields = m_strQsFields;
	m_Options->m_ReplaceSpecialChar = m_boolReplaceSpecialChar;
	m_Options->m_ScrollToSelected = m_boolScrollToSelected;
	m_Options->m_DOIURL = m_DOIURL;
	m_Options->m_DisableSave = m_boolDisableSave;
	
	return CPropertyPage::OnApply();
}

BOOL COptionsGeneralPage::OnInitDialog() 
{
	m_boolBackup = m_Options->m_Backup;
	m_boolAutoCompleteValues = m_Options->m_AutoCompleteValues;
	m_boolOpenLast = m_Options->m_OpenLastFile;
	m_boolShowCiteDlg = m_Options->m_ShowCiteDlg;
	m_boolSortCase = m_Options->m_SortCaseSensitive;
	m_boolSortOnSave = m_Options->m_SortOnSave;
	m_boolTranslate = m_Options->m_TranslateASCII;
	m_intLineLength = m_Options->m_LineLength;
	m_strCiteFormat = m_Options->m_CiteFormat;
	m_strQsFields = m_Options->m_QuickSearchFields;
	m_boolReplaceSpecialChar = m_Options->m_ReplaceSpecialChar;
	m_boolScrollToSelected = m_Options->m_ScrollToSelected;
	m_DOIURL = m_Options->m_DOIURL;
	m_boolDisableSave = m_Options->m_DisableSave;
	
	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
