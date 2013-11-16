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

  $Id: Coding.cpp,v 1.8 2006/06/06 18:52:18 stievie Exp $
*/

// Coding.cpp: Implementierung der Klasse CCoding.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Coding.h"
#include "Options.h"
#include "bibedt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCoding::CCoding()
{
	for (int i = 0; i < MAX_CHAR; i++) {
		m_EncodingTable[i] = _T('\0');
	}
	m_Loaded = FALSE;
}

CCoding::~CCoding()
{
	Clear();
}

/**
 * If the coding file does not exits extract the resource and save it.
 */
BOOL CCoding::SaveRes(CString name)
{
	HRSRC hr = FindResource(NULL, m_Res, _T("ENCODING"));
	if (hr == NULL)
		return FALSE;
	HGLOBAL hres = LoadResource(NULL, hr);
	if (hres == NULL)
		return FALSE;
	LPVOID lpres = LockResource(hres);
	if (lpres == NULL)
		return FALSE;
	CString strres((LPSTR)lpres);
	try {
		CFile f;
		f.Open(name, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
		f.Write(strres, strres.GetLength());
		f.Close();
		return TRUE;
	} catch (...) {
		return FALSE;
	}
}

/**
 * Translate the entity to the corresponding char
 */
TCHAR CCoding::GetChar(CString str)
{
	for (int i = 0; i < 256; i++) {
		if (m_EncodingTable[i] != NULL && str.Compare(m_EncodingTable[i]) == 0) {
			return i;
		}
	}
	return 0;
}

/**
 * Load the coding file
 */
void CCoding::Load()
{
	Clear();
	CFileFind finder;
	if (finder.FindFile(m_Filename)) {
		finder.Close();
	} else {
		if (!SaveRes(m_Filename)) {
			ShowError(_T("Can't find encoding file \"") + m_Filename + _T("\""));
			return;
		}
	}

	CFileException ex;
	CFile f;
	if (f.Open(m_Filename, CFile::modeRead | CFile::shareDenyWrite, &ex)) {
		char c;
		CString line;
		while (f.Read(&c, 1)) {
			switch (c) {
			case 10:
				break;
			case 13:
				if (!line.IsEmpty()) {
					AddCode(line);
					line.Empty();
				}
				break;
			default:
				line += c;
			}
		}
		f.Close();
		if (!line.IsEmpty()) {
			AddCode(line);
		}
	} else
		ex.ReportError();

	m_Loaded = TRUE;
}

/**
 * Clears the encoding table
 */
void CCoding::Clear()
{
	if (!m_Loaded)
		return;
	for (int i = 0; i < MAX_CHAR; i++) {
		if (m_EncodingTable[i])
			free(m_EncodingTable[i]);
		m_EncodingTable[i] = NULL;
	}
	m_Loaded = FALSE;
}

/**
 * Adds a coding item to the coding table
 */
void CCoding::AddCode(CString line)
{
	_TUCHAR c2 = line[0];
	line = line.Right(line.GetLength() - 2);
	m_EncodingTable[c2] = (TCHAR*)malloc((size_t)line.GetLength()+1);
	_tcscpy(m_EncodingTable[c2], line);
}
