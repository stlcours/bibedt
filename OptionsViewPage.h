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

  $Id: OptionsViewPage.h,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_OPTIONSVIEWPAGE_H__D8B03ACF_CB20_43AB_BA2A_B68C83D97DE3__INCLUDED_)
#define AFX_OPTIONSVIEWPAGE_H__D8B03ACF_CB20_43AB_BA2A_B68C83D97DE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsViewPage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsViewPage 

class COptionsViewPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsViewPage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsViewPage();
	~COptionsViewPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsViewPage)
	enum { IDD = IDD_OPTIONSPAGE_VIEW };
	BOOL	m_boolGridlines;
	BOOL	m_boolRowSelect;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsViewPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsViewPage)
	afx_msg void OnCheckRowselect();
	afx_msg void OnCheckGridlines();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSVIEWPAGE_H__D8B03ACF_CB20_43AB_BA2A_B68C83D97DE3__INCLUDED_
