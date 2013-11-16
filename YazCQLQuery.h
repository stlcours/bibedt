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

  $Id: YazCQLQuery.h,v 1.2 2005/09/06 15:31:43 stievie Exp $
*/

// YazCQLQuery.h: Schnittstelle für die Klasse CYazCQLQuery.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YAZCQLQUERY_H__9DFA4D75_D051_451D_9D6E_9A9549558953__INCLUDED_)
#define AFX_YAZCQLQUERY_H__9DFA4D75_D051_451D_9D6E_9A9549558953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YazQuery.h"

class CYazCQLQuery : public CYazQuery  
{
public:
	void SetWueryString(CString query);
	CYazCQLQuery();
	virtual ~CYazCQLQuery();

};

#endif // !defined(AFX_YAZCQLQUERY_H__9DFA4D75_D051_451D_9D6E_9A9549558953__INCLUDED_)
