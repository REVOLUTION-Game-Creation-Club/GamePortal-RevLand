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
	
	// ������Ʈ�� ���� 

	TCHAR m_strSubKey[MAX_PATH];
	TCHAR m_strInstallPath[MAX_PATH];
	TCHAR m_strExecPath[MAX_PATH];
	TCHAR m_strUninstallSubKey[MAX_PATH];
	TCHAR m_strUninstallName[MAX_PATH];

	// ��ġ ����
	
	TCHAR m_strIconFileName[64];		// ������ ���� �̸�
	TCHAR m_strIconPath[MAX_PATH];		// ������ ���� ���
	TCHAR m_strUninstallFileName[64];	// Uninstall ���� �̸� 
	TCHAR m_strUninstallPath[MAX_PATH];	// Uninstall ���� ���
	TCHAR m_strDestUnzipDir[MAX_PATH];	// ������ Ǯ ����� �Ǵ� ����
	TCHAR m_strDestUnzipPath[MAX_PATH]; // ������ Ǯ ��� ���

	// FTP ����

	TCHAR m_strContentDir[64];			// FTP�� Content zip ������ �ִ� ����
	TCHAR m_strContentFile[64];			// FTP�� Content zip ���ϸ�
	TCHAR m_strUpdateDir[64];			// FTP�� Update ������ �ִ� ����
	TCHAR m_strUpdateFile[64];			// FTP�� Update zip ���ϸ�
	TCHAR m_strTempDir[MAX_PATH];		// �ٿ�ε� ���� �ӽ� ����
	TCHAR m_strTempFile[MAX_PATH];		// �ٿ�ε� ���� ���ϸ�

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
