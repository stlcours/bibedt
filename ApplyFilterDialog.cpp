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

  $Id: ApplyFilterDialog.cpp,v 1.2 2005/10/11 23:22:14 stievie Exp $
*/

// ApplyFilterDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "ApplyFilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CApplyFilterDialog 


CApplyFilterDialog::CApplyFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CApplyFilterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CApplyFilterDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	m_Filter = NULL;
	m_SelFilter = NULL;
}


void CApplyFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApplyFilterDialog)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_LIST_FILTER, m_lstFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CApplyFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CApplyFilterDialog)
	ON_LBN_DBLCLK(IDC_LIST_FILTER, OnDblclkListFilter)
	ON_LBN_SELCHANGE(IDC_LIST_FILTER, OnSelchangeListFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CApplyFilterDialog 


void CApplyFilterDialog::AppendFilter(CBibItem *filter)
{
	if (filter) {
		POSITION p = filter->GetHeadPosition();
		while (p) {
			CField *f = (CField*)filter->GetNext(p);
			ASSERT(f);
			int i = m_lstFilter.AddString(f->GetName());
			m_lstFilter.SetItemDataPtr(i, f);
		}
	}
}

BOOL CApplyFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_Filter)
		AppendFilter(m_Filter);
	// Append default filter
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	if (pApp->m_BibDef && pApp->m_BibDef->GetFilter())
		AppendFilter(pApp->m_BibDef->GetFilter());	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CApplyFilterDialog::OnOK()
{
	CDialog::OnOK();

	int i = m_lstFilter.GetCurSel();
	if (i != -1) {
		m_SelFilter = (CField*)m_lstFilter.GetItemDataPtr(i);
	} else
		m_SelFilter = NULL;
}

void CApplyFilterDialog::OnDblclkListFilter() 
{
	OnOK();
}

void CApplyFilterDialog::OnSelchangeListFilter() 
{
	m_btnOk.EnableWindow(m_lstFilter.GetCurSel() != -1);
}
