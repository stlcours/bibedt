/*
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie@utanet.at, http://bibedt.sourceforge.net/

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

  $Id: KeysDialog.cpp,v 1.4 2006/05/25 14:15:46 stievie Exp $
*/

// KeysDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "KeysDialog.h"
#include "BibItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CKeysDialog 


CKeysDialog::CKeysDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CKeysDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeysDialog)
	//}}AFX_DATA_INIT
	m_BibList = NULL;
}


void CKeysDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeysDialog)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_EDIT_PREVIEW, m_editPreview);
	DDX_Control(pDX, IDC_LIST_KEYS, m_lstKeys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeysDialog, CDialog)
	//{{AFX_MSG_MAP(CKeysDialog)
	ON_LBN_DBLCLK(IDC_LIST_KEYS, OnDblclkListKeys)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST_KEYS, OnSelchangeListKeys)				
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CKeysDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_LIST_KEYS, ANF_TOP | ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_PREVIEW, ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CKeysDialog 


BOOL CKeysDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);
	
	ASSERT(m_BibList);
	POSITION p = m_BibList->GetHeadPosition();

	while (p) {
		CBibItem* item = (CBibItem*)m_BibList->GetNext(p);
		if (item->IsType(STR_FILTER) || item->IsType(STR_STRING) || item->IsType(STR_PREAMBLE) || item->IsType(STR_COMMENT))
			continue;
		
		int i = m_lstKeys.AddString(item->GetKey());
		m_lstKeys.SetItemData(i, (DWORD)item);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CKeysDialog::OnOK()
{
	int sel = m_lstKeys.GetCurSel();
	if (sel != -1) {
		CBibItem* item = (CBibItem*)m_lstKeys.GetItemData(sel);
		ASSERT(item);
		m_SelKey = item->GetKey();
	} else
		m_SelKey.Empty();
	CDialog::OnOK();
}

void CKeysDialog::OnDblclkListKeys() 
{
	OnOK();	
}

void CKeysDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void CKeysDialog::OnSelchangeListKeys() 
{
	int sel = m_lstKeys.GetCurSel();
	if (sel != -1) {
		CBibItem* item = (CBibItem*)m_lstKeys.GetItemData(sel);
		if (item) {
			m_editPreview.SetWindowText(item->GetPrettyString());
			m_btnOk.EnableWindow();
			return;
		}
	}
	m_editPreview.SetWindowText(NULL);
	m_btnOk.EnableWindow(FALSE);
}
