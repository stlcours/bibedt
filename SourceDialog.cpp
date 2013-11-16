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

  $Id: SourceDialog.cpp,v 1.21 2006/06/06 18:52:19 stievie Exp $
*/

// SourceDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "SourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSourceDialog 


CSourceDialog::CSourceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSourceDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSourceDialog)
	//}}AFX_DATA_INIT
	m_BibItem = NULL;
	m_BibList = NULL;
	m_Modified = FALSE;
	m_Lexer = -1;
	m_ReadOnly = FALSE;
}


void CSourceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSourceDialog)
	DDX_Control(pDX, IDC_SCINCTRL, m_ScintillaCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSourceDialog, CDialog)
	//{{AFX_MSG_MAP(CSourceDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CSourceDialog)
	ANCHOR_MAP_ENTRY(IDOK, ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_SCINCTRL, ANF_TOP | ANF_RIGHT | ANF_BOTTOM | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSourceDialog 

void CSourceDialog::SetBibItem(CBibItem *item)
{
	m_BibItem = item;
}

CBibItem* CSourceDialog::GetBibItem()
{
	return m_BibItem;
}

BOOL CSourceDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);

	m_ScintillaCtrl.Init();
	if (m_Lexer != -1)
		m_ScintillaCtrl.SetLexer(m_Lexer);

	m_ScintillaCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_ScintillaCtrl.SetDisplayFolding(FALSE);
	if (m_BibItem || m_BibList) {
		// Only show right edge when editing a BibItem or BibList
		COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
		m_ScintillaCtrl.SetRightEdge(pOp->m_LineLength);
	}
	if (m_BibItem)
		m_ScintillaCtrl.SetText(m_BibItem->GetSource());
	else if (m_BibList)
		m_ScintillaCtrl.SetText(m_BibList->GetSource());
	else if (!m_Source.IsEmpty())
		m_ScintillaCtrl.SetText(m_Source);
	m_ScintillaCtrl.SetReadOnly(m_ReadOnly);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSourceDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		m_ScintillaCtrl.GotoPosition(0);
		WINDOWPLACEMENT wp;
		((CBibedtApp*)AfxGetApp())->m_Options->ReadWindowPlacement(_T("SourceDialog"), &wp);
		if (wp.rcNormalPosition.bottom && wp.rcNormalPosition.right)
			MoveWindow(&wp.rcNormalPosition, FALSE);
	}
}

void CSourceDialog::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	((CBibedtApp*)AfxGetApp())->m_Options->WriteWindowPlacement(_T("SourceDialog"), wp);
	CDialog::OnDestroy();
}

CString CSourceDialog::GetSource()
{
	return m_Source;
}

void CSourceDialog::OnOK()
{
	m_Source = m_ScintillaCtrl.GetText();
	m_Modified = m_ScintillaCtrl.GetModify();
	CDialog::OnOK();
}

BOOL CSourceDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR *phDR;
	phDR = (NMHDR*)lParam;
	// does notification come from my scintilla window?
	if (phDR != NULL && phDR->hwndFrom == m_ScintillaCtrl.m_hWnd) {
		SCNotification *pMsg = (SCNotification*)lParam;
		switch (phDR->code) {
		case SCN_UPDATEUI:
			m_ScintillaCtrl.UpdateUI();
			break;
		}
		return TRUE;
	}
	return CWnd::OnNotify(wParam, lParam, pResult);
}

void CSourceDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void CSourceDialog::SetBibList(CBibList *list)
{
	m_BibList = list;
}


void CSourceDialog::SetSource(CString src)
{
	m_Source = src;
}

void CSourceDialog::SetLexer(int lexer)
{
	m_Lexer = lexer;
}

void CSourceDialog::SetReadOnly(BOOL val)
{
	m_ReadOnly = val;
}
