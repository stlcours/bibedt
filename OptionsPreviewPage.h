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

  $Id: OptionsPreviewPage.h,v 1.1 2006/08/06 13:55:44 stievie Exp $
*/

#if !defined(AFX_OPTIONSPREVIEWPAGE_H__0A29D34C_9574_4B29_BB24_6C4ADC08FB92__INCLUDED_)
#define AFX_OPTIONSPREVIEWPAGE_H__0A29D34C_9574_4B29_BB24_6C4ADC08FB92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPreviewPage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsPreviewPage 

class COptionsPreviewPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsPreviewPage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsPreviewPage();
	~COptionsPreviewPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsPreviewPage)
	enum { IDD = IDD_OPTIONSPAGE_PREVIEW };
	CComboBox	m_cboSans;
	CComboBox	m_cboProp;
	CComboBox	m_cboMono;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsPreviewPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsPreviewPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboFntProp();
	afx_msg void OnSelchangeComboFntProp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSPREVIEWPAGE_H__0A29D34C_9574_4B29_BB24_6C4ADC08FB92__INCLUDED_
