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

  $Id: Options.h,v 1.36 2006/08/12 16:06:17 stievie Exp $
*/

// Options.h: Schnittstelle für die Klasse COptions.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONS_H__0A2DE8E0_1DD0_4D82_98C6_14B0402168A8__INCLUDED_)
#define AFX_OPTIONS_H__0A2DE8E0_1DD0_4D82_98C6_14B0402168A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListViewPrint.h"
#include "ExporterList.h"

// The manual
static const TCHAR BIBEDT_MANUAL[] = _T("bibedt.pdf");
static const TCHAR CHANGELOG_FILE[] = _T("changelog.txt");

// Registry key for settings
static const TCHAR SETTINGS_KEY[] = _T("Settings");
// Default Template file
static const TCHAR DEF_BIB_FILE[] = _T("config.bib");
// Encoding files
static const TCHAR CODING_TEX[]   = _T("enc_tex.txt");
static const TCHAR CODING_HTML[]  = _T("enc_html.txt");
static const TCHAR CODING_RTF[]   = _T("enc_rtf.txt");
static const TCHAR CODING_XML[]   = _T("enc_xml.txt");
static const TCHAR XSL_FILENAME[] = _T("plain.xsl");
static const TCHAR SEARCH_PROFILES[] = _T("profiles.xml");
static const TCHAR XSL_PREVIEW[] = _T("preview.xsl");
static const TCHAR XSL_COPYHTML[] = _T("copyhtml.xsl");
static const TCHAR EXPORTER_FILE[] = _T("exporter.xml");
static const TCHAR XSL_KEYGEN[]  = _T("keygen.xsl");

static const TCHAR DEF_DOI_URL[] = _T("http://dx.doi.org/");

/**
 * \brief Options class
 *
 * Class to read write program options and settings.
 */
class COptions  
{
public:
	static CString GetLangDir();
	void UpdateFiles();
	CString m_ConfigDir;
	static CString FindFile(CString name);
	static CString RemoveBackslash(CString str);
	static CString AddBackslash(CString str);
	HWND GetEditorWindow();
	CExporterList* m_ExporterList;
	CString m_XSLFilename;
	CString ResolveDOI(CString doi);
	CString m_DOIURL;
	CString m_EditorClassName;
	CString m_EditorParentClass;
	CString m_SearchProfilesFile;
	BOOL m_AutoCompleteValues;
	BOOL m_ScrollToSelected;
	BOOL m_ReplaceSpecialChar;
	BOOL m_DisableSave;
	CString m_QuickSearchFields;
	BOOL m_OpenLastFile;
	void WriteWindowPlacement(CString key, WINDOWPLACEMENT val);
	void ReadWindowPlacement(CString key, WINDOWPLACEMENT* res);
	static CString GetChangelogFile();
	static CString GetManualFile();
	Units m_PrintUnits;
	int m_MarginBottom;
	int m_MarginRight;
	int m_MarginLeft;
	int m_MarginTop;
	void SetColWidth(int index, int width);
	void SetColName(int index, CString name);
	int GetColWidth(int index, int def);
	CString GetColName(int index, CString def);
	int m_ColCount;
	BOOL m_SortOnSave;
	CString m_EncodingTeX;
	CString m_EncodingHTML;
	CString m_EncodingRTF;
	CString m_EncodingXML;
	CString m_DefPreviewXSL;
	CString m_DefCopyHTMLXSL;
	CString m_KeygenXSL;
	CString m_FontProp;
	CString m_FontMono;
	CString m_FontSans;
	BOOL m_ShowCiteDlg;
	CString m_CiteFormat;
	UINT m_LineLength;
	static CString GetTempFilename(CString name);
	static CString GetExeName();
	static CString GetAppPath();
	CString m_TemplateFile;
	WINDOWPLACEMENT m_WindowPlacement;
	BOOL m_GridLines;
	BOOL m_TranslateASCII;
	BOOL m_Backup;
	BOOL m_SortCaseSensitive;
	void Save();
	void Load();
	COptions();
	virtual ~COptions();
private:
	HWND m_EditorWnd;
	static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
};

#endif // !defined(AFX_OPTIONS_H__0A2DE8E0_1DD0_4D82_98C6_14B0402168A8__INCLUDED_)
