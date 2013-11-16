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

  $Id: YazRecord.cpp,v 1.8 2006/06/06 18:52:19 stievie Exp $
*/

// YazRecord.cpp: Implementierung der Klasse CYazRecord.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "YazRecord.h"
#include "YazMARCParser.h"
#include "YazOPACParser.h"
#include "YazXMLParser.h"
#include "Yaz.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CYazRecord::CYazRecord(ZOOM_record rec)
{
	// Memory management is odd here.  The ZOOM-C record we've
	// just fetched (`r') is owned by the ZOOM-C result-set we
	// fetched it from (`rs.rs'), so the underlying (ZOOM-C)
	// record is _not_ destroyed when this object is destroyed:
	// it's done when the underlying result-set is deleted.
	m_hRecord = rec;

	m_Parser = NULL;
	switch (GetSyntax()) {
	case YCS_XML:
		m_Parser = new CYazXMLParser();
		break;
	case YCS_USMARC:
	case YCS_UKMARC:
	case YCS_DKMARC:
		m_Parser = new CYazMARCParser();
		break;
	case YCS_OPAC:
		m_Parser = new CYazOPACParser();
		break;
	default:
		throw "Unknown or not implemented syntax";
	}
	ASSERT(m_Parser);
	m_Parser->SetRawData(GetRaw());
	m_Parser->Parse();
	m_Type = m_Parser->GetType();
}

CYazRecord::~CYazRecord()
{
	// Nothing not destroy m_hRecord -- see comment in constructor

	if (m_Parser)
		delete m_Parser;
}

CString CYazRecord::GetRender()
{
	if (m_Render.IsEmpty())
		m_Render = GetRecord("render");
	return m_Render;
}

CString CYazRecord::GetRaw()
{
	if (m_Raw.IsEmpty())
		m_Raw = GetRecord("raw");
	return m_Raw;
}

CString CYazRecord::GetRecord(CString what)
{
	// what + "; charset=marc8,iso-8859-1"
	int len;
	const char* data = ZOOM_record_get(m_hRecord, what, &len);
	return CString(data);
}

YC_SYNTAX CYazRecord::GetSyntax()
{
	CString syn = GetRecord(_T("syntax"));
	if (syn.CompareNoCase(YCSS_XML) == 0 || syn.CompareNoCase(_T("text-XML")) == 0 || syn.CompareNoCase(_T("application-XML")) == 0)
		return YCS_XML;
	else if (syn.CompareNoCase(YCSS_GRS1) == 0)
		return YCS_GRS1;
	else if (syn.CompareNoCase(YCSS_SUTRS) == 0)
		return YCS_SUTRS;
	else if (syn.CompareNoCase(YCSS_USMARC) == 0)
		return YCS_UKMARC;
	else if (syn.CompareNoCase(YCSS_UKMARC) == 0)
		return YCS_UKMARC;
	else if (syn.CompareNoCase(YCSS_DKMARC) == 0)
		return YCS_DKMARC;
	else if (syn.CompareNoCase(YCSS_OPAC) == 0)
		return YCS_OPAC;
	else
		return YCS_UNKNOWN;
}

CString CYazRecord::GetValue(CString name)
{
	return m_Parser->GetValue(name);
}
