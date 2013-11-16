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

  $Id: FileWatch.cpp,v 1.3 2006/05/20 14:37:38 stievie Exp $
*/

// FileWatch.cpp: Implementierung der Klasse CFileWatch.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "FileWatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CFileWatch::CFileWatch()
{
	m_LastModified = 0;
	m_dwUpdateCount = 0;
}

CFileWatch::~CFileWatch()
{

}

void CFileWatch::SetFileName(CString fn)
{
	if (m_FileName.CompareNoCase(fn) != 0) {
		m_FileName = fn;
	}
	if (!m_FileName.IsEmpty())
		Update();
	else
		m_LastModified = 0;
}

void CFileWatch::Update()
{
	CFileFind ff;
	if (!ff.FindFile(m_FileName)) {
		m_LastModified = 0;
		return;
	}
	ff.FindNextFile();
	ff.GetLastWriteTime(m_LastModified);
	ff.Close();
}

FILECHANGE CFileWatch::GetModified()
{
	if (m_dwUpdateCount > 0)
		return FC_NONE;
	CTime newmod;
	CFileFind ff;
	if (!ff.FindFile(m_FileName)) {
		if (m_LastModified != 0) {
			// File has been deleted
			m_LastModified = 0;
			return FC_DELETE;
		} else
			return FC_NONE;
	}
	ff.FindNextFile();
	ff.GetLastWriteTime(newmod);
	ff.Close();
	if (newmod != m_LastModified) {
		m_LastModified = newmod;
		return FC_DATE;
	} else
		return FC_NONE;
}