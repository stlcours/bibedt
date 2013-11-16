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

  $Id: CodingRTF.h,v 1.4 2005/08/22 23:32:33 stievie Exp $
*/

// CodingRTF.h: Schnittstelle für die Klasse CCodingRTF.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODINGRTF_H__5A47C338_76FC_48A6_B75B_1F49E4BDC7AA__INCLUDED_)
#define AFX_CODINGRTF_H__5A47C338_76FC_48A6_B75B_1F49E4BDC7AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coding.h"

/**
 * \brief Does the conversion to RTF.
 */
class CCodingRTF : public CCoding  
{
public:
	CCodingRTF();
	virtual ~CCodingRTF();
	CString Encode(CString src);
	CString Decode(CString src);

};

#endif // !defined(AFX_CODINGRTF_H__5A47C338_76FC_48A6_B75B_1F49E4BDC7AA__INCLUDED_)
