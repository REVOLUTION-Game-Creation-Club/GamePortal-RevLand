#if !defined(AFX_UPDATEDLG_H__787EB281_0165_464B_9B1D_98F48D476D0D__INCLUDED_)
#define AFX_UPDATEDLG_H__787EB281_0165_464B_9B1D_98F48D476D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

class CUpdateDlg : public CDialog
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATE_DLG };
	CProgressCtrl	m_progUpdateVerCtrl;
	CProgressCtrl	m_progUpdateUnzipCtrl;
	CProgressCtrl	m_progUpdateDownCtrl;
	CString	m_strUpdateDown;
	CString	m_strUpdateUnzip;
	CString	m_strUpdateVer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCancel; // 이 값이 TRUE이면 정지시킨다 
	HANDLE m_hTimer;
	BOOL Unzip(LPCSTR strSrcFile);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDLG_H__787EB281_0165_464B_9B1D_98F48D476D0D__INCLUDED_)
