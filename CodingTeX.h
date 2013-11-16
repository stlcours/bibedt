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

  $Id: CodingTeX.h,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

// CodingTeX.h: Schnittstelle für die Klasse CCodingTeX.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODINGTEX_H__5935D4B3_4D2D_4A3B_A15B_04B9E0716E43__INCLUDED_)
#define AFX_CODINGTEX_H__5935D4B3_4D2D_4A3B_A15B_04B9E0716E43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coding.h"

/**
 * \brief Does the conversion fron/to TeX
 */
class CCodingTeX : public CCoding  
{
public:
	CCodingTeX();
	virtual ~CCodingTeX();
	CString GetString(UCHAR c);
	CString Encode(CString src);
	CString Decode(CString src);

};

#endif // !defined(AFX_CODINGTEX_H__5935D4B3_4D2D_4A3B_A15B_04B9E0716E43__INCLUDED_)
