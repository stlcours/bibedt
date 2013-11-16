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

  $Id: Options.cpp,v 1.37 2006/08/12 16:06:17 stievie Exp $
*/

// Options.cpp: Implementierung der Klasse COptions.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "Options.h"
#include "Globals.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

COptions::COptions()
{
	m_ExporterList = new CExporterList();
}

COptions::~COptions()
{
	Save();
	delete m_ExporterList;
}

/**
 * \brief Load options and settings from Registry.
 */
void COptions::Load()
{
	m_Backup = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("Backup"), 1);
	m_AutoCompleteValues = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("AutoCompleteValues"), 1);
	m_OpenLastFile = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("OpenLastFile"), 0);
	m_GridLines = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("GridLines"), 0);
	m_ReplaceSpecialChar = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ReplaceSpecialChar"), 1);
	m_ScrollToSelected = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ScrollToSelected"), 1);
	m_DisableSave = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("DisableSave"), 0);

	// Files
	m_ConfigDir = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("ConfigDir"), GetAppPath());
	UpdateFiles();
	((CBibedtApp*)AfxGetApp())->m_Language.SetCurLang(AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Language"), _T("")));
	// Fonts
	m_FontProp = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Font.Prop"), _T("Times New Roman"));
	m_FontMono = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Font.Mono"), _T("Courier New"));
	m_FontSans = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Font.Sans"), _T("MS Sans Serif"));

	m_TranslateASCII = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("TranslateASCII"), 1);
	m_SortCaseSensitive = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("CaseSensSort"), 0);
	m_SortOnSave = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("SortOnSave"), 0);
	m_LineLength = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("LineLength"), MAX_LINE);
	m_CiteFormat = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("CiteFormat"), _T("\\cite{%s}"));
	m_ShowCiteDlg = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ShowCiteDlg"), 1);
	m_DOIURL = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("DOIURL"), DEF_DOI_URL);
	if (!m_DOIURL.IsEmpty()) {
		if (m_DOIURL.Left(7).CompareNoCase(_T("http://")) != 0)
			m_DOIURL = _T("http://") + m_DOIURL;
		if (m_DOIURL.Right(1).Compare(_T("/")) != 0)
			m_DOIURL += _T("/");
	} else
		m_DOIURL = DEF_DOI_URL;
	m_EditorClassName = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("EditorClass"), _T(""));
	m_EditorParentClass = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("EditorParentClass"), _T(""));

	// Print
	m_MarginLeft = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("MarginLeft"), MARGIN_LEFT);
	m_MarginTop = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("MarginTop"), MARGIN_TOP);
	m_MarginRight = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("MarginRight"), MARGIN_RIGHT);
	m_MarginBottom = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("MarginBottom"), MARGIN_BOTTOM);
	m_PrintUnits = (enum Units)AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("PrintUnits"), 0);

	// Columns
	m_ColCount = AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ColCount"), 3);

	// Quicksearch
	m_QuickSearchFields = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("QuickSearchFields"), _T("author;title;"));

	// Window placement
	ReadWindowPlacement(_T(""),	&m_WindowPlacement);
}

/**
 * \brief Write options and setting to registry.
 */
void COptions::Save()
{
	m_ExporterList->Save();

	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("Backup"), m_Backup);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("AutoCompleteValues"), m_AutoCompleteValues);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("OpenLastFile"), m_OpenLastFile);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("GridLines"), m_GridLines);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ReplaceSpecialChar"), m_ReplaceSpecialChar);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ScrollToSelected"), m_ScrollToSelected);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("DisableSave"), m_DisableSave);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("ConfigDir"), m_ConfigDir);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("TranslateASCII"), m_TranslateASCII);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("CaseSensSort"), m_SortCaseSensitive);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("SortOnSave"), m_SortOnSave);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("LineLength"), m_LineLength);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("CiteFormat"), m_CiteFormat);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ShowCiteDlg"), m_ShowCiteDlg);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("DOIURL"), m_DOIURL);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("EditorClass"), m_EditorClassName);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("EditorParentClass"), m_EditorParentClass);
	POSITION p = ((CBibedtApp*)AfxGetApp())->m_Language.GetCurLang();
	if (p) {
		LANG_INFO lang = ((CBibedtApp*)AfxGetApp())->m_Language.GetAt(p);
		AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Language"), lang.path);
	}
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Font.Prop"), m_FontProp);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Font.Mono"), m_FontMono);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Font.Sans"), m_FontSans);
	
	// Print
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("MarginLeft"), m_MarginLeft);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("MarginTop"), m_MarginTop);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("MarginRight"), m_MarginRight);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("MarginBottom"), m_MarginBottom);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("PrintUnits"), m_PrintUnits);

	// Columns
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ColCount"), m_ColCount);

	// Quicksearch
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("QuickSearchFields"), m_QuickSearchFields);

	// Window placement
	WriteWindowPlacement(_T(""), m_WindowPlacement);
}

/**
 * \brief Return application path.
 */
CString COptions::GetAppPath()
{
	CString exe = GetExeName();
	int i = exe.ReverseFind(_T('\\'));
	if (i == -1)
		return _T("");
	exe = exe.Left(i);
	return exe;
}

/**
 * \brief Return program filename.
 */
CString COptions::GetExeName()
{
	TCHAR pcEXE[MAX_PATH];
	GetModuleFileName(NULL, pcEXE, MAX_PATH);
	return pcEXE;
}

/**
 * \brief Return filename of template file.
 *
 * Concatenates the Temp directroy and the parameter name.
 *
 * \param name The name of the file.
 */
CString COptions::GetTempFilename(CString name)
{
	CString tempfilename;
	CString tempdir = _T("");

	//Get the Temp-Dir.
	DWORD tmpdirlen = GetTempPath(0, NULL);
	TCHAR* pTmpDir = tempdir.GetBuffer(tmpdirlen);
	tmpdirlen = GetTempPath(tmpdirlen, pTmpDir);
	tempdir.ReleaseBuffer(); //tmpdirlen should not including the terminating null character, but XP seems to handle this differently...
	tempdir.Replace(_T('/'), _T('\\'));
	if (tempdir.Right(1) != _T("\\")) {
		//Assure ending '\' (XP seems to also handle this different...)
		tempdir += _T("\\");
	}
	return tempdir + name;
}

/**
 * \brief Return the name of a column.
 *
 * \param index The index of the column.
 * \param def The default name.
 */
CString COptions::GetColName(int index, CString def)
{
	CString key;
	key.Format(_T("ColName%d"), index);
	return AfxGetApp()->GetProfileString(SETTINGS_KEY, key, def);
}

/**
 * \brief Return the width of a column.
 *
 * \param index The index of the column.
 * \param def The default width.
 */
int COptions::GetColWidth(int index, int def)
{
	CString key;
	key.Format(_T("ColWidth%d"), index);
	return AfxGetApp()->GetProfileInt(SETTINGS_KEY, key, def);
}

/**
 * \brief Set the name of a column.
 *
 * \param index The index of the column.
 * \param name The new name.
 */
void COptions::SetColName(int index, CString name)
{
	CString key;
	key.Format(_T("ColName%d"), index);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, key, name);
}

/**
 * \brief Set the width of a column.
 *
 * \param index The index of the column.
 * \param width The new width.
 */
void COptions::SetColWidth(int index, int width)
{
	CString key;
	key.Format(_T("ColWidth%d"), index);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, key, width);
}

/**
 * \brief Return the Manual filename.
 *
 * Searches for bibedt.pdf either in the program directory or in the 'doc' subdirectory.
 */
CString COptions::GetManualFile()
{
	return FindFile(BIBEDT_MANUAL);
}

/**
 * \brief Return the ChangeLog filename.
 *
 * Searches for changelog.txt either in the program directory or in one level up.
 */
CString COptions::GetChangelogFile()
{
	return FindFile(CHANGELOG_FILE);
}

void COptions::ReadWindowPlacement(CString key, WINDOWPLACEMENT* res)
{
	CString k;
	if (!key.IsEmpty())
		k.Format(_T("%s\\%s"), SETTINGS_KEY, key);
	else
		k = SETTINGS_KEY;
	res->showCmd = AfxGetApp()->GetProfileInt(k, _T("wp.showCmd"), SW_SHOWNORMAL);
	res->rcNormalPosition.left = AfxGetApp()->GetProfileInt(k, _T("wp.rcNormalPosition.left"), 0);
	res->rcNormalPosition.top = AfxGetApp()->GetProfileInt(k, _T("wp.rcNormalPosition.top"), 0);
	res->rcNormalPosition.bottom = AfxGetApp()->GetProfileInt(k, _T("wp.rcNormalPosition.bottom"), 0);
	res->rcNormalPosition.right = AfxGetApp()->GetProfileInt(k, _T("wp.rcNormalPosition.right"), 0);
	res->flags = AfxGetApp()->GetProfileInt(k, _T("wp.flags"), WPF_SETMINPOSITION);
	res->ptMaxPosition.x = AfxGetApp()->GetProfileInt(k, _T("wp.ptMaxPosition.x"), 0xFFFFFFFF);
	res->ptMaxPosition.y = AfxGetApp()->GetProfileInt(k, _T("wp.ptMaxPosition.y"), 0xFFFFFFFF);
	res->ptMinPosition.x = AfxGetApp()->GetProfileInt(k, _T("wp.ptMinPosition.x"), 0xFFFFFFFF);
	res->ptMinPosition.y = AfxGetApp()->GetProfileInt(k, _T("wp.ptMinPosition.y"), 0xFFFFFFFF);
}

void COptions::WriteWindowPlacement(CString key, WINDOWPLACEMENT val)
{
	CString k;
	if (!key.IsEmpty())
		k.Format(_T("%s\\%s"), SETTINGS_KEY, key);
	else
		k = SETTINGS_KEY;
	if (val.showCmd == SW_SHOWNORMAL) {
		AfxGetApp()->WriteProfileInt(k, _T("wp.rcNormalPosition.left"), val.rcNormalPosition.left);
		AfxGetApp()->WriteProfileInt(k, _T("wp.rcNormalPosition.top"), val.rcNormalPosition.top);
		AfxGetApp()->WriteProfileInt(k, _T("wp.rcNormalPosition.bottom"), val.rcNormalPosition.bottom);
		AfxGetApp()->WriteProfileInt(k, _T("wp.rcNormalPosition.right"), val.rcNormalPosition.right);
	}
	AfxGetApp()->WriteProfileInt(k, _T("wp.showCmd"), val.showCmd);
	AfxGetApp()->WriteProfileInt(k, _T("wp.flags"), val.flags);
	AfxGetApp()->WriteProfileInt(k, _T("wp.ptMaxPosition.x"), val.ptMaxPosition.x);
	AfxGetApp()->WriteProfileInt(k, _T("wp.ptMaxPosition.y"), val.ptMaxPosition.y);
	AfxGetApp()->WriteProfileInt(k, _T("wp.ptMinPosition.x"), val.ptMinPosition.x);
	AfxGetApp()->WriteProfileInt(k, _T("wp.ptMinPosition.y"), val.ptMinPosition.y);
}

CString COptions::ResolveDOI(CString doi)
{
	CString ret = doi;
	if (ret.Left(_tcsclen(STR_DOIPROTOCOLL)).CompareNoCase(STR_DOIPROTOCOLL) == 0) {
		// Resolve DOI
		ret.Delete(0, _tcsclen(STR_DOIPROTOCOLL));
		ret = m_DOIURL + ret;
	}
	return ret;
}

HWND COptions::GetEditorWindow()
{
	m_EditorWnd = 0;
	if (!m_EditorClassName.IsEmpty() && !m_EditorParentClass.IsEmpty()) {
		HWND parent = FindWindow(m_EditorParentClass, NULL);
		EnumChildWindows(parent, EnumChildProc, (LPARAM)this);
	}
	return m_EditorWnd;
}

BOOL CALLBACK COptions::EnumChildProc(HWND hwnd, LPARAM lParam)
{
	COptions* o = (COptions*)lParam;
	LPTSTR fcn = (LPTSTR)malloc(80);
	BOOL ret;
	if (GetClassName(hwnd, fcn, 80)) {
		ret = _tcsicmp(o->m_EditorClassName, fcn) != 0;
		if (!ret)
			o->m_EditorWnd = hwnd;
	} else
		ret = TRUE;
	free(fcn);
	return ret;
}

CString COptions::AddBackslash(CString str)
{
	return (str.IsEmpty() || str.Right(1) == _T("\\")) ? str : str + _T("\\");
}

CString COptions::RemoveBackslash(CString str)
{
	if (!str.IsEmpty() && str.Right(1) == _T("\\"))
		str.Delete(str.GetLength()-1);
	return str;
}

CString COptions::FindFile(CString name)
{
	CFileFind finder;
	CString res;
	res.Format(_T("%s%s"), AddBackslash(GetAppPath()), name);
	BOOL found = finder.FindFile(res);
	if (!found)	{
		res.Format(_T("%s..\\%s"), AddBackslash(GetAppPath()), name);
		found = finder.FindFile(res);
		if (!finder.FindFile(res)) {
			res.Format(_T("%s..\\doc\\%s"), AddBackslash(GetAppPath()), name);
			if (!finder.FindFile(res))
				res.Empty();
		}
	}
	finder.Close();
	return res;
}

void COptions::UpdateFiles()
{
	m_TemplateFile = AddBackslash(m_ConfigDir) + DEF_BIB_FILE;
	m_EncodingTeX = AddBackslash(m_ConfigDir) + CODING_TEX;
	m_EncodingHTML = AddBackslash(m_ConfigDir) + CODING_HTML;
	m_EncodingRTF = AddBackslash(m_ConfigDir) + CODING_RTF;
	m_EncodingXML = AddBackslash(m_ConfigDir) + CODING_XML;
	m_XSLFilename = AddBackslash(m_ConfigDir) + XSL_FILENAME;
	m_SearchProfilesFile = AddBackslash(m_ConfigDir) + SEARCH_PROFILES;
	m_DefPreviewXSL = AddBackslash(m_ConfigDir) + XSL_PREVIEW;
	m_DefCopyHTMLXSL = AddBackslash(m_ConfigDir) + XSL_COPYHTML;
	m_KeygenXSL = AddBackslash(m_ConfigDir) + XSL_KEYGEN;
	// Load exporter list now
	m_ExporterList->m_ListFile = AddBackslash(m_ConfigDir) + EXPORTER_FILE;
	m_ExporterList->Load(TRUE);
}

CString COptions::GetLangDir()
{
	return AddBackslash(GetAppPath()) + _T("lang");
}
