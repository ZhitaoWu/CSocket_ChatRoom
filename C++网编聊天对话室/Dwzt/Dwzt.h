// Dwzt.h : main header file for the DWZT application
//

#if !defined(AFX_DWZT_H__5E5CC4E5_E8D9_4B73_9F37_A49C2D37C995__INCLUDED_)
#define AFX_DWZT_H__5E5CC4E5_E8D9_4B73_9F37_A49C2D37C995__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDwztApp:
// See Dwzt.cpp for the implementation of this class
//

class CDwztApp : public CWinApp
{
public:
	CDwztApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDwztApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDwztApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWZT_H__5E5CC4E5_E8D9_4B73_9F37_A49C2D37C995__INCLUDED_)
