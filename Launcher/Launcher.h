#if !defined(AFX_LAUNCHER_H__A9BFC451_80AC_44D2_BDEE_BD540DB31E36__INCLUDED_)
#define AFX_LAUNCHER_H__A9BFC451_80AC_44D2_BDEE_BD540DB31E36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Launcher.h : main header file for LAUNCHER.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLauncherApp : See Launcher.cpp for implementation.

class CLauncherApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAUNCHER_H__A9BFC451_80AC_44D2_BDEE_BD540DB31E36__INCLUDED)
