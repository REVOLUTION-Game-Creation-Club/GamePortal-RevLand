// InstallStep1.cpp : implementation file
//
#include "stdafx.h"
#include "Launcher.h"
#include "InstallStep1.h"
#include "RGPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef BIF_NEWDIALOGSTYLE 
#define BIF_NEWDIALOGSTYLE 0x0040 
#endif 

/////////////////////////////////////////////////////////////////////////////
// CInstallStep1 property page

IMPLEMENT_DYNCREATE(CInstallStep1, CPropertyPage)

CInstallStep1::CInstallStep1() : CPropertyPage(CInstallStep1::IDD)
{
	//{{AFX_DATA_INIT(CInstallStep1)
	m_strInstallPath = _T("");
	//}}AFX_DATA_INIT
}

CInstallStep1::~CInstallStep1()
{
}

void CInstallStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallStep1)
	DDX_Text(pDX, IDC_INSTALL_PATH_EDIT, m_strInstallPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstallStep1, CPropertyPage)
	//{{AFX_MSG_MAP(CInstallStep1)
	ON_EN_CHANGE(IDC_INSTALL_PATH_EDIT, OnChangeInstallPathEdit)
	ON_BN_CLICKED(IDC_FIND_BTN, OnFindBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallStep1 message handlers

BOOL CInstallStep1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);

	TCHAR strPath[MAX_PATH] = {0};

    ExpandEnvironmentStrings("%ProgramFiles%", strPath, MAX_PATH);

	lstrcpy(m_strRealInstallPath, strPath);
	
	m_strInstallPath.Format("%s\\RevGame\\%s", m_strRealInstallPath, GetPath()->m_strContentName);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CInstallStep1::OnWizardNext() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK);
	GetPath()->SetInstallPath(m_strRealInstallPath);
	return CPropertyPage::OnWizardNext();
}

void CInstallStep1::OnChangeInstallPathEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData(TRUE);
	if( m_strInstallPath.GetLength() == 0 )
	{
		((CPropertySheet*)GetParent())->SetWizardButtons(0);
	}
	else
	{
		((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	}
}

void CInstallStep1::OnFindBtn() 
{
	// Install 할 위치 선정
	LPMALLOC lpMalloc;    // A pointer to IMalloc

	char szDisplayName[_MAX_PATH];
	TCHAR strInstallPath[MAX_PATH];

	// Get the Shell"s default allocator
	if (::SHGetMalloc(&lpMalloc) != NOERROR)
	{
		return;
	}
	
	BROWSEINFO browseInfo;

	LPITEMIDLIST lpItemIDList;
//	browseInfo.hwndOwner = hWnd;
	browseInfo.hwndOwner = NULL;
	browseInfo.pidlRoot = NULL;
	browseInfo.pszDisplayName = szDisplayName;
//	browseInfo.lpszTitle = lpszTitle;
	browseInfo.lpszTitle = "폴더선택";
	browseInfo.ulFlags = BIF_NEWDIALOGSTYLE;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;

	// This next call displays the Browse For Folder dialog box
	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		if (::SHGetPathFromIDList(lpItemIDList, strInstallPath))
		{
			// At this point szBuffer contains the path the user
			// chose
    
			if (strInstallPath[0] == '\0')
			{
				// 에러
			}
		}
		else
		{
			// The thing referred to by lpItemIDList might
			// not have been a file system object.
			// For whatever reason, SHGetPathFromIDList
			// didn"t work!
			// 에러 
		}

		// ex) "c:\" "d:\"
		if( lstrlen(strInstallPath) == 3 )
		{
			// "c:\" -> "c:"
			strInstallPath[2] = NULL;
		}

		lstrcpy(m_strRealInstallPath, strInstallPath);
		m_strInstallPath.Format("%s\\RevGame\\%s", m_strRealInstallPath, GetPath()->m_strContentName);
		UpdateData(FALSE);

		if( m_strInstallPath.GetLength() == 0 )
		{
			((CPropertySheet*)GetParent())->SetWizardButtons(0);
		}
		else
		{
			((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
		}
	}
	
	// Free the lpItemIDList allocated by SHBrowseForFolder()
	lpMalloc->Free(lpItemIDList);

	// Release the shell"s allocator -- memory could leak if we don"t
	lpMalloc->Release();
}
