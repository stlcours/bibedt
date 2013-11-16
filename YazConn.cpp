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

  $Id: YazConn.cpp,v 1.4 2005/09/09 10:33:39 stievie Exp $
*/

// YazConn.cpp: Implementierung der Klasse CYazConn.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazConn.h"
#include "Yaz.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazConn::CYazConn(CString host, int port)
{
	m_Host = host;
	m_Port = port;
	m_hConnection = ZOOM_connection_new(host, port);
	int errcode;
	const char *errmsg;	// unused: carries same info as `errcode'
	const char *addinfo;
	if ((errcode = ZOOM_connection_error(m_hConnection, &errmsg, &addinfo)) != 0) {
		ZOOM_connection_destroy(m_hConnection);
		m_hConnection = 0;
		m_LastError = "Unable to connect to host\r\n" + CString(addinfo);
		m_Connected = FALSE;
	} else
		m_Connected = TRUE;
}

CYazConn::~CYazConn()
{
	if (m_Connected)
		ZOOM_connection_destroy(m_hConnection);
}

void CYazConn::SetOption(CString name, CString value)
{
	ZOOM_connection_option_set(m_hConnection, name, value);
}

CString CYazConn::GetOption(CString name)
{
	const char* ret = ZOOM_connection_option_get(m_hConnection, name);
	return CString(ret);
}

CYazResultSet CYazConn::Search(CYazQuery* query)
{
	ZOOM_resultset rs = ZOOM_connection_search(m_hConnection, query->GetHandle());
	return CYazResultSet(rs);
}
