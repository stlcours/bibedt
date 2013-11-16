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

  $Id: XSLTransform.h,v 1.2 2005/12/05 21:26:20 stievie Exp $
*/

// XSLTransform.h: Schnittstelle für die Klasse CXSLTransform.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSLTRANSFORM_H__00F6E1DD_8D4F_4DFC_9357_2CC6AA3C62AB__INCLUDED_)
#define AFX_XSLTRANSFORM_H__00F6E1DD_8D4F_4DFC_9357_2CC6AA3C62AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <libxml/parser.h>
#include <libxslt/transform.h>

class CXSLTransform  
{
public:
	CString GetXSLDoc() { return m_XSLDoc; }
	void SetXSLDoc(CString xsldoc);
	void Reset();
	CString AsString();
	xmlDocPtr Transform(CString filename);
	void Save(CString filename);
	xmlDocPtr Transform(xmlDocPtr doc);
	xsltStylesheetPtr GetStylePtr() { return m_Style; }
	CXSLTransform(CString xsldoc);
	virtual ~CXSLTransform();
	CString GetLastError() { return m_LastError; }

private:
	CString m_XSLDoc;
	CString m_LastError;
	xsltStylesheetPtr m_Style;
	xmlDocPtr m_Result;
};

#endif // !defined(AFX_XSLTRANSFORM_H__00F6E1DD_8D4F_4DFC_9357_2CC6AA3C62AB__INCLUDED_)
