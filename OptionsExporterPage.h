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

  $Id: OptionsExporterPage.h,v 1.7 2006/05/28 20:01:10 stievie Exp $
*/

#if !defined(AFX_OPTIONSEXPORTERPAGE_H__DA5C5360_BEC4_4341_8B2A_7C132F0A9621__INCLUDED_)
#define AFX_OPTIONSEXPORTERPAGE_H__DA5C5360_BEC4_4341_8B2A_7C132F0A9621__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsExporterPage.h : Header-Datei
//

#include "ExporterList.h"
#include "Export.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsExporterPage 

class COptionsExporterPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsExporterPage)

// Konstruktion
public:
	CExport* GetSelection();
	COptions * m_Options;
	COptionsExporterPage();
	~COptionsExporterPage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsExporterPage)
	enum { IDD = IDD_OPTIONSPAGE_EXPORTER };
	CButton	m_btnRename;
	CButton	m_btnRemove;
	CEdit	m_editFilter;
	CEdit	m_editExtension;
	CComboBox	m_cboEncoding;
	CButton	m_btnBrowseStyle;
	CListBox	m_lstExporter;
	CEdit	m_editStyleFile;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsExporterPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	DWORD m_UpdateCount;
	void BeginUpdate() { m_UpdateCount++; };
	void EndUpdate() { if (m_UpdateCount > 0) m_UpdateCount--; }
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsExporterPage)
	afx_msg void OnButtonBrowseStyle();
	afx_msg void OnButtonExporterAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListExporter();
	afx_msg void OnChangeEditStylefile();
	afx_msg void OnEditchangeComboEncoding();
	afx_msg void OnButtonExporterRename();
	afx_msg void OnButtonExporterRemove();
	afx_msg void OnSelchangeComboEncoding();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CExport* m_CurSel;
	void ApplySelection();
	void EnableControls(BOOL bEnable = TRUE);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSEXPORTERPAGE_H__DA5C5360_BEC4_4341_8B2A_7C132F0A9621__INCLUDED_
