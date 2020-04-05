// Revolution 김태영 2004년 11월 17일

// RGProc.h: interface for the CRGProc class.
// RGProc 은 Rev Game Procedure의 약자이며
// 전체 흐름을 제어한다
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGPROC_H__12FB096B_C157_4BE2_9FEC_DC04E27F8D87__INCLUDED_)
#define AFX_RGPROC_H__12FB096B_C157_4BE2_9FEC_DC04E27F8D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Singleton.h"

// 각 수행 결과를 나타내는 enum 값
typedef enum {
	RT_OK = 0,				// 정상적인 동작
	RT_NO_INSTALL,			// Install이 되지 않았을 때
	RT_NO_UPDATE,			// Update가 되지 않았을 때
	RT_INSTALL_FTP_ERR,		// FTP에 Install 파일이 연결 되지 않았을 때
	RT_INSTALL_USER_CANCEL,	// User에 의해 Install이 취소 되었을 때
	RT_INSTALL_REG_ERR,		// REG에 Install 정보를 저장할 때 에러
	RT_INSTALL_ZIP_ERR,		// Install 파일 압축 풀 때 에러
	RT_UPDATE_FTP_ERR,		// FTP의 Update 파일이 연결 되지 않았을 때
	RT_UPDATE_USER_CANCEL,	// User에 의해 Update이 취소 되었을 때
	RT_UPDATE_REG_ERR,		// REG에 Update 정보를 저장할 때 에러
	RT_UPDATE_ZIP_ERR,		// Update 파일 압축 풀 때 에러 
	ERR_UNDEF,				// 정해지지 않은 Error
} PROC_RETURN;

class CRGProc :
public CSingleton<CRGProc>
{
private:

	// Procedure의 상태

	typedef enum {
		NONE_S = 0,
		START_S,			// 시작
		CHECK_INSTALL_S,	// Install 되어 있는 지 체크
		INSTALL_S,			// Install 한다
		CHECK_UPDATE_S,		// Update 되어 있는 지 체크
		UPDATE_S,			// Update 한다
		EXEC_S,				// 게임을 실행한다
		EXIT_S
	} PROC_STATE;

	PROC_STATE m_procState;		// 현재 State
	PROC_RETURN m_procReturn;	
	
	// 웹 페이지에서 넘어온 정보이다

	TCHAR m_strUserID[64];		// UserID
	TCHAR m_strUserName[64];	// UserName
	TCHAR m_strContentName[64];	// ContentName
	DWORD m_dwScore;					// Score
	DWORD m_dwVersion;					// 게임의 최신 버젼

	HKEY m_hRootKey;		// 레지스트리 핸들
	HKEY m_hUninstallKey;	// 언인스톨 핸들
	DWORD m_dwRegVersion;	// 레지스트리에 있는 버젼 정보

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
