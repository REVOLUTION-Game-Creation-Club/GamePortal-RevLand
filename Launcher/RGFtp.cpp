// RGFtp.cpp: implementation of the CRGFtp class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "RGFtp.h"
#include "RGProc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRGFtp::CRGFtp()
{

}

CRGFtp::~CRGFtp()
{

}

BOOL CRGFtp::Connect(LPCSTR strURL, LPCSTR strUserID, LPCSTR strPwd)
{	
	m_hInternet = InternetOpen("FTPTEST", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (m_hInternet == NULL)
	{
		return FALSE;
	}
	
	m_hFtp = InternetConnect(m_hInternet, strURL, INTERNET_DEFAULT_FTP_PORT,
		strUserID,strPwd,INTERNET_SERVICE_FTP,0,0);
	
	if (m_hFtp==NULL) 
	{
		InternetCloseHandle(m_hInternet);
		return FALSE;
	}
	return TRUE;
}

void CRGFtp::DisConnect(void)
{
	InternetCloseHandle(m_hFtp);
	InternetCloseHandle(m_hInternet);
	m_hFtp=NULL;
	m_hInternet=NULL;
}

BOOL CRGFtp::BlockDownload(LPCSTR strRemotePath, LPCSTR strLocalPath)
{	
	return FtpGetFile(m_hFtp, strRemotePath, strLocalPath, FALSE, FILE_ATTRIBUTE_NORMAL,
		FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD,0);
}

BOOL CRGFtp::AsyncDownload(LPCSTR strRemotePath, LPCSTR strLocalPath, CProgressCtrl* lpProgressUnzipCtrl, CString* lpstrDown, CWnd* lpDlg, BOOL* lpbCancel)
{
	HINTERNET hRemote;
	HINTERNET hFind;

	WIN32_FIND_DATA wfd;
	HANDLE hLocal;
	DWORD dwRead,dwWritten,Prog;
	BOOL Result;
	char buf[1000];
	
	// ������ ���� ������ ���´�
	hFind = FtpFindFirstFile(m_hFtp, strRemotePath, &wfd, 0, 0);
	if( hFind == NULL )
	{
		return FALSE;
	}
	InternetCloseHandle(hFind);
	lpProgressUnzipCtrl->SetRange(0, 100);

	// ������ ������ �����Ѵ�.
	hRemote=FtpOpenFile(m_hFtp, strRemotePath, GENERIC_READ,FTP_TRANSFER_TYPE_BINARY,0);
	if (hRemote == NULL)
	{
		return FALSE;
	}

	// ������ Temp ������ �ִٸ� �����Ѵ�
	Result = DeleteFile(strLocalPath);

	// ���� ������ �����.
	hLocal = CreateFile(strLocalPath, GENERIC_WRITE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(hLocal == INVALID_HANDLE_VALUE)
	{
		InternetCloseHandle(hRemote);
		return FALSE;
	}

	// 1000����Ʈ�� ������ ���� ���¸� ����Ѵ�.
	int nCount = 0;
	Prog=0;
	for (;;) {
		Result=InternetReadFile(hRemote,buf,1000,&dwRead);
		if ((Result==TRUE) && (dwRead==0))
			break;
		WriteFile(hLocal,buf,dwRead,&dwWritten,NULL);
		Prog+=dwWritten;

		nCount++;

		lpProgressUnzipCtrl->SetPos((int)(((double)(Prog)/(double)((wfd.nFileSizeHigh*MAXDWORD) + wfd.nFileSizeLow))*100.0));

		if( nCount % 100 == 0 )                         
		{
			lpstrDown->Format("%d / %d KB �ٿ� ���Դϴ�", Prog/1024, wfd.nFileSizeLow/1024);
			lpDlg->UpdateData(FALSE);
		}

		// �����ȿ��� ����� �Է��� ���� �� �ְ� �Ѵ�
		GetProc()->MessageLoop();

		// ȣ���ϴ� �����쿡�� Cancel ��ư�� ������ ��� �ٿ�ε带 �����Ѵ�
		if( *lpbCancel == TRUE)
		{
			CloseHandle(hLocal);
			InternetCloseHandle(hRemote);
			return FALSE;
		}
	}
	
	*lpstrDown = _T("���������� �ٿ� �޾ҽ��ϴ�");
	lpDlg->UpdateData(FALSE);

	CloseHandle(hLocal);
	InternetCloseHandle(hRemote);
	return TRUE;
}

BOOL CRGFtp::ChangeDir(LPCSTR strChangeDir)
{
	return FtpSetCurrentDirectory(m_hFtp, strChangeDir);
}
