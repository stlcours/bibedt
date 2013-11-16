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

  $Id: YazUsMarcXMLParser.cpp,v 1.6 2006/06/06 18:52:19 stievie Exp $
*/

// YazUsMarcXMLParser.cpp: Implementierung der Klasse CYazUsMarcXMLParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazUsMarcXMLParser.h"
#include "Field.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazUsMarcXMLParser::CYazUsMarcXMLParser()
{
}

CYazUsMarcXMLParser::CYazUsMarcXMLParser(xmlDocPtr doc)
{
	m_Document = doc;
}

CYazUsMarcXMLParser::~CYazUsMarcXMLParser()
{

}

CString CYazUsMarcXMLParser::GetValue(CString name)
{
	if (name.IsEmpty() || m_Document == NULL)
		return _T("");

	CString str(_T(""));
	CString str2;
	if (name.CompareNoCase(STR_AUTHOR) == 0) {
		str = GetField(_T("100"), _T(' '), _T(' '), _T("a"));
		if (str.IsEmpty()) {
			// Try another field
			str = GetField(_T("700"), _T('1'), _T(' '), _T("a"));
		}
		// Remove trailing comma, if any
		if (!str.IsEmpty() && str.GetAt(str.GetLength()-1) == ',')
			str.Delete(str.GetLength()-1);
		// If the last name is first than swap the names
		int i = str.Find(" ", 0);
		if (i != -1) {
			// If there is a space inside the string ...
			if (str.GetAt(i-1) == ',' && str.Find(",", i+1) == -1 && str.Find(" and ", i+1) == -1) {
				// ... and a comma before, but no more commas,
				// only then we change the value. Otherwise there are probably
				// more authors and we can't know how this is formated.
				str2 = str.Left(i-1);
				str.Delete(0, i+1);				
				str += " " + str2;
			}
		}
	} else if (name.CompareNoCase(STR_TITLE) == 0) {
		str = GetField("245", '0', '0', "a");
		// Remove trailing trash, if any
		if (!str.IsEmpty())
			str.TrimRight(" \t/:;,");
		str2 = GetField("245", '0', '0', "b");
		if (!str2.IsEmpty()) {
			str2.TrimRight(" \t/:;,");
			str += " " + str2;
		}
	} else if (name.CompareNoCase(STR_EDITION) == 0) {
		str = GetField("250", ' ', ' ', "a");
	} else if (name.CompareNoCase(STR_SERIES) == 0) {
		str = GetField("490", ' ', ' ', "a");
	} else if (name.CompareNoCase(STR_PUBLISHER) == 0) {
		str = GetField("260", ' ', ' ', "b");
		if (str.IsEmpty())
			str = GetField("028", ' ', ' ', "b");
	} else if (name.CompareNoCase(STR_ADDRESS) == 0)
		str = GetField("260", ' ', ' ', "a");
	else if (name.CompareNoCase(STR_YEAR) == 0) {
		str = GetField("260", ' ', ' ', "c");
		str.TrimLeft(" \tc[");
		str.TrimRight(" \t]-");
	} else if (name.CompareNoCase("ISBN") == 0)
		str = GetField("020", ' ', ' ', "a");
	else if (name.CompareNoCase("Topic") == 0)
		str = GetField("650", ' ', '0', "a");
	else if (name.CompareNoCase("Contents") == 0)
		str = GetField("511", '1', ' ', "a");
	else if (name.CompareNoCase("Performer") == 0)
		str = GetField("511", '0', ' ', "a");

	if (!str.IsEmpty()) { 	 
		str.TrimRight(" \t/:;,");
	}
	return str;
}

/**
  008--BOOKS
   Character Positions
      24-27 - Nature of contents
         # - No specified nature of contents
         a - Abstracts/summaries							-> article
         b - Bibliographies
         c - Catalogs										-> book
         d - Dictionaries									-> book
         e - Encyclopedias									-> book
         f - Handbooks										-> book
         g - Legal articles									-> article
         h - Handbooks [OBSOLETE]							-> book
         i - Indexes										-> misc
         j - Patent document								-> misc
         k - Discographies									-> misc
         l - Legislation									-> techreport
         m - Theses											-> phdthesis
         n - Surveys of literature in a subject area		-> article
         o - Reviews										-> article
         p - Programmed texts								-> techreport
         q - Filmographies									-> misc
         r - Directories									-> book
         s - Statistics										-> article
         t - Technical reports								-> techreport
         u - Standards/specifications						-> techreport
         v - Legal cases and case notes						-> techreport
         w - Law reports and digests						-> techreport
         y - Yearbooks [OBSOLETE]							-> book
         z - Treaties										-> unpublished
         | - No attempt to code
*/
CString CYazUsMarcXMLParser::GetType()
{
	if (m_Document == NULL)
		return CString("");

	// By default a book
	CString res("book");

	xmlNodePtr control = GetControlField("008");
	if (control == NULL)
		return res;
	control = control->children;
	if (control == NULL || control->type != XML_TEXT_NODE)
		return res;
	CString data = control->content;
	
	if (data.IsEmpty())
		return res;

	CString sub = data.Mid(24, 3);
	if (sub.FindOneOf("agnos") != -1)
		return CString("article");
	else if (sub.FindOneOf("cdefhry") != -1)
		return CString("book");
	else if (sub.FindOneOf("ltpuvw") != -1)
		return CString("techreport");
	else if (sub.FindOneOf("m") != -1)
		return CString("phdthesis");
	else if (sub.FindOneOf("z") != -1)
		return CString("unpublished");
	else if (sub.FindOneOf("ijkq") != -1)
		return CString("misc");

	return res;
}

xmlNodePtr CYazUsMarcXMLParser::GetControlField(CString name)
{
	if (name.IsEmpty() || m_Document == NULL)
		return NULL;

	xmlNodePtr root;		   // Root node
	root = xmlDocGetRootElement(m_Document);
	// Find <controlfield> with tag
	xmlNodePtr data = GetNode(root->children, "controlfield", XML_ELEMENT_NODE);
	while (data != NULL && stricmp((const char*)xmlGetProp(data, (xmlChar*)&"tag"), name) != 0)
		data = GetNode(data->next, "controlfield", XML_ELEMENT_NODE);
	return data;
}

/**
 * Return the value from  a tag like:
 *
  <datafield tag="035" ind1=" " ind2=" ">
    <subfield code="9">(DLC)   97023698</subfield>
  </datafield>
 *
 * GetField("035", ' ', ' ', "9") should return (DLC)   97023698
 */

/**
 * For MARC21 (USMARC) interesting fields are:
 *   ISBN: 20 $a
 *   Author: 100 $a
 *   Title: 245 $a
 *   Publisher: 260 $a -> Address; $b -> Name; $c -> Date
 */
CString CYazUsMarcXMLParser::GetField(CString tag, TCHAR ind1, TCHAR ind2, CString code)
{
	xmlNodePtr root;		   // Root node
	root = xmlDocGetRootElement(m_Document);
	// Find <datafield> with tag
	xmlNodePtr data = GetNode(root->children, "datafield", XML_ELEMENT_NODE);
	while (data != NULL && !CheckField(data, tag, ind1, ind2))
		data = GetNode(data->next, "datafield", XML_ELEMENT_NODE);
	if (data == NULL)
		return "";
	// Find <subfield> with code
	xmlNodePtr sub = GetNode(data->children, "subfield", XML_ELEMENT_NODE);
	while (sub != NULL && stricmp((const char*)xmlGetProp(sub, (xmlChar*)&"code"), code) != 0)
		sub = GetNode(sub->next, "subfield", XML_ELEMENT_NODE);
	if (sub == NULL)
		return "";
	xmlNodePtr val = sub->children;
	if (val->type == XML_TEXT_NODE) {
		CString ret(val->content);
		if (ret.Right(1) == ".")
			ret.Delete(ret.GetLength()-1);
		return ret;
	} else
		return "";
}

BOOL CYazUsMarcXMLParser::CheckField(xmlNodePtr node, CString tag, TCHAR ind1, TCHAR ind2)
{
	if (node == NULL)
		return FALSE;
	xmlChar* t =	xmlGetProp(node, (xmlChar*)&"tag");
	xmlChar* i1 = xmlGetProp(node, (xmlChar*)&"ind1");
	xmlChar* i2 = xmlGetProp(node, (xmlChar*)&"ind2");

	return (strcmp((const char*)t, tag) == 0 /*&& *i1 == ind1 && *i2 == ind2*/);
}
