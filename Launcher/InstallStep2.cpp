// InstallStep2.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "InstallStep2.h"
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
// CInstallStep2 property page

IMPLEMENT_DYNCREATE(CInstallStep2, CPropertyPage)

CInstallStep2::CInstallStep2() : CPropertyPage(CInstallStep2::IDD)
{
	//{{AFX_DATA_INIT(CInstallStep2)
	m_strDown = _T("");
	m_strUnzip = _T("");
	//}}AFX_DATA_INIT
	m_bCancel = FALSE;
}

CInstallStep2::~CInstallStep2()
{
}

void CInstallStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallStep2)
	DDX_Control(pDX, IDC_INSTALL_BTN, m_ctrlInstallBtn);
	DDX_Control(pDX, IDC_UNZIP_PROGRESS, m_progressUnzipCtrl);
	DDX_Control(pDX, IDC_DOWN_PROGRESS, m_progressDownCtrl);
	DDX_Text(pDX, IDC_DOWN_STATIC, m_strDown);
	DDX_Text(pDX, IDC_UNZIP_STATIC, m_strUnzip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstallStep2, CPropertyPage)
	//{{AFX_MSG_MAP(CInstallStep2)
	ON_BN_CLICKED(IDC_INSTALL_BTN, OnInstallBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallStep2 message handlers

LRESULT CInstallStep2::OnWizardBack() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	
	return CPropertyPage::OnWizardBack();
}

BOOL CInstallStep2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_strDown = _T("");
	m_strUnzip = _T("");

	UpdateData(FALSE);
	
	m_progressDownCtrl.SetPos(0);
	m_progressUnzipCtrl.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInstallStep2::OnInstallBtn() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(0);
	m_ctrlInstallBtn.SetWindowText("��ġ ��...");
	m_ctrlInstallBtn.EnableWindow(FALSE);

	// Icon�� Uninstall ������ �ٿ� �ޱ� ���� ������ �����Ѵ�
	CreateDirectory(GetPath()->m_strIconPath,NULL);
	
	// Icon Path�� �����Ѵ�
	GetPath()->SetIconPath();

	// FTP���� Rev Land Icon �ٿ�
	if( GetFtp()->BlockDownload(GetPath()->m_strIconFileName, GetPath()->m_strIconPath) == FALSE )
	{
		EndDialog(RT_INSTALL_FTP_ERR);
		return;
	}

	// FTP���� Uninstall ���� �ٿ�
	if( GetFtp()->BlockDownload(GetPath()->m_strUninstallFileName, GetPath()->m_strUninstallPath) == FALSE)
	{
		EndDialog(RT_INSTALL_FTP_ERR);
		return;
	}

	// FTP ��ġ ��� ����
	if( GetFtp()->ChangeDir(GetPath()->m_strContentDir) == FALSE )
	{
		EndDialog(RT_INSTALL_FTP_ERR);
		return;
	}

	// ��ġ���� �ٿ� �ޱ�
	if( GetFtp()->AsyncDownload(GetPath()->m_strContentFile, GetPath()->m_strTempFile, &m_progressDownCtrl, &m_strDown, this, &m_bCancel) == FALSE )
	{
		if( m_bCancel )
		{
			m_bCancel = FALSE;
			EndDialog(RT_INSTALL_USER_CANCEL);
		}
		else
		{
			EndDialog(RT_INSTALL_FTP_ERR);
		}
		return;
	}
		
	m_strUnzip = _T("��ġ �غ����Դϴ�");

	UpdateData(FALSE);

	// ���� Ǯ� ��ġ �ϱ�
	if( Unzip(GetPath()->m_strTempFile) == FALSE )
	{
		EndDialog(RT_INSTALL_ZIP_ERR);
		return;
	}
}


BOOL CInstallStep2::Unzip(LPCSTR strSrcFile)
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

	m_progressUnzipCtrl.SetRange(0, numitems);

	for (int i = 0; i < numitems; i++)
	{ 
		GetZipItem(hz, i, &ze);
		
		GetPath()->SetDestUnzipPath(ze.name);

		m_strUnzip.Format("%s", ze.name);
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

		m_progressUnzipCtrl.SetPos(i+1);

		// �����ȿ��� ����� �Է��� ���� �� �ְ� �Ѵ�
		GetProc()->MessageLoop();
				
		if( m_bCancel )
		{
			CloseZip(hz);
			return FALSE;
		}
	}

	CloseZip(hz);
	
	m_strUnzip.Format("���������� ��ġ�� �Ϸ�Ǿ����ϴ�");
	UpdateData(FALSE);

	m_ctrlInstallBtn.SetWindowText("��ġ �Ϸ�");


	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_FINISH);

	return TRUE;
}

BOOL CInstallStep2::OnQueryCancel() 
{
	// ��� ��ư�� ������ ���
	m_bCancel = TRUE;	
	return CPropertyPage::OnQueryCancel();
}
