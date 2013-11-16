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

  $Id: ExportInternal.h,v 1.1 2006/05/25 14:15:47 stievie Exp $
*/

// ExportInternal.h: Schnittstelle für die Klasse CExportInternal.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTINTERNAL_H__0470F8CC_A1FC_4849_9F26_1BB224E0ED1D__INCLUDED_)
#define AFX_EXPORTINTERNAL_H__0470F8CC_A1FC_4849_9F26_1BB224E0ED1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExportGeneric.h"
#include "BibItem.h"

class CExportInternal : public CExportGeneric  
{
public:
	CExportInternal();
	virtual ~CExportInternal();
	CBibItem* GetItem() { return m_Item; }
	void SetItem(CBibItem* item) { m_Item = item; }

protected:
	CBibItem* m_Item;
};

#endif // !defined(AFX_EXPORTINTERNAL_H__0470F8CC_A1FC_4849_9F26_1BB224E0ED1D__INCLUDED_)
