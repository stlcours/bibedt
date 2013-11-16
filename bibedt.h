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

  $Id: bibedt.h,v 1.25 2006/08/06 13:55:44 stievie Exp $
*/

// bibedt.h : Haupt-Header-Datei für die Anwendung BIBEDT
//

#if !defined(AFX_BIBEDT_H__30A6BBAA_8E3C_4C25_A875_A6A34FB670E7__INCLUDED_)
#define AFX_BIBEDT_H__30A6BBAA_8E3C_4C25_A875_A6A34FB670E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

#include "Options.h"
#include "CodingTeX.h"
#include "BibDef.h"
#include "bibedtDoc.h"
#include "LinkStatic.h"
#include "MyBitmapButton.h"
#include "Language.h"

// View IDs
#define VIEW_SPLITTER      10
#define VIEW_SPLITTERVIEW  11

#define VIEW_TAB     1
#define VIEW_LIST    2
#define VIEW_SOURCE  3
#define VIEW_RECORD  4
#define VIEW_PREVIEW 5

static const TCHAR STIEVIE_MAIL[] = _T("stievie\x40users\x2Esourceforge\x2Enet");
static const TCHAR NILS_MAIL[] = _T("hops-1\x40users\x2Esourceforge\x2Enet");
static const TCHAR BIBEDT_URL[] = _T("http://bibedt.sourceforge.net/");

// Custom messages
#define WM_BE_LANUAGE_CHANGED (WM_APP + 5)
#define WM_BE_FONT_CHANGED    (WM_APP + 6)

/////////////////////////////////////////////////////////////////////////////
// CBibedtApp:
// Siehe bibedt.cpp für die Implementierung dieser Klasse
//

class CBibedtApp : public CWinApp
{
public:
	BOOL OnDDECommand(LPTSTR lpszCommand);
	CBibedtApp();
	COptions* m_Options;
	CCodingTeX* m_Coding;
	CBibDef* m_BibDef;
	UINT GetBibClipbrdFormat() { return m_BibClipbrdFormat; }
	UINT GetRtfClipbrdFormat() { return m_RtfClipbrdFormat; }
	UINT GetHtmlClipbrdFormat() { return m_HtmlClipbrdFormat; }
	CLanguage m_Language;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBibedtApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CBibedtApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsOptions();
	afx_msg void OnHelpCheckforupdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_BibClipbrdFormat;
	UINT m_RtfClipbrdFormat;
	UINT m_HtmlClipbrdFormat;
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	static CString GetAppVersion();
	static CString GetVersionString(LPCTSTR lpFile, LPCTSTR lpEntry);
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Version;
	CLinkStatic m_Email;
	CLinkStatic m_NilsEmail;
	CLinkStatic m_Web;
	CMyBitmapButton m_btnDonate;
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	afx_msg void OnDonate();
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BIBEDT_H__30A6BBAA_8E3C_4C25_A875_A6A34FB670E7__INCLUDED_)
