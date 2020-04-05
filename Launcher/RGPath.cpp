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

	// 레지스트리 관련 
	wsprintf(m_strSubKey, "Software\\RevGame\\%s", strContentName);
	lstrcpy(m_strUninstallSubKey, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\RevGame"));
	lstrcpy(m_strUninstallName, _T("레브게임 제거 T.T"));

	// 설치 관련
	lstrcpy(m_strIconFileName, _T("RevLand.ico"));
	lstrcpy(m_strUninstallFileName, _T("RGUninst.exe"));
	
	// Uninstall 파일을 저장할 Path 저장
	GetSystemDirectory(m_strUninstallPath, MAX_PATH);
	lstrcat(m_strUninstallPath, "\\");
	lstrcat(m_strUninstallPath, m_strUninstallFileName);

	// 압축을 풀 대상이 되는 폴더
	wsprintf(m_strDestUnzipDir, "RevGame\\%s", strContentName);

	// FTP에 Content zip 파일이 있는 폴더
	lstrcpy(m_strContentDir, _T("\\Contents"));

	// FTP에 Content zip 파일명
	wsprintf(m_strContentFile, "%s.zip", strContentName);

	// FTP에 Update 파일이 있는 폴더
	wsprintf(m_strUpdateDir, "\\Update\\%s", strContentName);

	// 다운로드 받을 임시 폴더
	GetTempPath(MAX_PATH, m_strTempDir);

	// 다운로드 받은 파일명
	wsprintf(m_strTempFile, "%s\\%s.zip", m_strTempDir, strContentName);
}

// m_strInstallPath이 셋팅된 후에 호출해야 함
void CRGPath::SetExecPath(void)
{
	// 실행할 게임 경로 설정
	// strInstallPath를 바꾸는 이유는 실행파일의 폴더지정을 위해서 이다
	wsprintf(m_strInstallPath, "%s\\RevGame\\%s", m_strInstallPath, m_strContentName);
	wsprintf(m_strExecPath,"%s\\%s.exe",m_strInstallPath, m_strContentName); 
}

// 압축 풀 파일 경로를 만든다
void CRGPath::SetDestUnzipPath(LPCTSTR strItemName)
{
	wsprintf(m_strDestUnzipPath, "%s\\%s", m_strDestUnzipDir, strItemName);
}

// 버젼 파일 이름을 생성한다
void CRGPath::SetUpdateFile(DWORD dwVersion)
{
	wsprintf(m_strUpdateFile, "%s%d.zip", m_strContentName, dwVersion);
}

// 설치 경로를 설정한다
void CRGPath::SetInstallPath(LPCTSTR strInstallPath)
{
	lstrcpy(m_strInstallPath, strInstallPath);

	// 아이콘을 다운 받기 전에 폴더를 생성한다
	wsprintf(m_strIconPath, "%s\\RevGame", strInstallPath);
}

// 아이콘 경로를 설정한다 
void CRGPath::SetIconPath(void)
{
	wsprintf(m_strIconPath, "%s\\RevGame\\%s", m_strInstallPath, m_strIconFileName);
}