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

  $Id: OptionsGeneralPage.h,v 1.12 2006/07/29 11:33:14 stievie Exp $
*/

#if !defined(AFX_OPTIONSGENERALPAGE_H__B275ADA0_9008_4364_8101_ECF5A50EBAC0__INCLUDED_)
#define AFX_OPTIONSGENERALPAGE_H__B275ADA0_9008_4364_8101_ECF5A50EBAC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneralPage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsGeneralPage 

class COptionsGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsGeneralPage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsGeneralPage();
	~COptionsGeneralPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsGeneralPage)
	enum { IDD = IDD_OPTIONSPAGE_GENERAL };
	CSpinButtonCtrl	m_spnLineLength;
	BOOL	m_boolBackup;
	BOOL	m_boolShowCiteDlg;
	BOOL	m_boolSortCase;
	BOOL	m_boolSortOnSave;
	BOOL	m_boolTranslate;
	CString	m_strCiteFormat;
	int		m_intLineLength;
	BOOL	m_boolOpenLast;
	CString	m_strQsFields;
	BOOL	m_boolReplaceSpecialChar;
	BOOL	m_boolScrollToSelected;
	BOOL	m_boolAutoCompleteValues;
	CString	m_DOIURL;
	BOOL	m_boolDisableSave;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsGeneralPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsGeneralPage)
	afx_msg void OnCheckBackup();
	afx_msg void OnChangeEditCiteformat();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSGENERALPAGE_H__B275ADA0_9008_4364_8101_ECF5A50EBAC0__INCLUDED_
