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

  $Id: XSLTransform.cpp,v 1.5 2006/07/19 20:32:39 stievie Exp $
*/

// XSLTransform.cpp: Implementierung der Klasse CXSLTransform.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "XSLTransform.h"
#include "Globals.h"
#include "libxslt/xsltutils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CXSLTransform::CXSLTransform(CString xsldoc)
{
	m_Style = NULL;
	m_Result = NULL;

	if (!xsldoc.IsEmpty()) {
		SetXSLDoc(xsldoc);
	}
}

CXSLTransform::~CXSLTransform()
{
	Reset();
}

/**
 * Apply stylesheet to doc and return the result
 */
xmlDocPtr CXSLTransform::Transform(xmlDocPtr doc)
{
	ASSERT(doc);
	CWaitCursor wait;
	if (m_Style) {
		m_Result = xsltApplyStylesheet(m_Style, doc, NULL);
	} else {
		// No style -> return the doc
		m_Result = doc;
	}
	return m_Result;
}

/**
 * Saves the result to filename
 */
void CXSLTransform::Save(CString filename)
{
	if (m_Result)
		xsltSaveResultToFilename(filename, m_Result, m_Style, 0);
}

/**
 * Transforms the sourcefile with filename
 */
xmlDocPtr CXSLTransform::Transform(CString filename)
{
	if (!filename.IsEmpty()) {
		xmlDocPtr doc = xmlParseFile(filename);
		xmlDocPtr d = Transform(doc);
		xmlFreeDoc(doc);
		return d;
	} else
		return NULL;
}

/**
 * Return the result as string
 */
CString CXSLTransform::AsString()
{
	int buffsize = 100;
	xmlChar *buff;// = (xmlChar*)malloc((size_t)buffsize);
	int i = xsltSaveResultToString(&buff, &buffsize, m_Result, m_Style);
	CString res(buff);
//	free(buff);
	return res;
}

/**
 * Clean up memory
 */
void CXSLTransform::Reset()
{
	// Also frees xsl in SetXSLDoc()
	if (m_Style) {
		xsltFreeStylesheet(m_Style);
		m_Style = NULL;
	}
	if (m_Result) {
		xmlFreeDoc(m_Result);
		m_Result = NULL;
	}
	m_LastError.Empty();
}

/**
 * Sets the style file
 *
 * \param xsldoc Either a filename or source of XSL file
 */
void CXSLTransform::SetXSLDoc(CString xsldoc)
{
	if (m_XSLDoc.Compare(xsldoc) != 0) {
		m_XSLDoc = xsldoc;
		Reset();
		if (xsldoc.IsEmpty()) {
			return;
		}
		xmlErrorPtr err = NULL;

		xmlDocPtr xsl = NULL;
		CFileFind ff;
		if (xsldoc.GetLength() < MAX_PATH && ff.FindFile(xsldoc)) {
			// xsldoc is a filename
			ff.Close();
			m_Style = xsltParseStylesheetFile((const xmlChar *)(LPCSTR)xsldoc);
			if (!m_Style || m_Style->errors > 0) {
				xmlFreeDoc(xsl);
				err = xmlGetLastError();
				if (err != NULL)
					m_LastError.Format(AfxLoadString(IDS_STRING_XSLPARSEERR), err->file, err->line, err->int2, err->code, err->message);
				else
					m_LastError.LoadString(IDS_STRING_UNKNOWN_XSLERROR);
				xmlResetLastError();
#ifdef _DEBUG
				TRACE1("CXSLTransform::SetXSLDoc(): %s\n", m_LastError);
#endif
			}
		} else {
			// xsldoc is a XSL source
			xsl = xmlParseMemory(xsldoc, xsldoc.GetLength());
			if (xsl) {
				m_Style = xsltParseStylesheetDoc(xsl);
				if (!m_Style || m_Style->errors > 0) {
					xmlFreeDoc(xsl);
					err = xmlGetLastError();
					if (err != NULL)
						m_LastError.Format(AfxLoadString(IDS_STRING_XSLPARSEERR), err->file, err->line, err->int2, err->code, err->message);
					else
						m_LastError.LoadString(IDS_STRING_UNKNOWN_XSLERROR);
					xmlResetLastError();
#ifdef _DEBUG
					TRACE1("CXSLTransform::SetXSLDoc(): %s\n", m_LastError);
#endif
				}
			} else {
				// XML parsing error
				err = xmlGetLastError();
				m_LastError.Format(AfxLoadString(IDS_STRING_XMLPARSEERR), err->file, err->line, err->int2, err->code, err->message);
				xmlResetLastError();
#ifdef _DEBUG
				TRACE1("CXSLTransform::SetXSLDoc(): %s\n", m_LastError);
#endif
			}
		}
	}
}
