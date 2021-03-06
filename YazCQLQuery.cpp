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

  $Id: YazCQLQuery.cpp,v 1.2 2005/09/06 15:31:43 stievie Exp $
*/

// YazCQLQuery.cpp: Implementierung der Klasse CYazCQLQuery.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazCQLQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazCQLQuery::CYazCQLQuery()
{

}

CYazCQLQuery::~CYazCQLQuery()
{

}

void CYazCQLQuery::SetWueryString(CString query)
{
	CYazQuery::SetQueryString(query);
	int ret = ZOOM_query_cql(m_hQuery, query);
	if (ret == -1) {
		// Something went wrong
		TRACE0("ZOOM_query_cql() failed\n");
	}
}
