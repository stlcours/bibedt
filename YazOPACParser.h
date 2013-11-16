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

  $Id: YazOPACParser.h,v 1.2 2005/09/05 10:15:52 stievie Exp $
*/

// YazOPACParser.h: Schnittstelle für die Klasse CYazOPACParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZOPACPARSER_H__6589F5CD_F524_4485_B1D2_B694CE04A4BA__INCLUDED_)
#define AFX_YAZOPACPARSER_H__6589F5CD_F524_4485_B1D2_B694CE04A4BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazParser.h"

class CYazOPACParser : public CYazParser  
{
public:
	virtual CString GetType();
	virtual CString GetValue(CString name);
	virtual BOOL Parse();
	CYazOPACParser();
	virtual ~CYazOPACParser();

};

#endif // !defined(AFX_YAZOPACPARSER_H__6589F5CD_F524_4485_B1D2_B694CE04A4BA__INCLUDED_)
