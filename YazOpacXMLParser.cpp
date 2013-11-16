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

  $Id: YazOpacXMLParser.cpp,v 1.3 2006/06/06 18:52:19 stievie Exp $
*/

// YazOpacXMLParser.cpp: Implementierung der Klasse CYazOpacXMLParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazOpacXMLParser.h"
#include "Field.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazOpacXMLParser::CYazOpacXMLParser()
{

}

CYazOpacXMLParser::CYazOpacXMLParser(xmlDocPtr doc)
{
	m_Document = doc;
}

CYazOpacXMLParser::~CYazOpacXMLParser()
{

}

CString CYazOpacXMLParser::GetType()
{
	CString t = GetField(_T("008"));
	if (t.IsEmpty())
		return _T("book");
	CString sub = t.Mid(24, 3);
	if (sub.FindOneOf(_T("agnos")) != -1)
		return _T("article");
	else if (sub.FindOneOf(_T("cdefhry")) != -1)
		return _T("book");
	else if (sub.FindOneOf(_T("ltpuvw")) != -1)
		return _T("techreport");
	else if (sub.FindOneOf(_T("m")) != -1)
		return _T("phdthesis");
	else if (sub.FindOneOf(_T("z")) != -1)
		return _T("unpublished");
	else if (sub.FindOneOf(_T("ijkq")) != -1)
		return _T("misc");

	return _T("book");
}

CString CYazOpacXMLParser::GetValue(CString name)
{
	if (name.IsEmpty() || m_Document == NULL)
		return CString("");

	CString str(_T(""));
	if (name.CompareNoCase(STR_AUTHOR) == 0) {
		str = GetField(_T("100"));
		if (str.IsEmpty())
			str = GetField(_T("700"));
	} else if (name.CompareNoCase(STR_TITLE) == 0) {
		str = GetField(_T("245"));
	} else if (name.CompareNoCase(STR_EDITION) == 0) {
		str = GetField(_T("250"));
	} else if (name.CompareNoCase(STR_SERIES) == 0) {
		str = GetField(_T("490"));
	} else if (name.CompareNoCase(STR_PUBLISHER) == 0) {
		str = GetField(_T("260"));
	} else if (name.CompareNoCase(STR_ADDRESS) == 0) {
		str = GetField(_T("490"));
	} else if (name.CompareNoCase(STR_YEAR) == 0) {
		str = GetField(_T("490"));
		int i = str.GetLength()-1;
		_TUCHAR c = str.GetAt(i--);
		while (_istdigit(c) || c == _T('-')) {
			c = str.GetAt(i--);
		}
		str = str.Mid(i);
	} else if (name.CompareNoCase(_T("ISBN")) == 0) {
		str = GetField(_T("020"));
	} else if (name.CompareNoCase(_T("Topic")) == 0) {
	} else if (name.CompareNoCase(_T("Contents")) == 0) {
	} else if (name.CompareNoCase(_T("Performer")) == 0) {
	}

	return str;
}

CString CYazOpacXMLParser::GetField(CString name)
{
	xmlNodePtr root;		   // Root node
	root = xmlDocGetRootElement(m_Document);
	// Find <datafield> with tag
	xmlNodePtr data = GetNode(root->children, name, XML_ELEMENT_NODE);
	xmlNodePtr val = data->children;
	if (val->type == XML_TEXT_NODE) {
		CString ret(val->content);
		if (ret.Right(1) == _T("."))
			ret.Delete(ret.GetLength()-1);
		return ret;
	} else
		return _T("");
}
