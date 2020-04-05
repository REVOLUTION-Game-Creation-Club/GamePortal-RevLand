// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "UpdateDlg.h"

#include  <io.h> // for _tcaccess

#include "XZip.h"
#include "XUnzip.h"

#include "RGProc.h"
#include "RGFtp.h"
#include "RGPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog


CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
	m_strUpdateDown = _T("");
	m_strUpdateUnzip = _T("");
	m_strUpdateVer = _T("");
	//}}AFX_DATA_INIT

	m_bCancel = FALSE;
}


void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	DDX_Control(pDX, IDC_UPDATE_VER_PROGRESS, m_progUpdateVerCtrl);
	DDX_Control(pDX, IDC_UPDATE_UNZIP_PROGRESS, m_progUpdateUnzipCtrl);
	DDX_Control(pDX, IDC_UPDATE_DOWN_PROGRESS, m_progUpdateDownCtrl);
	DDX_Text(pDX, IDC_UPDATE_DOWN_STATIC, m_strUpdateDown);
	DDX_Text(pDX, IDC_UPDATE_UNZIP_STATIC, m_strUpdateUnzip);
	DDX_Text(pDX, IDC_UPDATE_VER_STATIC, m_strUpdateVer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers

BOOL CUpdateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_hTimer = (HANDLE)SetTimer(1, 500, NULL);
	
	m_progUpdateVerCtrl.SetPos(0);
	m_progUpdateDownCtrl.SetPos(0);
	m_progUpdateUnzipCtrl.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CUpdateDlg::Unzip(LPCSTR strSrcFile)
{

#ifdef _UNICODE
	ZIPENTRYW ze;
#else
	ZIPENTRY ze; 
#endif

	HZIP hz;
		
	hz = OpenZip((void*)strSrcFile, (LPCTSTR)GetPath()->m_strInstallPath, 0, ZIP_FILENAME);

	if( hz == 0 )
	{
		return FALSE;
	}

	ZRESULT zr = GetZipItem(hz, -1, &ze); 

	if( zr != ZR_OK )
	{
		CloseZip(hz);
		return FALSE;
	}

	int numitems = ze.index;

	m_progUpdateUnzipCtrl.SetRange(0, numitems-1);

	for (int i = 0; i < numitems; i++)
	{ 
		GetZipItem(hz, i, &ze);
		
		GetPath()->SetDestUnzipPath(ze.name);

		m_strUpdateUnzip.Format("%s", ze.name);

		UpdateData(FALSE);

 		// delete target file if it exists
		::DeleteFile(GetPath()->m_strDestUnzipPath);

		int index = -1;

		zr = FindZipItem(hz, ze.name, TRUE, &index, &ze);

		zr = UnzipItem(hz, index, GetPath()->m_strDestUnzipPath, 0, ZIP_FILENAME);

		if (zr != ZR_OK)
		{
			CloseZip(hz);
			return FALSE;
		}

		if (_taccess(GetPath()->m_strDestUnzipPath, 04) != 0)
		{
			CloseZip(hz);
			return FALSE;
		}

		m_progUpdateUnzipCtrl.SetPos(i);
		
		// 루프안에서 사용자 입렵을 받을 수 있게 한다
		GetProc()->MessageLoop();
		
		if( m_bCancel )
		{
			CloseZip(hz);
			return FALSE;
		}
	}
	CloseZip(hz);
	UpdateData(FALSE);

	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_FINISH);

	return TRUE;
}

void CUpdateDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);
	
	// FTP 업데이트 경로 변경
	if( GetFtp()->ChangeDir(GetPath()->m_strUpdateDir) == FALSE )
	{
		EndDialog(RT_UPDATE_FTP_ERR);
		return;
	}

	USHORT shRange = (USHORT)GetProc()->GetVersion() - (USHORT)GetProc()->GetRegVersion();

	m_progUpdateVerCtrl.SetRange(0, shRange);

	for(DWORD i = ( GetProc()->GetRegVersion() + 1 ); i <= GetProc()->GetVersion(); i++)
	{
		m_strUpdateVer.Format("버젼 %d.0 으로 업데이트 중 입니다", i);
		UpdateData(FALSE);

		GetPath()->SetUpdateFile(i);

		m_progUpdateVerCtrl.SetPos(i-1);
		m_progUpdateDownCtrl.SetPos(0);
		m_progUpdateUnzipCtrl.SetPos(0);

		// 업데이트 파일 다운 받기
		if( GetFtp()->AsyncDownload(GetPath()->m_strUpdateFile, GetPath()->m_strTempFile, &m_progUpdateDownCtrl, &m_strUpdateDown, this, &m_bCancel) == FALSE )
		{
			if( m_bCancel )
			{
				m_bCancel = FALSE;
				EndDialog(RT_UPDATE_USER_CANCEL);
			}
			else
			{
				EndDialog(RT_UPDATE_FTP_ERR);
			}
			return;
		}

		// 압축 풀어서 설치 하기
		if( Unzip(GetPath()->m_strTempFile) == FALSE )
		{
			if(m_bCancel)
			{
				EndDialog(RT_UPDATE_USER_CANCEL);				
			}
			else
			{
				EndDialog(RT_UPDATE_ZIP_ERR);
			}
			return;
		}
		m_strUpdateDown = _T("");
		m_strUpdateUnzip = _T("");

		// 버젼이 업데이트 하는 데로 등록한다
		if( GetProc()->SetLocalVersion(&i) == RT_UPDATE_REG_ERR)
		{
			EndDialog(RT_UPDATE_REG_ERR);
			return;
		}
	}	

	m_strUpdateVer = _T("정상적으로 업데이트를 완료하였습니다");
	UpdateData(FALSE);

	EndDialog(RT_OK);
	CDialog::OnTimer(nIDEvent);
}

void CUpdateDlg::OnCancel() 
{
	m_bCancel = TRUE;	
}
