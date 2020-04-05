// RGFtp.h: interface for the CRGFtp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGFTP_H__AF547F0A_629D_40B9_BC3C_BF4E7FA34AAF__INCLUDED_)
#define AFX_RGFTP_H__AF547F0A_629D_40B9_BC3C_BF4E7FA34AAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <wininet.h>
#include "Singleton.h"

class CRGFtp:
public CSingleton<CRGFtp>  
{
	
private:
	HINTERNET m_hInternet;
	HINTERNET m_hFtp;

public:
	CRGFtp();
	virtual ~CRGFtp();

	BOOL Connect(LPCSTR strURL, LPCSTR strUserID, LPCSTR strPwd);
	void DisConnect(void);
	BOOL BlockDownload(LPCSTR strRemotePath, LPCSTR strLocalPath);
	BOOL AsyncDownload(LPCSTR strRemotePath, LPCSTR strLocalPath, CProgressCtrl* lpProgressUnzipCtrl, CString* lpstrDown, CWnd* lpDlg, BOOL* lpbCancel);
	BOOL ChangeDir(LPCSTR strDir);
};

inline CRGFtp* GetFtp(void)
{
	return CRGFtp::GetInstance();
}

#endif // !defined(AFX_RGFTP_H__AF547F0A_629D_40B9_BC3C_BF4E7FA34AAF__INCLUDED_)
