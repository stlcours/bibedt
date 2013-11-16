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

  $Id: YazQuery.h,v 1.2 2005/09/09 10:33:39 stievie Exp $
*/

// YazQuery.h: Schnittstelle für die Klasse CYazQuery.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZQUERY_H__DB3A7469_420D_4A2D_AA0E_BBE68985C9FB__INCLUDED_)
#define AFX_YAZQUERY_H__DB3A7469_420D_4A2D_AA0E_BBE68985C9FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "yaz/zoom.h"

class CYazQuery  
{
public:
	ZOOM_query GetHandle() const { return m_hQuery; }
	CYazQuery();
	virtual void SetQueryString(CString query);
	CString GetQueryString() const { return m_QueryString; }
	virtual ~CYazQuery();

protected:
	CString m_QueryString;
	ZOOM_query m_hQuery;
};

#endif // !defined(AFX_YAZQUERY_H__DB3A7469_420D_4A2D_AA0E_BBE68985C9FB__INCLUDED_)
