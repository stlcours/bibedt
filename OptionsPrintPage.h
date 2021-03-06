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

  $Id: OptionsPrintPage.h,v 1.4 2005/10/26 20:43:16 stievie Exp $
*/

#if !defined(AFX_OPTIONSPRINTPAGE_H__90F39AE3_17A9_40D4_887B_5E7A07ED76F7__INCLUDED_)
#define AFX_OPTIONSPRINTPAGE_H__90F39AE3_17A9_40D4_887B_5E7A07ED76F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPrintPage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsPrintPage 

class COptionsPrintPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsPrintPage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsPrintPage();
	~COptionsPrintPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsPrintPage)
	enum { IDD = IDD_OPTIONSPAGE_PRINT };
	int		m_intBottom;
	int		m_intLeft;
	int		m_intRight;
	int		m_intTop;
	int		m_intUnits;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsPrintPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsPrintPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUnits();
	afx_msg void OnChangeEditBottom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSPRINTPAGE_H__90F39AE3_17A9_40D4_887B_5E7A07ED76F7__INCLUDED_
