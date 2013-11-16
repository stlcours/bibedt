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

  $Id: YazXMLParser.h,v 1.6 2005/09/09 10:33:39 stievie Exp $
*/

// YazXMLParser.h: Schnittstelle für die Klasse CYazXMLParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZXMLPARSER_H__3B3EE575_E36D_4743_99C7_DB686B768C6B__INCLUDED_)
#define AFX_YAZXMLPARSER_H__3B3EE575_E36D_4743_99C7_DB686B768C6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazParser.h"
#include "libxml/parser.h"
#include "YazAbstractXMLParser.h"

class CYazXMLParser : public CYazParser  
{
public:
	virtual CString GetType();
	virtual CString GetValue(CString name);
	virtual BOOL Parse();
	CYazXMLParser();
	virtual ~CYazXMLParser();

protected:
	CYazAbstractXMLParser* m_Parser;
	xmlDocPtr m_Document;
};

#endif // !defined(AFX_YAZXMLPARSER_H__3B3EE575_E36D_4743_99C7_DB686B768C6B__INCLUDED_)
