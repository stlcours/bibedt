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

  $Id: BibFile.cpp,v 1.10 2005/08/22 23:32:33 stievie Exp $
*/

// BibFile.cpp: Implementierung der Klasse CBibFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BibFile.h"
#include "BibEdtList.h"
#include "BibReader.h"
#include "BibWriter.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibFile::CBibFile()
{
	m_Modified = FALSE;
	m_Backup = TRUE;
}

CBibFile::~CBibFile()
{
}

void CBibFile::NewFile()
{
	Clear();
	m_Filename.Empty();
	SetModified(FALSE);
}

BOOL CBibFile::Load(CFile* file)
{
	try {
		Clear();
		CBibReader *reader = new CBibReader(file);
		CBibList::Parse(reader);
		delete reader;
		SetModified(FALSE);
		return TRUE;
	} catch (CException e) {
		e.ReportError();
		return FALSE;
	}
}

BOOL CBibFile::Save(CFile* file)
{
	if (GetCount()) {
		Backup();
		CFileException ex;
		try {
#ifdef _DEBUG
			DWORD start = GetTickCount();
#endif
			CBibWriter *writer = new CBibWriter(file);
			POSITION h = GetHeadPosition();
			while (h) {
				CBibItem* bi = (CBibItem*)GetNext(h);
				ASSERT(bi);
				bi->SaveToFile(writer);
			}

			SetModified(FALSE);
			delete writer;
#ifdef _DEBUG
			TRACE1("CBibFile::Save(): Took %d ms\n", GetTickCount() - start);
#endif
			return TRUE;
		} catch (CFileException e) {
			e.ReportError();
			return FALSE;
		}
	}
	return TRUE;
}

void CBibFile::Backup()
{
	if (m_Backup && !m_Filename.IsEmpty())
		BackupFile(m_Filename);
}

BOOL CBibFile::GetCanSave()
{
	return (GetModified() || (m_Filename.IsEmpty() && GetCount() > 0));
}

BOOL CBibFile::GetCanSaveAs() const
{
	return (GetCount() > 0);
}
