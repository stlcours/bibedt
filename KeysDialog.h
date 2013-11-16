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

  $Id: KeysDialog.h,v 1.4 2006/05/25 14:15:46 stievie Exp $
*/

#if !defined(AFX_KEYSDIALOG_H__B9D42236_8B6F_4A29_9ECD_38B3A874E0D4__INCLUDED_)
#define AFX_KEYSDIALOG_H__B9D42236_8B6F_4A29_9ECD_38B3A874E0D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeysDialog.h : Header-Datei
//

#include "BibList.h"
#include "BPCtrlAnchorMap.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CKeysDialog 

class CKeysDialog : public CDialog
{
// Konstruktion
public:
	CString m_SelKey;
	void SetBibList(CBibList* lst) {m_BibList = lst; }
	CKeysDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CKeysDialog)
	enum { IDD = IDD_DIALOG_KEYS };
	CButton	m_btnOk;
	CEdit	m_editPreview;
	CListBox	m_lstKeys;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CKeysDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CKeysDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListKeys();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeListKeys();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBibList* m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_KEYSDIALOG_H__B9D42236_8B6F_4A29_9ECD_38B3A874E0D4__INCLUDED_
