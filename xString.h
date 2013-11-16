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

  $Id: xString.h,v 1.10 2006/06/06 18:52:19 stievie Exp $
*/

#ifndef _XSTRING_H
#define _XSTRING_H

#include <stdlib.h>
#include <limits.h>

#define xsValue(xs) ((xs)->buff)
#define xsTerminate(xs) (xsPut((xs), _T('\0')))
#define xsTerminated(xs) (xs->buff[xs->length+1] == _T('\0'))
#define xsLen(xs) ((xs)->length)
#define xsSize(xs) ((xs)->size)
#define xsGrow(xs,by) (xsResize(xs, xs->size + by))
#define xsChar(xs,i) ((xs)->buff[i])
#define xsRightChar(xs) (xsChar(xs, xs->length-1))
#define xsCopy(xs,xss) (xsCopy(xs, xss->buff))
#define xsCat(xs,xss) (xsCatS(xs, xss->buff))
#define xsNewInit(xs) (xsNewInit(xs->buff))
#define xsIsSpaceC(c) ((c == _T('\n') || c == _T('\r') || c == _T('\t') || c == _T(' ') || c == _T('\f')))
#define xsIsSpace(xs,i) (xsIsSpaceC(xs->buff[i]))
#define xsIsEmpty(xs) (xs->length == 0)
#define xsCompareS(xs,s) (_tcscmp(xs->buff, s))
#define xsICompareS(xs,s) (_tcsicmp(xs->buff, s))
#define xsCompare(xs1,xs2) (_tcscmp(xs1->buff, xs2->buff))
#define xsICompare(xs1,xs2) (_tcsicmp(xs1->buff, xs2->buff))

typedef struct _XSTRING {
	size_t length;      /**< Size used */
	size_t size;        /**< Size allocated */
	TCHAR* buff;         /**< The buffer */
} xString;

// Prototypes
BOOL xsResize(xString *const str, const size_t newsize);
BOOL xsAutoSize(xString *const str);
void xsPut(xString *const str, TCHAR c);
void xsDelete(xString *const str);
void xsClear(xString *const str);
xString* xsNew();
void xsCatS(xString *const str, const TCHAR *const s);
xString* xsNewInitS(const TCHAR *const s);
void xsCopyS(xString *const str, const TCHAR *const s);
void xsTrimRight(xString *const str);
void xsTrimLeft(xString *const str);
void xsTrim(xString *const str);
void xsToUpper(xString *const str);
void xsToLower(xString *const str);

#endif // !_XSTRING_H
