// Dlzy.h : main header file for the DLZY application
//

#if !defined(AFX_DLZY_H__2AC58092_B2D0_4DBC_8638_FE3B1943BA49__INCLUDED_)
#define AFX_DLZY_H__2AC58092_B2D0_4DBC_8638_FE3B1943BA49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlzyApp:
// See Dlzy.cpp for the implementation of this class
//

class CDlzyApp : public CWinApp
{
public:
	CDlzyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlzyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlzyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLZY_H__2AC58092_B2D0_4DBC_8638_FE3B1943BA49__INCLUDED_)
