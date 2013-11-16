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

  $Id: bibedt.cpp,v 1.36 2006/08/07 17:45:26 stievie Exp $
*/

// bibedt.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include <afxpriv.h>
#include "bibedt.h"

#include "MainFrm.h"
#include "bibedtView.h"
#include "Options.h"
#include "Globals.h"
#include "ScintillaWnd.h"
#include "OptionsSheet.h"
#include "DocMgrEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBibedtApp

BEGIN_MESSAGE_MAP(CBibedtApp, CWinApp)
	//{{AFX_MSG_MAP(CBibedtApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_HELP_CHECKFORUPDATE, OnHelpCheckforupdate)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBibedtApp Konstruktion

CBibedtApp::CBibedtApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBibedtApp-Objekt

CBibedtApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBibedtApp Initialisierung

BOOL CBibedtApp::InitInstance()
{

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.
   
	InitCommonControls();
#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// Ändern des Registrierungsschlüssels, unter dem unsere Einstellungen gespeichert sind.
	SetRegistryKey(AfxLoadString(IDS_STRING_REGKEY));

	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)
	m_Language.LoadLanguages();
	m_Options = new COptions();
	m_Options->Load();
	m_Coding = new CCodingTeX();
	m_Coding->m_Enabled = m_Options->m_TranslateASCII;
	m_Coding->m_Filename = m_Options->m_EncodingTeX;
	m_Coding->m_Res = _T("TEX");
	m_Coding->Load();
	m_BibDef = new CBibDef();

	CScintillaWnd::LoadScintillaDll();

	m_pDocManager = new CDocManagerEx;
	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBibedtDoc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		RUNTIME_CLASS(CBibedtView));
	
	AddDocTemplate(pDocTemplate);

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Verteilung der in der Befehlszeile angegebenen Befehle
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Register Bib Clipboard format
	m_BibClipbrdFormat = RegisterClipboardFormat(CF_BIB);
	// Register RTF Clipboard format
	m_RtfClipbrdFormat = RegisterClipboardFormat(CF_RTF);
	m_HtmlClipbrdFormat = RegisterClipboardFormat(CF_HTML);

	// Shell
	EnableShellOpen();
#ifndef _DEBUG
	RegisterShellFileTypes(TRUE);
#endif
	m_pMainWnd->DragAcceptFiles();
	
	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	m_pMainWnd->ShowWindow(m_Options->m_WindowPlacement.showCmd);
	m_pMainWnd->UpdateWindow();

	if (m_Options->m_OpenLastFile && cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew && (UINT)m_pRecentFileList->GetSize() > 0) {
		// Open last file at start
		CString fn = m_pRecentFileList->m_arrNames[0];
		CFileFind ff;
		if (ff.FindFile(fn)) {
			OnOpenRecentFile(ID_FILE_MRU_FILE1);
		} else {
			// Does not exist
			//m_pRecentFileList->Remove(0);
		}
		ff.Close();
	}
	return TRUE;
}

int CBibedtApp::ExitInstance() 
{
	delete m_Options;	
	delete m_Coding;
	delete m_BibDef;
	return CWinApp::ExitInstance();
}

BOOL CBibedtApp::OnDDECommand(LPTSTR lpszCommand)
{
	// Server: bibedt
	// Topic: System
	if (CWinApp::OnDDECommand(lpszCommand))
		return TRUE;

   // Handle any DDE commands recognized by your application
   // and return TRUE.  See implementation of CWinApp::OnDDEComand
   // for example of parsing the DDE command string.

	CString	strCommand(lpszCommand);
	CString	strFileName(lpszCommand);	

	CString	itemKey;
	CMainFrame* main = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (main == NULL)
		return FALSE;
	CBibedtDoc* doc = dynamic_cast<CBibedtDoc*>(main->GetActiveDocument());
	if (doc == NULL)
		return FALSE;
	int	nStart, nEnd;
	if (strCommand.Left(7).CompareNoCase(_T("[goto(\"")) == 0) {
		// handle goto command => [goto("filepath", "itemkey")]

		// get file name
		nStart = strCommand.Find(_T('"'));
		nEnd = strCommand.Find(_T('"'), nStart + 1);
		if (nStart == -1 || nEnd == -1 || nEnd - nStart <= 1)
			return FALSE;

		strFileName = strCommand.Mid(nStart + 1, nEnd - (nStart + 1));

		// get key
		nStart = strCommand.Find(_T('"'), nEnd + 1);
		nEnd = strCommand.Find(_T('"'), nStart + 1);
		if (nStart == -1 || nEnd == -1 || nEnd - nStart <= 1)
			return FALSE;

		itemKey = strCommand.Mid(nStart + 1, nEnd - (nStart + 1));

		// open the document
		OpenDocumentFile(strFileName);
		doc->SetSelected(itemKey);
		return TRUE;
	} else if (strCommand.Left(8).CompareNoCase(_T("[focus(\"")) == 0) {
		// [focus("key")]
		// get key
		nStart = strCommand.Find(_T('"'));
		nEnd = strCommand.Find(_T('"'), nStart + 1);
		if (nStart == -1 || nEnd == -1 || nEnd - nStart <= 1)
			return FALSE;
		itemKey = strCommand.Mid(nStart + 1, nEnd - (nStart + 1));
		doc->SetSelected(itemKey);
		return TRUE;
	} else if (strCommand.Left(7).CompareNoCase(_T("[find(\"")) == 0) {
		// [find("str")]
		nStart = strCommand.Find(_T('"'));
		nEnd = strCommand.Find(_T('"'), nStart + 1);
		if (nStart == -1 || nEnd == -1 || nEnd - nStart <= 1)
			return FALSE;
		itemKey = strCommand.Mid(nStart + 1, nEnd - (nStart + 1));
		main->SetQuicksearchText(itemKey);
		doc->DoQuickSearch(itemKey, main->GetQuicksearchFields(), TRUE);
		return TRUE;
	} else if (strCommand.Left(9).CompareNoCase(_T("[filter(\"")) == 0) {
		// [filter("name")]
		nStart = strCommand.Find(_T('"'));
		nEnd = strCommand.Find(_T('"'), nStart + 1);
		if (nStart == -1 || nEnd == -1 || nEnd - nStart <= 1)
			return FALSE;
		itemKey = strCommand.Mid(nStart + 1, nEnd - (nStart + 1));
		CBibItem* filter = doc->m_BibFile->Find(STR_FILTER);
		if (filter) {
			CField* flt = filter->Find(itemKey);
			if (flt) {
				main->SelectFilter(flt);
				doc->SetFilter(flt);
				return TRUE;
			}
		}
	}

   // Return FALSE for any DDE commands you do not handle.
   return FALSE;
}

void CBibedtApp::OnToolsOptions() 
{
	COptionsSheet dlg(IDS_STRING_OPTIONS_CAP);
	dlg.SetOptions(m_Options);
	if (dlg.DoModal() == IDOK) {
		if (m_BibDef->GetFilename().CompareNoCase(m_Options->m_TemplateFile) != 0) {
			m_BibDef->SetFilename(m_Options->m_TemplateFile);
			m_BibDef->Load();
		}
		m_Coding->m_Enabled = m_Options->m_TranslateASCII;
		if (m_Coding->m_Filename.CompareNoCase(m_Options->m_EncodingTeX) != 0) {
			m_Coding->m_Filename = m_Options->m_EncodingTeX;
			m_Coding->Load();
		}
	}	
}

void CBibedtApp::OnHelpCheckforupdate() 
{
	if ((DWORD)ShellExecute(NULL, _T("open"), CString(BIBEDT_URL) + _T("?version=") + CAboutDlg::GetAppVersion(), 
		NULL, NULL, SW_NORMAL) <= HINSTANCE_ERROR) {
	}
}

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	CWaitCursor wait;
	CString v;
	v.Format(_T("Version %s"), GetAppVersion());
#ifdef _DEBUG
	v += _T("  ***DEBUG***");
#endif
	//{{AFX_DATA_INIT(CAboutDlg)
	m_Version = v;
	//}}AFX_DATA_INIT
	m_Email.SetURL(_T("mailto:") + CString(STIEVIE_MAIL));
	m_NilsEmail.SetURL(_T("mailto:") + CString(NILS_MAIL));
	m_Web.SetURL(CString(BIBEDT_URL) + _T("?version=") + GetAppVersion());
	m_btnDonate.LoadBitmaps(IDB_DONATE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_VERSION, m_Version);
	DDX_Control(pDX, IDC_STATIC_STIEVIE, m_Email);
	DDX_Control(pDX, IDC_STATIC_NILS, m_NilsEmail);
	DDX_Control(pDX, IDC_STATIC_WEB, m_Web);
	DDX_Control(pDX, IDC_DONATE, m_btnDonate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_DONATE, OnDonate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausführen des Dialogfelds
void CBibedtApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CBibedtApp-Nachrichtenbehandlungsroutinen

CString CAboutDlg::GetVersionString(LPCTSTR lpFile, LPCTSTR lpEntry)
{
	TCHAR   szBuffer[MAX_PATH];
	DWORD   dwVerHandle = 0 ;
	DWORD   dwVerSize = GetFileVersionInfoSize((LPTSTR)lpFile, &dwVerHandle) ;
	CString strReturn ;
	HANDLE  hMem ;
	if (dwVerSize > 0 && (hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerSize)) != NULL) {
		LPSTR lpVerInfo = (LPSTR)GlobalLock(hMem);
		if (lpVerInfo != NULL) {
			LPSTR lpEntryBuffer;
			UINT nEntryLen;
			GetFileVersionInfo((LPTSTR)lpFile, dwVerHandle, dwVerSize, lpVerInfo);
			struct LANGANDCODEPAGE {
				WORD wLanguage;
				WORD wCodePage;
			} *lpTranslate;
			// Read the list of languages and code pages.
			VerQueryValue(lpVerInfo, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &nEntryLen);
			for (UINT i = 0; i < (nEntryLen/sizeof(struct LANGANDCODEPAGE)); i++) {
				_stprintf(szBuffer, _T("\\StringFileInfo\\%04x%04x\\%s"), lpTranslate[i].wLanguage, lpTranslate[i].wCodePage, lpEntry);
				// Retrieve file description for language and code page "i". 
				if (VerQueryValue(lpVerInfo, szBuffer, (LPVOID*)&lpEntryBuffer, &nEntryLen)) {
					strReturn = lpEntryBuffer;
					break;
				}
			}
			GlobalUnlock(hMem);
		}
		GlobalFree(hMem);
	}
	return strReturn;
}

CString CAboutDlg::GetAppVersion()
{
	CString v = CAboutDlg::GetVersionString(COptions::GetExeName(), _T("ProductVersion"));
	v.Replace(_T(", "), _T("."));
	return v;
}

void CAboutDlg::OnDonate()
{
	::ShellExecute(NULL, _T("open"), AfxLoadString(IDS_DONATE_URL),
		NULL, NULL, SW_SHOWNORMAL);
}
