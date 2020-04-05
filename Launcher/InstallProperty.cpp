// InstallProperty.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "resource.h"
#include "InstallProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstallProperty

IMPLEMENT_DYNAMIC(CInstallProperty, CPropertySheet)

CInstallProperty::CInstallProperty(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CInstallProperty::CInstallProperty(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_InstallStep1);
	AddPage(&m_InstallStep2);
}

CInstallProperty::~CInstallProperty()
{
	AddPage(&m_InstallStep1);
	AddPage(&m_InstallStep2);
}


BEGIN_MESSAGE_MAP(CInstallProperty, CPropertySheet)
	//{{AFX_MSG_MAP(CInstallProperty)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallProperty message handlers
