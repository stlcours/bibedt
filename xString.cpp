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

  $Id: xString.cpp,v 1.10 2006/06/06 18:52:19 stievie Exp $
*/

#include <string.h>
#include "stdafx.h"
#include "xString.h"

#define XS_INIT_SIZE 32

/**
 * Resize the string to newsize.
 * Returns TRUE on success otherwise FALSE.
 */
BOOL xsResize(xString *const str, const size_t newsize)
{
	TCHAR* newBuff = (TCHAR*)realloc(str->buff, newsize);
	if (!newBuff) {
#ifdef _DEBUG
		TRACE0("No memory\n");
#endif
		return FALSE;
	}
	str->size = newsize;
	str->buff = newBuff;
	return TRUE;
}

/**
 * Increases the size of the string
 */
BOOL xsAutoSize(xString *const str)
{
	if (str->size <= INT_MAX) {
		return xsResize(str, str->size * 2);
	}
#ifdef _DEBUG
		TRACE0("String size exceeds 2 GB\n");
#endif
	return FALSE;
}

void xsPut(xString *const str, TCHAR c)
{
	if (str->size == str->length)
		xsAutoSize(str);
	str->buff[str->length] = c;
	if (c)
		str->length++;
}

/**
 * Frees the allocated memory
 */
void xsDelete(xString *const str)
{
	if (str) {
		if (str->buff)
			free(str->buff);
		free(str);
	}
}

void xsClear(xString *const str)
{
	str->buff[0] = _T('\0');
	str->length = 0;
}

/**
 * Allocates a new string. All strings must be freed with xsDelete
 */
xString* xsNew()
{
	xString *const str = (xString*)malloc(sizeof(xString));
	str->size = XS_INIT_SIZE;
	str->buff = (TCHAR*)malloc((size_t)(XS_INIT_SIZE * sizeof(TCHAR)));
	xsClear(str);
	return str;
}

/**
 * Concatenates two strings
 */
void xsCatS(xString *const str, const TCHAR *const s)
{
	const size_t len = _tcsclen(s);
	if (str->length + len >= str->size)
		xsGrow(str, len + 1);
	_tcscpy(str->buff + str->length, s);
	str->length += len;
}

/**
 * Allocates a new string with an initial value
 */
xString* xsNewInitS(const TCHAR *const s)
{
	xString* str = xsNew();
	xsCatS(str, s);
	return str;
}

void xsCopyS(xString *const str, const TCHAR *const s)
{
	xsClear(str);
	xsCatS(str, s);
}

void xsTrimRight(xString *const str)
{
	while (xsIsSpaceC(xsRightChar(str)) && str->length > 0) {
		str->length--;
	}
}

void xsTrimLeft(xString *const str)
{
	while (xsIsSpace(str, 0) && str->length > 0) {
		for (size_t i = 1; i < str->length; i++) {
			str->buff[i-1] = str->buff[i];
		}
		str->length--;
	}
}

void xsTrim(xString *const str)
{
	xsTrimLeft(str);
	xsTrimRight(str);
}

void xsToUpper(xString *const str)
{
	for (size_t i = 0; i < str->length; i++) {
		str->buff[i] = _toupper(str->buff[i]);
	}
}

void xsToLower(xString *const str)
{
	for (size_t i = 0; i < str->length; i++) {
		str->buff[i] = _tolower(str->buff[i]);
	}
}
