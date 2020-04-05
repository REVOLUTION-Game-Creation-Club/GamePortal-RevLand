// LauncherPpg.cpp : Implementation of the CLauncherPropPage property page class.

#include "stdafx.h"
#include "Launcher.h"
#include "LauncherPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CLauncherPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CLauncherPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CLauncherPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CLauncherPropPage, "LAUNCHER.LauncherPropPage.1",
	0xcd4ae44a, 0xcf90, 0x49e9, 0xbd, 0xea, 0x68, 0x86, 0x1f, 0x97, 0xf7, 0x41)


/////////////////////////////////////////////////////////////////////////////
// CLauncherPropPage::CLauncherPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CLauncherPropPage

BOOL CLauncherPropPage::CLauncherPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_LAUNCHER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherPropPage::CLauncherPropPage - Constructor

CLauncherPropPage::CLauncherPropPage() :
	COlePropertyPage(IDD, IDS_LAUNCHER_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CLauncherPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherPropPage::DoDataExchange - Moves data between page and properties

void CLauncherPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CLauncherPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherPropPage message handlers
