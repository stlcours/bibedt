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

  $Id: CopyCitationDialog.h,v 1.6 2005/11/30 20:50:35 stievie Exp $
*/

#if !defined(AFX_COPYCITATIONDIALOG_H__BF7BAC3F_8308_4C11_9C4C_B0809CB1439A__INCLUDED_)
#define AFX_COPYCITATIONDIALOG_H__BF7BAC3F_8308_4C11_9C4C_B0809CB1439A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyCitationDialog.h : Header-Datei
//

#define CITE_KEYONLY 0
#define CITE_CITE    1
#define CITE_NOCITE  2
#define CITE_CUSTOM  3

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCopyCitationDialog 

class CCopyCitationDialog : public CDialog
{
// Konstruktion
public:
	void UpdateCopyString();
	CString m_CopyString;
	CString GetFormatString();
	void UpdateFormat();
	virtual void OnOK();
	void SetCiteFormat(int format);
	int GetCiteFormat();
	CString GetCopyString();
	void AddKey(CString key);
	CStringList * m_Keys;
	CCopyCitationDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CCopyCitationDialog)
	enum { IDD = IDD_DIALOG_COPYCITE };
	CStatic	m_StCustom;
	CComboBox	m_ComboCustom;
	CListBox	m_ListKeys;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCopyCitationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CCopyCitationDialog)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioCite();
	afx_msg void OnRadioCustom();
	afx_msg void OnRadioNocite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveHistory();
	void LoadHistory();
	int m_CiteFormat;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_COPYCITATIONDIALOG_H__BF7BAC3F_8308_4C11_9C4C_B0809CB1439A__INCLUDED_
