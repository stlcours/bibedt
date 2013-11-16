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

  $Id: GenFromAuxDialog.h,v 1.4 2006/07/08 11:23:44 stievie Exp $
*/

#if !defined(AFX_GENFROMAUXDIALOG_H__04F61854_5973_498A_A090_8C3BAD43449B__INCLUDED_)
#define AFX_GENFROMAUXDIALOG_H__04F61854_5973_498A_A090_8C3BAD43449B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenFromAuxDialog.h : Header-Datei
//

#include "BPCtrlAnchorMap.h"
#include "AuxParser.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGenFromAuxDialog 

class CGenFromAuxDialog : public CDialog
{
// Konstruktion
public:
	void AddLog(CString txt);
	static BOOL CALLBACK LogProc(CString fn, DWORD pOwner);
	CGenFromAuxDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	DECLARE_ANCHOR_MAP();
	void SetBibList(CBibList* lst) { m_BibList = lst; }

// Dialogfelddaten
	//{{AFX_DATA(CGenFromAuxDialog)
	enum { IDD = IDD_DIALOG_GENFROMAUX };
	CButton	m_btnReqFields;
	CButton	m_btnGenerate;
	CEdit	m_editAuxFile;
	CEdit	m_editLog;
	CEdit	m_editTargetFile;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CGenFromAuxDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CGenFromAuxDialog)
	afx_msg void OnButtonAuxbrowse();
	afx_msg void OnButtonTargetbrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonGenerate();
	afx_msg void OnChangeEditAuxfile();
	afx_msg void OnChangeEditTargetfile();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void RemoveNotRequiredFields(CBibItem* item, BOOL remove);
	CBibList* m_BibList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_GENFROMAUXDIALOG_H__04F61854_5973_498A_A090_8C3BAD43449B__INCLUDED_
