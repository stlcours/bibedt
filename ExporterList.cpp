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

  $Id: ExporterList.cpp,v 1.13 2006/08/12 16:06:17 stievie Exp $
*/

// ExporterList.cpp: Implementierung der Klasse CExporterList.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ExporterList.h"
#include "ExportBib.h"
#include "ExportRTF.h"
#include "ExportText.h"
#include "ExportXML.h"
#include "ExportGeneric.h"
#include "ExportPreview.h"
#include "ExportInternal.h"
#include "ExportCopyHtml.h"
#include "ExportKeygen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExporterList::CExporterList()
{
	m_Loaded = FALSE;
}

CExporterList::~CExporterList()
{
	Clear();
}

void CExporterList::Load(BOOL force /* = FALSE */)
{
	if (m_Loaded && !force)
		return;

	Clear();
	m_Modified = FALSE;
	// First add default exporter
	CExport* ex;
	ex = new CExportBib();
	AddTail((CObject*)ex);
	ex = new CExportText();
	AddTail((CObject*)ex);
	ex = new CExportRTF();
	AddTail((CObject*)ex);
	ex = new CExportXML();
	AddTail((CObject*)ex);
	ex = new CExportPreview();
	((CExportPreview*)ex)->Load(NULL);
	AddTail((CObject*)ex);
	ex = new CExportKeygen();
	((CExportKeygen*)ex)->Load(NULL);
	AddTail((CObject*)ex);
	ex = new CExportCopyHtml();
	((CExportCopyHtml*)ex)->Load(NULL);
	AddTail((CObject*)ex);
		
	// Then Load custom from XML file
#ifdef _UNICODE
	int nLen = _tcslen(m_ListFile);
	char *szFilename = new char[nLen+1];
	int i;
	for (i = 0; i <= nLen; i++)
		szFilename[i] = (char)m_ListFile[i];
	xmlDocPtr doc = xmlParseFile(szFilename);
	delete [] szFilename;
#else
	xmlDocPtr doc = xmlParseFile(m_ListFile);
#endif
	if (doc == NULL)
		return;

	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (root == NULL)
		return;
	xmlNodePtr ndexp = root->children;
	while (ndexp != NULL && ndexp->type != XML_ELEMENT_NODE)
		ndexp = root->next;
	while (ndexp != NULL) {
		CExportGeneric* gex = new CExportGeneric();
		gex->Load(ndexp);
		AddTail((CObject*)gex);
		ndexp = ndexp->next;
		while (ndexp != NULL && ndexp->type != XML_ELEMENT_NODE)
			ndexp = root->next;
	}
	xmlFreeDoc(doc);
}

void CExporterList::Save()
{
	if (m_Modified) {

		xmlDocPtr doc = xmlNewDoc((xmlChar*)&EXPORTER_VERSION);
		xmlNodePtr root = xmlNewNode(0, (xmlChar*)&EXPLIST_NAME);
		xmlDocSetRootElement(doc, root);
		POSITION p = GetHeadPosition();
		while (p) {
			CExportGeneric* ex = dynamic_cast<CExportGeneric*>(GetNext(p));
			if (ex) {
				if (CExporterList::IsExternalExporter(ex)) {
					// Only save generic exporter
					xmlNodePtr ndex = xmlNewChild(root, 0, (xmlChar*)&EXPORTER_NAME, 0);
					ex->Save(ndex);
				} else {
					ex->Save(NULL);
				}
			}
		}
#ifdef _UNICODE
		int nLen = _tcslen(m_ListFile);
		char *szFilename = new char[nLen+1];
		int i;
		for (i = 0; i <= nLen; i++)
			szFilename[i] = (char)m_ListFile[i];
		xmlSaveFile(szFilename, doc);
		delete [] szFilename;
#else
		xmlSaveFile(m_ListFile, doc);
#endif
		xmlFreeDoc(doc);

		m_Modified = FALSE;
	}
}

void CExporterList::Clear()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* e = (CExport*)GetNext(p);
		delete e;
	}
	RemoveAll();
}

void CExporterList::Assign(CExporterList *src)
{

}

CString CExporterList::GetFilter()
{
	CString res;
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)GetNext(p);
		CString str = exp->GetFilter();
		if (!str.IsEmpty() && res.Find(str) == -1)
			res += str + "|";
	}
	return res;
}

CExport * CExporterList::GetPreviewExporter()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)GetNext(p);
		if (dynamic_cast<CExportPreview*>(exp))
			return exp;
	}
	return NULL;
}

CExport * CExporterList::GetKeygenExporter()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)GetNext(p);
		if (dynamic_cast<CExportKeygen*>(exp))
			return exp;
	}
	return NULL;
}

BOOL CExporterList::IsExternalExporter(CExport* exp)
{
	return (dynamic_cast<CExportGeneric*>(exp) != NULL && dynamic_cast<CExportInternal*>(exp) == NULL);
}

CExport* CExporterList::GetCopyHtmlExporter()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)GetNext(p);
		if (dynamic_cast<CExportCopyHtml*>(exp))
			return exp;
	}
	return NULL;
}

CExport* CExporterList::GetRtfExporter()
{
	POSITION p = GetHeadPosition();
	while (p) {
		CExport* exp = (CExport*)GetNext(p);
		if (dynamic_cast<CExportRTF*>(exp))
			return exp;
	}
	return NULL;
}
