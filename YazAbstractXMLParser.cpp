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

  $Id: YazAbstractXMLParser.cpp,v 1.2 2005/09/09 10:33:39 stievie Exp $
*/

// YazAbstractXMLParser.cpp: Implementierung der Klasse CYazAbstractXMLParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazAbstractXMLParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazAbstractXMLParser::CYazAbstractXMLParser(xmlDocPtr doc)
{
	m_Document = doc;
}

CYazAbstractXMLParser::CYazAbstractXMLParser()
{
	m_Document = NULL;
}

CYazAbstractXMLParser::~CYazAbstractXMLParser()
{
}

xmlNodePtr CYazAbstractXMLParser::GetNode(xmlNodePtr node, CString name, xmlElementType type)
{
    xmlNode *cur_node = node;
	while (cur_node != NULL && (cur_node->type != type || name.CompareNoCase((const char*)cur_node->name) != 0))
		cur_node = cur_node->next;

	return cur_node;
}
