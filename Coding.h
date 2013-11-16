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

  $Id: Coding.h,v 1.7 2006/06/06 18:52:18 stievie Exp $
*/

// Coding.h: Schnittstelle für die Klasse CCoding.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODING_H__FB47BBDF_5847_4796_8C31_C6FCDD5BBFFC__INCLUDED_)
#define AFX_CODING_H__FB47BBDF_5847_4796_8C31_C6FCDD5BBFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Globals.h"

/**
 * \brief The base class to do the en-/decoding from/to various needed formats.
 *
 * This is an abstract class, descendants must override the following methods;
 * - CCoding::Encode(CString src)
 *   Encode src and return it
 * - CCoding::Decode(CString src)
 *   Decode src and return it
 */
class CCoding  
{
public:
	void Clear();
	BOOL GetLoaded() { return m_Loaded; }
	CString m_Res;
	CString m_Filename;
	BOOL m_Enabled;
	void Load();
	virtual CString Encode(CString src) = 0;
	virtual CString Decode(CString src) = 0;
	CCoding();
	virtual ~CCoding();

protected:
	BOOL m_Loaded;
	TCHAR *m_EncodingTable[MAX_CHAR];
	TCHAR GetChar(CString str);
private:
	void AddCode(CString line);
	BOOL SaveRes(CString name);
};

#endif // !defined(AFX_CODING_H__FB47BBDF_5847_4796_8C31_C6FCDD5BBFFC__INCLUDED_)
