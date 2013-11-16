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

  $Id: YazMARCParser.cpp,v 1.2 2005/09/05 10:15:52 stievie Exp $
*/

// YazMARCParser.cpp: Implementierung der Klasse CYazMARCParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazMARCParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazMARCParser::CYazMARCParser()
{
	m_Document = NULL;
}

CYazMARCParser::~CYazMARCParser()
{
	if (m_Document != NULL)
		xmlFreeDoc(m_Document);
}

BOOL CYazMARCParser::Parse()
{
	if (m_RawData.IsEmpty())
		return FALSE;

	m_Document = xmlParseMemory(m_RawData, m_RawData.GetLength());
	return m_Document != NULL;
}

CString CYazMARCParser::GetValue(CString name)
{
	if (name.IsEmpty() || m_Document == NULL)
		return CString("");

	xmlNodePtr ptr;		   // Root node
	ptr = xmlDocGetRootElement(m_Document);

	return "";
}

CString CYazMARCParser::GetType()
{
	return "";
}
