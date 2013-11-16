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

  $Id: Language.h,v 1.3 2006/06/04 11:09:42 stievie Exp $
*/

// Language.h: Schnittstelle für die Klasse CLanguage.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__58816B83_64A0_4F5D_AC1E_1CA74EC740EA__INCLUDED_)
#define AFX_LANGUAGE_H__58816B83_64A0_4F5D_AC1E_1CA74EC740EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _LANG_INFO {
	CString path;
	HINSTANCE hInstance;
	CString name;
} LANG_INFO;

class CLanguage  
{
public:
	LANG_INFO GetNext(POSITION &p);
	POSITION GetHeadPosition();
	LANG_INFO GetAt(POSITION p);
	POSITION SetCurLang(CString filename);
	static CString GetResLang(CString file);
	void LoadLanguages();
	POSITION Find(CString path);
	POSITION SetCurLang(LANG_INFO pLang);
	POSITION SetCurLang(DWORD nLang);
	CLanguage();
	virtual ~CLanguage();
	POSITION GetCurLang() { return m_CurLang; }
private:
	POSITION m_CurLang;
	CList <LANG_INFO, LANG_INFO&> m_Languages;

};

#endif // !defined(AFX_LANGUAGE_H__58816B83_64A0_4F5D_AC1E_1CA74EC740EA__INCLUDED_)
