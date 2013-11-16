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

  $Id: ColumnsDialog.cpp,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

// ColumnsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "ColumnsDialog.h"
#include "Options.h"
#include "InputBox.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CColumnsDialog 


CColumnsDialog::CColumnsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CColumnsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColumnsDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CColumnsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColumnsDialog)
	DDX_Control(pDX, IDC_BUTTON_UP, m_BtnUp);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_BtnDown);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_BtnRemove);
	DDX_Control(pDX, IDC_LIST_COLUMNS, m_ListColumns);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColumnsDialog, CDialog)
	//{{AFX_MSG_MAP(CColumnsDialog)
	ON_LBN_SELCHANGE(IDC_LIST_COLUMNS, OnSelchangeListColumns)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CColumnsDialog 

void CColumnsDialog::SetListCtrl(CListCtrl *value)
{
	m_ListCtrl = value;
}

BOOL CColumnsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LVCOLUMN col;
	TCHAR lpBuffer[256];
	col.pszText = lpBuffer;
	col.cchTextMax = 256;
	col.mask = LVCF_TEXT;
	for (int i = 0; i < m_ListCtrl->GetHeaderCtrl()->GetItemCount(); i++) {
		m_ListCtrl->GetColumn(i, &col);
		m_ListColumns.AddString(lpBuffer);
	}
	if (m_ListColumns.GetCount() > 0)
		m_ListColumns.SetCurSel(0);
	OnSelchangeListColumns();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CColumnsDialog::OnSelchangeListColumns() 
{
	int inx = m_ListColumns.GetCurSel();
	m_BtnRemove.EnableWindow(inx > -1);
	m_BtnUp.EnableWindow(inx > 0);
	m_BtnDown.EnableWindow(inx > -1 && inx < m_ListColumns.GetCount()-1);
}

void CColumnsDialog::OnOK()
{
	CDialog::OnOK();
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	CString col;
	pOp->m_ColCount = m_ListColumns.GetCount();
	int n;
	for (int i = 0; i < m_ListColumns.GetCount(); i++) {
		n = m_ListColumns.GetTextLen(i);
		m_ListColumns.GetText(i, col.GetBuffer(n));
		col.ReleaseBuffer();
		pOp->SetColName(i, col);
	}
}

void CColumnsDialog::OnButtonAdd() 
{
	CInputBox dlg;
	dlg.SetPrompt(AfxLoadString(IDS_STRING_COLPROMPT));
	dlg.SetCaption(AfxLoadString(IDS_STRING_COLCAPADD));
	if (dlg.DoModal()) {
		if (!dlg.m_strText.IsEmpty()) {
			int i = m_ListColumns.AddString(dlg.m_strText);
			m_ListColumns.SetCurSel(i);
			OnSelchangeListColumns();
		}
	}
}

void CColumnsDialog::OnButtonRemove() 
{
	int i = m_ListColumns.GetCurSel();
	if (i != -1) {
		m_ListColumns.DeleteString(i--);
		if (i >= 0)
			m_ListColumns.SetCurSel(i);
		else if (m_ListColumns.GetCount() > 0)
			m_ListColumns.SetCurSel(0);
		OnSelchangeListColumns();
	}
}

void CColumnsDialog::OnButtonUp() 
{
	int sel = m_ListColumns.GetCurSel();
	CString col;
	int n = m_ListColumns.GetTextLen(sel);
	m_ListColumns.GetText(sel, col.GetBuffer(n));
	col.ReleaseBuffer();
	m_ListColumns.DeleteString(sel);
	int newsel = m_ListColumns.InsertString(sel-1, col);
	m_ListColumns.SetCurSel(newsel);
	OnSelchangeListColumns();
}

void CColumnsDialog::OnButtonDown() 
{
	int sel = m_ListColumns.GetCurSel();
	CString col;
	int n = m_ListColumns.GetTextLen(sel);
	m_ListColumns.GetText(sel, col.GetBuffer(n));
	col.ReleaseBuffer();
	m_ListColumns.DeleteString(sel);
	int newsel = m_ListColumns.InsertString(sel+1, col);
	m_ListColumns.SetCurSel(newsel);
	OnSelchangeListColumns();
}
