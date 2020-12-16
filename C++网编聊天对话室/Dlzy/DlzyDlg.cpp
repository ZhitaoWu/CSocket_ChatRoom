// DlzyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dlzy.h"
#include "DlzyDlg.h"
#include "CSocket.h"
#include "MyThread.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlzyDlg dialog

CDlzyDlg::CDlzyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlzyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlzyDlg)
	m_peerPortNum = 60500;
	m_localPortNum =50500;        //端口号
	
	m_dataToSent = _T("");
	//}}AFX_DATA_INIT
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSocket = NULL;            //套接字的初始化
	m_bIsConnected = FALSE;      //连接状态
}

void CDlzyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlzyDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Control(pDX, IDC_PEERIPADDR, m_peerIPadd);
	DDX_Control(pDX, IDC_LOCALIPADDR, m_localIPadd);
	DDX_Text(pDX, IDC_EDIT_PEERPORTNUM, m_peerPortNum);
	DDX_Text(pDX, IDC_EDIT_LOCALPORTNUM, m_localPortNum);
	DDX_Text(pDX, IDC_EDIT_MSG, m_dataToSent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlzyDlg, CDialog)
	//{{AFX_MSG_MAP(CDlzyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SENT, OnButtonSent)
	ON_BN_CLICKED(IDC_BTNCTRLCONN, OnBtnctrlconn)
	ON_BN_CLICKED(IDC_BUTTON_THREAD, OnButtonThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlzyDlg message handlers

BOOL CDlzyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	/*
	MFC中的函数AfxSocketInit()包装了函数WSAStartup(),
	在支持WinSock的应用程序的初始化函数IninInstance()中调用AfxSocketInit()进行初始化,程序则不必调用WSACleanUp().
	*/
	//AfxSocketInit();	

	m_peerIPadd.SetAddress(192,168,245,130);        //设置对端IP地址
	m_localIPadd.SetAddress(192,168,1,102);			//设置本地的IP地址

	//UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlzyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlzyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlzyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


////////////////////////////////////////
void CDlzyDlg::OnButtonSent() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);       //
		int nSent;
		CString nStr;

	if (NULL == m_pSocket || !m_bIsConnected)
	{
		AfxMessageBox(TEXT("尚未打开端口!"));
		return;
	}
	else if (m_dataToSent.IsEmpty())
	{
		AfxMessageBox(TEXT("请在编辑框中输入要发送的数据!"));
		return;
	}
	
    nSent=m_pSocket->SendTo(m_dataToSent, m_dataToSent.GetLength(),  //发送消息
		                     m_peerPortNum, m_strPeerIPaddr);
	if(nSent!=SOCKET_ERROR){
		GetDlgItem(IDC_EDIT_MSG)->GetWindowText(nStr);            //获取编辑框的值赋值给nStr
		nStr.Format("%s 对wuzhiao说： \r\n%s\r\n","liuzeyu",m_dataToSent);  //格式化
		m_listMsg.AddString(nStr);      //显示在列表框中
		UpdateData(FALSE);                      //更新对话框
	}
	
}

void CDlzyDlg::OnBtnctrlconn()    //连接函数
{
	// TODO: Add your control notification handler code here
	if (NULL!= m_pSocket)          //当套接字为空
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if (!m_bIsConnected)          
	{
		m_bIsConnected = TRUE;     //连接状态

		UpdateData(TRUE);
		
		BYTE field[4];
		
		m_peerIPadd.GetAddress(field[0], field[1], field[2], field[3]);	    //获取对端地址	
		m_strPeerIPaddr.Format(TEXT("%d.%d.%d.%d"),     
			field[0], field[1], field[2], field[3]);       //格式化
		
		m_pSocket = new CCSocket();
		m_pSocket->Create(m_localPortNum, SOCK_DGRAM);             //创建数据报套接字
		m_pSocket->Bind(m_peerPortNum, m_strPeerIPaddr);          //绑定

		GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("断开连接"));
	}
	else
	{
		m_bIsConnected = FALSE;                                         
		GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("建立连接"));
	}

}

void CDlzyDlg::OnButtonThread() 
{
	// TODO: Add your control notification handler code here
	CWinThread* pThread = AfxBeginThread(RUNTIME_CLASS(CMyThread));
	
}
