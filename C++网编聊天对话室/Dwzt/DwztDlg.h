// DwztDlg.h : header file
//

#if !defined(AFX_DWZTDLG_H__03E49D8F_C68A_4E29_B527_0DE4263D394C__INCLUDED_)
#define AFX_DWZTDLG_H__03E49D8F_C68A_4E29_B527_0DE4263D394C__INCLUDED_
#define	WM_READY_TO_RECEIVE WM_USER+1   //�Զ�����Ϣ
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

	DWORD m_recvIP;  //1��WORD=2���ֽ� 1��DWORD=4���ֽڣ�������IP��ַ
	DWORD m_sendIP; //DWORD���޷��ŵ�,�൱��unsigned long

	int m_nFileSize_s;
	int m_nRecv;
	int m_nSend;
	static int nFileSize;
	bool m_posting;
	//LPVOID��һ��û�����͵�ָ�룬Ҳ����˵����Խ�LPVOID���͵ı�����ֵ���������͵�ָ��
	//DWORD���������ͣ��������Ƿ���ֵ��WINAPI�Ǻ���������ʽ�����վ���_stdcall��ʽ��
	//���ɱ����ú���������ջ�еĲ��������ַ�ʽ�ǲ���ʵ�ֿɱ�����ġ�


	static DWORD WINAPI RECVpROC(LPVOID lpParameter);
	//WPARAM��LPARAM������Ϣ������WPARAM˫�ֽڣ�LPARAM������
	//afx_msgΪ��Ϣ��־������ϵͳ����������Ϣӳ�䵽����ʵ����
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
