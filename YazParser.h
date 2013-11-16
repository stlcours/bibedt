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

  $Id: YazParser.h,v 1.7 2005/12/01 12:11:21 stievie Exp $
*/

// YazParser.h: Schnittstelle für die Klasse CYazParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZPARSER_H__12B45BBE_24C0_498F_AC28_27E649C99ECF__INCLUDED_)
#define AFX_YAZPARSER_H__12B45BBE_24C0_498F_AC28_27E649C99ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BeIconv.h"

class CYazParser  
{
public:
	virtual CString CharsetConv(CString str);
	virtual CString GetValue(CString name) = 0;
	CYazParser();
	virtual ~CYazParser();
	CString GetRawData() const { return m_RawData; }
	void SetRawData(CString data) { m_RawData = data; }
	virtual BOOL Parse() = 0;
	virtual CString GetType() = 0;
	CString m_SourceCharset;
	CString m_TargetCharset;

protected:
	CIconv m_Iconv;
	CString m_RawData;
};

#endif // !defined(AFX_YAZPARSER_H__12B45BBE_24C0_498F_AC28_27E649C99ECF__INCLUDED_)
