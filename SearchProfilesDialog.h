#if !defined(AFX_SEARCHPROFILESDIALOG_H__74F99B7B_866E_4C9F_AB49_86805341AC41__INCLUDED_)
#define AFX_SEARCHPROFILESDIALOG_H__74F99B7B_866E_4C9F_AB49_86805341AC41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchProfilesDialog.h : Header-Datei
//

#include "SearchProfile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSearchProfilesDialog 

class CSearchProfilesDialog : public CDialog
{
// Konstruktion
public:
	CSearchProfileList m_Profiles;
	void SetProfiles(CSearchProfileList* lst);
	CSearchProfilesDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSearchProfilesDialog)
	enum { IDD = IDD_DIALOG_EDITSEARCHPROFILES };
	CButton	m_btnUp;
	CButton	m_btnRename;
	CButton	m_btnRemove;
	CButton	m_btnDown;
	CListBox	m_lstProfiles;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSearchProfilesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSearchProfilesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRename();
	afx_msg void OnDblclkListProfiles();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnSelchangeListProfiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SEARCHPROFILESDIALOG_H__74F99B7B_866E_4C9F_AB49_86805341AC41__INCLUDED_
