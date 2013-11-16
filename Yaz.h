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

  $Id: Yaz.h,v 1.5 2006/06/06 18:52:19 stievie Exp $
*/

#ifndef _YAZ_H
#define _YAZ_H

typedef enum YC_SYNTAX {
	YCS_UNKNOWN, YCS_GRS1, YCS_SUTRS, YCS_USMARC, YCS_UKMARC, 
	YCS_DKMARC, YCS_XML, YCS_OPAC
};

static const TCHAR YCSS_UNKNOWN[] = _T("UNKNOWN");
static const TCHAR YCSS_GRS1[] = _T("GRS-1");
static const TCHAR YCSS_SUTRS[] = _T("SUTRS");
static const TCHAR YCSS_USMARC[] = _T("USMARC");
static const TCHAR YCSS_UKMARC[] = _T("UKMARC");
static const TCHAR YCSS_DKMARC[] = _T("DKMARC");
static const TCHAR YCSS_XML[] = _T("XML");
static const TCHAR YCSS_OPAC[] = _T("OPAC");

typedef enum QUERY_TYPE {
	QT_UNKNOWN, QT_PREFIX, QT_CQL, QT_CCL
};

#endif // !_YAZ_H