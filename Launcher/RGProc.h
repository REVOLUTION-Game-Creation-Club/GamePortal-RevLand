// Revolution ���¿� 2004�� 11�� 17��

// RGProc.h: interface for the CRGProc class.
// RGProc �� Rev Game Procedure�� �����̸�
// ��ü �帧�� �����Ѵ�
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGPROC_H__12FB096B_C157_4BE2_9FEC_DC04E27F8D87__INCLUDED_)
#define AFX_RGPROC_H__12FB096B_C157_4BE2_9FEC_DC04E27F8D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Singleton.h"

// �� ���� ����� ��Ÿ���� enum ��
typedef enum {
	RT_OK = 0,				// �������� ����
	RT_NO_INSTALL,			// Install�� ���� �ʾ��� ��
	RT_NO_UPDATE,			// Update�� ���� �ʾ��� ��
	RT_INSTALL_FTP_ERR,		// FTP�� Install ������ ���� ���� �ʾ��� ��
	RT_INSTALL_USER_CANCEL,	// User�� ���� Install�� ��� �Ǿ��� ��
	RT_INSTALL_REG_ERR,		// REG�� Install ������ ������ �� ����
	RT_INSTALL_ZIP_ERR,		// Install ���� ���� Ǯ �� ����
	RT_UPDATE_FTP_ERR,		// FTP�� Update ������ ���� ���� �ʾ��� ��
	RT_UPDATE_USER_CANCEL,	// User�� ���� Update�� ��� �Ǿ��� ��
	RT_UPDATE_REG_ERR,		// REG�� Update ������ ������ �� ����
	RT_UPDATE_ZIP_ERR,		// Update ���� ���� Ǯ �� ���� 
	ERR_UNDEF,				// �������� ���� Error
} PROC_RETURN;

class CRGProc :
public CSingleton<CRGProc>
{
private:

	// Procedure�� ����

	typedef enum {
		NONE_S = 0,
		START_S,			// ����
		CHECK_INSTALL_S,	// Install �Ǿ� �ִ� �� üũ
		INSTALL_S,			// Install �Ѵ�
		CHECK_UPDATE_S,		// Update �Ǿ� �ִ� �� üũ
		UPDATE_S,			// Update �Ѵ�
		EXEC_S,				// ������ �����Ѵ�
		EXIT_S
	} PROC_STATE;

	PROC_STATE m_procState;		// ���� State
	PROC_RETURN m_procReturn;	
	
	// �� ���������� �Ѿ�� �����̴�

	TCHAR m_strUserID[64];		// UserID
	TCHAR m_strUserName[64];	// UserName
	TCHAR m_strContentName[64];	// ContentName
	DWORD m_dwScore;					// Score
	DWORD m_dwVersion;					// ������ �ֽ� ����

	HKEY m_hRootKey;		// ������Ʈ�� �ڵ�
	HKEY m_hUninstallKey;	// ���ν��� �ڵ�
	DWORD m_dwRegVersion;	// ������Ʈ���� �ִ� ���� ����

	BOOL MakeURLShortCut(char *URL,char *IconPath,int nFolder,char *szFileName);
	
public:

	CRGProc();
	virtual ~CRGProc();

	void Init(LPCSTR strUserID, LPCSTR strUserName, LPCSTR strContentName, DWORD dwVersion, DWORD dwScore);
	void Exit(void);
	void Procedure(void);

	// Flow Function
	PROC_RETURN CheckInstall(void);
	PROC_RETURN Install(void);
	PROC_RETURN CheckUpdate(void);
	PROC_RETURN Update(void);
	PROC_RETURN Exec(void);

	// Get Method
	DWORD GetVersion(void) { return m_dwVersion; }
	DWORD GetRegVersion(void) { return m_dwRegVersion; }
	BOOL MessageLoop(void);
	PROC_RETURN SetLocalVersion(DWORD* lpdwVersion);
};

inline CRGProc* GetProc(void)
{
	return CRGProc::GetInstance();
}

#endif // !defined(AFX_RGPROC_H__12FB096B_C157_4BE2_9FEC_DC04E27F8D87__INCLUDED_)
