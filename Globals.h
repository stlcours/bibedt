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

  $Id: Globals.h,v 1.35 2006/08/05 16:10:27 stievie Exp $
*/

#if !defined(AFX_GLOBALS_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_)
#define AFX_GLOBALS_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibDef.h"

#define MAX_CHAR      256
// Maximum items in search dialogs
#define MAX_HISTORY   10

// URL where the manual can be downloaded
static const TCHAR MANUAL_URL[]   = _T("http://sourceforge.net/project/showfiles.php?group_id=142263&package_id=161101");

// Link protocolls
static const TCHAR STR_BIBPROTOCOLL[] = _T("bib://");
static const TCHAR STR_DOIPROTOCOLL[] = _T("doi:");

/**
 * This struct is needed to sort the ListView.
 * It is sent as lParamSort to CBibedtView::ListViewSortProc()
 */
typedef struct _LVSORTPARAM{	
	CListCtrl *pListView;	// The list control to be sorted.	
	int iHeader;			// The column.	
	BOOL bSortAsc;			// Sort ascendending or descendending
} LVSORTPARAM, *PLVSORTPARAM;

// For ComCtrl Version >= 6 (XP)
#if !defined(LVM_SETSELECTEDCOLUMN)
#	define LVM_SETSELECTEDCOLUMN (LVM_FIRST + 140)
#endif
#if !defined(HDF_SORTDOWN)
#	define HDF_SORTDOWN 0x0200
#endif
#if !defined(HDF_SORTUP)
#	define HDF_SORTUP 0x0400
#endif

#if !defined(BIF_USENEWUI)
#	define BIF_USENEWUI 0x0040
#endif

/**
 * Clipboard formats.
 */
#define CB_TEXT 1 << 0
#define CB_BIB  1 << 1
#define CB_RTF  1 << 2
#define CB_HTML 1 << 3

#define CF_BIB   _T("BIB_Clipboard_Format")
#define CF_HTML  _T("HTML Format")

// Maximum characters in a line
const MAX_LINE = 80;
// Whitespace characters
const TCHAR WHITESPACE[] = _T(" \t\r\n.,;:\"!?(){}[]");

// bit mask operations
#define BIT_SET(x, mask) \
    (((x) & (mask)) != 0)
#define SET_BIT(x, mask) \
    (x) |= (mask)
#define UNSET_BIT(x, mask) \
    (x) &= ~(mask)

#define NL _T("\r\n")

#ifdef _DEBUG
#	define NOT_IMPL TRACE2("Call to not implemented method in file %s, line %d!\n", __FILE__, __LINE__)
#else
#	define NOT_IMPL
#endif

// Global function
UINT RegisterClipbrdFormat();
UINT GetClipbrdFormat();
CBibDef * GetBibDef();
CString AfxLoadString(UINT nID);
CString BeautifyValue(CString val);
void ShowError(CString msg);
void ShowError(UINT nID);
CString ChangeFileExt(CString fn, CString ext);
BOOL ClipBrdPutData(CWnd *owner, CString data, DWORD format, BOOL empty);
CString ClipBrdGetData(CWnd *owner, DWORD format);
CString ExtractLastNames(CString str, TCHAR delimiter);
CString RemoveQuotes(CString str);
CString RemoveBrackets(CString str);
CString RemoveGarbage(CString str);
CString FormatAuthors(CString str);
BOOL BackupFile(CString filename);
DWORD SplitSepString(CString url, CStringList* lst);
void Capitalize(CString &str);
BOOL ShellExec(CString file);
CString EncodeFilename(CString filename);
CString DecodeFilename(CString filename);
void MakeValidKey(CString* key);
BOOL IsXP();
BOOL IsNT();

#endif // !defined(AFX_GLOBALS_H__5D500F4E_D579_4707_9D1B_4CAAC7A4872E__INCLUDED_)
