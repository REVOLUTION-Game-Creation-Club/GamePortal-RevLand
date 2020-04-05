// RGPath.h: interface for the CRGDlg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _RGDLG_
#define _RGDLG_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Singleton.h"

class CRGDlg :
public CSingleton<CRGDlg>
{

public:
	CRGDlg();
	virtual ~CRGDlg();

	void Init(void);

	static BOOL CALLBACK InstallStep1Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK InstallStep2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK InstallStep3Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

inline CRGDlg* GetDlg(void)
{
	return CRGDlg::GetInstance();
}

#endif
