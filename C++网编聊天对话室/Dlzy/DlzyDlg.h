// DlzyDlg.h : header file
//

#if !defined(AFX_DLZYDLG_H__B24B25B6_88FC_4F7B_871D_1FEAD4DB645E__INCLUDED_)
#define AFX_DLZYDLG_H__B24B25B6_88FC_4F7B_871D_1FEAD4DB645E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CDlzyDlg dialog
class CCSocket;
class CDlzyDlg : public CDialog
{
// Construction
public:
	void OnReceive();
	CString m_strPeerIPaddr;
	BOOL m_bIsConnected;
	CCSocket *m_pSocket;
	CDlzyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlzyDlg)
	enum { IDD = IDD_DLZY_DIALOG };
	CListBox	m_listMsg;
	CIPAddressCtrl	m_peerIPadd;
	CIPAddressCtrl	m_localIPadd;
	CString	m_dataToSend;
	UINT	m_peerPortNum;
	UINT	m_localPortNum;
	CString	m_dataToSent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlzyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlzyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSent();
	afx_msg void OnBtnctrlconn();
	afx_msg void OnButtonThread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLZYDLG_H__B24B25B6_88FC_4F7B_871D_1FEAD4DB645E__INCLUDED_)
