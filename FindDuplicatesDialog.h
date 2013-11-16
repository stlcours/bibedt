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

  $Id: FindDuplicatesDialog.h,v 1.11 2005/10/06 21:02:03 stievie Exp $
*/

#if !defined(AFX_FINDDUPLICATESDIALOG_H__E99EA78B_E749_48A5_BF94_5B234E534F93__INCLUDED_)
#define AFX_FINDDUPLICATESDIALOG_H__E99EA78B_E749_48A5_BF94_5B234E534F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDuplicatesDialog.h : Header-Datei
//

#include "bibedt.h"
#include "BibList.h"
#include "ScintillaBibWnd.h"
#include "BPCtrlAnchorMap.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDuplicatesDialog 

class CFindDuplicatesDialog : public CDialog
{
// Konstruktion
public:
	CString GetDuplicateField(CBibItem* bi1, CBibItem* bi2, CStringList *lstfields);
	BOOL m_CaseSens;
	BOOL m_Exact;
	CString m_Fields;
	void SelectOrBookmark(BOOL bookmark);
	DWORD m_DuplicateCount;
	void SetBibList(CBibList *value);
	CFindDuplicatesDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CFindDuplicatesDialog)
	enum { IDD = IDD_DIALOG_DUPLICATES };
	CButton	m_BtnBookmark;
	CButton	m_BtnSelect;
	CTreeCtrl	m_TreeItems;
	CScintillaBibWnd m_ScintillaCtrl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFindDuplicatesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CBibList * m_BibItems;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFindDuplicatesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeItems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonSelect();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkTreeItems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonBookmark();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM FindItem(CString key);
	BOOL DoFindDuplicates();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FINDDUPLICATESDIALOG_H__E99EA78B_E749_48A5_BF94_5B234E534F93__INCLUDED_
