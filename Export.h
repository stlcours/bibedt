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

  $Id: Export.h,v 1.15 2006/04/08 19:34:26 stievie Exp $
*/

// Export.h: Schnittstelle für die Klasse CExport.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORT_H__53D936E6_81E1_427E_8673_BC6E6486E351__INCLUDED_)
#define AFX_EXPORT_H__53D936E6_81E1_427E_8673_BC6E6486E351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibFile.h"
#include "BeIconv.h"	// Hinzugefügt von der Klassenansicht

/**
 * This is an abstract class, descendants must override the following methods;
 * - CExport::GetExt()
 *   The extension, e.g. .txt for textfiles
 * - CExport::GetFilter()
 *   The filter string, e.g. Textfiles (*.txt)|*.txt
 * - CExport::DoExport(CString filename)
 *   The method which actually exports the selected items
 * - CExport::GetSource()
 *   Returns the source
 * - CExport::GetItemSource()
 *   Return the source of one item
 * - CExport::Clone()
 *   Returns a copy of the exporter
 */
class CExport  
{
public:
	virtual CString EncodeString(CString str, BOOL rs);
	CString GetLastError() { return m_LastError; }
	virtual CExport* Clone() = 0;
	virtual void Assign(CExport* src);
	BOOL m_Selected;
	BOOL GetLoaded() { return m_Loaded; }
	CString GetName() { return m_Name; }
	BOOL m_SelOnly;
	virtual CString GetExt() = 0;
	virtual CString GetFilter() = 0;
	static int CALLBACK AuthorSortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void SetListCtrl(CListCtrl *list);
	DWORD m_LineLength;
	virtual void DoExport(CString filename) = 0;
	virtual CString GetSource() = 0;
	virtual CString GetItemSource(CBibItem* item) = 0;
	CExport();
	virtual ~CExport();

protected:
	CString m_LastError;
	BOOL m_Loaded;
	CString m_Name;
	CIconv m_Iconv;
	BOOL GetSelected(int index);
	CListCtrl * m_ListCtrl;
	CBibFile * m_BibList;
};

#endif // !defined(AFX_EXPORT_H__53D936E6_81E1_427E_8673_BC6E6486E351__INCLUDED_)
