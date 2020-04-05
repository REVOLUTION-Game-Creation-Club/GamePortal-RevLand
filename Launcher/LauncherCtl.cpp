// LauncherCtl.cpp : Implementation of the CLauncherCtrl ActiveX Control class.

#include "stdafx.h"
#include "Launcher.h"
#include "LauncherCtl.h"
#include "LauncherPpg.h"
#include "RGProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CLauncherCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CLauncherCtrl, COleControl)
	//{{AFX_MSG_MAP(CLauncherCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CLauncherCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CLauncherCtrl)
	DISP_FUNCTION(CLauncherCtrl, "LauchContent", LauchContent, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CLauncherCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CLauncherCtrl, COleControl)
	//{{AFX_EVENT_MAP(CLauncherCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CLauncherCtrl, 1)
	PROPPAGEID(CLauncherPropPage::guid)
END_PROPPAGEIDS(CLauncherCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CLauncherCtrl, "LAUNCHER.LauncherCtrl.1",
	0xdd0b32e9, 0x16dc, 0x4c00, 0x82, 0x38, 0x88, 0x39, 0x59, 0x43, 0x70, 0xa4)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CLauncherCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DLauncher =
		{ 0x109b3172, 0x3df4, 0x45f6, { 0x85, 0xbc, 0xb5, 0xc0, 0x55, 0xb3, 0xd0, 0x43 } };
const IID BASED_CODE IID_DLauncherEvents =
		{ 0x4c547a57, 0x5e8c, 0x4040, { 0xac, 0x2d, 0x26, 0x95, 0xfa, 0xfc, 0xf9, 0x28 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwLauncherOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CLauncherCtrl, IDS_LAUNCHER, _dwLauncherOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::CLauncherCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CLauncherCtrl

BOOL CLauncherCtrl::CLauncherCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_LAUNCHER,
			IDB_LAUNCHER,
			afxRegApartmentThreading,
			_dwLauncherOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::CLauncherCtrl - Constructor

CLauncherCtrl::CLauncherCtrl()
{
	InitializeIIDs(&IID_DLauncher, &IID_DLauncherEvents);
	m_bitIcon.LoadBitmap(IDB_LAUNCHER);
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::~CLauncherCtrl - Destructor

CLauncherCtrl::~CLauncherCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::OnDraw - Drawing function

void CLauncherCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CBitmap* lpOldBitmap;
	CDC memdc;
	memdc.CreateCompatibleDC(pdc);
	lpOldBitmap = (CBitmap*)memdc.SelectObject(&m_bitIcon);
	pdc->BitBlt(0,0, 50, 15, &memdc, 0, 0, SRCCOPY);
	memdc.SelectObject(lpOldBitmap);
	lpOldBitmap->DeleteObject();
	memdc.DeleteDC();
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::DoPropExchange - Persistence support

void CLauncherCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::OnResetState - Reset control to default state

void CLauncherCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl::AboutBox - Display an "About" box to the user

void CLauncherCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_LAUNCHER);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl message handlers

void CLauncherCtrl::LauchContent(LPCTSTR strUserID, LPCTSTR strUserName, LPCTSTR strContentName, long dwVersion, long dwScore) 
{
	GetProc()->Init(strUserID, strUserName, strContentName, dwVersion, dwScore);
	GetProc()->Procedure();
}
