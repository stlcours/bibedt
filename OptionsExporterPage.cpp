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

  $Id: OptionsExporterPage.cpp,v 1.15 2006/06/06 18:52:18 stievie Exp $
*/

// OptionsExporterPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsExporterPage.h"
#include "InputBox.h"
#include "ExportGeneric.h"
#include "BeIconv.h"
#include "FileDialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsExporterPage 

IMPLEMENT_DYNCREATE(COptionsExporterPage, CPropertyPage)

COptionsExporterPage::COptionsExporterPage() : CPropertyPage(COptionsExporterPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsExporterPage)
	//}}AFX_DATA_INIT
	m_UpdateCount = 0;
	m_CurSel = NULL;
}

COptionsExporterPage::~COptionsExporterPage()
{
}

void COptionsExporterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsExporterPage)
	DDX_Control(pDX, IDC_BUTTON_EXPORTER_RENAME, m_btnRename);
	DDX_Control(pDX, IDC_BUTTON_EXPORTER_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_EDIT_FILTER, m_editFilter);
	DDX_Control(pDX, IDC_EDIT_EXTENSION, m_editExtension);
	DDX_Control(pDX, IDC_COMBO_ENCODING, m_cboEncoding);
	DDX_Control(pDX, IDC_BUTTON_BROWSE_STYLE, m_btnBrowseStyle);
	DDX_Control(pDX, IDC_LIST_EXPORTER, m_lstExporter);
	DDX_Control(pDX, IDC_EDIT_STYLEFILE, m_editStyleFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsExporterPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsExporterPage)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_STYLE, OnButtonBrowseStyle)
	ON_BN_CLICKED(IDC_BUTTON_EXPORTER_ADD, OnButtonExporterAdd)
	ON_LBN_SELCHANGE(IDC_LIST_EXPORTER, OnSelchangeListExporter)
	ON_EN_CHANGE(IDC_EDIT_STYLEFILE, OnChangeEditStylefile)
	ON_CBN_EDITCHANGE(IDC_COMBO_ENCODING, OnEditchangeComboEncoding)
	ON_BN_CLICKED(IDC_BUTTON_EXPORTER_RENAME, OnButtonExporterRename)
	ON_BN_CLICKED(IDC_BUTTON_EXPORTER_REMOVE, OnButtonExporterRemove)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODING, OnSelchangeComboEncoding)
	ON_EN_CHANGE(IDC_EDIT_EXTENSION, OnChangeEditStylefile)
	ON_EN_CHANGE(IDC_EDIT_FILTER, OnChangeEditStylefile)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsExporterPage 

void COptionsExporterPage::OnButtonBrowseStyle() 
{
	CString f;
	CString fn;
	m_editStyleFile.GetWindowText(fn);
	f.Format(_T("%s|%s||"), AfxLoadString(IDS_STRING_XSLFILTER), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(TRUE, _T(".xsl"), fn, OFN_HIDEREADONLY | OFN_ENABLESIZING, f, this);	
	if (dlg.DoModal() == IDOK) {
		m_editStyleFile.SetWindowText(dlg.GetPathName());
	}	
}

void COptionsExporterPage::OnButtonExporterAdd() 
{
	CInputBox dlg;
	dlg.SetCaption(AfxLoadString(IDS_STRING_ADDEXPORTER));
	dlg.SetPrompt(AfxLoadString(IDS_STRING_ADDEXPORTER_PROMPT));
	if (dlg.DoModal() == IDOK && !dlg.m_strText.IsEmpty()) {
		CExportGeneric* exp = new CExportGeneric();
		exp->SetName(dlg.m_strText);
		int i = m_lstExporter.AddString(exp->GetName());
		m_lstExporter.SetItemDataPtr(i, exp);
		m_lstExporter.SetCurSel(i);
		OnSelchangeListExporter();
		SetModified();
		m_editStyleFile.SetFocus();
	}
}

BOOL COptionsExporterPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	POSITION p = m_Options->m_ExporterList->GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)m_Options->m_ExporterList->GetNext(p);
		CExport* cexp = exp->Clone();
		int i = m_lstExporter.AddString(cexp->GetName());
		m_lstExporter.SetItemDataPtr(i, cexp);
	}
	if (m_lstExporter.GetCount() > 0)
		m_lstExporter.SetCurSel(0);
	OnSelchangeListExporter();
	// Encoding
	CIconv ic;
	CStringList lst;
	ic.List(&lst);
	p = lst.GetHeadPosition();
	while (p) {
		m_cboEncoding.AddString(lst.GetNext(p));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void COptionsExporterPage::OnSelchangeListExporter() 
{
	ApplySelection();

	BeginUpdate();
	CExport* exp = GetSelection();
	if (exp != NULL) {
		CExportGeneric* expgen = dynamic_cast<CExportGeneric*>(exp);
		if (expgen) {
			// Its a generic exporter
			BOOL external = CExporterList::IsExternalExporter(expgen);
			m_editStyleFile.SetWindowText(expgen->GetStyleFile());
			m_cboEncoding.SetWindowText(expgen->GetEncoding());
			m_editExtension.SetWindowText(expgen->GetExt());
			m_editFilter.SetWindowText(expgen->GetFilter());
			EnableControls();
			if (!external) {
				m_btnRemove.EnableWindow(FALSE);
				m_btnRename.EnableWindow(FALSE);
			}
		} else {
			// Its a built in Exporter
			EnableControls(FALSE);
		}		
	} else {
		EnableControls(FALSE);
	}
	m_CurSel = exp;
	EndUpdate();
}

void COptionsExporterPage::OnChangeEditStylefile() 
{
	if (m_UpdateCount == 0)
		SetModified();	
}

void COptionsExporterPage::OnEditchangeComboEncoding() 
{
	if (m_UpdateCount == 0)
		SetModified();	
}

BOOL COptionsExporterPage::OnApply() 
{
	OnSelchangeListExporter();
	m_Options->m_ExporterList->Clear();
	int c = m_lstExporter.GetCount();
	for (int i = 0; i < c; i++) {
		CExport* exp = (CExport*)m_lstExporter.GetItemDataPtr(i);
		ASSERT(exp);
		CExport* nexp = exp->Clone();
		m_Options->m_ExporterList->AddTail((CObject*)nexp);
	}
	
	return CPropertyPage::OnApply();
}

void COptionsExporterPage::OnButtonExporterRename() 
{
	CInputBox dlg;
	dlg.SetCaption(AfxLoadString(IDS_STRING_RENAMEEXPORTER));
	dlg.SetPrompt(AfxLoadString(IDS_STRING_ADDEXPORTER_PROMPT));

	CExport* exp = GetSelection();
	ASSERT(exp);
	CExportGeneric* expgen = dynamic_cast<CExportGeneric*>(exp);
	if (!expgen)
		return;
	dlg.m_strText = expgen->GetName();
	if (dlg.DoModal() == IDOK && !dlg.m_strText.IsEmpty()) {
		expgen->SetName(dlg.m_strText);
		SetModified();
	}
}

void COptionsExporterPage::OnButtonExporterRemove() 
{
	CExport* exp = GetSelection();
	ASSERT(exp);
	CExportGeneric* expgen = dynamic_cast<CExportGeneric*>(exp);
	if (expgen) {
		delete expgen;
		int i = m_lstExporter.GetCurSel();
		m_lstExporter.DeleteString(i);
		SetModified();
		OnSelchangeListExporter();
	}
}

void COptionsExporterPage::EnableControls(BOOL bEnable)
{
	m_editStyleFile.EnableWindow(bEnable);
	m_btnBrowseStyle.EnableWindow(bEnable);
	m_cboEncoding.EnableWindow(bEnable);
	m_editExtension.EnableWindow(bEnable);
	m_editFilter.EnableWindow(bEnable);
	m_btnRemove.EnableWindow(bEnable);
	m_btnRename.EnableWindow(bEnable);
	if (!bEnable) {
		m_editStyleFile.SetWindowText(NULL);
		m_cboEncoding.SetWindowText(NULL);
		m_editExtension.SetWindowText(NULL);
		m_editFilter.SetWindowText(NULL);
	}
}

void COptionsExporterPage::OnSelchangeComboEncoding() 
{
	if (m_UpdateCount == 0)
		SetModified();	
}

void COptionsExporterPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	int c = m_lstExporter.GetCount();
	for (int i = 0; i < c; i++) {
		CExport* exp = (CExport*)m_lstExporter.GetItemDataPtr(i);
		ASSERT(exp);
		delete exp;
	}	
}

void COptionsExporterPage::ApplySelection()
{
	if (m_CurSel) {
		CExportGeneric* sel = dynamic_cast<CExportGeneric*>(m_CurSel);
		if (sel) {
			// Apply changes
			CString str;
			m_editStyleFile.GetWindowText(str);
			sel->SetStyleFile(str);
			m_cboEncoding.GetWindowText(str);
			sel->SetEncoding(str);
			m_editExtension.GetWindowText(str);
			// dot is part of the extension
			if (str.Left(1) != _T('.'))
				str = _T('.') + str;
			sel->SetExt(str);
			m_editFilter.GetWindowText(str);
			sel->SetFilter(str);
		}
	}
}

CExport* COptionsExporterPage::GetSelection()
{
	int i = m_lstExporter.GetCurSel();
	if (i != LB_ERR) {
		CExport* res = (CExport*)m_lstExporter.GetItemDataPtr(i);
		return res;
	} else
		return NULL;
}
