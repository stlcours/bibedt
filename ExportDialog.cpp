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

  $Id: ExportDialog.cpp,v 1.3 2005/11/30 21:07:39 stievie Exp $
*/

// ExportDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "ExportDialog.h"
#include "Export.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportDialog

IMPLEMENT_DYNAMIC(CExportDialog, CFileDialog)

CExportDialog::CExportDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_ofn.Flags |= OFN_ENABLETEMPLATE;
	m_ofn.hInstance = AfxGetInstanceHandle();
	m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_EXPORT_FILTER);
	m_ExporterList = NULL;
}


BEGIN_MESSAGE_MAP(CExportDialog, CFileDialog)
	//{{AFX_MSG_MAP(CExportDialog)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST_EXPORTER, OnSelchangeListExporter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// DoDataExchange
void CExportDialog::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXFileDialog)
	DDX_Control(pDX, IDC_LIST_EXPORTER, m_lstExporter);
	//}}AFX_DATA_MAP
}

BOOL CExportDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();

	m_lstExporter.ResetContent();
	if (m_ExporterList) {
		POSITION p = m_ExporterList->GetHeadPosition();
		while (p) {
			CExport* exp = (CExport*)m_ExporterList->GetNext(p);
			int i = m_lstExporter.AddString(exp->GetName());
			m_lstExporter.SetItemDataPtr(i, exp);
			m_lstExporter.SetSel(i, exp->m_Selected);
		}
	}
	OnSelchangeListExporter();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CExportDialog::OnOK()
{
	CFileDialog::OnOK();
}

void CExportDialog::OnSize(UINT nType, int cx, int cy) 
{
	CFileDialog::OnSize(nType, cx, cy);
	
	// Right of the list is right of the OK button
	// I hope thats nice on all Win32
	CWnd* btnok = GetParent()->GetDlgItem(IDOK);
	ASSERT(btnok);
	CRect ok;
	btnok->GetWindowRect(&ok);
	ScreenToClient(&ok);
	CRect fltrc;
	m_lstExporter.GetWindowRect(&fltrc);
	ScreenToClient(&fltrc);

	fltrc.right = ok.right;
	m_lstExporter.MoveWindow(&fltrc);
}

void CExportDialog::SetExporterList(CExporterList *lst)
{
	m_ExporterList = lst;
}

void CExportDialog::OnSelchangeListExporter()
{
	CWnd* btnok = GetParent()->GetDlgItem(IDOK);
	btnok->EnableWindow(m_lstExporter.GetSelCount() > 0);
	int c = m_lstExporter.GetCount();
	CExport* ex;
	for (int i = 0; i < c; i++) {
		ex = (CExport*)m_lstExporter.GetItemDataPtr(i);

		if (m_lstExporter.GetSel(i)) {
			ex->m_Selected = TRUE;
		} else {
			ex->m_Selected = FALSE;
		}
	}
}

