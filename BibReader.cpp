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

  $Id: BibReader.cpp,v 1.5 2006/06/06 18:52:18 stievie Exp $
*/

/* Buffered file reader, didn't find something suitable in MFC. 
   Maybe it's just me and I should read the docs... 
*/

// BibReader.cpp: Implementierung der Klasse CBibReader.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "BibReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibReader::CBibReader(CFile *file)
{
	// Read from a file
	m_Buffer = NULL;
	m_Position = -1;
	try	{
		m_Length = file->GetLength();
		m_Buffer = new TCHAR[m_Length];
		file->Read(m_Buffer, m_Length);
		m_Position = 0;
	} catch (CFileException ex) {
		throw;
	}
}

CBibReader::CBibReader(CString src)
{
	// Read from string
	m_Length = src.GetLength();
	m_Buffer = new TCHAR[m_Length];
	memcpy(m_Buffer, src, m_Length);
	m_Position = 0;
}

CBibReader::~CBibReader()
{
	if (m_Buffer != NULL)
		delete [] m_Buffer;
}

UINT CBibReader::Read(void* lpBuf, UINT nCount)
{
	ASSERT(lpBuf != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nCount));
	DWORD dwRead;
	if (m_Position + nCount < m_Length)
		dwRead = nCount;
	else
		dwRead = m_Length - m_Position;

	memcpy(lpBuf, m_Buffer + m_Position, dwRead);
	m_Position += dwRead;
	return dwRead;
}

LONG CBibReader::Seek(LONG lOff, UINT nFrom)
{
	switch (nFrom) {
	case CFile::begin:
		if (lOff > 0 && lOff < (signed int)m_Length)
			m_Position = lOff;
		else if (lOff < 0)
			m_Position = 0;
		else
			m_Position = m_Length-1;
		break;
	case CFile::current:
		if (m_Position + lOff < m_Length)
			m_Position += lOff;
		else if (lOff < 0)
			m_Position = 0;
		else
			m_Position  = m_Length-1;
		break;
	case CFile::end:
		if (m_Position - lOff > 0)
			m_Position -= lOff;
		else if (lOff < 0)
			m_Position = m_Length-1;
		else
			m_Position  = 0;
		break;
	}
	return m_Position;
}

TCHAR CBibReader::GetAt(UINT pos) const
{
	if (pos < m_Length && pos > 0)
		return m_Buffer[pos];
	else
		return 0;
}
