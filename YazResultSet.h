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

  $Id: YazResultSet.h,v 1.1 2005/08/31 11:42:52 stievie Exp $
*/

// YazResultSet.h: Schnittstelle für die Klasse CYazResultSet.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZRESULTSET_H__24374F30_78C3_4AF2_9665_0EED1C55B532__INCLUDED_)
#define AFX_YAZRESULTSET_H__24374F30_78C3_4AF2_9665_0EED1C55B532__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazRecord.h"
#include "yaz/zoom.h"

class CYazResultSet  
{
public:
	CYazRecord GetRecord(int index);
	int GetCount();
	CYazResultSet(ZOOM_resultset result);
	virtual ~CYazResultSet();
protected:
	ZOOM_resultset m_hResultSet;

};

#endif // !defined(AFX_YAZRESULTSET_H__24374F30_78C3_4AF2_9665_0EED1C55B532__INCLUDED_)
