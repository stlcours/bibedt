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

  $Id: bibedtView.cpp,v 1.114 2006/08/09 07:35:05 stievie Exp $
*/

// bibedtView.cpp : Implementierung der Klasse CBibedtView
//

#include <afxole.h>
#include <commctrl.h>

#include "stdafx.h"
#include "bibedt.h"
#include "MainFrm.h"

#include "bibedtView.h"
#include "BibedtDoc.h"
#include "BibFile.h"
#include "SearchDialog.h"
#include "Globals.h"
#include "Options.h"
#include "SourceDialog.h"
#include "CopyCitationDialog.h"
#include "ColumnsDialog.h"
#include "ExportRTF.h"
#include "ExportGeneric.h"
#include "FindDuplicatesDialog.h"
#include "FindDupOptionsDialog.h"
#include "ExportDialog.h"
#include "ExportCopyHtml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBibedtView

IMPLEMENT_DYNCREATE(CBibedtView, CListView)

BEGIN_MESSAGE_MAP(CBibedtView, CListView)
	//{{AFX_MSG_MAP(CBibedtView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_COMMAND(ID_VIEW_GRIDLINES, OnViewGridlines)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRIDLINES, OnUpdateViewGridlines)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_EDIT_COPYCITATION, OnEditCopycitation)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYCITATION, OnUpdateEditCopycitation)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_VIEW_COLUMNS, OnViewColumns)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND, OnUpdateSearchFind)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFilePrint)
	ON_COMMAND(ID_SEARCH_FINDNEXT, OnSearchFindnext)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FINDNEXT, OnUpdateSearchFindnext)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_WM_DRAWITEM()
	ON_UPDATE_COMMAND_UI(ID_SEARCH_TOGGLEBOOKMARK, OnUpdateSearchTogglebookmark)
	ON_COMMAND(ID_SEARCH_TOGGLEBOOKMARK, OnSearchTogglebookmark)
	ON_COMMAND(ID_SEARCH_CLEARBOOKMARKS, OnSearchClearbookmarks)
	ON_COMMAND(ID_SEARCH_NEXTBOOKMARK, OnSearchNextbookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_NEXTBOOKMARK, OnUpdateSearchNextbookmark)
	ON_COMMAND(ID_SEARCH_PREVIOUSBOOKMARK, OnSearchPreviousbookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_PREVIOUSBOOKMARK, OnUpdateSearchPreviousbookmark)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FINDDUPLICATE, OnUpdateSearchFindduplicate)
	ON_COMMAND(ID_SEARCH_FINDDUPLICATE, OnSearchFindduplicate)
	ON_COMMAND(ID_SEARCH_FIND, OnSearchFind)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_CLEARBOOKMARKS, OnUpdateSearchClearbookmarks)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_RECORD_GENERATEKEY, OnRecordGeneratekey)
	ON_UPDATE_COMMAND_UI(ID_RECORD_GENERATEKEY, OnUpdateRecordGeneratekey)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBibedtView Konstruktion/Destruktion

CBibedtView::CBibedtView()
{
	CBibedtApp * pApp = (CBibedtApp*)AfxGetApp();
	m_SearchFields = pApp->m_Options->m_QuickSearchFields;
	m_SearchRegExpr = FALSE;
	m_SearchMatchCase = FALSE;
	m_SearchSelOnly = FALSE;
	m_SearchWholeWords = FALSE;
	m_CiteFormat = -1;
	m_SortCol = -1;
	m_SortIndicator.Create(IDB_BITMAP_HEADER_SORT, 10, 2, RGB(255, 0, 255));
	m_ImageList.Create(IDB_BITMAP_LISTVIEW, 16, 1, RGB(255, 0, 255));
	VERIFY(m_PopupMenu.LoadMenu(IDR_MENU_LISTVIEW));
}

CBibedtView::~CBibedtView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBibedtView Zeichnen

void CBibedtView::OnDraw(CDC* pDC)
{
	CBibedtDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

void CBibedtView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// Initialize printing
	m_Print.SetListCtrl(&GetListCtrl());
	m_Print.SetView(this);
}

/////////////////////////////////////////////////////////////////////////////
// CBibedtView Drucken

BOOL CBibedtView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CListCtrl *lc = &GetListCtrl();

	if (lc->GetSelectedCount()) {
		UNSET_BIT(pInfo->m_pPD->m_pd.Flags, PD_NOSELECTION);
		SET_BIT(pInfo->m_pPD->m_pd.Flags, PD_SELECTION);
	} else
		SET_BIT(pInfo->m_pPD->m_pd.Flags, PD_NOSELECTION);

	// Initialize default values
	m_Print.OnPreparePrinting(pInfo);
	// Now set the margins
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_Print.SetMarginUnit(pOp->m_PrintUnits);
	m_Print.SetMarginLeft(pOp->m_MarginLeft);
	m_Print.SetMarginTop(pOp->m_MarginTop);
	m_Print.SetMarginRight(pOp->m_MarginRight);
	m_Print.SetMarginBottom(pOp->m_MarginBottom);

	// Standardvorbereitung
	return DoPreparePrinting(pInfo);

}

void CBibedtView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CWaitCursor wait;
	m_Print.OnBeginPrinting(pDC, pInfo);
}

void CBibedtView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   m_Print.OnEndPrinting(pDC, pInfo);
}

void CBibedtView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Print.OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBibedtView Diagnose

#ifdef _DEBUG
void CBibedtView::AssertValid() const
{
	CListView::AssertValid();
}

void CBibedtView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CBibedtDoc* CBibedtView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBibedtDoc)));
	return (CBibedtDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBibedtView Nachrichten-Handler

int CBibedtView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style |= LVS_REPORT | LVS_EDITLABELS | LVS_SHOWSELALWAYS;
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBibedtApp *pApp = (CBibedtApp*)AfxGetApp();

	CListCtrl *lc = &GetListCtrl();

	SetupColumns();
	DWORD extst = lc->GetExtendedStyle();
	if (pApp->m_Options->m_GridLines)
	  SET_BIT(extst, LVS_EX_GRIDLINES);

	lc->SetExtendedStyle(extst | LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT);
	lc->SetImageList(&m_ImageList, LVSIL_SMALL);

	return 0;
}

void CBibedtView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = CDRF_DODEFAULT;

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
	CListCtrl *lc = &GetListCtrl();
	CRect rcItem;
	CBibItem* pBibItem;
	int colcount, i;

	switch (pLVCD->nmcd.dwDrawStage) {
	case CDDS_PREPAINT:
		// We want a notification for each item, if this window is not focused
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		// An item should be drawn.

		// Different text color for items with missing fields
		pBibItem = (CBibItem*)lc->GetItemData(nItem);
		if (pBibItem != NULL && pBibItem->GetMissingFields() != 0) {
			pLVCD->clrText = MISSING_COLOR;
			SetTextColor(pLVCD->nmcd.hdc, MISSING_COLOR);
		} else
			SetTextColor(pLVCD->nmcd.hdc, GetSysColor(COLOR_WINDOWTEXT));

		if (GetFocused(nItem)) {
			CBrush wind;
			// We would like to paint all subitems
			lc->GetItemRect(nItem, rcItem, LVIR_BOUNDS);
			// Clear rect
			SetBkColor(pLVCD->nmcd.hdc, GetSysColor(COLOR_WINDOW));
			wind.CreateSysColorBrush(COLOR_WINDOW);
			FillRect(pLVCD->nmcd.hdc, rcItem, wind);

			rcItem.left += 20;
			if (GetSelected(nItem)) {
				CBrush bSel;
				if (GetFocus() == this) {
					SetBkColor(pLVCD->nmcd.hdc, GetSysColor(COLOR_HIGHLIGHT));
					SetTextColor(pLVCD->nmcd.hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
					bSel.CreateSysColorBrush(COLOR_HIGHLIGHT);
				} else {
					SetBkColor(pLVCD->nmcd.hdc, GetSysColor(COLOR_BTNFACE));
					bSel.CreateSysColorBrush(COLOR_BTNFACE);
				}
				FillRect(pLVCD->nmcd.hdc, rcItem, bSel);
			}
			// Draw focus rect
			DrawFocusRect(pLVCD->nmcd.hdc, rcItem);

			// Draw all subitems, moved to here to fix bug #1464177
			colcount = lc->GetHeaderCtrl()->GetItemCount();
			for (i = 0; i < colcount; i++) {
				lc->GetSubItemRect(nItem, i, LVIR_LABEL, rcItem);
				if (i)
					rcItem.left += 6;
				else {
					rcItem.left += 2;
 					// The icon
					CRect rcIcon;
					lc->GetSubItemRect(nItem, 0, LVIR_ICON, rcIcon);
 					LVITEM li;
 					li.mask = LVIF_IMAGE;
 					li.iSubItem = 0;
 					li.iItem = nItem;
 					if (lc->GetItem(&li))
 						ImageList_Draw(m_ImageList, li.iImage, pLVCD->nmcd.hdc, rcIcon.left, 
 							rcIcon.top, ILD_TRANSPARENT);
				}

				rcItem.right -= 5;
				// Draw the text of the subitem
				CString txt;
				txt = lc->GetItemText(nItem, i);
				DrawText(pLVCD->nmcd.hdc, txt, txt.GetLength(), &rcItem, 
					DT_END_ELLIPSIS | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);

			}
			// We did it all
			*pResult = CDRF_SKIPDEFAULT;
		} else
			*pResult = CDRF_DODEFAULT;
		break;
	}
}

void CBibedtView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!IsXP()) {
		// ListView on XP has already sortheader, we need do it only on previous win versions
		CListCtrl *lc = &GetListCtrl();
		CBrush brush;
		CRect rc(lpDrawItemStruct->rcItem);
		if (nIDCtl == lc->GetHeaderCtrl()->GetDlgCtrlID() && rc.Width() > 0) {
			// This seems to be the header -> draw sort arrow

			VERIFY(brush.CreateSysColorBrush(COLOR_BTNFACE));

			FillRect(lpDrawItemStruct->hDC, rc, brush);
			HDITEM hdi;
			TCHAR  lpBuffer[MAX_PATH];
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = MAX_PATH;

			lc->GetHeaderCtrl()->GetItem(lpDrawItemStruct->itemID, &hdi);
			CSize tex;
			int len = _tcslen(lpBuffer);
			GetTextExtentPoint32(lpDrawItemStruct->hDC, lpBuffer, len, &tex);
			DWORD x;
			DWORD y;
			x = rc.left + 5;
			// Vertical middle
			y = (rc.Height() >> 1) - (tex.cy >> 1);
			// Draw the text
			
			ExtTextOut(lpDrawItemStruct->hDC, x, y, ETO_CLIPPED, rc, lpBuffer, len, NULL);
			if (lpDrawItemStruct->itemID == m_SortCol) {
				// Draw the arrow
				x = rc.left + tex.cx + 20;
				y = rc.top + ((rc.Height() >> 1) - 5);
				if (x + 10 < rc.right)
					// Don't draw if the column is too narrow
					ImageList_Draw(m_SortIndicator, m_SortAsc, lpDrawItemStruct->hDC, x, y, ILD_TRANSPARENT); 
			}
		}
	}
	CListView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//DEL void CBibedtView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
//DEL {
//DEL 	CListCtrl *lc = &GetListCtrl();
//DEL 
//DEL 	LVITEM li;
//DEL 	li.mask = LVIF_IMAGE;
//DEL 	li.iSubItem = 0;
//DEL 	li.iItem = lpDrawItemStruct->itemID;
//DEL 	if (!lc->GetItem(&li))
//DEL 		return;
//DEL 
//DEL 	// Clear all
//DEL 	CBrush wind;
//DEL 	wind.CreateSysColorBrush(COLOR_WINDOW);
//DEL 	FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, wind);
//DEL 
//DEL 	// Depending on selection and/or focus the item has a different background and text color
//DEL 	BOOL focused = GetFocused(lpDrawItemStruct->itemID);
//DEL 	BOOL selected = GetSelected(lpDrawItemStruct->itemID);
//DEL 
//DEL 	CBrush brush;
//DEL 	COLORREF textcol = COLOR_WINDOWTEXT;
//DEL 	if (focused && !selected) {
//DEL 		brush.CreateSolidBrush(FOCUS_HIGHLIGHT);
//DEL 	} else if (selected) {
//DEL 		if (GetFocus() == this) {
//DEL 			brush.CreateSysColorBrush(COLOR_HIGHLIGHT);
//DEL 			textcol = SetTextColor(lpDrawItemStruct->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
//DEL 		} else
//DEL 			brush.CreateSysColorBrush(COLOR_BTNFACE);
//DEL 	} else {
//DEL 		brush.CreateSysColorBrush(COLOR_WINDOW);
//DEL 	}
//DEL 	// Fill the rect with the color
//DEL 	CRect rect(lpDrawItemStruct->rcItem);
//DEL 	rect.left += 20;
//DEL 	rect.right -= 2;
//DEL 	FillRect(lpDrawItemStruct->hDC, rect, brush);
//DEL 
//DEL 	CString txt;
//DEL 	for (int i = 0; i < lc->GetHeaderCtrl()->GetItemCount(); i++) {
//DEL 		// Draw Columns
//DEL 		txt = lc->GetItemText(lpDrawItemStruct->itemID, i);
//DEL 
//DEL 		lc->GetHeaderCtrl()->GetItemRect(i, rect);
//DEL 		rect.OffsetRect(0, lpDrawItemStruct->rcItem.top);
//DEL 		if (i == 0) {
//DEL 			// First column -> move to right for the icon
//DEL 			rect.left += 22;
//DEL 		} else
//DEL 			rect.left += 2;
//DEL 		rect.right -= 2;
//DEL 		
//DEL 		DrawText(lpDrawItemStruct->hDC, txt, txt.GetLength(), &rect, 
//DEL 			DT_END_ELLIPSIS | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);
//DEL 	}
//DEL 	
//DEL 	// Set old text color
//DEL 	SetTextColor(lpDrawItemStruct->hDC, textcol);
//DEL 
//DEL 	// The icon
//DEL 	ImageList_Draw(m_ImageList, li.iImage, lpDrawItemStruct->hDC, lpDrawItemStruct->rcItem.left + 2, 
//DEL 		lpDrawItemStruct->rcItem.top, ILD_TRANSPARENT);
//DEL 
//DEL 	if (focused) {
//DEL 		// Focus rect
//DEL 		CRect foc(lpDrawItemStruct->rcItem);
//DEL 		foc.left += 20;
//DEL 		foc.right -= 2;
//DEL 		DrawFocusRect(lpDrawItemStruct->hDC, foc);
//DEL 	}
//DEL }

void CBibedtView::SetupColumns()
{
	// Default columns
	const DEF_NAMES[] = {IDS_STRING_LV_COL_KEY, IDS_STRING_LV_COL_AUTHOR, IDS_STRING_LV_COL_TITLE};
	const DEF_WIDTHS[] = {100, 200, 300};

	CListCtrl *lc = &GetListCtrl();
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;

	for (int i = lc->GetHeaderCtrl()->GetItemCount(); i >= 0; i--)
		lc->DeleteColumn(i);
	CString defname;
	DWORD defwidth;
	DWORD flags;
	if (IsXP())
		flags = LVCFMT_LEFT;
	else
		flags = LVCFMT_LEFT | HDF_OWNERDRAW;
	for (i = 0; i < pOp->m_ColCount; i++) {
		if (i < 3) {
			defname = AfxLoadString(DEF_NAMES[i]);
			defwidth = DEF_WIDTHS[i];
		} else {
			defname = _T("");
			defwidth = 100;
		}
		lc->InsertColumn(i+1, pOp->GetColName(i, defname), flags, pOp->GetColWidth(i, defwidth));
	}
}

void CBibedtView::Populate()
{
	// Reset sorting
	m_SortAsc = TRUE;
	m_SortCol = -1;

	m_Updating = TRUE;
	CListCtrl *lc = &GetListCtrl();
	lc->SetRedraw(FALSE);
	lc->DeleteAllItems();
	AddList(GetDocument()->m_BibFile->GetHeadPosition(), FALSE);
	m_Updating = FALSE;
	lc->SetRedraw();
	if (GetDocument()->GetSelected()) {
		// Focus selected item
		int i = GetItemIndex(GetDocument()->GetSelected());
		if (i != -1) {
			SetFocused(i, TRUE);
			lc->EnsureVisible(i, FALSE);
		}
	}
}

void CBibedtView::OnViewGridlines() 
{
	CBibedtApp* app = (CBibedtApp*)AfxGetApp();
	app->m_Options->m_GridLines = !app->m_Options->m_GridLines;
	SetGridLines(app->m_Options->m_GridLines);
}

void CBibedtView::OnUpdateViewGridlines(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CBibedtApp*)AfxGetApp())->m_Options->m_GridLines);
}

void CBibedtView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i = pNMListView->iItem;
	if (i != -1) {
		GetDocument()->SetSelected(GetSelectedItem());
		GetDocument()->ActivateView(VIEW_RECORD);
	}
	
	*pResult = 0;
}

void CBibedtView::DoMarkMatches()
{
	CWaitCursor wait;
	ClearBookmarks();
	int firstmatch = -1;

	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetItemCount(); i++) {
		if (m_SearchSelOnly) {
			if (GetSelected(i)) {
				if (Matches(i)) {
					if (firstmatch == -1)
						firstmatch = i;
					SetBookmark(i, TRUE);
				}
			}
		} else {
			if (Matches(i)) {
				if (firstmatch == -1)
					firstmatch = i;
				SetBookmark(i, TRUE);
			}
		}
	}
	if (firstmatch != -1)
		lc->EnsureVisible(firstmatch, FALSE);
}

void CBibedtView::DoSearch()
{
	CListCtrl *lc = &GetListCtrl();
	int i = -1;
	for (i = 0; i < lc->GetItemCount(); i++) {
		if (m_SearchSelOnly) {
			if (GetSelected(i)) {
				if (Matches(i)) {
					break;
				}
			}
		} else {
			if (Matches(i)) {
				break;
			}
		}
	}
	UnselectAll();
	if (i != -1) {
		SetSelected(i, TRUE);
		lc->SetSelectionMark(i);
		lc->EnsureVisible(i, FALSE);
		SetFocused(i, TRUE);
	} else
		MessageBeep(MB_ICONEXCLAMATION);
}

BOOL CBibedtView::Matches(int item)
{
	BOOL res = FALSE;
	CListCtrl *lc = &GetListCtrl();
	CBibItem *bi = (CBibItem*)lc->GetItemData(item);
	if (!bi || !bi->IsVisible() || !bi->IsRegularItem())
		return FALSE;
	return (!bi->MatchesFields(m_SearchText, m_SearchFields, m_SearchRegExpr, m_SearchWholeWords, m_SearchMatchCase, FALSE).IsEmpty());
}

/**
 * Returns TRUE when a field with name f is visible in the LV
 */
BOOL CBibedtView::IsFieldVisible(CString f)
{
	LVCOLUMN col;
	TCHAR lpBuffer[256];
	col.pszText = lpBuffer;
	col.cchTextMax = 256;
	col.mask = LVCF_TEXT;
	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetHeaderCtrl()->GetItemCount(); i++)  {
		lc->GetColumn(i, &col);
		if (f.CompareNoCase(lpBuffer) == 0)
			return TRUE;
	}
	return FALSE;
}

void CBibedtView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((&GetListCtrl())->GetSelectedCount());
}

void CBibedtView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((&GetListCtrl())->GetSelectedCount());
}

void CBibedtView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((&GetListCtrl())->GetSelectedCount());
}

void CBibedtView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	pCmdUI->Enable(IsClipboardFormatAvailable(pApp->GetBibClipbrdFormat()) || IsClipboardFormatAvailable(CF_TEXT));
}

void CBibedtView::OnDestroy() 
{
	CListView::OnDestroy();
	
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	CListCtrl *lc = &GetListCtrl();

	for (int i = 0; i < lc->GetHeaderCtrl()->GetItemCount(); i++) {
		pOp->SetColWidth(i, lc->GetColumnWidth(i));
	}
	CRect r;
	GetWindowRect(&r);
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ListViewHeight"), r.Height());
}

void CBibedtView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if (pDispInfo->item.pszText != NULL) {
		CListCtrl *lc = &GetListCtrl();
		int i = pDispInfo->item.iItem;
		CBibItem* b = (CBibItem*)lc->GetItemData(i);
		b->SetKey(pDispInfo->item.pszText);
		*pResult = 1;
	} else
		*pResult = 0;
}

void CBibedtView::OnEditCopycitation() 
{
	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	CListCtrl *lc = &GetListCtrl();
	if (pOp->m_ShowCiteDlg) {
		// Show dialog
		CCopyCitationDialog dlg;
		for (int i = 0; i < lc->GetItemCount(); i++) {
			if (GetSelected(i)) {
				dlg.AddKey(lc->GetItemText(i, 0));
			}
		}
		if (m_CiteFormat != -1)
			dlg.SetCiteFormat(m_CiteFormat);
		if (dlg.DoModal() == IDOK) {
			m_CiteFormat = dlg.GetCiteFormat();
			CString s = dlg.GetCopyString();
			if (!s.IsEmpty())
				ClipBrdPutData(this, s, CB_TEXT, TRUE);
		}
	} else {
		// Dont show dialog, use default
		CString res;
		CString key;
		CListCtrl *lc = &GetListCtrl();
		for (int i = 0; i < lc->GetItemCount(); i++) {
			if (GetSelected(i)) {
				key.Format(pOp->m_CiteFormat, lc->GetItemText(i, 0));
				res += key + NL;
			}
		}
		if (!res.IsEmpty()) {
			if (res.Right(2).Compare(NL) == 0)
				// delete trailing CrLf
				res.Delete(res.GetLength());
			ClipBrdPutData(this, res, CB_TEXT, TRUE);
		}
	}
}

void CBibedtView::OnUpdateEditCopycitation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());	
}

void CBibedtView::SetGridLines(BOOL val)
{
	CListCtrl *lc = &GetListCtrl();
	DWORD extst = lc->GetExtendedStyle();
	if (val) {
		SET_BIT(extst, LVS_EX_GRIDLINES);
	} else {
		UNSET_BIT(extst, LVS_EX_GRIDLINES);
	}
	lc->SetExtendedStyle(extst);
}

void CBibedtView::SetRowSelect(BOOL val)
{
	CListCtrl *lc = &GetListCtrl();
	DWORD extst = lc->GetExtendedStyle();
	if (val) {
		SET_BIT(extst, LVS_EX_FULLROWSELECT);
	} else {
		UNSET_BIT(extst, LVS_EX_FULLROWSELECT);
	}
	lc->SetExtendedStyle(extst);
}

void CBibedtView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CListCtrl *lc = &GetListCtrl();
	CMenu* pPopup = NULL;
	if (pWnd->GetSafeHwnd() == lc->GetSafeHwnd()) {
		pPopup = m_PopupMenu.GetSubMenu(0);
	} else if (pWnd->GetSafeHwnd() == lc->GetHeaderCtrl()->GetSafeHwnd()) {
		pPopup = m_PopupMenu.GetSubMenu(1);
	}

	if (pPopup != NULL) {
		// Update Menuitems
		AfxGetMainWnd()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopup->m_hMenu, MAKELONG(0, FALSE));
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

CBibItem * CBibedtView::GetSelectedItem()
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	if (i == -1)
		return NULL;
	CBibItem *res = (CBibItem*)lc->GetItemData(i);
	return res;
}

void CBibedtView::OnEditCut() 
{
	OnEditCopy();
	OnEditDelete();
}

void CBibedtView::OnEditCopy() 
{
	CWaitCursor wait;
	CString res;
	CListCtrl *lc = &GetListCtrl();

	for (int i = 0; i < lc->GetItemCount(); i++) {
		if (GetSelected(i)) {
			CBibItem *bi = (CBibItem*)lc->GetItemData(i);
			if (bi) {
				res += bi->GetSource() + NL;
			}
		}
	}

	ClipBrdPutData(this, res, CB_TEXT, TRUE);
	ClipBrdPutData(this, res, CB_BIB, FALSE);

	CExporterList* el = ((CBibedtApp*)AfxGetApp())->m_Options->m_ExporterList;
	// Also put it as RTF to the Clipbrd
	CExportRTF* rtfexp = (CExportRTF*)el->GetRtfExporter();
	if (rtfexp) {
		rtfexp->m_SelOnly = lc->GetSelectedCount();
		rtfexp->m_LineLength = ((CBibedtApp*)AfxGetApp())->m_Options->m_LineLength;
		rtfexp->SetListCtrl(lc);
		res = rtfexp->GetSource();
		ClipBrdPutData(this, res, CB_RTF, FALSE);
	}

	// And finally HTML
	CExportCopyHtml* exp = (CExportCopyHtml*)el->GetCopyHtmlExporter();
	if (exp) {
		exp->m_SelOnly = lc->GetSelectedCount();
		exp->SetListCtrl(lc);
		res = exp->GetSource();
		ClipBrdPutData(this, res, CB_HTML, FALSE);
	}
}

void CBibedtView::OnEditPaste() 
{
	CWaitCursor wait;
	CBibedtApp* pApp = (CBibedtApp*)AfxGetApp();
	CString s;
	if (IsClipboardFormatAvailable(pApp->GetBibClipbrdFormat()))
		// We've our own clipboard format
		s = ClipBrdGetData(this, CB_BIB);
	else if (IsClipboardFormatAvailable(CF_TEXT))
		// try with plain text
		s = ClipBrdGetData(this, CB_TEXT);

	if (s.IsEmpty())
		return;

	CBibFile *f = new CBibFile();
	CBibReader *reader = new CBibReader(s);
	f->Parse(reader);
	if (f->GetCount()) {
		POSITION p = GetDocument()->m_BibFile->GetTailPosition();
		GetDocument()->m_BibFile->Append(f);
		if (p)
			// Not an empty list
			GetDocument()->m_BibFile->GetNext(p);
		AddList(p, TRUE);
		GetDocument()->UpdateAllViews(this, UR_PASTE);
	}
	delete reader;
	delete f;
}

void CBibedtView::OnEditDelete() 
{
	CListCtrl *lc = &GetListCtrl();
	for (int i = lc->GetItemCount() - 1; i >= 0; i--) {
		if (GetSelected(i)) {
			CBibItem *bi = (CBibItem*)lc->GetItemData(i);
			if (bi) {
				GetDocument()->DeleteItem(bi);
			}
			// The list view item is deleted in OnUpdate called by CDocument
			// so we need not delete it here from the LV.
		}
	}
}

LRESULT CBibedtView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) {
	case WM_NOTIFY:
		if (lParam) {
			NMHEADER *hdn = (LPNMHEADER)lParam;  		
			if (hdn->hdr.code == HDN_ITEMCLICKA || hdn->hdr.code == HDN_ITEMCLICKW)	{  // ???  
				SortList(hdn->iItem);
			}
		}
		break;
	}
	return CListView::WindowProc(message, wParam, lParam);
}

void CBibedtView::SortList(int col)
{
	LVSORTPARAM ss;
	int i;
	ss.iHeader = col;
	ss.pListView = &GetListCtrl();
	if (m_SortCol != col)
		m_SortAsc = TRUE;
	ss.bSortAsc = m_SortAsc;
	
	// Now sort it
	ss.pListView->SortItems(ListViewSortProc, (LPARAM)&ss);

	if (IsXP()) {
		// Use native sort arrows provided by ComCtrl v >= 6 (XP) if possible

		// First select the column
		ss.pListView->SendMessage(LVM_SETSELECTEDCOLUMN, (WPARAM)col, 0);

		// Tell the header the column
		CHeaderCtrl *header = ss.pListView->GetHeaderCtrl();
		HDITEM hditem;
		for (i = 0; i < header->GetItemCount(); i++) {
			hditem.mask = HDI_FORMAT;
			header->GetItem(i, &hditem);
			UNSET_BIT(hditem.fmt, HDF_SORTUP | HDF_SORTDOWN);
			if (i == col)
				hditem.fmt |= m_SortAsc ? HDF_SORTUP : HDF_SORTDOWN;
			header->SetItem(i, &hditem);
		}
	}

	// Invert sort order
	m_SortAsc = !m_SortAsc;
	// Store sort column
	m_SortCol = col;

	// Scroll to focused item
	CBibItem* foc = GetDocument()->GetSelected();
	if (foc) {
		i = GetItemIndex(foc);
		if (i != -1)
			ss.pListView->EnsureVisible(i, FALSE);
	}
}

int CALLBACK CBibedtView::ListViewSortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	LVCOLUMN col;
	TCHAR lpBuffer[256];
	col.pszText = lpBuffer;
	col.cchTextMax = 256;
	col.mask = LVCF_TEXT;

	PLVSORTPARAM ss = (PLVSORTPARAM)lParamSort;
	CString s1;
	CString s2;
	CListCtrl *lc = ss->pListView;
	CBibItem* b1 = (CBibItem*)lParam1;
	CBibItem* b2 = (CBibItem*)lParam2;

	col.iSubItem = ss->iHeader;
	lc->GetColumn(ss->iHeader, &col);
	CString fn(lpBuffer);

	s1 = b1->GetFieldValue(fn);
	s2 = b2->GetFieldValue(fn);

	COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
	int res;
	if (pOp->m_SortCaseSensitive)
		res = s1.Compare(s2);
	else
		res = s1.CompareNoCase(s2);
	return ss->bSortAsc ? res : -res;
}

BOOL CBibedtView::GetSelected(int index)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (lc->GetItem(&item)) {
		return BIT_SET(item.state, LVIS_SELECTED);
	} else
		return FALSE;
}

void CBibedtView::SetSelected(int index, BOOL selected)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_SELECTED;
	if (lc->GetItem(&item)) {
		if (selected)
			SET_BIT(item.state, LVIS_SELECTED);
		else
			UNSET_BIT(item.state, LVIS_SELECTED);
		lc->SetItem(&item);
	}
}

BOOL CBibedtView::GetFocused(int index)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_FOCUSED;
	if (lc->GetItem(&item)) {
		return BIT_SET(item.state, LVIS_FOCUSED);
	}
	return FALSE;
}

void CBibedtView::SetFocused(int index, BOOL focused)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_STATE;
	item.iItem = index;
	item.iSubItem = 0;
	item.stateMask = LVIS_FOCUSED;
	if (lc->GetItem(&item)) {
		if (focused)
			SET_BIT(item.state, LVIS_FOCUSED);
		else
			UNSET_BIT(item.state, LVIS_FOCUSED);
		lc->SetItem(&item);
	}
}

/**
 * Fill the columns of the list with the item
 */
void CBibedtView::SetColumnValues(int pos, CBibItem *item)
{
	ASSERT(pos != -1);

	CListCtrl *lc = &GetListCtrl();
	CBibDef *def = GetBibDef();
	int colcount = lc->GetHeaderCtrl()->GetItemCount();
	LVCOLUMN col;
	TCHAR lpBuffer[256];
	col.pszText = lpBuffer;
	col.cchTextMax = 256;
	col.mask = LVCF_TEXT;

	for (int co = 0; co < colcount; co++) {
		col.iSubItem = co;
		lc->GetColumn(co, &col);
		CString str = item->GetFieldValue(lpBuffer);
		if (!str.IsEmpty())
			lc->SetItemText(pos, co, str);
		else
			lc->SetItemText(pos, co, NULL);
	}
}

int CBibedtView::AddItem(int pos, CBibItem *item, BOOL select)
{
	CListCtrl *lc = &GetListCtrl();
	int rp;
	if (pos = -1)
		pos = lc->GetItemCount();

	if (item->IsRegularItem()) {
		// Only add real BibItems to the LV
		rp = lc->InsertItem(pos, item->GetKey(), -1);
		// Set subitems
		SetColumnValues(rp, item);
		lc->SetItemData(rp, (DWORD)item);
		// Bookmarked
		SetBookmark(rp, item->m_Bookmarked);

		if (select)
			SetSelected(rp, TRUE);
	}
	return rp;
}

void CBibedtView::AddList(POSITION p, BOOL select)
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetItemCount()-1;
	CBibList *lst = GetDocument()->m_BibFile;
	if (p == NULL)
		p = lst->GetHeadPosition();
	CBibItem* bi = NULL;
	m_Updating = TRUE;
	while (p) {
		bi = (CBibItem*)lst->GetNext(p);
		if (bi && bi->IsVisible()) {
			i = AddItem(i+1, bi, select);
		}
	}
	if (select) {
		lc->EnsureVisible(i, FALSE);
		GetDocument()->SetSelected(bi);
		GetDocument()->UpdateAllViews(this, UR_SELECTED, bi);
	}
	m_Updating = FALSE;
}

void CBibedtView::OnEditSelectAll() 
{
	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetItemCount(); i++)
		SetSelected(i, TRUE);
}

void CBibedtView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());	
}

void CBibedtView::UnselectAll()
{
	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetItemCount(); i++)
		SetSelected(i, FALSE);
}

void CBibedtView::OnViewColumns() 
{
	CColumnsDialog dlg;
	dlg.SetListCtrl(&GetListCtrl());
	if (dlg.DoModal() == IDOK) {
		SetupColumns();
		Populate();
	}
}

void CBibedtView::DoExport()
{
	CExporterList* exlst = ((CBibedtApp*)AfxGetApp())->m_Options->m_ExporterList;
	CExportDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_ENABLESIZING, 
		AfxLoadString(IDS_STRING_ALLFILTER) + _T("|") + exlst->GetFilter() + _T("|"), this);
	dlg.SetExporterList(exlst);
	if (dlg.DoModal() == IDOK) {
		CListCtrl *lc = &GetListCtrl();
		BOOL selonly = lc->GetSelectedCount() > 0;
		CWaitCursor wait;
		POSITION p = exlst->GetHeadPosition();
		while (p) {
			CExport* ex = (CExport*)exlst->GetNext(p);
			if (ex->m_Selected) {
				ex->m_SelOnly = selonly;
				ex->m_LineLength = ((CBibedtApp*)AfxGetApp())->m_Options->m_LineLength;
				ex->SetListCtrl(lc);
				ex->DoExport(ChangeFileExt(dlg.GetPathName(), ex->GetExt()));
				CString err = ex->GetLastError();
				if (!err.IsEmpty())
					ShowError(err);
			}
		}
	}	
}

void CBibedtView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl *lc = &GetListCtrl();
	int i;
	CBibItem *item;
	m_Updating = TRUE;
	switch (lHint) {
	case UR_SRCEDITED:
	case UR_OPENFILE:
	case UR_APPENDFILE:
		if (pSender != this) {
			Populate();
		}
		m_SortCol = -1;
		break;
	case UR_SORTED:
	case UR_FILTERED:
		Populate();
		m_SortCol = -1;
		break;
	case UR_RECADDED:
		i = AddItem(-1, (CBibItem*)pHint, FALSE);
		break;
	case UR_RECREMOVED:
		i = GetItemIndex((CBibItem*)pHint);
		if (i > -1)
			lc->DeleteItem(i);
		break;
	case UR_RECEDITED:
	case UR_RECSRCEDITED:
		if (pHint) {
			item = (CBibItem*)pHint;
			i = GetItemIndex(item);
			if (i > -1)
				SetColumnValues(i, item);
		}
		break;
	case UR_SELECTED:
		if (pSender != this) {
			i = GetItemIndex((CBibItem*)pHint);
			if (i == -1 && pHint != NULL) {
				// It is currently not in the list, maybe invisible
				// Add it to the list
				i = AddItem(lc->GetItemCount(), (CBibItem*)pHint, FALSE);
			}
			if (i != -1) {
				SetFocused(i, TRUE);
				lc->EnsureVisible(i, FALSE);
				lc->SetSelectionMark(i);
			}
		}
		break;
	case UR_NEWFILE:
		lc->DeleteAllItems();
		m_SortCol = -1;
		break;
	}
	m_Updating = FALSE;
}

void CBibedtView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CBibedtView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (!m_Updating) {
		if (pNMListView->iItem != -1) {
			// There must be one item which has the focus, you can not "unfocus" an item.
			// On loading a file the first item is focused, so always an item should be focused
			if (pNMListView->uChanged == LVIF_STATE && BIT_SET(pNMListView->uNewState, LVIS_FOCUSED)) {
				CListCtrl *lc = &GetListCtrl();
				CBibItem *sel = (CBibItem*)lc->GetItemData(pNMListView->iItem);
				GetDocument()->SetSelected(sel);
				GetDocument()->UpdateAllViews(this, UR_SELECTED, sel);
			}
		} else {
			GetDocument()->SetSelected(NULL);
			GetDocument()->UpdateAllViews(this, UR_SELECTED);
		}
	}
		
	*pResult = 0;
}

void CBibedtView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());
}

void CBibedtView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());
}

int CBibedtView::GetItemIndex(CBibItem *item)
{
	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetItemCount(); i++) {
		if ((CBibItem*)lc->GetItemData(i) == item) {
			return i;
		}
	}
	return -1;
}

void CBibedtView::OnSearchFind() 
{
	CSearchDialog dlg;
	dlg.m_boolMatchBase = m_SearchMatchCase;
	dlg.m_boolSelOnly = m_SearchSelOnly;
	dlg.m_boolWholeWords = m_SearchWholeWords;
	dlg.m_boolRegEx = m_SearchRegExpr;
	dlg.SetSearchText(m_SearchText);
	if (m_SearchFields.IsEmpty())
		dlg.m_strSearchFields = AfxLoadString(IDS_STRING_ALLFIELDS);
	else
		dlg.m_strSearchFields = m_SearchFields;
	CStringList lst;
	GetDocument()->m_BibFile->GetAllFieldNames(&lst);
	dlg.m_SearchFields = &lst;
	switch (dlg.DoModal()) {
	case IDOK:
		m_SearchMatchCase = dlg.m_boolMatchBase;
		m_SearchSelOnly = dlg.m_boolSelOnly;
		m_SearchWholeWords = dlg.m_boolWholeWords;
		m_SearchRegExpr = dlg.m_boolRegEx;
		m_SearchText = dlg.GetSearchText();
		m_SearchFields = dlg.m_strSearchFields;
		if (m_SearchFields.CompareNoCase(AfxLoadString(IDS_STRING_ALLFIELDS)) == 0)
			m_SearchFields.Empty();
		else {
			if (m_SearchFields.Right(1) != _T(";"))
				m_SearchFields += _T(";");
		}
		(&GetListCtrl())->SetFocus();
		DoSearch();
		break;
	case IDC_BUTTON_SEARCH_MARKALL:
		m_SearchMatchCase = dlg.m_boolMatchBase;
		m_SearchSelOnly = dlg.m_boolSelOnly;
		m_SearchWholeWords = dlg.m_boolWholeWords;
		m_SearchRegExpr = dlg.m_boolRegEx;
		m_SearchText = dlg.GetSearchText();
		m_SearchFields = dlg.m_strSearchFields;
		if (m_SearchFields.CompareNoCase(AfxLoadString(IDS_STRING_ALLFIELDS)) == 0)
			m_SearchFields.Empty();
		else {
			if (m_SearchFields.Right(1) != _T(";"))
				m_SearchFields += _T(";");
		}
		(&GetListCtrl())->SetFocus();
		DoMarkMatches();
		break;
	}
}

void CBibedtView::OnUpdateSearchFind(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());	
}

void CBibedtView::OnSearchFindnext() 
{
	UnselectAll();
	CListCtrl *lc = &GetListCtrl();
	int start = lc->GetSelectionMark();
	start++;
	for (int i = start; i < lc->GetItemCount(); i++) {
		if (Matches(i)) {
			SetSelected(i, TRUE);
			lc->SetSelectionMark(i);
			SetFocused(i, TRUE);
			lc->EnsureVisible(i, FALSE);
			return;
		}
	}
	MessageBeep(MB_ICONEXCLAMATION);
}

void CBibedtView::OnUpdateSearchFindnext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded() && !m_SearchText.IsEmpty());	
}

void CBibedtView::OnFilePrintPreview() 
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.

	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;

	// Get the ID of the currently active pane
	CMainFrame *mf = (CMainFrame*)AfxGetMainWnd();
	TVisualObject *vo = mf->m_Framework.GetActivePane();
	CWnd *parent = vo->GetParentWnd()->GetParent();
	ASSERT(parent);
	// This window with this ID will be hidden during previewing
	pState->nIDMainPane = parent->GetDlgCtrlID();

	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.

	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this,
							RUNTIME_CLASS(CPreviewView), pState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case

		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
	}
}

void CBibedtView::OnFilePrint() 
{
	CView::OnFilePrint();	
}

void CBibedtView::SetBookmark(int index, BOOL set)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_IMAGE;
	item.iItem = index;
	item.iSubItem = 0;
	if (lc->GetItem(&item)) {
		if (set)
			item.iImage = 0;
		else
			item.iImage = -1;
		lc->SetItem(&item);
		CRect ir;
		if (lc->GetItemRect(index, &ir, LVIR_ICON))
			lc->InvalidateRect(ir);
		CBibItem *bi = (CBibItem*)lc->GetItemData(index);
		ASSERT(bi);
		bi->m_Bookmarked = set;
	}

}

void CBibedtView::ClearBookmarks()
{
	CListCtrl *lc = &GetListCtrl();
	for (int i = 0; i < lc->GetItemCount(); i++) {
		SetBookmark(i, FALSE);
	}
}

void CBibedtView::ToggleBookmark(int index)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_IMAGE;
	item.iSubItem = 0;
	item.iItem = index;
	if (lc->GetItem(&item)) {
		SetBookmark(index, item.iImage == -1);
	}
}

void CBibedtView::OnUpdateSearchTogglebookmark(CCmdUI* pCmdUI) 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	pCmdUI->Enable(i != -1);
}

void CBibedtView::OnSearchTogglebookmark() 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	if (i != -1)
		ToggleBookmark(i);
}

void CBibedtView::OnSearchClearbookmarks() 
{
	ClearBookmarks();
}

void CBibedtView::OnUpdateSearchClearbookmarks(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());
}

int CBibedtView::GetNextBookmark(int index)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_IMAGE;
	item.iSubItem = 0;
	for (int i = index + 1; i < lc->GetItemCount(); i++) {
		item.iItem = i;
		if (lc->GetItem(&item) && item.iImage != -1) {
			return i;
		}
	}

	return -1;
}

int CBibedtView::GetPreviousBookmark(int index)
{
	CListCtrl *lc = &GetListCtrl();
	LVITEM item;
	item.mask = LVIF_IMAGE;
	item.iSubItem = 0;
	for (int i = index - 1; i >= 0; i--) {
		item.iItem = i;
		if (lc->GetItem(&item) && item.iImage != -1) {
			return i;
		}
	}

	return -1;
}

void CBibedtView::OnSearchNextbookmark() 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	int bm = GetNextBookmark(i);
	if (bm != -1) {
		SetSelected(bm, TRUE);
		lc->EnsureVisible(bm, FALSE);
		lc->SetSelectionMark(bm);
	} else
		MessageBeep(MB_ICONEXCLAMATION);
}

void CBibedtView::OnUpdateSearchNextbookmark(CCmdUI* pCmdUI) 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	pCmdUI->Enable(i != -1);
}

void CBibedtView::OnSearchPreviousbookmark() 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	int bm = GetPreviousBookmark(i);
	if (bm != -1) {
		SetSelected(bm, TRUE);
		lc->EnsureVisible(bm, FALSE);
		lc->SetSelectionMark(bm);
	} else
		MessageBeep(MB_ICONEXCLAMATION);
}

void CBibedtView::OnUpdateSearchPreviousbookmark(CCmdUI* pCmdUI) 
{
	CListCtrl *lc = &GetListCtrl();
	int i = lc->GetSelectionMark();
	pCmdUI->Enable(i != -1);
}

void CBibedtView::OnUpdateSearchFindduplicate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetLoaded());	
}

void CBibedtView::OnSearchFindduplicate() 
{
	CFindDupOptionsDialog op;
	op.SetBibList(GetDocument()->m_BibFile);
	if (op.DoModal() == IDOK) {
		CFindDuplicatesDialog dlg;
		dlg.m_Fields = op.m_Fields;
		dlg.m_Exact = op.m_Exact;
		dlg.m_CaseSens = op.m_CaseSens;
		dlg.SetBibList(GetDocument()->m_BibFile);
		if (dlg.DoModal() == IDOK) {
			// Nothing to do here
		}
	}
}

void CBibedtView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_DELETE) {
		// We handle the delete key here (not with an accelerator) because
		// of conflicts with edits.
		OnEditDelete();
	}
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CBibedtView::OnRecordGeneratekey() 
{
	CBibItem* item = GetDocument()->GetSelected();
	CString key = GetDocument()->GenerateKey(item);
	if (!key.IsEmpty()) {
		item->SetKey(key);
		GetDocument()->SetModifiedFlag(GetDocument()->IsModified() || item->GetModified());
		int i = GetItemIndex(item);
		if (i != -1) {
			CListCtrl* lst = &GetListCtrl();
			lst->SetItemText(i, 0, key);
		}
		GetDocument()->UpdateAllViews(this, UR_RECEDITED, item);
	}
}

void CBibedtView::OnUpdateRecordGeneratekey(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetSelected() != NULL);	
}

void CBibedtView::OnFileExport() 
{
	DoExport();	
}