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

  $Id: ExportGeneric.cpp,v 1.9 2006/08/12 16:06:17 stievie Exp $
*/

// ExportGeneric.cpp: Implementierung der Klasse CExportGeneric.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "ExportGeneric.h"
#include "libxml/tree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportGeneric::CExportGeneric()
{
	m_Transform = NULL;
	m_LinkStyle = FALSE;
}

CExportGeneric::~CExportGeneric()
{
	if (m_Transform)
		delete m_Transform;
}

CString CExportGeneric::GetSource()
{
	m_LastError.Empty();
	// First get the XML source
	CString src = CExportXML::GetSource();

#ifdef _DEBUG
	CFile f;
	try {
		f.Open(_T("C:\\TEMP\\bibedt_test.xml"), CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		f.Write(src, src.GetLength());
		f.Close();
	} catch (...) {	}
#endif

	// Parse the XML source
#ifdef _UNICODE
	int nLen = _tcslen(src);
	char *szSrc = new char[nLen+1];
	int i;
	for (i = 0; i <= nLen; i++)
		szSrc[i] = (char)src[i];
	xmlDocPtr doc = xmlParseMemory(szSrc, nLen);
	delete [] szSrc;
#else
	xmlDocPtr doc = xmlParseMemory(src, src.GetLength());
#endif
	if (doc == NULL) {
		xmlErrorPtr err = xmlGetLastError();
		m_LastError.Format(AfxLoadString(IDS_STRING_XMLPARSEERR), err->file, err->line, err->int2, err->code, err->message);
		TRACE(m_LastError);
		xmlResetLastError();
		return _T("");
	}
	// Transform it
	if (!m_Transform)
		m_Transform = new CXSLTransform(m_StyleFile);
	else
		m_Transform->SetXSLDoc(m_StyleFile);
	m_LastError = m_Transform->GetLastError();
	if (!m_LastError.IsEmpty()) {
		xmlFreeDoc(doc);
		return _T("");	
	}
	xmlDocPtr res = m_Transform->Transform(doc);
	m_LastError = m_Transform->GetLastError();
	TRACE(m_LastError);
	xmlFreeDoc(doc);
	if (!m_LastError.IsEmpty())
		return _T("");

	// Get it as string
	CString strres = m_Transform->AsString();
	return strres;
}

void CExportGeneric::Load(xmlNodePtr node)
{
	m_Name = GetValue(node, "name", "");
	m_StyleFile = GetValue(node, "style", "");
	m_Encoding = GetValue(node, "encoding", "");
	m_Ext = GetValue(node, "ext", "");
	m_Filter = GetValue(node, "filter", "");	
	m_Iconv.SetTargetCharset(m_Encoding);
}

void CExportGeneric::Save(xmlNodePtr node)
{
	xmlNewChild(node, 0, (xmlChar*)&"name", (xmlChar*)(LPCSTR)m_Name);
	xmlNewChild(node, 0, (xmlChar*)&"style", (xmlChar*)(LPCSTR)m_StyleFile);
	xmlNewChild(node, 0, (xmlChar*)&"encoding", (xmlChar*)(LPCSTR)m_Encoding);
	xmlNewChild(node, 0, (xmlChar*)&"ext", (xmlChar*)(LPCSTR)m_Ext);
	xmlNewChild(node, 0, (xmlChar*)&"filter", (xmlChar*)(LPCSTR)m_Filter);
}

void CExportGeneric::Assign(CExport *src)
{
	CExportXML::Assign(src);
	CExportGeneric* exp = dynamic_cast<CExportGeneric*>(src);
	if (exp) {
		m_Ext = exp->GetExt();
		m_Filter = exp->GetFilter();
	}
}

CExport* CExportGeneric::Clone()
{
	CExport* res = new CExportGeneric();
	res->Assign(this);
	return res;
}

xmlNodePtr CExportGeneric::FindNode(xmlNodePtr nd, CString name)
{
	xmlNodePtr node = nd;
	while (node != NULL && stricmp((const char*)node->name, name) != 0)
		node = node->next;
	if (node != NULL)
		return node->children;
	else
		return NULL;
}

CString CExportGeneric::GetValue(xmlNodePtr node, CString name, CString def)
{
	if (!node)
		return def;
	xmlNodePtr nd;
	nd = FindNode(node->children, name);
	if (nd && nd->type == XML_TEXT_NODE)
		return nd->content;
	else
		return def;
}

void CExportGeneric::SetExt(CString value)
{
	if (!value.IsEmpty() && value.GetAt(0) != '.')
		m_Ext = "." + value;
	else
		m_Ext = value;
}

CString CExportGeneric::EncodeString(CString str, BOOL rs)
{
	// encodes &, < and >
//	CString ret = m_Coding->Encode(str);
//	return m_Iconv.Convert(ret);
	return CExportXML::EncodeString(str, rs);
}
