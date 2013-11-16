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

  $Id: OptionsEditorPage.h,v 1.2 2006/03/29 19:44:49 stievie Exp $
*/

#if !defined(AFX_OPTIONSEDITORPAGE_H__9E4F17FB_C258_4AF3_8347_6434680509AC__INCLUDED_)
#define AFX_OPTIONSEDITORPAGE_H__9E4F17FB_C258_4AF3_8347_6434680509AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsEditorPage.h : Header-Datei
//

#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsEditorPage 

class COptionsEditorPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsEditorPage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsEditorPage();
	~COptionsEditorPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsEditorPage)
	enum { IDD = IDD_OPTIONSPAGE_DEFEDITOR };
	CString	m_strChClass;
	CString	m_strTlClass;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsEditorPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsEditorPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTlclass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSEDITORPAGE_H__9E4F17FB_C258_4AF3_8347_6434680509AC__INCLUDED_
