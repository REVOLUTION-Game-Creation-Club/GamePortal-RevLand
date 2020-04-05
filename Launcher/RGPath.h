// RGPath.h: interface for the CRGPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGPath_H__4FE797D4_B913_4194_A246_A00247E1A667__INCLUDED_)
#define AFX_RGPath_H__4FE797D4_B913_4194_A246_A00247E1A667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Singleton.h"

class CRGPath :
public CSingleton<CRGPath>
{

public:
	CRGPath();
	virtual ~CRGPath();

	// Content Name
	TCHAR m_strContentName[64];
	
	// 레지스트리 관련 

	TCHAR m_strSubKey[MAX_PATH];
	TCHAR m_strInstallPath[MAX_PATH];
	TCHAR m_strExecPath[MAX_PATH];
	TCHAR m_strUninstallSubKey[MAX_PATH];
	TCHAR m_strUninstallName[MAX_PATH];

	// 설치 관련
	
	TCHAR m_strIconFileName[64];		// 아이콘 파일 이름
	TCHAR m_strIconPath[MAX_PATH];		// 아이콘 파일 경로
	TCHAR m_strUninstallFileName[64];	// Uninstall 파일 이름 
	TCHAR m_strUninstallPath[MAX_PATH];	// Uninstall 파일 경로
	TCHAR m_strDestUnzipDir[MAX_PATH];	// 압축을 풀 대상이 되는 폴더
	TCHAR m_strDestUnzipPath[MAX_PATH]; // 압축을 풀 대상 경로

	// FTP 관련

	TCHAR m_strContentDir[64];			// FTP에 Content zip 파일이 있는 폴더
	TCHAR m_strContentFile[64];			// FTP에 Content zip 파일명
	TCHAR m_strUpdateDir[64];			// FTP에 Update 파일이 있는 폴더
	TCHAR m_strUpdateFile[64];			// FTP에 Update zip 파일명
	TCHAR m_strTempDir[MAX_PATH];		// 다운로드 받을 임시 폴더
	TCHAR m_strTempFile[MAX_PATH];		// 다운로드 받은 파일명

	void Init(LPCTSTR strContentName);
	void SetExecPath(void);
	void SetDestUnzipPath(LPCTSTR strItemName);
	void SetUpdateFile(DWORD dwVersion);
	void SetUninstallPath(void);
	void SetInstallPath(LPCTSTR strInstallPath);
	void SetIconPath(void);
};

inline CRGPath* GetPath(void)
{
	return CRGPath::GetInstance();
}

#endif // !defined(AFX_RGPath_H__4FE797D4_B913_4194_A246_A00247E1A667__INCLUDED_)
