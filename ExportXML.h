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

  $Id: ExportXML.h,v 1.17 2006/06/06 18:52:18 stievie Exp $
*/

// ExportXML.h: Schnittstelle für die Klasse CExportXML.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTXML_H__AE05F54B_5524_429D_B1A2_14A341855734__INCLUDED_)
#define AFX_EXPORTXML_H__AE05F54B_5524_429D_B1A2_14A341855734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Export.h"
#include "BeIconv.h"

static const TCHAR XML_VER[] = _T("1.0");
static const TCHAR XML_HEAD[] = _T("<?xml version=\"%s\" encoding=\"%s\"?>");
static const TCHAR XML_ROOTNAME[] = _T("bibliography");
#define XML_DOCTYPE _T("<!DOCTYPE bibliography [\r\n\
  <!ENTITY amp    \"&#x026;\">\r\n\
  <!ENTITY lt     \"&#x03C;\">\r\n\
  <!ENTITY gt     \"&#x03E;\">\r\n\
  <!ENTITY nbsp   \"&#x0A0;\">\r\n\
  <!ENTITY emsp   \"&#x02003;\">\r\n\
  <!ENTITY thinsp \"&#x02009;\">\r\n\
  <!ENTITY ndash  \"&#x02013;\">\r\n\
  <!ENTITY mdash  \"&#x02014;\">\r\n\
  <!ENTITY lsquo  \"&#x02018;\">\r\n\
  <!ENTITY rsquo  \"&#x02019;\">\r\n\
  <!ENTITY sbquo  \"&#x0201A;\">\r\n\
  <!ENTITY ldquo  \"&#x0201C;\">\r\n\
  <!ENTITY rdquo  \"&#x0201D;\">\r\n\
  <!ENTITY sdquo  \"&#x0201E;\">\r\n\
]>\r\n")

class CExportXML : public CExport  
{
public:
	virtual CString EncodeString(CString str, BOOL rs);
	virtual CExport* Clone();
	virtual void Assign(CExport* src);
	CString m_StyleFile;
	CString m_Encoding;
	virtual CString GetBody();
	virtual CString GetFooter();
	virtual CString GetHeader();
	virtual CString GetSource();
	virtual CString GetExt();
	virtual CString GetFilter();
	virtual CString GetItemSource(CBibItem* item);
	virtual void GetItemSource(xString *const str, CBibItem* item);
	virtual void DoExport(CString filename);
	CExportXML();
	virtual ~CExportXML();
protected:
	virtual CString GetDocType();
	BOOL m_LinkStyle;
	void Load();
};

#endif // !defined(AFX_EXPORTXML_H__AE05F54B_5524_429D_B1A2_14A341855734__INCLUDED_)
