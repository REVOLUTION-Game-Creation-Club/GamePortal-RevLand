#if !defined(AFX_LAUNCHERCTL_H__CF8FA07D_E251_4FC5_81FE_0048D86F9735__INCLUDED_)
#define AFX_LAUNCHERCTL_H__CF8FA07D_E251_4FC5_81FE_0048D86F9735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// LauncherCtl.h : Declaration of the CLauncherCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CLauncherCtrl : See LauncherCtl.cpp for implementation.

class CLauncherCtrl : public COleControl
{
	DECLARE_DYNCREATE(CLauncherCtrl)

// Constructor
public:
	CLauncherCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLauncherCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CLauncherCtrl();

	DECLARE_OLECREATE_EX(CLauncherCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CLauncherCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CLauncherCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CLauncherCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CLauncherCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CLauncherCtrl)
	afx_msg void LauchContent(LPCTSTR strUserID, LPCTSTR strUserName, LPCTSTR strContentName, long dwVersion, long dwScore);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CLauncherCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CLauncherCtrl)
	dispidLauchContent = 1L,
	//}}AFX_DISP_ID
	};
private:
	CBitmap m_bitIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAUNCHERCTL_H__CF8FA07D_E251_4FC5_81FE_0048D86F9735__INCLUDED)
