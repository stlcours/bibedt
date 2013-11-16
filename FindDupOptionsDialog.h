/*
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie@utanet.at, http://bibedt.sourceforge.net/

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

  $Id: FindDupOptionsDialog.h,v 1.1 2005/09/02 20:08:22 stievie Exp $
*/

#if !defined(AFX_FINDDUPOPTIONSDIALOG_H__5A904CD9_C8F4_4272_A4CD_6F314AB32F97__INCLUDED_)
#define AFX_FINDDUPOPTIONSDIALOG_H__5A904CD9_C8F4_4272_A4CD_6F314AB32F97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDupOptionsDialog.h : Header-Datei
//

#include "BibList.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDupOptionsDialog 

class CFindDupOptionsDialog : public CDialog
{
// Konstruktion
public:
	CString m_Fields;
	CFindDupOptionsDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	void SetBibList(CBibList* lst) { m_BibList = lst; }
	virtual void OnOK();
	CBibList* GetBibList() { return m_BibList; }

// Dialogfelddaten
	//{{AFX_DATA(CFindDupOptionsDialog)
	enum { IDD = IDD_DIALOG_FINDDUPLOP };
	CComboBox	m_cboFields;
	BOOL	m_CaseSens;
	BOOL	m_Exact;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFindDupOptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFindDupOptionsDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBibList* m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FINDDUPOPTIONSDIALOG_H__5A904CD9_C8F4_4272_A4CD_6F314AB32F97__INCLUDED_
