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

  $Id: InputBox.h,v 1.4 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_INPUTBOX_H__DB870308_3225_46DB_96B5_7B514785CAFB__INCLUDED_)
#define AFX_INPUTBOX_H__DB870308_3225_46DB_96B5_7B514785CAFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputBox.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInputBox 

/**
 * \brief A simple InputBox.
 *
 * A Dialog with one Edit and a OK and Cancel button.
 */
class CInputBox : public CDialog
{
// Konstruktion
public:
	CString m_Caption;
	void SetCaption(CString caption);
	void SetPrompt(CString prompt);
	CInputBox(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CInputBox)
	enum { IDD = IDD_DIALOG_INPUTBOX };
	CStatic	m_StPrompt;
	CString	m_strText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CInputBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CInputBox)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_Prompt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_INPUTBOX_H__DB870308_3225_46DB_96B5_7B514785CAFB__INCLUDED_
