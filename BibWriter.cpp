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

  $Id: BibWriter.cpp,v 1.8 2006/07/29 11:33:14 stievie Exp $
*/

// BibWriter.cpp: Implementierung der Klasse CBibWriter.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Globals.h"
#include "BibWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBibWriter::CBibWriter(CFile *file)
{
	m_File = file;
	m_Written = 0;
}

CBibWriter::~CBibWriter()
{
	// Flush everything not yet written
	Flush();
}

void CBibWriter::Write(LPCTSTR str)
{
	int l = _tcslen(str);

	if (l < BUFFER_SIZE) {
		if (m_Written + l > BUFFER_SIZE)
			// Would exceed buffer -> write it to file
			Flush();
		memcpy(m_Buffer + m_Written, str, l);
		m_Written += l;
	} else {
		// Write directly to file
		Flush();
		m_File->Write(str, l);
	}
}

void CBibWriter::WriteLn(LPCTSTR str)
{
	Write(str);
	Write(NL);
}

void CBibWriter::Flush()
{
	if (m_Written) {
		m_File->Write(m_Buffer, m_Written);
		m_Written = 0;
	}
}
