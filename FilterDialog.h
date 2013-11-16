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

  $Id: FilterDialog.h,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_FILTERDIALOG_H__C25B9E21_588D_467A_823F_242B6C386DCF__INCLUDED_)
#define AFX_FILTERDIALOG_H__C25B9E21_588D_467A_823F_242B6C386DCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterDialog.h : Header-Datei
//

#include "BPCtrlAnchorMap.h"
#include "BibItem.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFilterDialog 

class CFilterDialog : public CDialog
{
// Konstruktion
public:
	void MoveFilter(int curinx, int newinx);
	void SetSelected(int index, BOOL selected);
	void Apply();
	CBibItem * GetFilter();
	~CFilterDialog();
	void SetFilter(CBibItem* filter);
	CFilterDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CFilterDialog)
	enum { IDD = IDD_DIALOG_FILTER };
	CButton	m_BtnDown;
	CButton	m_BtnUp;
	CButton	m_BtnRemove;
	CButton	m_BtnEdit;
	CListCtrl	m_lvFields;
	CEdit	m_EditCond;
	CEdit	m_EditField;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFilterDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEndlabeleditListFilters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListFilters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonEdit();
	afx_msg void OnItemchangedListFilters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangingListFilters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_Updating;
	void EnableControls();
	int m_Selected;
	CBibItem * m_Filter;
	CBibList * m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FILTERDIALOG_H__C25B9E21_588D_467A_823F_242B6C386DCF__INCLUDED_
