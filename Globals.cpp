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

  $Id: Globals.cpp,v 1.35 2006/08/13 15:50:03 stievie Exp $
*/

#include "stdafx.h"
#include "Globals.h"
#include "bibedt.h"

BOOL IsNT()
{
	static DWORD platformid = 0;
	if (platformid == 0) {
		OSVERSIONINFO version;
		version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		::GetVersionEx(&version);
		platformid = version.dwPlatformId;
	}
	return (platformid == VER_PLATFORM_WIN32_NT);
}

BOOL IsXP()
{
	static DWORD major = 0, minor = 0, platformid = 0;
	if (major == 0) {
		OSVERSIONINFO version;
		version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		::GetVersionEx(&version);
		major = version.dwMajorVersion;
		minor = version.dwMinorVersion;
		platformid = version.dwPlatformId;
	}
	return (platformid == VER_PLATFORM_WIN32_NT && major >= 5 && minor >= 1);
}

BOOL ShellExec(CString file)
{
	BOOL succ = (DWORD)ShellExecute(0, _T("open"), file, NULL, NULL, SW_NORMAL) > HINSTANCE_ERROR;
	if (!succ) {
		// Try notepad
		succ = (DWORD)ShellExecute(0, _T("open"), _T("notepad.exe"), DecodeFilename(file), NULL, SW_NORMAL) > HINSTANCE_ERROR;
	}
	return succ;
}

void MakeValidKey(CString* key)
{
	for (int i = key->GetLength()-1; i >= 0; i--) {
		TCHAR c = key->GetAt(i);
		//     0x2A   -   0x7E
		if (c < _T('*') || c > _T('{') || c == _T(','))
			key->Delete(i);
	}
}

CString EncodeFilename(CString filename)
{
	CString res(filename);
	res.Replace(_T("\\"), _T("/"));
	if (res.GetAt(1) == ':') {
		// Absolute
		res = _T("file:///") + res;
	}
	return res;
}

CString DecodeFilename(CString filename)
{
	CString res(filename);
	if (res.Left(8).CompareNoCase(_T("file:///")) == 0)
		res.Delete(0, 8);
	res.Replace(_T("/"), _T("\\"));
	return res;
}

CBibDef * GetBibDef()
{
	return ((CBibedtApp*)AfxGetApp())->m_BibDef;
}

void Capitalize(CString &str)
{
	str.MakeLower();
	TCHAR c = str.GetAt(0);
	if (c > 96 && c < 128)
		str.SetAt(0, c - _T('a') + _T('A'));
}

CString AfxLoadString(UINT nID)
{
	CString szText;
	if (szText.LoadString(nID))
		return szText;
	else
		return _T("");
}

/**
 * Replaces non-printable characters with symbols.
 */
CString BeautifyValue(CString val)
{
	val.Replace(_T("\r\n"), _T("¶"));
	val.Replace(_T("\t"), _T("»"));
	return val;
}

DWORD SplitSepString(CString url, CStringList* lst)
{
	DWORD c = 0;
	int ps = 0;
	int pe = -1;
	CString str;
	lst->RemoveAll();
	do {
		pe = url.Find(_T(";"), ps+1);
		if (pe == -1)
			str = url.Mid(ps, url.GetLength() - ps);
		else
			str = url.Mid(ps, pe - ps);
		str.TrimLeft();
		str.TrimRight();
		lst->AddTail(str);
		ps = pe + 1;
		c++;
	} while (pe != -1);
	return c;
}

void ShowError(CString msg)
{
	AfxMessageBox(msg, MB_ICONEXCLAMATION, 0);
}

void ShowError(UINT nID)
{
	AfxMessageBox(nID, MB_ICONEXCLAMATION, 0);
}

CString ChangeFileExt(CString fn, CString ext)
{
	int i = fn.ReverseFind(_T('.'));
	CString res;
	if (i > -1)
		res = fn.Mid(0, i) + ext;
	else
		res = fn + ext;
	return res;
}

BOOL ClipBrdPutData(CWnd *owner, CString data, DWORD format, BOOL empty)
{
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	if (!owner)
		owner = pApp->GetMainWnd();

	if (!OpenClipboard(owner->m_hWnd))
		return FALSE;
	if (empty && !EmptyClipboard()) {
		CloseClipboard();
		return FALSE;
	}
	HGLOBAL hMem;
	if (format != CB_HTML)
		hMem = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, data.GetLength()+1);
	else
		hMem = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, data.GetLength()+400);
	if (hMem == NULL) {
		CloseClipboard();
		return FALSE;
	}
	TCHAR* m = (TCHAR*)GlobalLock(hMem);
	if (m == NULL) {
		CloseClipboard();
		return FALSE;
	}
	if (format == CB_HTML) {
		// http://msdn.microsoft.com/workshop/networking/clipboard/htmlclipboard.asp
		// http://support.microsoft.com/kb/q274308/
		// Create a template string for the HTML header...
		_tcscpy(m,
			_T("Version:0.9\r\n")
			_T("StartHTML:00000000\r\n")
			_T("EndHTML:00000000\r\n")
			_T("StartFragment:00000000\r\n")
			_T("EndFragment:00000000\r\n")
			_T("<html><body>\r\n")
			_T("<!--StartFragment -->\r\n"));
		// Append the HTML...
		_tcscat(m, (LPCTSTR)data);
		_tcscat(m, _T("\r\n"));
		// Finish up the HTML format...
		_tcscat(m,
			_T("<!--EndFragment-->\r\n")
			_T("</body>\r\n")
			_T("</html>"));

		// Now go back, calculate all the lengths, and write out the
		// necessary header information. Note, wsprintf() truncates the
		// string when you overwrite it so you follow up with code to replace
		// the 0 appended at the end with a '\r'...
		TCHAR *ptr = _tcsstr(m, _T("StartHTML"));
		wsprintf(ptr+10, _T("%08u"), _tcsstr(m, _T("<html>")) - m);
		*(ptr+10+8) = _T('\r');

		ptr = _tcsstr(m, _T("EndHTML"));
		wsprintf(ptr+8, _T("%08u"), _tcsclen(m));
		*(ptr+8+8) = _T('\r');

		ptr = _tcsstr(m, _T("StartFragment"));
		wsprintf(ptr+14, _T("%08u"), _tcsstr(m, _T("<!--StartFrag")) - m);
		*(ptr+14+8) = _T('\r');

		ptr = _tcsstr(m, _T("EndFragment"));
		wsprintf(ptr+12, _T("%08u"), _tcsstr(m, _T("<!--EndFrag")) - m);
		*(ptr+12+8) = _T('\r');

		// Now you have everything in place ready to put on the
		// clipboard.
	} else
		_tcscpy(m, (LPCTSTR)data);
	GlobalUnlock(m);
	if (format == CB_TEXT)
		SetClipboardData(CF_TEXT, m);
	else if (format == CB_RTF)
		SetClipboardData(pApp->GetRtfClipbrdFormat(), m);
	else if (format == CB_HTML) {
		SetClipboardData(pApp->GetHtmlClipbrdFormat(), m);
	} else if (format == CB_BIB)
		SetClipboardData(pApp->GetBibClipbrdFormat(), m);
	
	CloseClipboard();

	return TRUE;
}

CString ClipBrdGetData(CWnd *owner, DWORD format)
{
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	if (!owner)
		owner = pApp->GetMainWnd();

	if (!OpenClipboard(owner->m_hWnd))
		return _T("");
	HANDLE cd;
	if (format == CB_BIB)
		cd = GetClipboardData(pApp->GetBibClipbrdFormat());
	else
		cd = GetClipboardData(CF_TEXT);
	CString res;
	if (cd) {
		int size = GlobalSize(cd);
		if (size == 0) {
			CloseClipboard();
			return _T("");
		}
		LPVOID m = GlobalLock(cd);
		if (m == NULL) {
			CloseClipboard();
			return _T("");
		}

		TCHAR *buff = new TCHAR[size];
		memcpy(buff, m, size);
		GlobalUnlock(m);
		res = buff;
		delete [] buff;
	}
	CloseClipboard();
	return res;
}

/**
 * Extracts the last names from an author or editor string
 */
CString ExtractLastNames(CString str, TCHAR delimiter)
{
/* BUG: Foo Bar Jr. does not work, where Bar is the last name
   However, this should be written as Foo {Bar Jr.}, but this 
   doesn't work either...

   Well, test it now!
*/
	// First Last and some one and ...
	CString res;
	int p = str.Find(_T(" and "), 0);
	int p2;
	TCHAR c;
	CString an;
	int brackets = 0;
	while (p > -1) {
		p2 = p - 1;
		an.Empty();
		while (p2 >= 0) {
			c = str.GetAt(p2--);
			if (c == _T(' ') && !brackets)
				break;
			else if (c == _T('}'))
				brackets++;
			else if (c == _T('{'))
				brackets--;
			else
				an = c + an;
		}
		p = str.Find(_T(" and "), p+1);
		if (p > -1)
			an += delimiter;
		res += an;
	}
	brackets = 0;
	CString last;
	p = str.GetLength();
	if (p) {
		an.Empty();
		if (!res.IsEmpty())
			res += delimiter;
		p2 = p - 1;
		while (p2 >= 0) {
			c = str.GetAt(p2--);
			if (c == _T(' ') && !brackets)
				break;
			else if (c == _T('}'))
				brackets++;
			else if (c == _T('{'))
				brackets--;
			else
				an = c + an;
		}
		res += an;
	}
	return res;
}

/**
 * Replace all _and_ except the last with ,_
 */
CString FormatAuthors(CString str)
{
	CString res = str;
	int p = res.Find(_T(" and "), 0);
	while (p > -1) {
		if (res.Find(_T(" and "), p+5) > -1) {
			res.Delete(p, 5);
			res.Insert(p, _T(", "));
		} else
			break;
		p = res.Find(_T(" and "), 0);
	}
	res.Remove(_T('{'));
	res.Remove(_T('}'));
	return res;
}

/**
 * Remove double quotes at the begin and end of a string.
 */
CString RemoveQuotes(CString str)
{
	CString res = str;
	while (res.Left(1) == _T("\"") && res.Right(1) == _T("\"")) {
		res.Delete(0, 1);
		res.Delete(str.GetLength()-2, 1);
	}
	return res;
}

/**
 * Remove curly brackets at the begin and end of a string.
 */
CString RemoveBrackets(CString str)
{
	CString res = str;
	while (res.Left(1) == _T("{") && res.Right(1) == _T("}")) {
		res.Delete(0, 1);
		res.Delete(str.GetLength()-2, 1);
	}
	return res;
}

/**
 * Remove Quotes and bracktes.
 */
CString RemoveGarbage(CString str)
{
	CString res = RemoveQuotes(str);
	res = RemoveBrackets(res);
	res = RemoveQuotes(res);
	return res;
}

/**
 * \brief Create a backup copy of a file.
 *
 * Backups a file with the extension .~ext
 *
 * \param filename The name of the file to copy.
 */
BOOL BackupFile(CString filename)
{
	CString fn = filename;
	CString ext = _T("bib");
	int i = fn.ReverseFind(_T('.'));
	if (i != -1) {
		ext = fn.Right(fn.GetLength() - i - 1);
		fn.Delete(i, fn.GetLength() - i);
	}
	fn += _T(".~") + ext;
	try {
		CopyFile(filename, fn, FALSE);
	} catch (...) { 
		return FALSE;
	}
	return TRUE;
}
