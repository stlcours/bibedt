// SearchProfilesDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "SearchProfilesDialog.h"
#include "InputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSearchProfilesDialog 


CSearchProfilesDialog::CSearchProfilesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchProfilesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchProfilesDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CSearchProfilesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchProfilesDialog)
	DDX_Control(pDX, IDC_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, IDC_BUTTON_RENAME, m_btnRename);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_LIST_PROFILES, m_lstProfiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchProfilesDialog, CDialog)
	//{{AFX_MSG_MAP(CSearchProfilesDialog)
	ON_BN_CLICKED(IDC_BUTTON_RENAME, OnButtonRename)
	ON_LBN_DBLCLK(IDC_LIST_PROFILES, OnDblclkListProfiles)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_LBN_SELCHANGE(IDC_LIST_PROFILES, OnSelchangeListProfiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSearchProfilesDialog 

BOOL CSearchProfilesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	POSITION p = m_Profiles.GetHeadPosition();
	while (p) {
		CSearchProfile* profile = (CSearchProfile*)m_Profiles.GetNext(p);
		int i = m_lstProfiles.AddString(profile->m_Name);
		m_lstProfiles.SetItemDataPtr(i, profile);
	}
	if (m_lstProfiles.GetCount() > 0)
		m_lstProfiles.SetCurSel(0);
	OnSelchangeListProfiles();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSearchProfilesDialog::SetProfiles(CSearchProfileList *lst)
{
	m_Profiles.Assign(lst);
}

void CSearchProfilesDialog::OnButtonRename() 
{
	int i = m_lstProfiles.GetCurSel();
	if (i == -1)
		return;

	CSearchProfile* profile = (CSearchProfile*)m_lstProfiles.GetItemDataPtr(i);

	CInputBox dlg;
	dlg.SetCaption(AfxLoadString(IDS_STRING_RENPROF));
	dlg.SetPrompt(AfxLoadString(IDS_STRING_RENPROFPROMPT));
	dlg.m_strText = profile->m_Name;
	if (dlg.DoModal() == IDOK && !dlg.m_strText.IsEmpty()) {
		CString name = dlg.m_strText;
		profile->m_Name = name;
		m_lstProfiles.DeleteString(i);
		i = m_lstProfiles.InsertString(i, name);
		m_lstProfiles.SetItemDataPtr(i, profile);
		m_lstProfiles.SetCurSel(i);
		OnSelchangeListProfiles();
	}
}

void CSearchProfilesDialog::OnDblclkListProfiles() 
{
	OnButtonRename();
}

void CSearchProfilesDialog::OnButtonAdd() 
{
	CInputBox dlg;
	dlg.SetCaption(AfxLoadString(IDS_STRING_NEWPROFCAP));
	dlg.SetPrompt(AfxLoadString(IDS_STRING_NEWPROFPROMPT));
	if (dlg.DoModal() == IDOK && !dlg.m_strText.IsEmpty()) {
		CString name = dlg.m_strText;
		CSearchProfile* profile = m_Profiles.New(name);
		int i = m_lstProfiles.AddString(name);
		m_lstProfiles.SetItemDataPtr(i, profile);
		m_lstProfiles.SetCurSel(i);
		OnSelchangeListProfiles();
	}
}

void CSearchProfilesDialog::OnButtonRemove() 
{
	int i = m_lstProfiles.GetCurSel();
	if (i == -1)
		return;
	CSearchProfile* profile = (CSearchProfile*)m_lstProfiles.GetItemDataPtr(i);
	m_Profiles.Delete(profile);
	m_lstProfiles.DeleteString(i);
	if (i > 0)
		i--;
	else if (i >= m_lstProfiles.GetCount())
		i = -1;
	m_lstProfiles.SetCurSel(i);
	OnSelchangeListProfiles();
}

void CSearchProfilesDialog::OnButtonUp() 
{
	int cur = m_lstProfiles.GetCurSel();
	if (cur == -1)
		return;
	m_Profiles.Move(cur, cur-1);
	CSearchProfile* profile = (CSearchProfile*)m_lstProfiles.GetItemDataPtr(cur);
	m_lstProfiles.DeleteString(cur);
	int newsel = m_lstProfiles.InsertString(cur-1, profile->m_Name);
	m_lstProfiles.SetItemDataPtr(newsel, profile);
	m_lstProfiles.SetCurSel(newsel);
	OnSelchangeListProfiles();
}

void CSearchProfilesDialog::OnButtonDown() 
{
	int cur = m_lstProfiles.GetCurSel();
	if (cur == -1)
		return;
	m_Profiles.Move(cur, cur+1);
	CSearchProfile* profile = (CSearchProfile*)m_lstProfiles.GetItemDataPtr(cur);
	m_lstProfiles.DeleteString(cur);
	int newsel = m_lstProfiles.InsertString(cur+1, profile->m_Name);
	m_lstProfiles.SetItemDataPtr(newsel, profile);
	m_lstProfiles.SetCurSel(newsel);
	OnSelchangeListProfiles();
}

void CSearchProfilesDialog::OnSelchangeListProfiles() 
{
	int i = m_lstProfiles.GetCurSel();
	m_btnRename.EnableWindow(i != -1);
	m_btnRemove.EnableWindow(i != -1);
	m_btnUp.EnableWindow(i != -1 && i > 0);
	m_btnDown.EnableWindow(i != -1 && i < m_lstProfiles.GetCount() - 1);
}
