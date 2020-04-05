// RGPath.cpp: implementation of the CRGDlg class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "RGDlg.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRGDlg::CRGDlg()
{
	
}

CRGDlg::~CRGDlg()
{

}

void CRGDlg::Init(void)
{
	InitCommonControls();
        
	MessageBox(NULL, "ASdf", "ASdf", MB_OK);
}

BOOL CALLBACK CRGDlg::InstallStep1Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_NOTIFY:
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK CRGDlg::InstallStep2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_NOTIFY:
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK CRGDlg::InstallStep3Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_NOTIFY:
		return TRUE;
	}
	return FALSE;
}
