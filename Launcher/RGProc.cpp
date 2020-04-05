// RGProc.cpp: implementation of the CRGProc class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <winerror.h>
#include <tchar.h>
#include <shlobj.h>

#include "RGProc.h"
#include "RGPath.h"
#include "RGFtp.h"
#include "RGDlg.h"

#include "InstallProperty.h"
#include "UpdateDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRGProc::CRGProc()
{
	m_procState = NONE_S;
	m_procReturn = RT_OK;
	memset(m_strUserID, 0, sizeof(TCHAR)*64);
	memset(m_strContentName, 0, sizeof(TCHAR)*64);
	m_dwScore = 0;
	m_dwVersion = 0;
	m_dwRegVersion = 0;
	m_hRootKey = NULL;
}

CRGProc::~CRGProc()
{

}
		
void CRGProc::Init(LPCSTR strUserID, LPCSTR strUserName, LPCSTR strContentName, DWORD dwVersion, DWORD dwScore)
{
	// State state 로 지정한다 
	m_procState = START_S;

	// 초기 정보를 가져온다
	lstrcpy(m_strUserID, strUserID);
	lstrcpy(m_strUserName, strUserName);
	lstrcpy(m_strContentName, strContentName);

	m_dwVersion = dwVersion;
	m_dwScore = dwScore;

	// 레지스트리 핸들 초기화
	m_hRootKey = NULL;
	m_hUninstallKey = NULL;
	
	// Com 초기화
	CoInitialize(0);

	// Path 초기화
	GetPath()->Init(strContentName);

	// FTP 초기화
	GetFtp()->Connect(_T("revgame.knu.ac.kr"), _T("anonymous"), _T("guest@rev.knu.ac.kr"));

}

void CRGProc::Exit(void)
{
	switch( m_procReturn )
	{
	case RT_INSTALL_FTP_ERR:
		MessageBox(NULL, "설치 파일을 다운받지 못하였습니다", "알림", MB_OK);
		break;
	case RT_INSTALL_ZIP_ERR:
		MessageBox(NULL, "설치를 정상적으로 하지 못하였습니다", "알림", MB_OK);
		break;
	case RT_INSTALL_USER_CANCEL:
		MessageBox(NULL, "사용자의 의해 설치가 중단되었습니다", "알림", MB_OK);
		break;
	case RT_UPDATE_FTP_ERR:
		MessageBox(NULL, "업데이트 파일을 다운받지 못하였습니다", "알림", MB_OK);
		break;
	case RT_UPDATE_ZIP_ERR:
		MessageBox(NULL, "업데이트를 정상적으로 하지 못하였습니다", "알림", MB_OK);
		break;
	case RT_UPDATE_USER_CANCEL:
		MessageBox(NULL, "사용자의 의해 업데이트가 중단되었습니다", "알림", MB_OK);
		break;
	}

	// 레지스트리 해제
	RegCloseKey(m_hRootKey);
	RegCloseKey(m_hUninstallKey);

	// FTP 해제
	GetFtp()->DisConnect();

	// Com 해제
	CoUninitialize();
}

void CRGProc::Procedure(void)
{
	// Exit State가 아닐 때 까지 Flow을 진행한다

	while(m_procState != EXIT_S)
	{
		switch(m_procState)
		{

		// 시작하면 Install이 되어 있는지 체크한다	
		case START_S:
			m_procState = CHECK_INSTALL_S;
			break;

		// Install이 되어 있으면 Update가 되어 있는지 체크하고 
		// 안 되어 있으면 Install 한다
		case CHECK_INSTALL_S:
			switch( m_procReturn = CheckInstall() )
			{
			case RT_OK:
				m_procState = CHECK_UPDATE_S;
				break;
			case RT_NO_INSTALL:
				m_procState = INSTALL_S;
				break;
			}
			break;

		// Install이 정상적으로 하면 Update가 되어 있는지 체크하고
		// 정상적으로 Install이 되지 않으면 Exit한다
		case INSTALL_S:
			switch( m_procReturn = Install() )
			{
			case RT_OK:
				m_procState = CHECK_UPDATE_S;
				break;
			default:
				m_procState = EXIT_S;
				break;
			}
			break;

		// Update가 되어 있으면 게임 실행을 하고
		// 그렇지 않으면 업데이트를 한다
		case CHECK_UPDATE_S:
			switch( m_procReturn = CheckUpdate() )
			{
			case RT_OK:
				m_procState = EXEC_S;
				break;
			case RT_NO_UPDATE:
				m_procState = UPDATE_S;
				break;
			case RT_NO_INSTALL:
				m_procState = INSTALL_S;
				break;
			}
			break;

		// Update를 정상적으로 하면 게임 실행을 하고
		// 그렇지 않으면 Exit를 한다
		case UPDATE_S:
			switch( m_procReturn = Update() )
			{
			case RT_OK:
				m_procState = EXEC_S;
				break;
			default:
				m_procState = EXIT_S;
				break;
			}
			break;

		// 게임을 실행을 하는 시키는 데,
		// 정상적으로 설치가 되지 않았다면 다시 설치한다
		case EXEC_S:
			m_procReturn = Exec();
			switch( m_procReturn )
			{
			case RT_OK:
				m_procState = EXIT_S;
				break;
			case RT_NO_INSTALL:
				MessageBox(NULL, "제대로 설치되지 않아 설치 마법사를 사직합니다", "알림", MB_OK);
				m_procState = INSTALL_S;
				break;
			}
			break;
		}
	}
	Exit();
}

PROC_RETURN CRGProc::CheckInstall(void)
{
	DWORD dwPathLen = MAX_PATH;
	DWORD dwSizeVersion =  sizeof(DWORD);

	// 등록된 레지스트리가 있는 지 체크
	if( RegOpenKeyEx(HKEY_CURRENT_USER, GetPath()->m_strSubKey, 0, KEY_ALL_ACCESS, &m_hRootKey) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}
	// 설치 경로 정보를 가져온다
	if( RegQueryValueEx(m_hRootKey, "InstallPath", 0, NULL, (LPBYTE)GetPath()->m_strInstallPath, &dwPathLen) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}

	// 버젼 정보를 가져온다
	if( RegQueryValueEx(m_hRootKey, "Version", 0, NULL, (LPBYTE)&m_dwRegVersion, &dwSizeVersion) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}
	
	return RT_OK;
}

PROC_RETURN CRGProc::Install(void)
{
	// Install Wizard 을 실행한다
	// 이 Dlg에서는 FTP에서 파일 다운과 Unzip 설치를 주로 하고 ( 진행상황을 보여주기 위함이다 )
	// 그 이후에 레지스트리 등록을 한다

	CInstallProperty wzInstallDlg("설치");
	wzInstallDlg.SetWizardMode();
	int rc = wzInstallDlg.DoModal();

	if( rc != 12325) // 마침 버튼을 클릭했을 경우 rc는 12325로 되어 있다
	{
		if( rc == IDCANCEL )
		{
			rc = RT_INSTALL_USER_CANCEL;
		}
		return (PROC_RETURN)rc;
	}

	// 키를 설치한다
	RegCreateKeyEx(HKEY_CURRENT_USER, GetPath()->m_strSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &m_hRootKey, NULL);

	// 레지스트리에 경로 정보 등록
	if(RegSetValueEx(m_hRootKey, "InstallPath", 0, REG_SZ, (LPBYTE)GetPath()->m_strInstallPath, lstrlen(GetPath()->m_strInstallPath)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// 초기 설치를 하면 Version은 1로 된다
	m_dwRegVersion = 1;

	// 레지스트리에 버젼 정보 등록
	if(RegSetValueEx(m_hRootKey, "Version", 0, REG_DWORD, (LPBYTE)&m_dwRegVersion, sizeof(DWORD)) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// 레지스트리에 Uninstall 정보 등록
	
	// Uninstall 레지스트리 등록
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, GetPath()->m_strUninstallSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &m_hUninstallKey, NULL);

	// 제어판의 프로그램 추가/제거에 표시되는 이름
	if(RegSetValueEx(m_hUninstallKey, "DisplayName", 0, REG_SZ, (LPBYTE)GetPath()->m_strUninstallName, lstrlen(GetPath()->m_strUninstallName)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// 언인스톨을 하기 위해 실행파일 Path을 지정합니다
	if(RegSetValueEx(m_hUninstallKey, "UninstallString", 0, REG_SZ, (LPBYTE)GetPath()->m_strUninstallPath, lstrlen(GetPath()->m_strUninstallPath)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// 바탕화면에 RevLand 연결 url 쇼트 컷을 생성한다
	MakeURLShortCut("http://revgame.knu.ac.kr", GetPath()->m_strIconPath, CSIDL_DESKTOP, "레브랜드.url");

	return RT_OK;
}

PROC_RETURN CRGProc::CheckUpdate(void)
{	
	// 버젼을 체크하여
	// 웹페이지에서 넘겨온 버젼보다
	// 레지스트리에 등록된 버젼이 낮다면 업데이트가 필요하다고 판단
	if( m_dwVersion > m_dwRegVersion )
	{
		return RT_NO_UPDATE;
	}
	// 레지스트리에 등록된 버젼이 웹페이지에서 넘겨온 버젼보다 
	// 더 높다면, 잘못 설치 되었다고 판단 새로 설치한다
	else if ( m_dwVersion < m_dwRegVersion )
	{
		return RT_NO_INSTALL;
	}
	return RT_OK;
}

PROC_RETURN CRGProc::Update(void)
{
	// 업데이트 Dialog 를 띄운다
	CUpdateDlg UpdateDlg;
	PROC_RETURN rt = (PROC_RETURN)UpdateDlg.DoModal();
	if(  rt != RT_OK)
	{
		return rt;
	}

	// 업데이트를 정상적으로 마쳤다면,
	// 웹에서 넘어온 버젼 정보를 레지스트리에 등록한다
	if( RegSetValueEx(m_hRootKey, "Version", 0, REG_DWORD, (LPBYTE)&m_dwVersion, sizeof(DWORD)) != ERROR_SUCCESS )
	{
		return RT_UPDATE_REG_ERR;
	}

	return RT_OK;
}

PROC_RETURN CRGProc::Exec(void)
{
	HINSTANCE hInst;
	TCHAR strParam[128];

	// 실행 경로를 셋팅한다
	GetPath()->SetExecPath();

	// 파라미터를 설정한다
	// UserID와 Score를 실행파일에 넘긴다
	wsprintf(strParam, "%s %s %d", m_strUserID, m_strUserName, m_dwScore);

	// 실행시킨다
	hInst = ShellExecute(NULL,NULL, GetPath()->m_strExecPath, strParam, GetPath()->m_strInstallPath, SW_SHOWNORMAL);

	// 실행 파일을 찾을 수 없다면
	if(hInst == (HINSTANCE)ERROR_FILE_NOT_FOUND )
	{
		return RT_NO_INSTALL;
	}
	return RT_OK;
}

// 인터넷 URL에 대한 쇼트컷을 특수폴더나 지정한 경로에 만든다.
// URL:URL
// IconPath:아이콘 파일의 풀 패스
// nFolder:특수 폴더. 이 폴더에 FileName이 지정한 서브 디렉토리에 쇼트컷이 생성된다. 이 값이 -10이면 szFolder는 절대경로이다.
// szFileName:쇼트컷 파일의 파일명. 서브 디렉토리를 포함할 수 있으묘 nFolder가 -1이면 절대경로가 된다.
// 리턴값:쇼트컷 생성에 실패하면 FALSE를 리턴한다.
// 주의:쇼트컷이 만들어질 경로는 반드시 이미 존재해야 한다.
BOOL CRGProc::MakeURLShortCut(char *URL,char *IconPath,int nFolder,char *szFileName)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST lpidl;
	char szSCPath[MAX_PATH];
	char szShortcutInfo[MAX_PATH];
	HANDLE hFile;
	DWORD dwWritten;

	// 쇼트컷이 만들어질 경로를 구한다. 특수 폴더와 절대경로값이 조합되어 하나의 풀 패스가 만들어진다.
	if (nFolder != -1) {
		SHGetSpecialFolderLocation(HWND_DESKTOP, nFolder, &lpidl);
		SHGetPathFromIDList(lpidl, szSCPath);
		strcat(szSCPath, "\\");
		strcat(szSCPath, szFileName);
		SHGetMalloc(&pMalloc);
		pMalloc->Free(lpidl);
		pMalloc->Release();
	}
	if (nFolder == -1) {
		strcpy(szSCPath, szFileName);
	}

	// 쇼트컷에 기록될 정보를 만든다.
	wsprintf(szShortcutInfo, "[InternetShortcut]\r\nURL=%s\r\nIconIndex=0\r\nIconFile=%s\r\n"
		"Modified=000000000000000000\r\n",URL, IconPath);

	// 쇼트컷 파일을 생성한다.
	hFile = CreateFile(szSCPath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile) {
		return FALSE;
	}
	WriteFile(hFile, szShortcutInfo, strlen(szShortcutInfo), &dwWritten, NULL);
	CloseHandle(hFile);

	return TRUE;
}

// 메시지 루프이다. 루프안에 이 함수를 호출함으로써 사용자 입력을 받도록 한다
BOOL CRGProc::MessageLoop(void)
{
	MSG Message;
	if(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) 
	{
		if(Message.message == WM_QUIT)
		{
			PostQuitMessage(0);
			return FALSE;
		}

		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return TRUE;
}

PROC_RETURN CRGProc::SetLocalVersion(DWORD* lpdwVersion)
{
	// 버전 정보를 레지스트리에 등록한다
	if( RegSetValueEx(m_hRootKey, "Version", 0, REG_DWORD, (LPBYTE)lpdwVersion, sizeof(DWORD)) != ERROR_SUCCESS )
	{
		return RT_UPDATE_REG_ERR;
	}
	return RT_OK; 
}