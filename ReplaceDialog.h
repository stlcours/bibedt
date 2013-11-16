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

  $Id: ReplaceDialog.h,v 1.7 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_REPLACEDIALOG_H__8EE886BC_15CA_439F_9CB2_2C7E6A1D93C3__INCLUDED_)
#define AFX_REPLACEDIALOG_H__8EE886BC_15CA_439F_9CB2_2C7E6A1D93C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceDialog.h : Header-Datei
//

#include "ScintillaBibWnd.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CReplaceDialog 

class CReplaceDialog : public CDialog
{
// Konstruktion
public:
	void SaveHistory(CString key, CComboBox* cbo);
	void LoadHistory(CString key, CComboBox* cbo);
	void SetEditor(CScintillaBibWnd * editor);
	CReplaceDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CReplaceDialog)
	enum { IDD = IDD_DIALOG_REPLACETEXT };
	CButton	m_BtnReplaceAll;
	CButton	m_BtnFind;
	CButton	m_btnReplace;
	CComboBox	m_cboSearchText;
	CComboBox	m_cboReplaceText;
	BOOL	m_MatchCase;
	BOOL	m_RegExpr;
	BOOL	m_WholeWords;
	CString	m_ReplaceText;
	CString	m_SearchText;
	BOOL	m_SelOnly;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CReplaceDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CReplaceDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFindnext();
	afx_msg void OnButtonReplace();
	afx_msg void OnButtonReplaceall();
	afx_msg void OnDestroy();
	afx_msg void OnEditchangeComboText();
	afx_msg void OnSelchangeComboText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CScintillaBibWnd * m_Editor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_REPLACEDIALOG_H__8EE886BC_15CA_439F_9CB2_2C7E6A1D93C3__INCLUDED_
