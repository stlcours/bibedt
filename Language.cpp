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

  $Id: Language.cpp,v 1.5 2006/07/30 17:44:57 stievie Exp $
*/

// Language.cpp: Implementierung der Klasse CLanguage.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "Language.h"
#include "Options.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CLanguage::CLanguage()
{
	m_CurLang = NULL;
}

CLanguage::~CLanguage()
{
	POSITION p = m_Languages.GetHeadPosition();
	while (p) {
		LANG_INFO li = m_Languages.GetNext(p);
		if (li.hInstance != NULL && li.hInstance != AfxGetInstanceHandle())
			FreeLibrary(li.hInstance);
	}
}

POSITION CLanguage::SetCurLang(DWORD nLang)
{
	POSITION p = m_Languages.FindIndex(nLang);
	if (p != NULL) {
		LANG_INFO lang = m_Languages.GetAt(p);
		return SetCurLang(lang);
	} else {
		ShowError(IDS_ERR_NOSUCHLANGUAGE);
		return m_CurLang;
	}
}

POSITION CLanguage::SetCurLang(LANG_INFO Lang)
{
	POSITION prlang = m_CurLang;
	if (Lang.hInstance == NULL) {
		Lang.hInstance = ::LoadLibrary(Lang.path);
		if (Lang.hInstance == NULL) {
			ShowError(IDS_ERR_LOADINGLANGLIB);
			return m_CurLang;
		}
	}
	AfxSetResourceHandle(Lang.hInstance);
	m_CurLang = Find(Lang.path);
	if (AfxGetMainWnd() != NULL && ::IsWindow(AfxGetMainWnd()->m_hWnd))
		AfxGetMainWnd()->SendMessage(WM_BE_LANUAGE_CHANGED, 0, 0);
	return prlang;
}

POSITION CLanguage::Find(CString path)
{
	if (path.IsEmpty())
		return m_Languages.GetHeadPosition();

	POSITION p = m_Languages.GetHeadPosition();
	POSITION prev;
	while (p) {
		prev = p;
		if (path.CompareNoCase(m_Languages.GetNext(p).path) == 0) {
			return prev;
		}
	}
	return NULL;
}

void CLanguage::LoadLanguages()
{
	LANG_INFO native;
	native.hInstance = AfxGetInstanceHandle();
	native.name = _T("English");
	native.path = _T("");
	m_Languages.AddTail(native);

	CString ld = COptions::AddBackslash(COptions::GetLangDir()) + _T("*.dll");
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(ld, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if (CAboutDlg::GetVersionString(COptions::GetExeName(), 
				_T("ProductVersion")).Compare(CAboutDlg::GetVersionString(COptions::AddBackslash(COptions::GetLangDir()) + fd.cFileName,
				_T("ProductVersion"))) == 0) {
				LANG_INFO li;
				li.hInstance = NULL;
				li.path = COptions::AddBackslash(COptions::GetLangDir()) + fd.cFileName;
				li.name = CAboutDlg::GetVersionString(li.path, _T("Comments"));
				m_Languages.AddTail(li);
			}
		} while (FindNextFile(hFind, &fd) != 0);

		FindClose(hFind);
	}
	m_CurLang = m_Languages.GetHeadPosition();
}

POSITION CLanguage::SetCurLang(CString filename)
{
	POSITION p = Find(filename);
	if (p && p != m_CurLang) {
		return SetCurLang(m_Languages.GetAt(p));
	}
	return m_CurLang;
}

LANG_INFO CLanguage::GetAt(POSITION p)
{
	ASSERT(p);
	return m_Languages.GetAt(p);		 
}

POSITION CLanguage::GetHeadPosition()
{
	return m_Languages.GetHeadPosition();
}

LANG_INFO CLanguage::GetNext(POSITION &p)
{
	return m_Languages.GetNext(p);
}
