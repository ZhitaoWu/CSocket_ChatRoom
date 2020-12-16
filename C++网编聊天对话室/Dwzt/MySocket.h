#if !defined(AFX_MYSOCKET_H__4B9C5BEE_994E_4FD3_BAC2_10AF5F87DEAB__INCLUDED_)
#define AFX_MYSOCKET_H__4B9C5BEE_994E_4FD3_BAC2_10AF5F87DEAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
	afx_msg void OnButtonFtp();
	afx_msg void OnButtonSend();
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__4B9C5BEE_994E_4FD3_BAC2_10AF5F87DEAB__INCLUDED_)
