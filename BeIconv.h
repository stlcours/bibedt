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

  $Id: BeIconv.h,v 1.3 2005/12/01 12:58:23 stievie Exp $
*/

// Iconv.h: Schnittstelle für die Klasse CIconv.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICONV_H__BC32EBE2_49DC_40F7_85B9_B98C21F81A44__INCLUDED_)
#define AFX_ICONV_H__BC32EBE2_49DC_40F7_85B9_B98C21F81A44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iconv.h"
#include "yaz/yaz-iconv.h"
#include "CodingTeX.h"
#include "CodingRTF.h"
#include "CodingHTML.h"

class CIconv  
{
public:
	void SetTargetCharset(CString value);
	void SetSourceCharset(CString value);
	CString Convert(CString str);
	CString GetSourceCharset() { return m_SourceCharset; }
	CString GetTargetCharset() { return m_TargetCharset; }
	void List(CStringList* lst);
	CIconv();
	virtual ~CIconv();

private:
	void LoadTeX();
	void LoadHTML();
	void LoadRTF();
	static int print_one(unsigned int namescount, const char * const * names, void* data);
protected:
	CCodingHTML m_CodingHTML;
	CCodingRTF m_CodingRTF;
	CCodingTeX m_CodingTeX;
	CString ConvertTeX(CString str);
	CString ConvertRTF(CString str);
	CString ConvertHTML(CString str);
	CString ConvertIconv(CString str);
	CString m_TargetCharset;
	CString m_SourceCharset;
	yaz_iconv_t m_hIconv;
};

#endif // !defined(AFX_ICONV_H__BC32EBE2_49DC_40F7_85B9_B98C21F81A44__INCLUDED_)
