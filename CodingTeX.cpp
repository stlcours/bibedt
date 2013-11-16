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

  $Id: CodingTeX.cpp,v 1.14 2006/06/06 18:52:18 stievie Exp $
*/

// CodingTeX.cpp: Implementierung der Klasse CCodingTeX.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "CodingTeX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCodingTeX::CCodingTeX()
{

}

CCodingTeX::~CCodingTeX()
{

}

/**
 * Translate non-ASCII characters into TeX escape sequences.
 */
CString CCodingTeX::Encode(CString src)
{
	if (!m_Enabled)
		return src;
	CString res;
	CString str;
	_TUCHAR c;
	for (int i = 0; i < src.GetLength(); i++) {
		c = src.GetAt(i);
		if (!m_EncodingTable[c]) {
			res += c;
		} else {
			str.Format(_T("{%s}"), m_EncodingTable[c]);
			res += str;
		}
	}
	return res;
}

/**
 * Translate TeX escape sequences into non-ASCII characters.
 * The escape sequences must be enclosed in curly brackets {}.
 */
CString CCodingTeX::Decode(CString src)
{
	if (!m_Enabled)
		return src;
	_TUCHAR e = 0;
	int p = -1;
	UINT brack = 0;
	CString str;
	CString res;
	CString tmp;

// 871 ms
	LPCTSTR lpSrc = src;
	int length = src.GetLength();
	int i = 0;
	while (i < length) {
		switch (lpSrc[i]) {
		case _T('{'):
			// could be something like {\c{c}} for ç
			brack++;
			str += lpSrc[i];
			break;
		case _T('}'):
			if (brack)
				brack--;
			str += lpSrc[i];
			if (str.GetAt(0) == _T('{'))	{
				tmp = str.Mid(1, str.GetLength() - 2);
				e = GetChar(tmp);
				if (e) {
					res += e;
					str.Empty();
				} else if (!brack) {
					res += str;
					str.Empty();
				}
			}
			break;
		default:
			if (!brack)
				res += lpSrc[i];
			else
				str += lpSrc[i];
		}
		i++;
	}
//*/

	return res;
}

CString CCodingTeX::GetString(UCHAR c)
{
	CString ret;
	if (m_EncodingTable[c] != NULL)
		ret.Format(_T("{%s}"), m_EncodingTable[c]);
	return ret;		
}
