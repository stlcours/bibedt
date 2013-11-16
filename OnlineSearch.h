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

  $Id: OnlineSearch.h,v 1.15 2006/06/06 18:52:18 stievie Exp $
*/

#if !defined(AFX_ONLINESEARCH_H__A3FF1BE0_3D31_48B9_9319_3B896FD8D247__INCLUDED_)
#define AFX_ONLINESEARCH_H__A3FF1BE0_3D31_48B9_9319_3B896FD8D247__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnlineSearch.h : Header-Datei
//

#include "BPCtrlAnchorMap.h"
#include "BibList.h"
#include "bibedtDoc.h"
#include "Yaz.h"
#include "SearchProfile.h"

static const TCHAR YAZ_MANUAL[] = _T("yaz.pdf");
static const TCHAR YAZ_MANUAL_URL[] = _T("http://indexdata.dk/yaz/doc/");

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COnlineSearch 

class COnlineSearch : public CDialog
{
// Konstruktion
public:
	CString m_RecordSyntax;
	void DoSearch();
	void UpdateProfileList();
	void SaveProfile();
	void SetQueryType(QUERY_TYPE q);
	void SetDocument(CBibedtDoc* doc) { m_Document = doc; }
	QUERY_TYPE GetQueryType();
	void SetBibList(CBibList* lst) { m_BibList = lst; }
	CBibList m_Results;
	COnlineSearch(CWnd* pParent = NULL);   // Standardkonstruktor
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(COnlineSearch)
	enum { IDD = IDD_DIALOG_ONLINESEARCH };
	CButton	m_chkSavePass;
	CSpinButtonCtrl	m_spinRecEnd;
	CEdit	m_editRecEnd;
	CButton	m_btnImport;
	CEdit	m_editRawData;
	CStatic	m_staticResults;
	CSpinButtonCtrl	m_spinRecStart;
	CEdit	m_editRecStart;
	CSpinButtonCtrl	m_spinPort;
	CComboBox	m_cboProfiles;
	CEdit	m_editUser;
	CEdit	m_editProxy;
	CEdit	m_editPass;
	CEdit	m_editGroup;
	CListCtrl	m_lstResults;
	CEdit	m_editSearchFor;
	CEdit	m_editHost;
	CEdit	m_editPort;
	CEdit	m_editDatabase;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COnlineSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COnlineSearch)
	afx_msg void OnSearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonImport();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnButtonNewprofile();
	afx_msg void OnSelchangeComboProfiles();
	afx_msg void OnButtonEditprofile();
	afx_msg void OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonNext();
	afx_msg void OnCloseClick();
	afx_msg void OnButtonHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSearchProfileList m_ProfilesList;
	CBibedtDoc* m_Document;
	BOOL GetSelected(int i);
	CBibList* m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ONLINESEARCH_H__A3FF1BE0_3D31_48B9_9319_3B896FD8D247__INCLUDED_
