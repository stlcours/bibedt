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

  $Id: OptionsSheet.h,v 1.9 2006/08/06 13:55:44 stievie Exp $
*/

#if !defined(AFX_OPTIONSSHEET_H__201693F3_9FEB_4F19_BB46_079D888459F8__INCLUDED_)
#define AFX_OPTIONSSHEET_H__201693F3_9FEB_4F19_BB46_079D888459F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsSheet.h : Header-Datei
//

#include "OptionsGeneralPage.h"
#include "OptionsFilePage.h"
#include "OptionsPrintPage.h"
#include "OptionsExporterPage.h"
#include "OptionsEditorPage.h"
#include "OptionsLanguagePage.h"
#include "OptionsPreviewPage.h"
#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

class COptionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsSheet)

// Konstruktion
public:
	COptionsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementierung
public:
	void SetOptions(COptions *value);
	COptions * m_Options;
	COptionsGeneralPage m_PageGeneral;
	COptionsFilePage m_PageFile;
	COptionsPrintPage m_PagePrint;
	COptionsExporterPage m_PageExporter;
	COptionsEditorPage m_PageEditor;
	COptionsLanguagePage m_PageLanguage;
	COptionsPreviewPage m_PagePreview;

	virtual ~COptionsSheet();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(COptionsSheet)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSSHEET_H__201693F3_9FEB_4F19_BB46_079D888459F8__INCLUDED_
