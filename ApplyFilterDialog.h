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

  $Id: ApplyFilterDialog.h,v 1.2 2005/10/11 23:22:14 stievie Exp $
*/

#if !defined(AFX_APPLYFILTERDIALOG_H__C65C9C2F_4810_44F3_91C5_D290982EB89E__INCLUDED_)
#define AFX_APPLYFILTERDIALOG_H__C65C9C2F_4810_44F3_91C5_D290982EB89E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ApplyFilterDialog.h : Header-Datei
//

#include "BibItem.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CApplyFilterDialog 

class CApplyFilterDialog : public CDialog
{
// Konstruktion
public:
	void SetFilter(CBibItem* filter) { m_Filter = filter; }
	CApplyFilterDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	CField* m_SelFilter;
	virtual void OnOK();

// Dialogfelddaten
	//{{AFX_DATA(CApplyFilterDialog)
	enum { IDD = IDD_DIALOG_APPLYFILTER };
	CButton	m_btnOk;
	CListBox	m_lstFilter;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CApplyFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void AppendFilter(CBibItem* filter);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CApplyFilterDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListFilter();
	afx_msg void OnSelchangeListFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBibItem* m_Filter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_APPLYFILTERDIALOG_H__C65C9C2F_4810_44F3_91C5_D290982EB89E__INCLUDED_
