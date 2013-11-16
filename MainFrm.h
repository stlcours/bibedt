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

  $Id: MainFrm.h,v 1.25 2006/06/03 14:14:34 stievie Exp $
*/

// MainFrm.h : Schnittstelle der Klasse CMainFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EE46AA4E_F335_4C75_85E7_4F9AEB02B7C7__INCLUDED_)
#define AFX_MAINFRM_H__EE46AA4E_F335_4C75_85E7_4F9AEB02B7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VisualFx.h"
#include "ToolbarEx.h"

class CMainFrame : public CFrameWnd
{
	
protected: // Nur aus Serialisierung erzeugen
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebundene Elemente der Steuerleiste
	CStatusBar  m_wndStatusBar;
	CToolBarEx  m_wndToolBar;
	CDialogBar  m_wndFilter;
	CDialogBar  m_wndQuickSearch;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateKeyIndicator(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnFilePageSetup();
	afx_msg void OnHelpChangelog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateViewToolbarsFilter(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarsFilter();
	afx_msg void OnViewToolbarsQuicksearch();
	afx_msg void OnUpdateViewToolbarsQuicksearch(CCmdUI* pCmdUI);
	afx_msg void OnHelpManual();
	afx_msg void OnViewToolbarsCustomize();
	afx_msg void OnViewListview();
	afx_msg void OnViewSourceview();
	afx_msg void OnViewRecord();
	afx_msg void OnUpdateViewRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewListview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSourceview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewResetquicksearch(CCmdUI* pCmdUI);
	afx_msg void OnViewResetquicksearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SelectFilter(CField* filter);
	void SetQuicksearchText(CString str);
	CString GetQuicksearchFields();
	void AppendFilter(CBibItem *filter);
	void DoQuicksearch();
	void UpdateQuicksearchFields(CStringList *lst);
	void ResetQuicksearch();
	void FocusActiveView();
	void UpdateFilter(CBibItem* filter);
	void EnableView(DWORD dwID, BOOL enable);
	BOOL ActivateView(DWORD dwID);
	TVisualFramework m_Framework;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAINFRM_H__EE46AA4E_F335_4C75_85E7_4F9AEB02B7C7__INCLUDED_)
