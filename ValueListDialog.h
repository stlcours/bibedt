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

  $Id: ValueListDialog.h,v 1.3 2006/08/13 11:05:00 stievie Exp $
*/

#if !defined(AFX_VALUELISTDIALOG_H__70997668_029E_4BEB_A4F5_16C54B0D9542__INCLUDED_)
#define AFX_VALUELISTDIALOG_H__70997668_029E_4BEB_A4F5_16C54B0D9542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValueListDialog.h : Header-Datei
//

#include "bibedt.h"
#include "BPCtrlAnchorMap.h"
#include "BibList.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CValueListDialog 

class CValueListDialog : public CDialog
{
// Konstruktion
public:
	void Refresh();
	CBibList *GetBibList() { return m_BibList; }
	void SetBibList(CBibList *val) { m_BibList = val; }
	CValueListDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CValueListDialog)
	enum { IDD = IDD_DIALOG_VALUELIST };
	CListCtrl	m_lvValues;
	CComboBox	m_cboField;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CValueListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CValueListDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRefresh();
	afx_msg void OnSelchangeComboField();
	afx_msg void OnEditchangeComboField();
	afx_msg void OnPopupSelect();
	afx_msg void OnUpdatePopupSelect(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDblclkListValues(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SelectMatching();
	CString m_CurField;
	CBibList * m_BibList;
	CMenu m_PopupMenu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VALUELISTDIALOG_H__70997668_029E_4BEB_A4F5_16C54B0D9542__INCLUDED_
