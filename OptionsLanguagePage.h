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

  $Id: OptionsLanguagePage.h,v 1.1 2006/06/04 11:09:43 stievie Exp $
*/

#if !defined(AFX_OPTIONSLANGUAGEPAGE_H__7749624C_3C40_4EB6_B24F_1BF5AD3C1107__INCLUDED_)
#define AFX_OPTIONSLANGUAGEPAGE_H__7749624C_3C40_4EB6_B24F_1BF5AD3C1107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsLanguagePage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsLanguagePage 

class COptionsLanguagePage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsLanguagePage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsLanguagePage();
	~COptionsLanguagePage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsLanguagePage)
	enum { IDD = IDD_OPTIONSPAGE_LANGUAGE };
	CComboBox	m_cboLangs;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsLanguagePage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CLanguage* GetLang();
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsLanguagePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLangs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSLANGUAGEPAGE_H__7749624C_3C40_4EB6_B24F_1BF5AD3C1107__INCLUDED_
