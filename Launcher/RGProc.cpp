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
	// State state �� �����Ѵ� 
	m_procState = START_S;

	// �ʱ� ������ �����´�
	lstrcpy(m_strUserID, strUserID);
	lstrcpy(m_strUserName, strUserName);
	lstrcpy(m_strContentName, strContentName);

	m_dwVersion = dwVersion;
	m_dwScore = dwScore;

	// ������Ʈ�� �ڵ� �ʱ�ȭ
	m_hRootKey = NULL;
	m_hUninstallKey = NULL;
	
	// Com �ʱ�ȭ
	CoInitialize(0);

	// Path �ʱ�ȭ
	GetPath()->Init(strContentName);

	// FTP �ʱ�ȭ
	GetFtp()->Connect(_T("revgame.knu.ac.kr"), _T("anonymous"), _T("guest@rev.knu.ac.kr"));

}

void CRGProc::Exit(void)
{
	switch( m_procReturn )
	{
	case RT_INSTALL_FTP_ERR:
		MessageBox(NULL, "��ġ ������ �ٿ���� ���Ͽ����ϴ�", "�˸�", MB_OK);
		break;
	case RT_INSTALL_ZIP_ERR:
		MessageBox(NULL, "��ġ�� ���������� ���� ���Ͽ����ϴ�", "�˸�", MB_OK);
		break;
	case RT_INSTALL_USER_CANCEL:
		MessageBox(NULL, "������� ���� ��ġ�� �ߴܵǾ����ϴ�", "�˸�", MB_OK);
		break;
	case RT_UPDATE_FTP_ERR:
		MessageBox(NULL, "������Ʈ ������ �ٿ���� ���Ͽ����ϴ�", "�˸�", MB_OK);
		break;
	case RT_UPDATE_ZIP_ERR:
		MessageBox(NULL, "������Ʈ�� ���������� ���� ���Ͽ����ϴ�", "�˸�", MB_OK);
		break;
	case RT_UPDATE_USER_CANCEL:
		MessageBox(NULL, "������� ���� ������Ʈ�� �ߴܵǾ����ϴ�", "�˸�", MB_OK);
		break;
	}

	// ������Ʈ�� ����
	RegCloseKey(m_hRootKey);
	RegCloseKey(m_hUninstallKey);

	// FTP ����
	GetFtp()->DisConnect();

	// Com ����
	CoUninitialize();
}

void CRGProc::Procedure(void)
{
	// Exit State�� �ƴ� �� ���� Flow�� �����Ѵ�

	while(m_procState != EXIT_S)
	{
		switch(m_procState)
		{

		// �����ϸ� Install�� �Ǿ� �ִ��� üũ�Ѵ�	
		case START_S:
			m_procState = CHECK_INSTALL_S;
			break;

		// Install�� �Ǿ� ������ Update�� �Ǿ� �ִ��� üũ�ϰ� 
		// �� �Ǿ� ������ Install �Ѵ�
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

		// Install�� ���������� �ϸ� Update�� �Ǿ� �ִ��� üũ�ϰ�
		// ���������� Install�� ���� ������ Exit�Ѵ�
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

		// Update�� �Ǿ� ������ ���� ������ �ϰ�
		// �׷��� ������ ������Ʈ�� �Ѵ�
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

		// Update�� ���������� �ϸ� ���� ������ �ϰ�
		// �׷��� ������ Exit�� �Ѵ�
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

		// ������ ������ �ϴ� ��Ű�� ��,
		// ���������� ��ġ�� ���� �ʾҴٸ� �ٽ� ��ġ�Ѵ�
		case EXEC_S:
			m_procReturn = Exec();
			switch( m_procReturn )
			{
			case RT_OK:
				m_procState = EXIT_S;
				break;
			case RT_NO_INSTALL:
				MessageBox(NULL, "����� ��ġ���� �ʾ� ��ġ �����縦 �����մϴ�", "�˸�", MB_OK);
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

	// ��ϵ� ������Ʈ���� �ִ� �� üũ
	if( RegOpenKeyEx(HKEY_CURRENT_USER, GetPath()->m_strSubKey, 0, KEY_ALL_ACCESS, &m_hRootKey) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}
	// ��ġ ��� ������ �����´�
	if( RegQueryValueEx(m_hRootKey, "InstallPath", 0, NULL, (LPBYTE)GetPath()->m_strInstallPath, &dwPathLen) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}

	// ���� ������ �����´�
	if( RegQueryValueEx(m_hRootKey, "Version", 0, NULL, (LPBYTE)&m_dwRegVersion, &dwSizeVersion) != ERROR_SUCCESS )
	{
		return RT_NO_INSTALL;
	}
	
	return RT_OK;
}

PROC_RETURN CRGProc::Install(void)
{
	// Install Wizard �� �����Ѵ�
	// �� Dlg������ FTP���� ���� �ٿ�� Unzip ��ġ�� �ַ� �ϰ� ( �����Ȳ�� �����ֱ� �����̴� )
	// �� ���Ŀ� ������Ʈ�� ����� �Ѵ�

	CInstallProperty wzInstallDlg("��ġ");
	wzInstallDlg.SetWizardMode();
	int rc = wzInstallDlg.DoModal();

	if( rc != 12325) // ��ħ ��ư�� Ŭ������ ��� rc�� 12325�� �Ǿ� �ִ�
	{
		if( rc == IDCANCEL )
		{
			rc = RT_INSTALL_USER_CANCEL;
		}
		return (PROC_RETURN)rc;
	}

	// Ű�� ��ġ�Ѵ�
	RegCreateKeyEx(HKEY_CURRENT_USER, GetPath()->m_strSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &m_hRootKey, NULL);

	// ������Ʈ���� ��� ���� ���
	if(RegSetValueEx(m_hRootKey, "InstallPath", 0, REG_SZ, (LPBYTE)GetPath()->m_strInstallPath, lstrlen(GetPath()->m_strInstallPath)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// �ʱ� ��ġ�� �ϸ� Version�� 1�� �ȴ�
	m_dwRegVersion = 1;

	// ������Ʈ���� ���� ���� ���
	if(RegSetValueEx(m_hRootKey, "Version", 0, REG_DWORD, (LPBYTE)&m_dwRegVersion, sizeof(DWORD)) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// ������Ʈ���� Uninstall ���� ���
	
	// Uninstall ������Ʈ�� ���
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, GetPath()->m_strUninstallSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &m_hUninstallKey, NULL);

	// �������� ���α׷� �߰�/���ſ� ǥ�õǴ� �̸�
	if(RegSetValueEx(m_hUninstallKey, "DisplayName", 0, REG_SZ, (LPBYTE)GetPath()->m_strUninstallName, lstrlen(GetPath()->m_strUninstallName)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// ���ν����� �ϱ� ���� �������� Path�� �����մϴ�
	if(RegSetValueEx(m_hUninstallKey, "UninstallString", 0, REG_SZ, (LPBYTE)GetPath()->m_strUninstallPath, lstrlen(GetPath()->m_strUninstallPath)+1) != ERROR_SUCCESS)
	{
		return RT_INSTALL_REG_ERR;
	}

	// ����ȭ�鿡 RevLand ���� url ��Ʈ ���� �����Ѵ�
	MakeURLShortCut("http://revgame.knu.ac.kr", GetPath()->m_strIconPath, CSIDL_DESKTOP, "���귣��.url");

	return RT_OK;
}

PROC_RETURN CRGProc::CheckUpdate(void)
{	
	// ������ üũ�Ͽ�
	// ������������ �Ѱܿ� ��������
	// ������Ʈ���� ��ϵ� ������ ���ٸ� ������Ʈ�� �ʿ��ϴٰ� �Ǵ�
	if( m_dwVersion > m_dwRegVersion )
	{
		return RT_NO_UPDATE;
	}
	// ������Ʈ���� ��ϵ� ������ ������������ �Ѱܿ� �������� 
	// �� ���ٸ�, �߸� ��ġ �Ǿ��ٰ� �Ǵ� ���� ��ġ�Ѵ�
	else if ( m_dwVersion < m_dwRegVersion )
	{
		return RT_NO_INSTALL;
	}
	return RT_OK;
}

PROC_RETURN CRGProc::Update(void)
{
	// ������Ʈ Dialog �� ����
	CUpdateDlg UpdateDlg;
	PROC_RETURN rt = (PROC_RETURN)UpdateDlg.DoModal();
	if(  rt != RT_OK)
	{
		return rt;
	}

	// ������Ʈ�� ���������� ���ƴٸ�,
	// ������ �Ѿ�� ���� ������ ������Ʈ���� ����Ѵ�
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

	// ���� ��θ� �����Ѵ�
	GetPath()->SetExecPath();

	// �Ķ���͸� �����Ѵ�
	// UserID�� Score�� �������Ͽ� �ѱ��
	wsprintf(strParam, "%s %s %d", m_strUserID, m_strUserName, m_dwScore);

	// �����Ų��
	hInst = ShellExecute(NULL,NULL, GetPath()->m_strExecPath, strParam, GetPath()->m_strInstallPath, SW_SHOWNORMAL);

	// ���� ������ ã�� �� ���ٸ�
	if(hInst == (HINSTANCE)ERROR_FILE_NOT_FOUND )
	{
		return RT_NO_INSTALL;
	}
	return RT_OK;
}

// ���ͳ� URL�� ���� ��Ʈ���� Ư�������� ������ ��ο� �����.
// URL:URL
// IconPath:������ ������ Ǯ �н�
// nFolder:Ư�� ����. �� ������ FileName�� ������ ���� ���丮�� ��Ʈ���� �����ȴ�. �� ���� -10�̸� szFolder�� �������̴�.
// szFileName:��Ʈ�� ������ ���ϸ�. ���� ���丮�� ������ �� ������ nFolder�� -1�̸� �����ΰ� �ȴ�.
// ���ϰ�:��Ʈ�� ������ �����ϸ� FALSE�� �����Ѵ�.
// ����:��Ʈ���� ������� ��δ� �ݵ�� �̹� �����ؾ� �Ѵ�.
BOOL CRGProc::MakeURLShortCut(char *URL,char *IconPath,int nFolder,char *szFileName)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST lpidl;
	char szSCPath[MAX_PATH];
	char szShortcutInfo[MAX_PATH];
	HANDLE hFile;
	DWORD dwWritten;

	// ��Ʈ���� ������� ��θ� ���Ѵ�. Ư�� ������ �����ΰ��� ���յǾ� �ϳ��� Ǯ �н��� ���������.
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

	// ��Ʈ�ƿ� ��ϵ� ������ �����.
	wsprintf(szShortcutInfo, "[InternetShortcut]\r\nURL=%s\r\nIconIndex=0\r\nIconFile=%s\r\n"
		"Modified=000000000000000000\r\n",URL, IconPath);

	// ��Ʈ�� ������ �����Ѵ�.
	hFile = CreateFile(szSCPath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile) {
		return FALSE;
	}
	WriteFile(hFile, szShortcutInfo, strlen(szShortcutInfo), &dwWritten, NULL);
	CloseHandle(hFile);

	return TRUE;
}

// �޽��� �����̴�. �����ȿ� �� �Լ��� ȣ�������ν� ����� �Է��� �޵��� �Ѵ�
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
	// ���� ������ ������Ʈ���� ����Ѵ�
	if( RegSetValueEx(m_hRootKey, "Version", 0, REG_DWORD, (LPBYTE)lpdwVersion, sizeof(DWORD)) != ERROR_SUCCESS )
	{
		return RT_UPDATE_REG_ERR;
	}
	return RT_OK; 
}