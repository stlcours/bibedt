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

  $Id: FindDialog.h,v 1.8 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_FINDDIALOG_H__10C85CFC_F324_4F5E_BFCE_65F20B2542AC__INCLUDED_)
#define AFX_FINDDIALOG_H__10C85CFC_F324_4F5E_BFCE_65F20B2542AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDialog 

class CFindDialog : public CDialog
{
// Konstruktion
public:
	CString m_SearchText;
	BOOL m_Backward;
	CFindDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();

// Dialogfelddaten
	//{{AFX_DATA(CFindDialog)
	enum { IDD = IDD_DIALOG_FINDTEXT };
	CButton	m_BtnMark;
	CButton	m_BtnOk;
	CComboBox	m_cboText;
	BOOL	m_MatchCase;
	BOOL	m_WholeWords;
	BOOL	m_RegExpr;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFindDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFindDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMark();
	afx_msg void OnEditchangeComboText();
	afx_msg void OnSelchangeComboText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Update();
	void SaveHistory();
	void LoadHistory();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FINDDIALOG_H__10C85CFC_F324_4F5E_BFCE_65F20B2542AC__INCLUDED_
