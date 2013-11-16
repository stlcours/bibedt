// HTMLViewer
//
// © 2004 Karl Runmo ,runmo@hotmail.com
//   - Modified 2006 by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.

#include <windows.h>

#ifdef USE_CXIMAGE
#include "CxImage\ximage.h"
#endif

#ifndef __HTMLVIEWER_H__
#define __HTMLVIEWER_H__

#define DEF_PROP_FONT _T("Times New Roman")
#define DEF_MONO_FONT _T("Courier New")
#define DEF_SANS_FONT _T("MS Sans Serif")

class CHTMLStringVector
{
	char **m_pszStrings;
	int *m_pnStrings;
	int *m_pnIndexValues;
	int m_nStrings;
public:
	CHTMLStringVector();
	~CHTMLStringVector();
	void Clean();
	int AddString(char *szString,int nSize=-1);
	int SetString(int nIndex, char *szString, int nSize=-1);
	char *GetString(int nIndex,int *pnSize=NULL);
	int GetCount();
	int SetCount(int nCount);
	char *operator [] (int nIndex);
	CHTMLStringVector &operator =(CHTMLStringVector &s);
	int MakeIndex(char *szString, int nLenght);
	int GetIndex(int nIndex);
	void DeleteString(int nIndex);

	int MoveString(int nFrom, int nTo);
};
class CHTMLStringTable
{
	CHTMLStringVector **m_pVektors;
	CHTMLStringVector m_err;
	int m_nVektors;
	int m_nRowSize;
public:
	CHTMLStringTable();
	~CHTMLStringTable();
	int AddRow(char **pszRow, int nRow);
	int AddRow();
	int InsertRow(int nRow);
	int AddString(int nRow, char *szString, int nString=-1);
	int DeleteRow(int nRow);
	int SetString(int nRow, int nIndex, char *szString, int nString=-1);
	char* GetString(int nRow, int nIndex,int *pnSize=NULL);
	int GetCount();

	CHTMLStringVector &operator [] (int nRow);
	CHTMLStringTable &operator = (CHTMLStringTable &st);

	int MoveRow(int nFrom, int nTo);

	void Reset();
	int SplitString(char *szData,char *szFieldSep, char *szRowSep);
};

enum TYPES{
	TEXT,
	IMAGE,
	BREAK,
	COMPOUND
};

///////////////////////////////////////////////////////////////////////////////
//
// CHTMLProgress
//
// This class should be implemented by the user of CHTMLViewer.
//
///////////////////////////////////////////////////////////////////////////////
class CHTMLProgress
{
public:
	virtual void Reading(BOOL bImage, int nPos, int nSize) = 0;
	virtual void LinkClicked(char *szLink, int nLink) = 0;
	virtual void SetCursor(BOOL bLink,char *szLink, int nLink) = 0;
	virtual void SetTitle(char *szTitle) = 0;

	virtual char *ReadHTTPData(char *szUrl,int *pnSize) = 0;
	virtual void ImageLoaded(int nDone, int nCount) = 0;

	// Control functions, return -1 if no control support.
	virtual int CreateForm(char *szAction, char *szMethod) = 0;
	virtual int CreateTextBox(int nSize, int nMaxChar,SIZE scSize,char *szText, BOOL bMultiline,char *szName,int nForm,BOOL bPassword) = 0;
	virtual int CreateButton(SIZE scSize,char *szText,char *szName,int nForm) = 0;
	virtual int CreateRadio(SIZE scSize,char *szValue,char *szName,int nForm) = 0;
	virtual int CreateCheckbox(SIZE scSize,char *szValue,char *szName,int nForm) = 0;
	virtual int CreateListbox(SIZE scSize,CHTMLStringTable &stOptions,int nSelected,char *szName,int nForm) = 0;
	virtual void MoveControl(int nControlID, POINT pPos) = 0;

	virtual void UpdateScreen(RECT &r) = 0;
};

class CHTMLBitmaps;
class CHTMLViewer;

class CHTMLItem
{
public:
	int m_nType;
	SIZE m_scBounds;
	POINT m_pPos;
	int m_nFrames;
	int m_nFrameSize;
	COLORREF m_colFrame;
	char m_szFont[100];
	int m_nFontSize;
	int m_nFontBold;
	int m_nFontItalic;
	COLORREF m_colText;
	COLORREF m_colBkg;
	int m_nHFormat;
	int m_nVFormat;
	TCHAR *m_szText;
	int m_nBmp;
	int m_nBmpBkg;
	int m_nRow;
	int m_nCol;
	int m_nColSpan;
	int m_nRowSpan;
	int m_nWidth;
	int m_nTableWidth;
	int m_nTableFrameSize;
	int m_nHeight;
	int m_nTableHeight;
	int m_nCellPadding;
	int m_nCellSpacing;
	int m_nLink;
	HANDLE m_hEvent;
	int m_nMinColumnWidth;
	int m_nAMinColumnWidth;
	int m_nMaxColumnWidth;
	int m_nColumnWidth;
	BOOL m_bSelected;
	BOOL m_bNoBreak;
	int m_nControlID;
	int m_nAbsoluteAlign;
	int m_bClear;

	CHTMLItem **m_ppSubItems;
	int m_nSubItems;

	CHTMLItem();
	~CHTMLItem();

	static void GetStringSize(char *szFont,int nFontSize, int bBold, int bItalic, SIZE *sc,char *szString,int nMaxWidth,int nLen);
	void Offset(int nX, int nY);
	// Text-object
	static CHTMLItem *NewText(char *szText,int nFrames,int nFrameSize, COLORREF colFrame,char *szFont,int nFontSize,
		int nFontBold,int nFontItalic,COLORREF colText,COLORREF colBkg,int nHFormat,int nVFormat,int nLink,BOOL bNoBreak);
	// Image-object
	static CHTMLItem *NewImage(char *szImageName, int nFrames, int nFrameSize, COLORREF colFrame,int nHFormat,CHTMLBitmaps &Images,int nLink,BOOL bNoBreak,BOOL bBackground,int nBorder);
	// Break-object
	static CHTMLItem *NewBreak(int nHeight,int nWidth,int nHFormat,int bClear);
	// Compound-object
	static CHTMLItem *NewCompound(int nRow, int nCol, int nWidth,int nHFormat,int nVFormat, COLORREF colBkg,BOOL bBorder,int nColSpan,int nRowSpan,int nCellPadding,int nCellSpacing,int nTableWidth,int nBmpBkg,int nHeight,int nTableHeight,COLORREF colBorder,int nAbsoluteAlign);

	BOOL WaitForImage(CHTMLBitmaps &Images,BOOL bWaitForImages);
};

class CHTMLBitmap
{
	BOOL m_bEmptyBitmap;
#ifdef USE_CXIMAGE
	CxImage *m_pImage;
	int m_nImages;
	int m_nCurrImage;
	CxImage **m_pImages;
	int *m_pnFrameDelay;
#else
	HBITMAP m_bmBmp;
#endif
	int m_nCounter;
	char *m_szImageName;
	char *m_szImageData;
	int m_nImageData;
	HANDLE m_hDone;
	SIZE m_Size;
	CHTMLProgress *m_pProgress;
	CHTMLBitmaps *m_pParent;
	BOOL m_bLoaded;
	BOOL m_bBackground;
public:
	CHTMLBitmap(char *szImageName,CHTMLProgress *pProgress,CHTMLBitmaps *pParent,BOOL bBackground);
	~CHTMLBitmap();

	void LoadBitmap();

	char *GetImageName();
	BOOL GetBackground();
	BOOL GetBitmap(BOOL bWaitForImage=FALSE);
	BOOL IsEmptyBitmap();
	BOOL IsLoaded();
	BOOL IsCreated();
	void DestroyBitmap();
	void GetSize(SIZE &sc);
	int Width();
	int Height();
	void BitBlt(HDC hDC, int x, int y, int wx=-1, int wy=-1);
	void StretchBlt(HDC hDC,int x, int y, int wx, int wy);

	int TimerTick();
};
class CHTMLBitmaps
{
	CHTMLBitmap **m_ppBitmaps;
	int m_nBitmaps;
	CHTMLProgress *m_pProgress;
	CHTMLViewer *m_pViewer;

	HBITMAP m_bmEmpty;
	long m_nDownloads;
	HANDLE m_hMutex;
	BOOL m_bStop;
public:
	CHTMLBitmaps(CHTMLProgress *pProgress);
	~CHTMLBitmaps();

	void SetViewer(CHTMLViewer *pViewer);

	int GetCount();
	int AddBitmap(char *szImageName,BOOL bBackground);
	CHTMLBitmap &operator[](int nIndex);
	void ImageLoaded();

	HBITMAP GetEmptyBitmap();
	void WaitForDownload();

	void ThTimer();
	void Stop();
};
class CHTMLViewer
{
	int m_nItemCount;
	int m_nLevelCount;
	CHTMLItem **m_ppItems;
	int m_nItems;
	CHTMLProgress *m_pProgress;
	CHTMLBitmaps m_Images;
	CHTMLStringTable m_Links;
	COLORREF m_bgCol;
	int m_nBmpBkg;
	int m_nActiveLink;
	int m_nListLevel;
	int m_nCurrForm;
	BOOL m_bReading;
	BOOL m_bWaitForImages;
	char *m_FontProp;
	char *m_FontFixed;
	char *m_FontSans;

	void AddItem(CHTMLItem **&ppItems, int &nItems);

	void AddHTML(char *szHTMLData, CHTMLItem **&ppItems, int &nItems, char *szFont,
		int nFontSize,COLORREF colText,char *szBaseUrl,int nLevel,int nHFormat,BOOL bNoBreak);
	void CalcPositions(RECT &rPos, CHTMLItem **&ppItems, int &nItems);
	void Draw(HDC hDC, RECT &r, CHTMLItem **&ppItems, int &nItems,int nX, int nY);
	int OnMouseOver(CHTMLItem **&ppItems, int &nItems,int nX, int nY,BOOL bClick);

	void GetProperties(char *szData,CHTMLStringTable &st);
	COLORREF GetCol(char *szData);
	void AdjustHR(int nWidth, CHTMLItem **&ppItems, int &nItems);
	void Select(RECT &r,CHTMLItem **&ppItems, int &nItems);
	void CopySelected(CHTMLItem **&ppItems, int &nItems,char *&szCopy,int &nLen);
	void UpdateImage(CHTMLItem **&ppItems, int &nItems,int nImage);
	void UpdateLink(CHTMLItem **&ppItems, int &nItems,int nLink);
public:
	char *GetFontProp() { return m_FontProp; }
	void SetFontProp(char *val) { 
		m_FontProp = (char*)realloc(m_FontProp, strlen(val) + 1);
		strcpy(m_FontProp, val); 
	}
	char *GetFontFixed() { return m_FontFixed; }
	void SetFontFixed(char *val) { 
		m_FontFixed = (char*)realloc(m_FontFixed, strlen(val) + 1);
		strcpy(m_FontFixed, val); 
	}
	char *GetFontSans() { return m_FontSans; }
	void SetFontSans(char *val) { 
		m_FontSans = (char*)realloc(m_FontSans, strlen(val) + 1);
		strcpy(m_FontSans, val); 
	}
	void SelectItem(CHTMLItem **&ppItems, int &nItems);
	void SelectAll();
	int GetItemsCount();
	BOOL IsSelected(CHTMLItem **&ppItems, int &nItems);
	void Unselect(CHTMLItem **&ppItems, int &nItems);
	void Unselect();
	BOOL HasSelection();
	CHTMLViewer(CHTMLProgress *pProgress,BOOL bWaitForImages=FALSE);
	~CHTMLViewer();
	void SetHTML(char *szHTMLData,char *szFont,int nFontSize,COLORREF colText,char *szBaseUrl);
	void CalcPositions(RECT &rPos);
	void Draw(HDC hDC,RECT &r, int nX, int nY);

	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);

	void Statistics(int &nItems, int &nImages,int &nLinks,int &nLevel);
	void Select(RECT &r);
	void CopySelected();

	void AddBaseToUrl(char *szUrl,char *szFullUrl,char *szBase);

	void UpdateImage(int nImage);
	void UpdateLink(int nLink);
	BOOL IsReading();
protected:
};

#endif