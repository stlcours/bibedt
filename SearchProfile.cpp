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

  $Id: SearchProfile.cpp,v 1.7 2006/06/06 18:52:18 stievie Exp $
*/

// SearchProfile.cpp: Implementierung der Klasse CSearchProfile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SearchProfile.h"
#include "libxml/parser.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/* CSearchProfile */

CSearchProfile::CSearchProfile()
{
	m_Port = 0;
	m_QueryType = QT_PREFIX;
	m_SavePass = FALSE;
	m_TargetCharset = _T("ISO88591");
	m_SourceCharset = _T("UTF8");
}

CSearchProfile::~CSearchProfile()
{

}

CString CSearchProfile::GetValue(xmlNodePtr node, CString name, CString def)
{
	xmlNodePtr nd;
	nd = FindNode(node->children, name);
	if (nd && nd->type == XML_TEXT_NODE)
		return nd->content;
	else
		return def;
}

int CSearchProfile::GetValue(xmlNodePtr node, CString name, int def)
{
	xmlNodePtr nd;
	nd = FindNode(node->children, name);
	if (nd && nd->type == XML_TEXT_NODE)
		return atoi((const char*)nd->content);
	else
		return def;
}

void CSearchProfile::Load(xmlNodePtr node)
{
	m_Name = GetValue(node, "name", "");
	m_Database = GetValue(node, "database", "");
	m_Group = GetValue(node, "group", "");
	m_Host = GetValue(node, "host", "");
	m_Port = GetValue(node, "port", 0);
	m_Proxy = GetValue(node, "proxy", "");
	m_QueryType = (QUERY_TYPE)GetValue(node, "querytype", QT_PREFIX);
	m_SavePass = GetValue(node, "savepass", FALSE);
	if (m_SavePass)
		m_Password = GetValue(node, "pass", "");
	else
		m_Password.Empty();
	// Charset
	m_SourceCharset = GetValue(node, "sourcecharset", "UTF8");
	m_TargetCharset = GetValue(node, "targetcharset", "ISO88591");
}

void CSearchProfile::Save(xmlNodePtr node)
{
	xmlNewChild(node, 0, (xmlChar*)&"name", (xmlChar*)(LPCSTR)m_Name);
	xmlNewChild(node, 0, (xmlChar*)&"database", (xmlChar*)(LPCSTR)m_Database);
	xmlNewChild(node, 0, (xmlChar*)&"group", (xmlChar*)(LPCSTR)m_Group);
	xmlNewChild(node, 0, (xmlChar*)&"host", (xmlChar*)(LPCSTR)m_Host);
	CString s;
	s.Format("%d", m_Port);
	xmlNewChild(node, 0, (xmlChar*)&"port", (xmlChar*)(LPCSTR)s);
	xmlNewChild(node, 0, (xmlChar*)&"proxy", (xmlChar*)(LPCSTR)m_Proxy);
	s.Format("%d", m_QueryType);
	xmlNewChild(node, 0, (xmlChar*)&"querytype", (xmlChar*)(LPCSTR)s);
	xmlNewChild(node, 0, (xmlChar*)&"user", (xmlChar*)(LPCSTR)m_User);
	s.Format("%d", m_SavePass);
	xmlNewChild(node, 0, (xmlChar*)&"savepass", (xmlChar*)(LPCSTR)s);
	if (m_SavePass) {
		xmlNewChild(node, 0, (xmlChar*)&"pass", (xmlChar*)(LPCSTR)m_Password);
	} else {
		xmlNewChild(node, 0, (xmlChar*)&"pass", NULL);
	}
	// Charset
	xmlNewChild(node, 0, (xmlChar*)&"sourcecharset", (xmlChar*)(LPCSTR)m_SourceCharset);
	xmlNewChild(node, 0, (xmlChar*)&"targetcharset", (xmlChar*)(LPCSTR)m_TargetCharset);
}

xmlNodePtr CSearchProfile::FindNode(xmlNodePtr nd, CString name)
{
	xmlNodePtr node = nd;
	while (node != NULL && stricmp((const char*)node->name, name) != 0)
		node = node->next;
	if (node != NULL)
		return node->children;
	else
		return NULL;
}

void CSearchProfile::Assign(CSearchProfile *profile)
{
	m_Database = profile->m_Database;
	m_Group = profile->m_Group;
	m_Host = profile->m_Host;
	m_Name = profile->m_Name;
	m_Password = profile->m_Password;
	m_Port = profile->m_Port;
	m_Proxy = profile->m_Proxy;
	m_QueryType = profile->m_QueryType;
	m_User = profile->m_User;
}

/* CSearchProfileList */

CSearchProfileList::CSearchProfileList()
{
	m_SavePass = FALSE;
}

CSearchProfileList::~CSearchProfileList()
{
	Clear();
}

void CSearchProfileList::Load(CString filename)
{
	xmlDocPtr doc = xmlParseFile(filename);
	if (doc == NULL)
		return;

	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (root == NULL)
		return;
	xmlNodePtr profile = root->children;
	while (profile != NULL && profile->type != XML_ELEMENT_NODE)
		profile = root->next;
	while (profile != NULL) {
		CSearchProfile* prof = new CSearchProfile();
		prof->m_SavePass = m_SavePass;
		AddTail((CObject*)prof);
		prof->Load(profile);
		profile = profile->next;
		while (profile != NULL && profile->type != XML_ELEMENT_NODE)
			profile = root->next;
	}
	xmlFreeDoc(doc);
}

void CSearchProfileList::Save(CString filename)
{
	xmlDocPtr doc = xmlNewDoc((xmlChar*)&PROFILES_VERSION);
	xmlNodePtr root = xmlNewNode(0, (xmlChar*)&PROFILES_NAME);
	xmlDocSetRootElement(doc, root);
	POSITION p = GetHeadPosition();
	while (p) {
		CSearchProfile* prof = (CSearchProfile*)GetNext(p);
		xmlNodePtr profile = xmlNewChild(root, 0, (xmlChar*)&PROFILE_NAME, 0);
		prof->Save(profile);
	}
	xmlSaveFile(filename, doc);
	xmlFreeDoc(doc);
}

void CSearchProfileList::Clear()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CSearchProfile* prof = (CSearchProfile*)GetNext(p);
		delete prof;
	}
	RemoveAll();
}

CSearchProfile* CSearchProfileList::New()
{
	CSearchProfile* profile = new CSearchProfile();
	AddTail((CObject*)profile);
	return profile;
}

CSearchProfile* CSearchProfileList::New(CString name)
{
	CSearchProfile* profile = New();
	profile->m_Name = name;
	return profile;
}

void CSearchProfileList::Delete(CSearchProfile *profile)
{
	if (profile == NULL)
		return;
	POSITION p = Find((CObject*)profile);
	if (p)
		RemoveAt(p);
	delete profile;
}

void CSearchProfileList::Assign(CSearchProfileList *lst)
{
	Clear();
	POSITION p = lst->GetHeadPosition();
	while (p) {
		CSearchProfile* profile = (CSearchProfile*)GetNext(p);
		New()->Assign(profile);
	}
}
