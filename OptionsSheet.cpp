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

  $Id: OptionsSheet.cpp,v 1.10 2006/08/06 13:55:44 stievie Exp $
*/

// OptionsSheet.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

IMPLEMENT_DYNAMIC(COptionsSheet, CPropertySheet)

COptionsSheet::COptionsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_PageGeneral);
	AddPage(&m_PageFile);
	AddPage(&m_PagePrint);
	AddPage(&m_PageExporter);
	AddPage(&m_PagePreview);
	AddPage(&m_PageEditor);
	AddPage(&m_PageLanguage);
}

COptionsSheet::COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

COptionsSheet::~COptionsSheet()
{
}


BEGIN_MESSAGE_MAP(COptionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionsSheet)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsSheet 

BOOL COptionsSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Speziellen Code hier einfügen
	
	return bResult;
}

void COptionsSheet::SetOptions(COptions *value)
{
	m_Options = value;
	m_PageGeneral.m_Options = m_Options;
	m_PageFile.m_Options = m_Options;
	m_PagePrint.m_Options = m_Options;
	m_PageExporter.m_Options = m_Options;
	m_PagePreview.m_Options = m_Options;
	m_PageEditor.m_Options = m_Options;
	m_PageLanguage.m_Options = m_Options;
}
