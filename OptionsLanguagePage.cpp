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

  $Id: OptionsLanguagePage.cpp,v 1.1 2006/06/04 11:09:43 stievie Exp $
*/

// OptionsLanguagePage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsLanguagePage.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsLanguagePage 

IMPLEMENT_DYNCREATE(COptionsLanguagePage, CPropertyPage)

COptionsLanguagePage::COptionsLanguagePage() : CPropertyPage(COptionsLanguagePage::IDD)
{
	//{{AFX_DATA_INIT(COptionsLanguagePage)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

COptionsLanguagePage::~COptionsLanguagePage()
{
}

void COptionsLanguagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsLanguagePage)
	DDX_Control(pDX, IDC_COMBO_LANGS, m_cboLangs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsLanguagePage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsLanguagePage)
	ON_CBN_SELCHANGE(IDC_COMBO_LANGS, OnSelchangeComboLangs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsLanguagePage 

BOOL COptionsLanguagePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CLanguage *lang = GetLang();
	POSITION p = lang->GetHeadPosition();
	POSITION prev;
	while (p) {
		prev = p;
		LANG_INFO lng = lang->GetNext(p);
		int i = m_cboLangs.AddString(lng.name);
		m_cboLangs.SetItemDataPtr(i, p);
		if (prev == lang->GetCurLang())
			m_cboLangs.SetCurSel(i);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL COptionsLanguagePage::OnApply() 
{	
	GetLang()->SetCurLang(m_cboLangs.GetCurSel());

	return CPropertyPage::OnApply();
}

CLanguage* COptionsLanguagePage::GetLang()
{
	return &((CBibedtApp*)AfxGetApp())->m_Language;
}

void COptionsLanguagePage::OnSelchangeComboLangs() 
{
	SetModified();
}
