#if !defined(AFX_INSTALLPROPERTY_H__9842EC73_3E90_435B_B9A0_237D1A0A733D__INCLUDED_)
#define AFX_INSTALLPROPERTY_H__9842EC73_3E90_435B_B9A0_237D1A0A733D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstallProperty.h : header file
//

#include "resource.h"
#include "InstallStep1.h"
#include "InstallStep2.h"

/////////////////////////////////////////////////////////////////////////////
// CInstallProperty

class CInstallProperty : public CPropertySheet
{
	DECLARE_DYNAMIC(CInstallProperty)

// Construction
public:
	CInstallProperty(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CInstallProperty(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

	CInstallStep1 m_InstallStep1;
	CInstallStep2 m_InstallStep2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallProperty)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInstallProperty();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInstallProperty)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLPROPERTY_H__9842EC73_3E90_435B_B9A0_237D1A0A733D__INCLUDED_)
