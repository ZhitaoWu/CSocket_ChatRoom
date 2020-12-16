#if !defined(AFX_MYTHREAD_H__F79EC7FE_9871_43BB_B62E_9D24EA21C00F__INCLUDED_)
#define AFX_MYTHREAD_H__F79EC7FE_9871_43BB_B62E_9D24EA21C00F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyThread.h : header file
//

#include "MyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMyThread thread

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)
protected:
	CMyThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CMyDlg m_dlg;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyThread();

	// Generated message map functions
	//{{AFX_MSG(CMyThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTHREAD_H__F79EC7FE_9871_43BB_B62E_9D24EA21C00F__INCLUDED_)
