// Launcher.cpp : Implementation of CLauncherApp and DLL registration.

#include "stdafx.h"
#include "Launcher.h"

// 인증서
// 레지스트리에 clsid를 등록하는 함수이다

#include "cathelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CLauncherApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x88ce394c, 0xb688, 0x49de, { 0xa5, 0x31, 0xbd, 0xdc, 0xfa, 0x9a, 0x45, 0x49 } };


// 인증서 [

const CATID CATID_SafeForScripting     =
                {0x7dd95801,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};
const CATID CATID_SafeForInitializing  =
                {0x7dd95802,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}}; 

const GUID CDECL BASED_CODE _ctlid =
        {0xdd0b32e9, 0x16dc, 0x4c00, 0x82, 0x38, 0x88, 0x39, 0x59, 0x43, 0x70, 0xa4};

// ] 인증서 

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CLauncherApp::InitInstance - DLL initialization

BOOL CLauncherApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CLauncherApp::ExitInstance - DLL termination

int CLauncherApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	// 인증서 [

	if (FAILED( CreateComponentCategory(CATID_SafeForScripting, L"Controls that are safely scriptable") ))
            return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data") ))
            return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( RegisterCLSIDInCategory(_ctlid, CATID_SafeForScripting) ))
            return ResultFromScode(SELFREG_E_CLASS);

    if (FAILED( RegisterCLSIDInCategory(_ctlid, CATID_SafeForInitializing) ))
            return ResultFromScode(SELFREG_E_CLASS);

	// ] 인증서 

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
