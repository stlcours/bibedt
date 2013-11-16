/*
  BibEdt
  Copyright (C) 2006, Ascher Stefan. All rights reserved.
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

  $Id: OptionsEditorPage.cpp,v 1.2 2006/03/29 19:44:49 stievie Exp $
*/

// OptionsEditorPage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsEditorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsEditorPage 

IMPLEMENT_DYNCREATE(COptionsEditorPage, CPropertyPage)

COptionsEditorPage::COptionsEditorPage() : CPropertyPage(COptionsEditorPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsEditorPage)
	m_strChClass = _T("");
	m_strTlClass = _T("");
	//}}AFX_DATA_INIT
}

COptionsEditorPage::~COptionsEditorPage()
{
}

void COptionsEditorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsEditorPage)
	DDX_Text(pDX, IDC_EDIT_CHCLASS, m_strChClass);
	DDX_Text(pDX, IDC_EDIT_TLCLASS, m_strTlClass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsEditorPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsEditorPage)
	ON_EN_CHANGE(IDC_EDIT_TLCLASS, OnChangeEditTlclass)
	ON_EN_CHANGE(IDC_EDIT_CHCLASS, OnChangeEditTlclass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsEditorPage 

BOOL COptionsEditorPage::OnInitDialog() 
{
	m_strTlClass = m_Options->m_EditorParentClass;
	m_strChClass = m_Options->m_EditorClassName;

	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL COptionsEditorPage::OnApply() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	m_Options->m_EditorParentClass = m_strTlClass;
	m_Options->m_EditorClassName = m_strChClass;

	return CPropertyPage::OnApply();
}

void COptionsEditorPage::OnChangeEditTlclass() 
{
	SetModified();
}
