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

  $Id: SourceDialog.h,v 1.12 2006/04/09 21:41:13 stievie Exp $
*/

#if !defined(AFX_SOURCEDIALOG_H__8125108A_5B76_4B50_9CC8_F8E482A60C60__INCLUDED_)
#define AFX_SOURCEDIALOG_H__8125108A_5B76_4B50_9CC8_F8E482A60C60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceDialog.h : Header-Datei
//

#include "BibItem.h"
#include "BibList.h"
#include "ScintillaBibWnd.h"
#include "BPCtrlAnchorMap.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSourceDialog 

class CSourceDialog : public CDialog
{
// Konstruktion
public:
	BOOL m_ReadOnly;
	void SetReadOnly(BOOL val);
	int m_Lexer;
	void SetLexer(int lexer);
	void SetSource(CString src);
	BOOL m_Modified;
	void SetBibList(CBibList *list);
	CString GetSource();
	CBibItem* GetBibItem();
	void SetBibItem(CBibItem* item);
	CSourceDialog(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual void OnOK();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_ANCHOR_MAP();

// Dialogfelddaten
	//{{AFX_DATA(CSourceDialog)
	enum { IDD = IDD_DIALOG_SOURCE };
	CScintillaBibWnd m_ScintillaCtrl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSourceDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSourceDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBibList * m_BibList;
	CString m_Source;
	CBibItem* m_BibItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SOURCEDIALOG_H__8125108A_5B76_4B50_9CC8_F8E482A60C60__INCLUDED_
