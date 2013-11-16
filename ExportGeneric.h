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

  $Id: ExportGeneric.h,v 1.4 2006/04/06 18:24:09 stievie Exp $
*/

// ExportGeneric.h: Schnittstelle für die Klasse CExportGeneric.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTGENERIC_H__1AE5A6C3_217A_4327_A1FD_FBC549C6B16B__INCLUDED_)
#define AFX_EXPORTGENERIC_H__1AE5A6C3_217A_4327_A1FD_FBC549C6B16B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExportXML.h"
#include "XSLTransform.h"	// Hinzugefügt von der Klassenansicht

class CExportGeneric : public CExportXML  
{
public:
	virtual CString EncodeString(CString str, BOOL rs);
	virtual void SetExt(CString value);
	virtual CExport* Clone();
	virtual void Assign(CExport* src);
	virtual void Save(xmlNodePtr node);
	virtual void Load(xmlNodePtr node);
	CExportGeneric();
	virtual ~CExportGeneric();
	virtual CString GetExt() { return m_Ext; }
	virtual CString GetFilter() { return m_Filter; }
	virtual void SetFilter(CString f) { m_Filter = f; }
	virtual CString GetSource();
	virtual void SetName(CString n) { m_Name = n; }
	virtual CString GetStyleFile() { return m_StyleFile; }
	virtual void SetStyleFile(CString s) { m_StyleFile = s; }
	virtual CString GetEncoding() { return m_Encoding; }
	virtual void SetEncoding(CString e) { m_Encoding = e; }

protected:
	static CString GetValue(xmlNodePtr node, CString name, CString def);
	static xmlNodePtr FindNode(xmlNodePtr nd, CString name);
	CXSLTransform *m_Transform;
	CString m_Filter;
	CString m_Ext;
};

#endif // !defined(AFX_EXPORTGENERIC_H__1AE5A6C3_217A_4327_A1FD_FBC549C6B16B__INCLUDED_)
