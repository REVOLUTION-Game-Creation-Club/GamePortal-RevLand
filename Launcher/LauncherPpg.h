#if !defined(AFX_LAUNCHERPPG_H__FA620CC6_5969_4C94_983C_C40D74F80E4F__INCLUDED_)
#define AFX_LAUNCHERPPG_H__FA620CC6_5969_4C94_983C_C40D74F80E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// LauncherPpg.h : Declaration of the CLauncherPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CLauncherPropPage : See LauncherPpg.cpp.cpp for implementation.

class CLauncherPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CLauncherPropPage)
	DECLARE_OLECREATE_EX(CLauncherPropPage)

// Constructor
public:
	CLauncherPropPage();

// Dialog Data
	//{{AFX_DATA(CLauncherPropPage)
	enum { IDD = IDD_PROPPAGE_LAUNCHER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CLauncherPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAUNCHERPPG_H__FA620CC6_5969_4C94_983C_C40D74F80E4F__INCLUDED)
