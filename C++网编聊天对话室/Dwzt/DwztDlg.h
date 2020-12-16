// DwztDlg.h : header file
//

#if !defined(AFX_DWZTDLG_H__03E49D8F_C68A_4E29_B527_0DE4263D394C__INCLUDED_)
#define AFX_DWZTDLG_H__03E49D8F_C68A_4E29_B527_0DE4263D394C__INCLUDED_
#define	WM_READY_TO_RECEIVE WM_USER+1   //自定义消息
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDwztDlg dialog
class CCSocket;
class CDwztDlg : public CDialog
{
// Construction
public:
	SOCKET m_socket;
	FILE* m_file;

	DWORD m_recvIP;  //1个WORD=2个字节 1个DWORD=4个字节，用来存IP地址
	DWORD m_sendIP; //DWORD是无符号的,相当于unsigned long

	int m_nFileSize_s;
	int m_nRecv;
	int m_nSend;
	static int nFileSize;
	bool m_posting;
	//LPVOID是一个没有类型的指针，也就是说你可以将LPVOID类型的变量赋值给任意类型的指针
	//DWORD是数据类型，在这里是返回值，WINAPI是函数调用形式，最终就是_stdcall形式，
	//即由被调用函数来清理栈中的参数，这种方式是不能实现可变参数的。


	static DWORD WINAPI RECVpROC(LPVOID lpParameter);
	//WPARAM，LPARAM都是消息参数，WPARAM双字节，LPARAM长整型
	//afx_msg为消息标志，它向系统声明：有消息映射到函数实现体
	afx_msg void OnReadyToRecv(WPARAM wParam, LPARAM lParam);
	void OnReceive();
	CString m_strPeerIPaddr;
	BOOL m_bIsConnected;
	CCSocket *m_pSocket;
	CDwztDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDwztDlg)
	enum { IDD = IDD_DWZT_DIALOG };
	CProgressCtrl	m_progress_s;
	CProgressCtrl	m_progress_r;
	CIPAddressCtrl	m_peerIPadd;
	CIPAddressCtrl	m_localIPadd;
	CListBox	m_listMsg;
	CButton	m_btnSend;
	CButton	m_btnFtp;
	CString	m_dataToSent;
	UINT	m_localPortNum;
	UINT	m_peerPortNum;
	CString	m_filePath;
	CString	m_recv;
	CString	m_send;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDwztDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDwztDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonFtp();
	afx_msg void OnBtnctrlconn();
	afx_msg void OnButtonClear();
	afx_msg void OnFindFile();
	afx_msg void OnSentFile();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWZTDLG_H__03E49D8F_C68A_4E29_B527_0DE4263D394C__INCLUDED_)
