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

  $Id: ExporterList.h,v 1.7 2006/08/12 16:06:17 stievie Exp $
*/

// ExporterList.h: Schnittstelle für die Klasse CExporterList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTERLIST_H__C69C190E_2CBD_45E2_AE73_B505AFD11207__INCLUDED_)
#define AFX_EXPORTERLIST_H__C69C190E_2CBD_45E2_AE73_B505AFD11207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibEdtList.h"
#include "ExportPreview.h"

static const char EXPORTER_VERSION[] = "1.0";
static const char EXPLIST_NAME[] = "explist";
static const char EXPORTER_NAME[] = "exporter";

class CExporterList : public CBibEdtList  
{
public:
	CExport * GetKeygenExporter();
	CExport* GetRtfExporter();
	CExport* GetCopyHtmlExporter();
	static BOOL IsExternalExporter(CExport* exp);
	CExport * GetPreviewExporter();
	CString GetFilter();
	CString m_ListFile;
	virtual void Assign(CExporterList* src);
	void Clear();
	void Save();
	void Load(BOOL force = FALSE);
	CExporterList();
	virtual ~CExporterList();

protected:
	BOOL m_Loaded;
};

#endif // !defined(AFX_EXPORTERLIST_H__C69C190E_2CBD_45E2_AE73_B505AFD11207__INCLUDED_)
