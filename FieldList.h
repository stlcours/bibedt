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

  $Id: FieldList.h,v 1.5 2006/08/13 12:19:50 stievie Exp $
*/

// FieldList.h: Schnittstelle für die Klasse CFieldList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDLIST_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_)
#define AFX_FIELDLIST_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Field.h"
#include "BibEdtList.h"

class CFieldList : public CBibEdtList 
{
public:
	CFieldList * GetCorssRefed();
	void Clear();
	void Append(CFieldList *lst);
	CField * New();
	void DeleteEmpty();
	void ClearValues();
	void Delete(CField* f);
	void Assign(CFieldList* src);
	void SetModified(BOOL value);
	BOOL GetModified();
	void LoadFromFile(CBibReader* file);
	CField* Find(CString name);
	CField* Add(CString name, CString value);
	CObList * GetOwner() { return m_Owner; }
	CFieldList();
	virtual ~CFieldList();
protected:
	CObList *m_Owner;
};

#endif // !defined(AFX_FIELDLIST_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_)
