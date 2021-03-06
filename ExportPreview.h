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

  $Id: ExportPreview.h,v 1.3 2006/05/25 14:15:46 stievie Exp $
*/

// ExportPreview.h: Schnittstelle f�r die Klasse CExportPreview.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTPREVIEW_H__C164016A_8586_4610_84B7_4A13C19EF085__INCLUDED_)
#define AFX_EXPORTPREVIEW_H__C164016A_8586_4610_84B7_4A13C19EF085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExportInternal.h"

class CExportPreview : public CExportInternal  
{
public:
	virtual CExport* Clone();
	virtual CString EncodeString(CString str, BOOL rs);
	virtual void Save(xmlNodePtr node);
	virtual void Load(xmlNodePtr node);
	virtual CString GetSource();
	CExportPreview();
	virtual ~CExportPreview();
};

#endif // !defined(AFX_EXPORTPREVIEW_H__C164016A_8586_4610_84B7_4A13C19EF085__INCLUDED_)
