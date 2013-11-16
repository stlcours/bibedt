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

  $Id: ColumnsDialog.h,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_COLUMNSDIALOG_H__A946017A_2828_464F_B9A3_DDB69BD67B71__INCLUDED_)
#define AFX_COLUMNSDIALOG_H__A946017A_2828_464F_B9A3_DDB69BD67B71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColumnsDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CColumnsDialog 

class CColumnsDialog : public CDialog
{
// Konstruktion
public:
	CListCtrl * m_ListCtrl;
	void SetListCtrl(CListCtrl *value);
	CColumnsDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();

// Dialogfelddaten
	//{{AFX_DATA(CColumnsDialog)
	enum { IDD = IDD_DIALOG_COLUMNS };
	CButton	m_BtnUp;
	CButton	m_BtnDown;
	CButton	m_BtnRemove;
	CListBox	m_ListColumns;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CColumnsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CColumnsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListColumns();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_COLUMNSDIALOG_H__A946017A_2828_464F_B9A3_DDB69BD67B71__INCLUDED_
