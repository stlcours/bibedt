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

  $Id: YazRecord.h,v 1.6 2005/09/09 10:33:39 stievie Exp $
*/

// YazRecord.h: Schnittstelle für die Klasse CYazRecord.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZRECORD_H__3C1ED295_8C13_480F_B2A5_4AF81150F8B0__INCLUDED_)
#define AFX_YAZRECORD_H__3C1ED295_8C13_480F_B2A5_4AF81150F8B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "yaz/zoom.h"
#include "Yaz.h"
#include "YazParser.h"

class CYazRecord  
{
public:
	CString GetValue(CString name);
	YC_SYNTAX GetSyntax();
	CString GetRecord(CString what);
	CString GetRaw();
	CString GetRender();
	CYazRecord(ZOOM_record rec);
	virtual ~CYazRecord();
	CString GetType() const { return m_Type; }

protected:
	CString m_Render;
	CYazParser* m_Parser;
	ZOOM_record m_hRecord;
	CString m_Type;
	CString m_Raw;
};

#endif // !defined(AFX_YAZRECORD_H__3C1ED295_8C13_480F_B2A5_4AF81150F8B0__INCLUDED_)
