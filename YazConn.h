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

  $Id: YazConn.h,v 1.2 2005/09/09 10:33:39 stievie Exp $
*/

// YazConn.h: Schnittstelle für die Klasse CYazConn.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZCONN_H__51E9B2E1_AD0C_4028_B116_A7EF30484AEB__INCLUDED_)
#define AFX_YAZCONN_H__51E9B2E1_AD0C_4028_B116_A7EF30484AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "yaz/zoom.h"
#include "YazResultSet.h"	// Hinzugefügt von der Klassenansicht
#include "YazQuery.h"

class CYazConn  
{
public:
	CString GetLastError() { return m_LastError; }
	CYazResultSet Search(CYazQuery* query);
	CString GetOption(CString name);
	int GetPort() const { return m_Port; }
	CString GetHost() const { return m_Host; }
	BOOL GetConnected() const { return m_Connected; }
	void SetOption(CString name, CString value);
	CYazConn(CString host, int port);
	virtual ~CYazConn();

private:
	ZOOM_connection m_hConnection;
	int m_Port;
	CString m_Host;
protected:
	CString m_LastError;
	BOOL m_Connected;
};

#endif // !defined(AFX_YAZCONN_H__51E9B2E1_AD0C_4028_B116_A7EF30484AEB__INCLUDED_)
