#include <windows.h>
#include <TCHAR.H>
#include <shlobj.h>

#include "resource.h"
 
#define MAX_GAME 256 // 최대 게임 수 이다

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

// Window 핸들
HWND g_hDlgMain;
HWND g_hList;
HWND g_hButton;
HWND g_hEdit;

HKEY g_hRootKey;

TCHAR g_listInstallPath[MAX_GAME][MAX_PATH];

DWORD g_dwGameCount;

DWORD RegEnum(HKEY key);
DWORD UpdateReg(void);
BOOL DeleteTree(char *path);
BOOL Uninstall(char* strContentName);
BOOL UninstallRoot(void);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
        g_hInst = hInstance;
        DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG), HWND_DESKTOP, MainDlgProc);
        return 0;
}
 
BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage, WPARAM wParam, LPARAM lParam)
{
        switch(iMessage)
        {
        case WM_INITDIALOG:
                g_hDlgMain = hDlg;
				g_hButton = GetDlgItem(hDlg, IDC_UNINSTALL_BTN);
				g_hList = GetDlgItem(hDlg, IDC_LIST);
				g_hEdit = GetDlgItem(hDlg, IDC_PROGRESS_EDIT);

				SetDlgItemText(hDlg, IDC_PROGRESS_EDIT, "");

				if( !UpdateReg() )
				{
					SetWindowText(g_hEdit, "알림 : 설치 경로를 찾을 수 없습니다");
					EnableWindow(g_hButton, FALSE);
				}
                return TRUE;
 
        case WM_COMMAND:
                switch(LOWORD(wParam))
                {
                case IDOK:
                case IDCANCEL:
                    EndDialog(hDlg, 0);
                    return TRUE;
				// 제거 버튼을 눌렸을 때
				case IDC_UNINSTALL_BTN:
					{
						char strContentName[MAX_PATH];
						int nCount;
						
						// 설치된 게임 갯수를 가져온다
						nCount = SendMessage(g_hList, LB_GETCOUNT, 0, 0);

						// 제거 버튼을 비활성화 시킨다
						EnableWindow(g_hButton, FALSE);

						if( nCount == 0 )
						{
							SetWindowText(g_hEdit, "알림 : 설치 경로를 찾을 수 없습니다");
							return FALSE;
						}

						for(int i=0; i<nCount; i++)
						{
							SendMessage(g_hList, LB_SETCURSEL, (WPARAM)i, 0);
							SendMessage(g_hList, LB_GETTEXT, i, (LPARAM)strContentName);
							if( Uninstall(strContentName) == FALSE )
							{
								SetWindowText(g_hEdit, "알림 : 정상적으로 삭제하지 못하였습니다");
							}
						}	

						UpdateReg();
						if( UninstallRoot() == FALSE )
						{
							SetWindowText(g_hEdit, "알림 : 정상적으로 삭제하지 못하였습니다");
						}

						// 제거 버튼을 활성화 시킨다
						EnableWindow(g_hButton, TRUE);
					}
                }
                return FALSE;
        }
        return FALSE;
}

// 레지스트리 키를 열어 RegEum 함수를 호출해 리스트를 업데이트 하고 갯수를 구한다
DWORD UpdateReg(void)
{
	DWORD dwPathLen = MAX_PATH;
	DWORD dwRt = 0;

	// 등록된 레지스트리가 있는 지 체크
	if( RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\RevGame", 0, KEY_ALL_ACCESS, &g_hRootKey) != ERROR_SUCCESS )
	{
		return 0;
	}

	dwRt = RegEnum(g_hRootKey);
	RegCloseKey(g_hRootKey);
	return dwRt;
}


// key아래의 모든 서브 키와 값을 조사한다.
DWORD RegEnum(HKEY key)
{
	char lpSubKey[MAX_PATH];
	char lpValue[MAX_PATH];

	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime;

	SendMessage(g_hList,LB_RESETCONTENT,0,0);

	// 서브키의 목록의 조사해 리스트 박스에 채워 넣는다.
	Result=ERROR_SUCCESS;
	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumKeyEx(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
		if (Result==ERROR_SUCCESS) {
			SendMessage(g_hList,LB_ADDSTRING,0,(LONG)lpSubKey);
		}
	}

	// 값의 목록을 조사해 리스트 박스에 채워 넣는다.
	Result=ERROR_SUCCESS;
	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumValue(key,i,lpValue,&Size,NULL,NULL,NULL,NULL);
		if (Result==ERROR_SUCCESS) {
			SendMessage(g_hList,LB_ADDSTRING,0,(LONG)lpValue);
		}
	}
	return i;
}

// 지정한 패스의 디렉토리를 하위 디렉토리까지 삭제한다.
// 원칙적으로 D:\Path\*.*형태로 디렉토리를 지정해야 하나 D:\Path로 넘겨주어도 된다.
BOOL DeleteTree(char *path)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	char fname[MAX_PATH];
	BOOL bResult=TRUE;
	char drive[_MAX_DRIVE];
	char dir[MAX_PATH];
	char newpath[MAX_PATH];

	// 삭제대상 디렉토리는 최소한 C:\D 정도의 길이를 가져야 한다. C: 등과 인수가 혹시
	// 잘못 전달될 경우를 위한 최소한의 안전장치이다.
	if (strlen(path) <= 4)
		return FALSE;

	// \*.*가 붙어있지 않을 경우 붙여준다.
	strcpy(newpath,path);
	if (strcmp(newpath+strlen(newpath)-4,"\\*.*") != 0)
		strcat(newpath,"\\*.*");
	hSrch=FindFirstFile(newpath,&wfd);
	if (hSrch == INVALID_HANDLE_VALUE) 
		return FALSE;
	_splitpath(newpath,drive,dir,NULL,NULL);
	while (bResult) {
		wsprintf(fname,"%s%s%s",drive,dir,wfd.cFileName);
		SetWindowText(g_hEdit, wfd.cFileName);
		// 읽기 전용 속성을 가진 경우 이 속성을 먼저 해제한다.
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
			SetFileAttributes(fname,FILE_ATTRIBUTE_NORMAL);
		}
		// 서브 디렉토리가 발견되면 디렉토리 안까지 삭제한다. '.', '..'은 제외
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (wfd.cFileName[0]!='.') {
				wsprintf(newpath,"%s%s%s\\*.*",drive,dir,wfd.cFileName);
				DeleteTree(newpath);
			}
		} else {
			DeleteFile(fname);
		}
		bResult=FindNextFile(hSrch,&wfd);
	}
	FindClose(hSrch);
	// 마지막으로 자기 자신을 삭제한다.끝의 \를 제거한다.
	wsprintf(fname, "%s%s", drive, dir);
	fname[strlen(fname)-1] = 0;
	if (RemoveDirectory(fname) == FALSE) {
		// 탐색기가 사용하고 있는 폴더는 삭제되지 않으므로 에러처리를 하였다. 그러나 굳이 필요한 것은 아니다.
		//DWORD err=GetLastError();
		//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,err,0,newpath,MAX_PATH,NULL);
		//MessageBox(NULL, newpath,"알림",MB_OK);
		//return FALSE;
	}
	return TRUE;
}

// Content의 설치 파일과 레지스트리 값을 삭제 한다
BOOL Uninstall(char* strContentName)
{
	HKEY hRootKey;
	HKEY hSubKey;
	TCHAR strSubKey[MAX_PATH];
	TCHAR strInstallPath[MAX_PATH];
	DWORD dwPathLen = MAX_PATH;

	// Content의 SubKey를 셋팅한다
	wsprintf(strSubKey, "Software\\RevGame\\%s", strContentName);

	// 등록된 레지스트리가 있는 지 체크
	if( RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}
	
	// 설치 경로 정보를 가져온다
	if( RegQueryValueEx(hSubKey, "InstallPath", 0, NULL, (LPBYTE)strInstallPath, &dwPathLen) != ERROR_SUCCESS )
	{
		return FALSE;
	}

	// 설치 경로를 설정한다
	lstrcat(strInstallPath, "\\Revgame\\");

	lstrcat(g_listInstallPath[g_dwGameCount++], strInstallPath);
	lstrcat(strInstallPath, strContentName);

	// 설치된 경로를 모두 삭제한다
	DeleteTree(strInstallPath);

	RegCloseKey(hSubKey);

	// 등록된 Content 레지스트리를 삭제한다
	if( RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\RevGame", 0, KEY_ALL_ACCESS, &hRootKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}

	RegDeleteKey(hRootKey, strContentName);
	RegCloseKey(hRootKey);

	return TRUE;
}

BOOL UninstallRoot(void)
{
	HKEY hRootKey;

	// 각 Content의 Install Path를 모두 삭제한다
	for(DWORD i=0; i<= g_dwGameCount; i++)
	{
		DeleteTree(g_listInstallPath[i]);
	}

	// RevGame 레지스트리를 삭제한다
	if( RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS, &hRootKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}

	RegDeleteKey(hRootKey, "RevGame");
	RegCloseKey(hRootKey);


	// RevGame 레지스트리를 삭제한다
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS, &hRootKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}
	RegDeleteKey(hRootKey, "RevGame");
	RegCloseKey(hRootKey);

	// 바탕화면에 아이콘이 있다면 삭제한다

	LPMALLOC pMalloc;
	LPITEMIDLIST lpidl;
	char szSCPath[MAX_PATH];

	SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DESKTOP, &lpidl);
	SHGetPathFromIDList(lpidl, szSCPath);
	strcat(szSCPath, "\\");
	strcat(szSCPath, "레브랜드.url");
	SHGetMalloc(&pMalloc);
	pMalloc->Free(lpidl);
	pMalloc->Release();

	// 파일을 삭제한다
	DeleteFile(szSCPath);

	SetWindowText(g_hEdit, _T("정상적으로 제거를 하였습니다"));
	return TRUE;
}