#if !defined(AFX_INSTALLSTEP1_H__5A088D18_F7B2_4D26_971D_AE20050A2DA9__INCLUDED_)
#define AFX_INSTALLSTEP1_H__5A088D18_F7B2_4D26_971D_AE20050A2DA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstallStep1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallStep1 dialog

class CInstallStep1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CInstallStep1)

// Construction
public:
	CInstallStep1();
	~CInstallStep1();

// Dialog Data
	//{{AFX_DATA(CInstallStep1)
	enum { IDD = IDD_INSTALL_STEP1_DLG };
	CString	m_strInstallPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInstallStep1)
	public:
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInstallStep1)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeInstallPathEdit();
	afx_msg void OnFindBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	TCHAR m_strRealInstallPath[MAX_PATH];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLSTEP1_H__5A088D18_F7B2_4D26_971D_AE20050A2DA9__INCLUDED_)
