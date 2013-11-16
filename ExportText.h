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

  $Id: ExportText.h,v 1.11 2006/04/08 19:34:26 stievie Exp $
*/

// ExportText.h: Schnittstelle für die Klasse CExportText.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTTEXT_H__FB7CA40A_CC68_4E81_836A_F7825BCFB213__INCLUDED_)
#define AFX_EXPORTTEXT_H__FB7CA40A_CC68_4E81_836A_F7825BCFB213__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Export.h"

/**
 * \brief The Text exporter.
 * 
 * The class to export a subset of the loaded file as plain text.
 */
class CExportText : public CExport  
{
public:
	virtual CExport* Clone();
	virtual CString GetSource();
	virtual CString GetExt();
	virtual CString GetFilter();
	virtual void DoExport(CString filename);
	virtual CString GetItemSource(CBibItem* item);
	CExportText();
	virtual ~CExportText();

};

#endif // !defined(AFX_EXPORTTEXT_H__FB7CA40A_CC68_4E81_836A_F7825BCFB213__INCLUDED_)
