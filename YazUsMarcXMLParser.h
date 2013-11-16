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

  $Id: YazUsMarcXMLParser.h,v 1.2 2006/06/06 18:52:19 stievie Exp $
*/

// YazUsMarcXMLParser.h: Schnittstelle für die Klasse CYazUsMarcXMLParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZUSMARCXMLPARSER_H__962B2694_2255_4D2A_8CFB_4A52D0CA1EE1__INCLUDED_)
#define AFX_YAZUSMARCXMLPARSER_H__962B2694_2255_4D2A_8CFB_4A52D0CA1EE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "libxml/parser.h"
#include "YazAbstractXMLParser.h"

class CYazUsMarcXMLParser : public CYazAbstractXMLParser
{
public:
	virtual CString GetType();
	virtual CString GetValue(CString name);
	CYazUsMarcXMLParser();
	CYazUsMarcXMLParser(xmlDocPtr doc);
	virtual ~CYazUsMarcXMLParser();
private:
	static BOOL CheckField(xmlNodePtr node, CString tag, TCHAR ind1, TCHAR ind2);
	CString GetField(CString tag, TCHAR ind1, TCHAR ind2, CString code);
	xmlNodePtr GetControlField(CString name);
};

#endif // !defined(AFX_YAZUSMARCXMLPARSER_H__962B2694_2255_4D2A_8CFB_4A52D0CA1EE1__INCLUDED_)
