// RGPath.cpp: implementation of the CRGPath class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <tchar.h>
#include "RGPath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRGPath::CRGPath()
{

}

CRGPath::~CRGPath()
{

}

void CRGPath::Init(LPCTSTR strContentName)
{
	lstrcpy(m_strContentName, strContentName);

	// ������Ʈ�� ���� 
	wsprintf(m_strSubKey, "Software\\RevGame\\%s", strContentName);
	lstrcpy(m_strUninstallSubKey, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\RevGame"));
	lstrcpy(m_strUninstallName, _T("������� ���� T.T"));

	// ��ġ ����
	lstrcpy(m_strIconFileName, _T("RevLand.ico"));
	lstrcpy(m_strUninstallFileName, _T("RGUninst.exe"));
	
	// Uninstall ������ ������ Path ����
	GetSystemDirectory(m_strUninstallPath, MAX_PATH);
	lstrcat(m_strUninstallPath, "\\");
	lstrcat(m_strUninstallPath, m_strUninstallFileName);

	// ������ Ǯ ����� �Ǵ� ����
	wsprintf(m_strDestUnzipDir, "RevGame\\%s", strContentName);

	// FTP�� Content zip ������ �ִ� ����
	lstrcpy(m_strContentDir, _T("\\Contents"));

	// FTP�� Content zip ���ϸ�
	wsprintf(m_strContentFile, "%s.zip", strContentName);

	// FTP�� Update ������ �ִ� ����
	wsprintf(m_strUpdateDir, "\\Update\\%s", strContentName);

	// �ٿ�ε� ���� �ӽ� ����
	GetTempPath(MAX_PATH, m_strTempDir);

	// �ٿ�ε� ���� ���ϸ�
	wsprintf(m_strTempFile, "%s\\%s.zip", m_strTempDir, strContentName);
}

// m_strInstallPath�� ���õ� �Ŀ� ȣ���ؾ� ��
void CRGPath::SetExecPath(void)
{
	// ������ ���� ��� ����
	// strInstallPath�� �ٲٴ� ������ ���������� ���������� ���ؼ� �̴�
	wsprintf(m_strInstallPath, "%s\\RevGame\\%s", m_strInstallPath, m_strContentName);
	wsprintf(m_strExecPath,"%s\\%s.exe",m_strInstallPath, m_strContentName); 
}

// ���� Ǯ ���� ��θ� �����
void CRGPath::SetDestUnzipPath(LPCTSTR strItemName)
{
	wsprintf(m_strDestUnzipPath, "%s\\%s", m_strDestUnzipDir, strItemName);
}

// ���� ���� �̸��� �����Ѵ�
void CRGPath::SetUpdateFile(DWORD dwVersion)
{
	wsprintf(m_strUpdateFile, "%s%d.zip", m_strContentName, dwVersion);
}

// ��ġ ��θ� �����Ѵ�
void CRGPath::SetInstallPath(LPCTSTR strInstallPath)
{
	lstrcpy(m_strInstallPath, strInstallPath);

	// �������� �ٿ� �ޱ� ���� ������ �����Ѵ�
	wsprintf(m_strIconPath, "%s\\RevGame", strInstallPath);
}

// ������ ��θ� �����Ѵ� 
void CRGPath::SetIconPath(void)
{
	wsprintf(m_strIconPath, "%s\\RevGame\\%s", m_strInstallPath, m_strIconFileName);
}