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

  $Id: YazOpacXMLParser.h,v 1.2 2005/09/06 15:31:43 stievie Exp $
*/

// YazOpacXMLParser.h: Schnittstelle für die Klasse CYazOpacXMLParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZOPACXMLPARSER_H__7FFFA91F_501E_4020_8A1B_D06CD45A8D3A__INCLUDED_)
#define AFX_YAZOPACXMLPARSER_H__7FFFA91F_501E_4020_8A1B_D06CD45A8D3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazAbstractXMLParser.h"

class CYazOpacXMLParser : public CYazAbstractXMLParser  
{
public:
	virtual CString GetType();
	virtual CString GetValue(CString name);
	CYazOpacXMLParser();
	CYazOpacXMLParser(xmlDocPtr doc);
	virtual ~CYazOpacXMLParser();

private:
	CString GetField(CString name);
};

#endif // !defined(AFX_YAZOPACXMLPARSER_H__7FFFA91F_501E_4020_8A1B_D06CD45A8D3A__INCLUDED_)
