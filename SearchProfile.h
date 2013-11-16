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

  $Id: SearchProfile.h,v 1.5 2005/09/27 11:04:09 stievie Exp $
*/

// SearchProfile.h: Schnittstelle für die Klasse CSearchProfile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHPROFILE_H__A5242542_9A63_40DC_A32E_895BF8F84000__INCLUDED_)
#define AFX_SEARCHPROFILE_H__A5242542_9A63_40DC_A32E_895BF8F84000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "libxml/tree.h"
#include "Yaz.h"
#include "BibEdtList.h"

static const char PROFILES_VERSION[] = "1.0";
static const char PROFILES_NAME[] = "profiles";
static const char PROFILE_NAME[] = "profile";

class CSearchProfile  
{
public:
	CString m_TargetCharset;
	CString m_SourceCharset;
	CString m_Password;
	BOOL m_SavePass;
	void Assign(CSearchProfile* profile);
	void Save(xmlNodePtr node);
	void Load(xmlNodePtr node);
	QUERY_TYPE m_QueryType;
	CString m_Database;
	CString m_Group;
	CString m_User;
	CString m_Proxy;
	int m_Port;
	CString m_Host;
	CString m_Name;
	CSearchProfile();
	virtual ~CSearchProfile();

private:
	static CString GetValue(xmlNodePtr node, CString name, CString def);
	static int GetValue(xmlNodePtr node, CString name, int def);
	static xmlNodePtr FindNode(xmlNodePtr nd, CString name);
};

class CSearchProfileList : public CBibEdtList  
{
public:
	BOOL m_SavePass;
	CSearchProfile* New();
	void Assign(CSearchProfileList* lst);
	void Delete(CSearchProfile* profile);
	CSearchProfile* New(CString name);
	void Clear();
	void Save(CString filename);
	void Load(CString filename);
	CSearchProfileList();
	virtual ~CSearchProfileList();

};

#endif // !defined(AFX_SEARCHPROFILE_H__A5242542_9A63_40DC_A32E_895BF8F84000__INCLUDED_)
