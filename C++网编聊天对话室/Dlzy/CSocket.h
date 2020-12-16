#if !defined(AFX_CSOCKET_H__6497FA10_0A6C_49C2_B385_5EDC509188CC__INCLUDED_)
#define AFX_CSOCKET_H__6497FA10_0A6C_49C2_B385_5EDC509188CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCSocket command target
class CCSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCSocket();
	virtual ~CCSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKET_H__6497FA10_0A6C_49C2_B385_5EDC509188CC__INCLUDED_)
