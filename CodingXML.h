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

  $Id: CodingXML.h,v 1.1 2005/10/09 18:47:05 stievie Exp $
*/

// CodingXML.h: Schnittstelle für die Klasse CCodingXML.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODINGXML_H__1DD1036C_14E3_4635_9C0B_7164C6B2BDF5__INCLUDED_)
#define AFX_CODINGXML_H__1DD1036C_14E3_4635_9C0B_7164C6B2BDF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coding.h"

class CCodingXML : public CCoding  
{
public:
	CString Decode(CString src);
	CString Encode(CString src);
	CCodingXML();
	virtual ~CCodingXML();

};

#endif // !defined(AFX_CODINGXML_H__1DD1036C_14E3_4635_9C0B_7164C6B2BDF5__INCLUDED_)
