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

  $Id: SearchDialog.h,v 1.9 2006/06/17 11:43:35 stievie Exp $
*/

#if !defined(AFX_SEARCHDIALOG_H__453D3121_B388_42C4_8B29_4DD1714201DC__INCLUDED_)
#define AFX_SEARCHDIALOG_H__453D3121_B388_42C4_8B29_4DD1714201DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSearchDialog 

class CSearchDialog : public CDialog
{
// Konstruktion
public:
	CStringList* m_SearchFields;
	void Update();
	void SetSearchText(CString val) { m_SearchText = val; }
	CString GetSearchText() { return m_SearchText;  }
	CSearchDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();

// Dialogfelddaten
	//{{AFX_DATA(CSearchDialog)
	enum { IDD = IDD_DIALOG_SEARCH };
	CComboBox	m_cboSearchFields;
	CButton	m_btnMarkAll;
	CButton	m_BtnOk;
	CComboBox	m_cboText;
	BOOL	m_boolMatchBase;
	BOOL	m_boolSelOnly;
	BOOL	m_boolWholeWords;
	BOOL	m_boolRegEx;
	CString	m_strSearchFields;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSearchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSearchDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboText();
	afx_msg void OnSelchangeComboText();
	afx_msg void OnButtonSearchMarkall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadHistory();
	void SaveHistory();
	CString m_SearchText;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SEARCHDIALOG_H__453D3121_B388_42C4_8B29_4DD1714201DC__INCLUDED_
