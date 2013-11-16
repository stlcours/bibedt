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

  $Id: StringsDialog.h,v 1.11 2006/06/06 18:52:19 stievie Exp $
*/

#if !defined(AFX_STRINGSDIALOG_H__3D17A22E_88D1_472E_B89E_4E1B6E5EB520__INCLUDED_)
#define AFX_STRINGSDIALOG_H__3D17A22E_88D1_472E_B89E_4E1B6E5EB520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StringsDialog.h : Header-Datei
//

#include "BibList.h"
#include "ScintillaBibWnd.h"
#include "BPCtrlAnchorMap.h"

const TCHAR STR_NEWSTRING[] = _T("NewString");

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CStringsDialog 

class CStringsDialog : public CDialog
{
// Konstruktion
public:
	CBibList * GetBibList();
	int m_Selected;
	void Populate();
	void SetBibList(CBibList* value);
	CStringsDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	~CStringsDialog();
	virtual void OnOK();
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CStringsDialog)
	enum { IDD = IDD_DIALOG_STRING };
	CButton	m_BtnApply;
	CButton	m_BtnUndo;
	CButton	m_BtnSource;
	CButton	m_BtnRemove;
	CButton	m_BtnEdit;
	CListCtrl	m_ListStrings;
	CScintillaBibWnd m_ScintillaCtrl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CStringsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CStringsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonRemove();
	afx_msg void OnDeleteitemListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitemListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnButtonSource();
	afx_msg void OnDblclkListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonUndo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKeydownListStrings(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Apply();
	void Update();
	BOOL m_Updating;
	CBibList* m_BibList;
	CBibList* m_TmpList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_STRINGSDIALOG_H__3D17A22E_88D1_472E_B89E_4E1B6E5EB520__INCLUDED_
