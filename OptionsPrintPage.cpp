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

  $Id: OptionsPrintPage.cpp,v 1.5 2005/10/26 20:43:16 stievie Exp $
*/

// OptionsPrintPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsPrintPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsPrintPage 

IMPLEMENT_DYNCREATE(COptionsPrintPage, CPropertyPage)

COptionsPrintPage::COptionsPrintPage() : CPropertyPage(COptionsPrintPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsPrintPage)
	m_intBottom = 0;
	m_intLeft = 0;
	m_intRight = 0;
	m_intTop = 0;
	m_intUnits = -1;
	//}}AFX_DATA_INIT
}

COptionsPrintPage::~COptionsPrintPage()
{
}

void COptionsPrintPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPrintPage)
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_intBottom);
	DDV_MinMaxInt(pDX, m_intBottom, 0, 1024);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_intLeft);
	DDV_MinMaxInt(pDX, m_intLeft, 0, 1024);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_intRight);
	DDV_MinMaxInt(pDX, m_intRight, 0, 1024);
	DDX_Text(pDX, IDC_EDIT_TOP, m_intTop);
	DDV_MinMaxInt(pDX, m_intTop, 0, 1024);
	DDX_CBIndex(pDX, IDC_COMBO_UNITS, m_intUnits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPrintPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsPrintPage)
	ON_CBN_SELCHANGE(IDC_COMBO_UNITS, OnSelchangeComboUnits)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM, OnChangeEditBottom)
	ON_EN_CHANGE(IDC_EDIT_LEFT, OnChangeEditBottom)
	ON_EN_CHANGE(IDC_EDIT_RIGHT, OnChangeEditBottom)
	ON_EN_CHANGE(IDC_EDIT_TOP, OnChangeEditBottom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsPrintPage 

BOOL COptionsPrintPage::OnApply() 
{
	m_Options->m_MarginTop = m_intTop;
	m_Options->m_MarginLeft = m_intLeft;
	m_Options->m_MarginRight = m_intRight;
	m_Options->m_MarginBottom = m_intBottom;
	m_Options->m_PrintUnits = (enum Units)m_intUnits;
	
	return CPropertyPage::OnApply();
}

BOOL COptionsPrintPage::OnInitDialog() 
{
	m_intTop = m_Options->m_MarginTop;
	m_intLeft = m_Options->m_MarginLeft;
	m_intRight = m_Options->m_MarginRight;
	m_intBottom = m_Options->m_MarginBottom;
	m_intUnits = (int)m_Options->m_PrintUnits;

	CPropertyPage::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void COptionsPrintPage::OnSelchangeComboUnits() 
{
	SetModified();	
}

void COptionsPrintPage::OnChangeEditBottom() 
{
	SetModified();	
}
