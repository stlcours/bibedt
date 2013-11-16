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

  $Id: BeIconv.cpp,v 1.7 2006/06/17 11:43:34 stievie Exp $
*/

// Iconv.cpp: Implementierung der Klasse CIconv.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "BeIconv.h"
#include "Options.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIconv::CIconv()
{
	m_hIconv = NULL;
}

CIconv::~CIconv()
{
	if (m_hIconv) {
		yaz_iconv_close(m_hIconv);
	}
}

void CIconv::List(CStringList *lst)
{
	lst->RemoveAll();
	// MARC8 is from YAZ
	lst->AddHead(_T("MARC8"));
	// Internal Encoding
	lst->AddHead(_T("HTML"));
	lst->AddHead(_T("TeX"));
	lst->AddHead(_T("RTF"));

	iconvlist(print_one, lst);
}

int CIconv::print_one(unsigned int namescount, const char *const *names, void *data)
{
	CStringList* lst = (CStringList*)data;
	if (namescount > 0) {
		lst->AddTail(names[0]);
	}
	return 0;
}

CString CIconv::ConvertIconv(CString str)
{
	if (m_hIconv == NULL) {
#ifdef _UNICODE
		int nLen = _tcslen(m_TargetCharset);
		char *szTarget = new char[nLen+1];
		int i;
		for (i = 0; i <= nLen; i++)
			szTarget[i] = (char)m_TargetCharset[i];
		nLen = _tcslen(m_SourceCharset);
		char *szSource = new char[nLen+1];
		for (i = 0; i <= nLen; i++)
			szSource[i] = (char)m_SourceCharset[i];
		m_hIconv = yaz_iconv_open(szTarget, szSource);
		delete [] szTarget;
		delete [] szSource;
#else
		m_hIconv = yaz_iconv_open(m_TargetCharset, m_SourceCharset);
#endif
#ifdef _DEBUG
		if (m_hIconv == NULL)
			TRACE2("CIconv::Convert(): iconv_open filed, source: %s; target: %s\n", m_SourceCharset, m_TargetCharset);
#endif
	}

	if (!str.IsEmpty()) { 	 
		if (m_hIconv != NULL) { 	 
			CString out; 	 
			size_t inleft = str.GetLength(); 	 
			size_t outleft = 4 * inleft + 2; 	 
			LPTSTR inbuff = str.GetBuffer(inleft); 	 
			LPTSTR outbuff = out.GetBuffer(outleft);
			memset(outbuff, 0, outleft);
			size_t ret;
#ifdef _UNICODE
			// FIXME
			ret = 0;
#else
			ret = yaz_iconv(m_hIconv, &inbuff, &inleft, &outbuff, &outleft);
#endif
			if (ret == (size_t)(-1)) { 	 
				TRACE0("CIconv::Convert(): iconv failed\n"); 	 
				return str; 	 
			} 	 
			outbuff -= ret; 	 
			out.ReleaseBuffer(); 	 
			return out;
		}
	}
	return str;
}

CString CIconv::Convert(CString str)
{
	if (m_TargetCharset.CompareNoCase(_T("HTML")) == 0) {
		return ConvertHTML(str);
	} else if (m_TargetCharset.CompareNoCase(_T("TeX")) == 0) {
		return ConvertTeX(str);
	} else if (m_TargetCharset.CompareNoCase(_T("RTF")) == 0) {
		return ConvertRTF(str);
	} else
		return ConvertIconv(str);
}

void CIconv::SetSourceCharset(CString value)
{
	if (value.CompareNoCase(m_SourceCharset) != 0) {
		if (m_hIconv) {
			yaz_iconv_close(m_hIconv);
		}
		m_SourceCharset = value;
	}
}

void CIconv::SetTargetCharset(CString value)
{
	if (value.CompareNoCase(m_TargetCharset) != 0) {
		if (m_hIconv) {
			yaz_iconv_close(m_hIconv);
		}
		m_TargetCharset = value;
	}
}

CString CIconv::ConvertHTML(CString str)
{
	LoadHTML();
	return m_CodingHTML.Encode(str);
}

CString CIconv::ConvertTeX(CString str)
{
	LoadTeX();
	return m_CodingTeX.Encode(str);
}

CString CIconv::ConvertRTF(CString str)
{
	LoadRTF();
	return m_CodingRTF.Encode(str);
}

void CIconv::LoadRTF()
{
	if (!m_CodingRTF.GetLoaded()) {
		COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
		m_CodingRTF.m_Res = _T("RTF");
		m_CodingRTF.m_Filename = o->m_EncodingRTF;
		m_CodingRTF.m_Enabled = TRUE;
		m_CodingRTF.Load();
	}
}

void CIconv::LoadHTML()
{
	if (!m_CodingHTML.GetLoaded()) {
		COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
		m_CodingHTML.m_Res = _T("HTML");
		m_CodingHTML.m_Filename = o->m_EncodingHTML;
		m_CodingHTML.m_Enabled = TRUE;
		m_CodingHTML.Load();
	}
}

void CIconv::LoadTeX()
{
	if (!m_CodingTeX.GetLoaded()) {
		COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
		m_CodingTeX.m_Res = _T("TeX");
		m_CodingTeX.m_Filename = o->m_EncodingTeX;
		m_CodingTeX.m_Enabled = TRUE;
		m_CodingTeX.Load();
	}
}
