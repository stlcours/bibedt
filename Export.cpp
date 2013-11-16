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

  $Id: Export.cpp,v 1.15 2006/08/11 11:56:01 stievie Exp $
*/

// Export.cpp: Implementierung der Klasse CExport.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Export.h"
#include "BibFile.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExport::CExport()
{
	m_LineLength = 80;
	m_BibList = new CBibFile();
	m_Loaded = FALSE;
	m_Selected = FALSE;
	m_SelOnly = FALSE;
}

CExport::~CExport()
{
	delete m_BibList;
}

/**
 * \brief Set the list control to be exported.
 *
 * This class needs for variaous reasons the ListCtrl to be exported.
 */
void CExport::SetListCtrl(CListCtrl *list)
{
	m_ListCtrl = list;
	m_BibList->Clear();
	for (int i = 0; i < m_ListCtrl->GetItemCount(); i++) {
		if (!m_SelOnly || GetSelected(i)) {
			CBibItem *bi = (CBibItem*)m_ListCtrl->GetItemData(i);
			if (bi)
				m_BibList->New(dynamic_cast<CBibList*>(bi->GetOwner()))->Assign(bi);
		}
	}
	m_BibList->Sort(AuthorSortProc);
}

/**
 * \brief Sort the list by author names
 *
 * Sort procedure to sort the list by author names. It is automatically
 * called by CExport::SetListCtrl(CListCtrl *list). 
 */
int CExport::AuthorSortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CBibList *lst = (CBibList*)lParamSort;
	POSITION p = lst->FindIndex(lParam1);
	if (!p)
		return 0;
	CBibItem *bi1 = (CBibItem*)lst->GetAt(p);
	p = lst->FindIndex(lParam2);
	if (!p)
		return 0;
	CBibItem *bi2 = (CBibItem*)lst->GetAt(p);
	int res = 0;
	CField *fi1 = bi1->Find(STR_AUTHOR);
	if (!fi1)
		// No author try editor
		fi1 = bi1->Find(STR_EDITOR);
	CField *fi2 = bi2->Find(STR_AUTHOR);
	if (!fi2)
		// ditto
		fi2 = bi2->Find(STR_EDITOR);
	if (fi1 && fi2)
		res = ExtractLastNames(fi1->GetValue(), ' ').CompareNoCase(ExtractLastNames(fi2->GetValue(), ' '));
	if (!res) {
		// exactly the same -> use additionally the year
		fi1 = bi1->Find(STR_YEAR);
		fi2 = bi2->Find(STR_YEAR);
		if (fi1 && fi2)
			res = fi1->GetValue().CompareNoCase(fi2->GetValue());
	}
	return res;
}

/**
 * \brief Return TRUE when the item is selected in m_ListCtrl.
 * 
 * We need it, because only selected items are exported or, if none 
 * are selected all are exported.
 */
BOOL CExport::GetSelected(int index)
{
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (m_ListCtrl->GetItem(&item)) {
		return BIT_SET(item.state, LVIS_SELECTED);
	} else
		return FALSE;
}


void CExport::Assign(CExport* src)
{
	m_Name = src->GetName();
	m_Selected = src->m_Selected;
}

/**
 * Just return the string as it is.
 * If some exporter needs some encoding it should override this method.
 */
CString CExport::EncodeString(CString str, BOOL rs)
{
	return str;
}