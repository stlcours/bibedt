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

  $Id: PreambleDialog.h,v 1.11 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_PREAMBLEDIALOG_H__E729AF69_D787_4525_8F13_12B44DDD1E9F__INCLUDED_)
#define AFX_PREAMBLEDIALOG_H__E729AF69_D787_4525_8F13_12B44DDD1E9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreambleDialog.h : Header-Datei
//

#include "BibList.h"
#include "ScintillaBibWnd.h"
#include "BPCtrlAnchorMap.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreambleDialog 

class CPreambleDialog : public CDialog
{
// Konstruktion
public:
	CPreambleDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	~CPreambleDialog();

public:
	CBibList * GetBibList();
	int m_Selection;
	void SetBibList(CBibList* value);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnOK();
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CPreambleDialog)
	enum { IDD = IDD_DIALOG_PREAMBLE };
	CButton	m_BtnSource;
	CButton	m_BtnUndo;
	CButton	m_BtnApply;
	CButton	m_BtnRemove;
	CListCtrl	m_lvPreambles;
	CScintillaBibWnd m_ScintillaCtrl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPreambleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPreambleDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnButtonAddfield();
	afx_msg void OnClickListPreambles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonFieldremove();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonUndo();
	afx_msg void OnButtonSource();
	afx_msg void OnDblclkListPreambles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeydownListPreambles(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Update();
	void Apply();
	CBibList* m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PREAMBLEDIALOG_H__E729AF69_D787_4525_8F13_12B44DDD1E9F__INCLUDED_
