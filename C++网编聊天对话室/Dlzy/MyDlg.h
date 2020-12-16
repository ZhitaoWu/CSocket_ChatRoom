#if !defined(AFX_MYDLG_H__52961DD8_E2FE_4C69_93FB_E2B8FA5D1EF7__INCLUDED_)
#define AFX_MYDLG_H__52961DD8_E2FE_4C69_93FB_E2B8FA5D1EF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
typedef struct{
    CListBox* pList;
	CString strFtp;
    CString strName;
    CString strPwd;
}FTP_INFO;
class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CButton	m_btnQuery;
	CListBox	m_listFile;
	CEdit	m_editPwd;
	CEdit	m_editName;
	CEdit	m_editFtp;
	CButton	m_btnUpload;
	CButton	m_btnDownload;
	CButton	m_btnCancle;
	CString	m_strFtp;
	CString	m_strName;
	CString	m_strPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	afx_msg void OnButtonCancle();
	afx_msg void OnButtonDownload();
	afx_msg void OnButtonUpload();
	afx_msg void OnButtonQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__52961DD8_E2FE_4C69_93FB_E2B8FA5D1EF7__INCLUDED_)
