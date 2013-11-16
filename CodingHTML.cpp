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

  $Id: CodingHTML.cpp,v 1.5 2006/06/06 18:52:18 stievie Exp $
*/

// CodingHTML.cpp: Implementierung der Klasse CCodingHTML.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "CodingHTML.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCodingHTML::CCodingHTML()
{

}

CCodingHTML::~CCodingHTML()
{

}

/**
 * Translate non-ASCII charachter to HTML entities.
 */
CString CCodingHTML::Encode(CString src)
{
	if (!m_Enabled)
		return src;
	CString res;
	_TUCHAR c;
	for (int i = 0; i < src.GetLength(); i++) {
		c = src.GetAt(i);
		if (!m_EncodingTable[c]) {
			res += c;
		} else {
			res += m_EncodingTable[c];
		}
	}
	return res;
}

/**
 * Decode src.
 * This method is not implemented -- it just returns src
 * unmodified --, becaue it's not needed but must be overridden.
 */
CString CCodingHTML::Decode(CString src)
{
	NOT_IMPL;
	CString res = src;
	return res;
}
