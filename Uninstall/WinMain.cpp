#include <windows.h>
#include <TCHAR.H>
#include <shlobj.h>

#include "resource.h"
 
#define MAX_GAME 256 // �ִ� ���� �� �̴�

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

// Window �ڵ�
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
					SetWindowText(g_hEdit, "�˸� : ��ġ ��θ� ã�� �� �����ϴ�");
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
				// ���� ��ư�� ������ ��
				case IDC_UNINSTALL_BTN:
					{
						char strContentName[MAX_PATH];
						int nCount;
						
						// ��ġ�� ���� ������ �����´�
						nCount = SendMessage(g_hList, LB_GETCOUNT, 0, 0);

						// ���� ��ư�� ��Ȱ��ȭ ��Ų��
						EnableWindow(g_hButton, FALSE);

						if( nCount == 0 )
						{
							SetWindowText(g_hEdit, "�˸� : ��ġ ��θ� ã�� �� �����ϴ�");
							return FALSE;
						}

						for(int i=0; i<nCount; i++)
						{
							SendMessage(g_hList, LB_SETCURSEL, (WPARAM)i, 0);
							SendMessage(g_hList, LB_GETTEXT, i, (LPARAM)strContentName);
							if( Uninstall(strContentName) == FALSE )
							{
								SetWindowText(g_hEdit, "�˸� : ���������� �������� ���Ͽ����ϴ�");
							}
						}	

						UpdateReg();
						if( UninstallRoot() == FALSE )
						{
							SetWindowText(g_hEdit, "�˸� : ���������� �������� ���Ͽ����ϴ�");
						}

						// ���� ��ư�� Ȱ��ȭ ��Ų��
						EnableWindow(g_hButton, TRUE);
					}
                }
                return FALSE;
        }
        return FALSE;
}

// ������Ʈ�� Ű�� ���� RegEum �Լ��� ȣ���� ����Ʈ�� ������Ʈ �ϰ� ������ ���Ѵ�
DWORD UpdateReg(void)
{
	DWORD dwPathLen = MAX_PATH;
	DWORD dwRt = 0;

	// ��ϵ� ������Ʈ���� �ִ� �� üũ
	if( RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\RevGame", 0, KEY_ALL_ACCESS, &g_hRootKey) != ERROR_SUCCESS )
	{
		return 0;
	}

	dwRt = RegEnum(g_hRootKey);
	RegCloseKey(g_hRootKey);
	return dwRt;
}


// key�Ʒ��� ��� ���� Ű�� ���� �����Ѵ�.
DWORD RegEnum(HKEY key)
{
	char lpSubKey[MAX_PATH];
	char lpValue[MAX_PATH];

	DWORD i;
	LONG Result;
	DWORD Size;
	FILETIME FileTime;

	SendMessage(g_hList,LB_RESETCONTENT,0,0);

	// ����Ű�� ����� ������ ����Ʈ �ڽ��� ä�� �ִ´�.
	Result=ERROR_SUCCESS;
	for (i=0;Result==ERROR_SUCCESS;i++) {
		Size=MAX_PATH;
		Result=RegEnumKeyEx(key,i,lpSubKey,&Size,NULL,NULL,NULL,&FileTime);
		if (Result==ERROR_SUCCESS) {
			SendMessage(g_hList,LB_ADDSTRING,0,(LONG)lpSubKey);
		}
	}

	// ���� ����� ������ ����Ʈ �ڽ��� ä�� �ִ´�.
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

// ������ �н��� ���丮�� ���� ���丮���� �����Ѵ�.
// ��Ģ������ D:\Path\*.*���·� ���丮�� �����ؾ� �ϳ� D:\Path�� �Ѱ��־ �ȴ�.
BOOL DeleteTree(char *path)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	char fname[MAX_PATH];
	BOOL bResult=TRUE;
	char drive[_MAX_DRIVE];
	char dir[MAX_PATH];
	char newpath[MAX_PATH];

	// ������� ���丮�� �ּ��� C:\D ������ ���̸� ������ �Ѵ�. C: ��� �μ��� Ȥ��
	// �߸� ���޵� ��츦 ���� �ּ����� ������ġ�̴�.
	if (strlen(path) <= 4)
		return FALSE;

	// \*.*�� �پ����� ���� ��� �ٿ��ش�.
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
		// �б� ���� �Ӽ��� ���� ��� �� �Ӽ��� ���� �����Ѵ�.
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
			SetFileAttributes(fname,FILE_ATTRIBUTE_NORMAL);
		}
		// ���� ���丮�� �߰ߵǸ� ���丮 �ȱ��� �����Ѵ�. '.', '..'�� ����
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
	// ���������� �ڱ� �ڽ��� �����Ѵ�.���� \�� �����Ѵ�.
	wsprintf(fname, "%s%s", drive, dir);
	fname[strlen(fname)-1] = 0;
	if (RemoveDirectory(fname) == FALSE) {
		// Ž���Ⱑ ����ϰ� �ִ� ������ �������� �����Ƿ� ����ó���� �Ͽ���. �׷��� ���� �ʿ��� ���� �ƴϴ�.
		//DWORD err=GetLastError();
		//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,err,0,newpath,MAX_PATH,NULL);
		//MessageBox(NULL, newpath,"�˸�",MB_OK);
		//return FALSE;
	}
	return TRUE;
}

// Content�� ��ġ ���ϰ� ������Ʈ�� ���� ���� �Ѵ�
BOOL Uninstall(char* strContentName)
{
	HKEY hRootKey;
	HKEY hSubKey;
	TCHAR strSubKey[MAX_PATH];
	TCHAR strInstallPath[MAX_PATH];
	DWORD dwPathLen = MAX_PATH;

	// Content�� SubKey�� �����Ѵ�
	wsprintf(strSubKey, "Software\\RevGame\\%s", strContentName);

	// ��ϵ� ������Ʈ���� �ִ� �� üũ
	if( RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}
	
	// ��ġ ��� ������ �����´�
	if( RegQueryValueEx(hSubKey, "InstallPath", 0, NULL, (LPBYTE)strInstallPath, &dwPathLen) != ERROR_SUCCESS )
	{
		return FALSE;
	}

	// ��ġ ��θ� �����Ѵ�
	lstrcat(strInstallPath, "\\Revgame\\");

	lstrcat(g_listInstallPath[g_dwGameCount++], strInstallPath);
	lstrcat(strInstallPath, strContentName);

	// ��ġ�� ��θ� ��� �����Ѵ�
	DeleteTree(strInstallPath);

	RegCloseKey(hSubKey);

	// ��ϵ� Content ������Ʈ���� �����Ѵ�
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

	// �� Content�� Install Path�� ��� �����Ѵ�
	for(DWORD i=0; i<= g_dwGameCount; i++)
	{
		DeleteTree(g_listInstallPath[i]);
	}

	// RevGame ������Ʈ���� �����Ѵ�
	if( RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS, &hRootKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}

	RegDeleteKey(hRootKey, "RevGame");
	RegCloseKey(hRootKey);


	// RevGame ������Ʈ���� �����Ѵ�
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS, &hRootKey) != ERROR_SUCCESS )
	{
		return FALSE;
	}
	RegDeleteKey(hRootKey, "RevGame");
	RegCloseKey(hRootKey);

	// ����ȭ�鿡 �������� �ִٸ� �����Ѵ�

	LPMALLOC pMalloc;
	LPITEMIDLIST lpidl;
	char szSCPath[MAX_PATH];

	SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DESKTOP, &lpidl);
	SHGetPathFromIDList(lpidl, szSCPath);
	strcat(szSCPath, "\\");
	strcat(szSCPath, "���귣��.url");
	SHGetMalloc(&pMalloc);
	pMalloc->Free(lpidl);
	pMalloc->Release();

	// ������ �����Ѵ�
	DeleteFile(szSCPath);

	SetWindowText(g_hEdit, _T("���������� ���Ÿ� �Ͽ����ϴ�"));
	return TRUE;
}