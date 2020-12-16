#if !defined(AFX_DLG_CLOSE_H__4EB5A023_2F89_4055_B19F_4942CAB2252B__INCLUDED_)
#define AFX_DLG_CLOSE_H__4EB5A023_2F89_4055_B19F_4942CAB2252B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Close.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Close dialog

class Dlg_Close : public CDialog
{
// Construction
public:
	Dlg_Close(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_Close)
	enum { IDD = IDD_CLOSE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Close)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Close)
	afx_msg void OnButtonStay();
	afx_msg void OnButtonClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CLOSE_H__4EB5A023_2F89_4055_B19F_4942CAB2252B__INCLUDED_)
