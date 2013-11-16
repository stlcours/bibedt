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

  $Id: YazResultSet.cpp,v 1.1 2005/08/31 11:42:52 stievie Exp $
*/

// YazResultSet.cpp: Implementierung der Klasse CYazResultSet.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazResultSet.h"
#include "YazQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazResultSet::CYazResultSet(ZOOM_resultset result)
{
	m_hResultSet = result;
}

CYazResultSet::~CYazResultSet()
{
	if (m_hResultSet != 0)
		ZOOM_resultset_destroy(m_hResultSet);
}

int CYazResultSet::GetCount()
{
	return (int)ZOOM_resultset_size(m_hResultSet);
}

CYazRecord CYazResultSet::GetRecord(int index)
{
	ASSERT(index >= 0);
	ZOOM_record rec = ZOOM_resultset_record(m_hResultSet, (size_t)index);
	return CYazRecord(rec);
}
