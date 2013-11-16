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

  $Id: YazXMLParser.cpp,v 1.11 2006/06/06 18:52:19 stievie Exp $
*/

// YazXMLParser.cpp: Implementierung der Klasse CYazXMLParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazXMLParser.h"
#include "libxml/xpath.h"
#include "Field.h"
#include "YazUsMarcXMLParser.h"
#include "YazOpacXMLParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazXMLParser::CYazXMLParser()
{
	m_Document = NULL;
	m_Parser = NULL;
	m_TargetCharset = _T("ISO88591");
//	m_SourceCharset = "MARC8";
	m_SourceCharset = _T("UTF8");
}

CYazXMLParser::~CYazXMLParser()
{
	if (m_Document != NULL)
		xmlFreeDoc(m_Document);
	if (m_Parser != NULL)
		delete m_Parser;
}

BOOL CYazXMLParser::Parse()
{
	if (m_RawData.IsEmpty())
		return FALSE;

	m_Document = xmlParseMemory(m_RawData, m_RawData.GetLength());
	if (m_Document != NULL) {
		xmlNodePtr root = xmlDocGetRootElement(m_Document);
		if (strstr(m_RawData, "MARC21") != NULL)
			// MARC21
			m_Parser = new CYazUsMarcXMLParser(m_Document);
		else if (stricmp((const char*)root->name, "HEAD") == 0) {
			// OPAC
			// BUG: libxml can't parse the output because the tag names are not valid!!!
			m_Parser = new CYazOpacXMLParser(m_Document);
		}
		// No more parser implemented!!!
	} else {
#ifdef _DEBUG
		// XML parsing error
		xmlErrorPtr err = xmlGetLastError();
		AfxTrace(_T("XML error (ln %d, col %d): (%d) %s"), err->line, err->int2, err->code, err->message);
#endif
	}
	
	return m_Document != NULL;
}

CString CYazXMLParser::GetValue(CString name)
{
	if (m_Parser != NULL) {
		CString val = m_Parser->GetValue(name);
		return CharsetConv(val);
	} else
		return _T("");
}

CString CYazXMLParser::GetType()
{
	if (m_Parser != NULL) {
		return m_Parser->GetType();
	} else
		return _T("");
}
