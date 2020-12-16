#if !defined(AFX_DLG_LOGIN_H__94BB8E80_C94F_480A_8E90_71D3401CC7FF__INCLUDED_)
#define AFX_DLG_LOGIN_H__94BB8E80_C94F_480A_8E90_71D3401CC7FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_login dialog

class Dlg_login : public CDialog
{
// Construction
public:
	void OnPaint();
	HICON m_hIcon;
	Dlg_login(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_login)
	enum { IDD = IDD_LOGIN_DIALOG };
	CString	m_strLoginName;
	CString	m_strLoginPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_login)
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LOGIN_H__94BB8E80_C94F_480A_8E90_71D3401CC7FF__INCLUDED_)
