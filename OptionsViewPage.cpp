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

  $Id: OptionsViewPage.cpp,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

// OptionsViewPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsViewPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsViewPage 

IMPLEMENT_DYNCREATE(COptionsViewPage, CPropertyPage)

COptionsViewPage::COptionsViewPage() : CPropertyPage(COptionsViewPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsViewPage)
	m_boolGridlines = FALSE;
	m_boolRowSelect = FALSE;
	//}}AFX_DATA_INIT
}

COptionsViewPage::~COptionsViewPage()
{
}

void COptionsViewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsViewPage)
	DDX_Check(pDX, IDC_CHECK_GRIDLINES, m_boolGridlines);
	DDX_Check(pDX, IDC_CHECK_ROWSELECT, m_boolRowSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsViewPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsViewPage)
	ON_BN_CLICKED(IDC_CHECK_ROWSELECT, OnCheckRowselect)
	ON_BN_CLICKED(IDC_CHECK_GRIDLINES, OnCheckGridlines)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsViewPage 

void COptionsViewPage::OnCheckRowselect() 
{
	SetModified();	
}

void COptionsViewPage::OnCheckGridlines() 
{
	SetModified();	
}

BOOL COptionsViewPage::OnApply() 
{
	m_Options->m_GridLines = m_boolGridlines;
	m_Options->m_FullRowSelect = m_boolRowSelect;
	
	return CPropertyPage::OnApply();
}

BOOL COptionsViewPage::OnInitDialog() 
{
	m_boolGridlines = m_Options->m_GridLines;
	m_boolRowSelect = m_Options->m_FullRowSelect;

	CPropertyPage::OnInitDialog();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
