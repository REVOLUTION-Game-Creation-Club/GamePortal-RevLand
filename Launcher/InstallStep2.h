#if !defined(AFX_INSTALLSTEP2_H__B6AF529C_0AD7_4D84_A054_F65CBCC2FBDE__INCLUDED_)
#define AFX_INSTALLSTEP2_H__B6AF529C_0AD7_4D84_A054_F65CBCC2FBDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstallStep2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallStep2 dialog

class CInstallStep2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CInstallStep2)

// Construction
public:
	CInstallStep2();
	~CInstallStep2();

// Dialog Data
	//{{AFX_DATA(CInstallStep2)
	enum { IDD = IDD_INSTALL_STEP2_DLG };
	CButton	m_ctrlInstallBtn;
	CProgressCtrl	m_progressUnzipCtrl;
	CProgressCtrl	m_progressDownCtrl;
	CString	m_strDown;
	CString	m_strUnzip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInstallStep2)
	public:
	virtual LRESULT OnWizardBack();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInstallStep2)
	virtual BOOL OnInitDialog();
	afx_msg void OnInstallBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCancel;
	BOOL Unzip(LPCSTR strSrcFile);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLSTEP2_H__B6AF529C_0AD7_4D84_A054_F65CBCC2FBDE__INCLUDED_)
