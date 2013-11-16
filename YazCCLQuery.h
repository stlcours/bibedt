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

  $Id: YazCCLQuery.h,v 1.1 2005/08/31 11:42:52 stievie Exp $
*/

// YazCCLQuery.h: Schnittstelle für die Klasse CYazCCLQuery.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZCCLQUERY_H__8E800DCA_85E4_4A79_AB07_6D08E6B5DB63__INCLUDED_)
#define AFX_YAZCCLQUERY_H__8E800DCA_85E4_4A79_AB07_6D08E6B5DB63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazQuery.h"

class CYazCCLQuery : public CYazQuery  
{
public:
	CYazCCLQuery();
	virtual ~CYazCCLQuery();
	virtual void SetQueryString(CString query);

};

#endif // !defined(AFX_YAZCCLQUERY_H__8E800DCA_85E4_4A79_AB07_6D08E6B5DB63__INCLUDED_)
