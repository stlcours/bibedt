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

  $Id: ExportDialog.h,v 1.2 2005/11/30 20:50:35 stievie Exp $
*/

#if !defined(AFX_EXPORTDIALOG_H__C7FF487A_55AA_4B22_8D3F_D94DB77DF4BA__INCLUDED_)
#define AFX_EXPORTDIALOG_H__C7FF487A_55AA_4B22_8D3F_D94DB77DF4BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportDialog.h : Header-Datei
//

#include "ExporterList.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CExportDialog 

class CExportDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CExportDialog)

public:
	virtual void OnOK();
	void SetExporterList(CExporterList* lst);
	CExporterList* GetExporterList() { return m_ExporterList; }
	CExportDialog(BOOL bOpenFileDialog, // TRUE für FileOpen, FALSE für FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CExportDialog)
	CListBox	m_lstExporter;
	//}}AFX_DATA

// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CExportDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

protected:
	CExporterList* m_ExporterList;
	//{{AFX_MSG(CExportDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeListExporter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EXPORTDIALOG_H__C7FF487A_55AA_4B22_8D3F_D94DB77DF4BA__INCLUDED_
