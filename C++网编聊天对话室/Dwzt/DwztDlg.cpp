// DwztDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dwzt.h"
#include "DwztDlg.h"
#include "CSocket.h"
#include "MyThread.h"
#include "Dlg_Close.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CDwztDlg* pDlg;
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
// CDwztDlg dialog
int CDwztDlg::nFileSize=0;	// 初始化文件大小
CDwztDlg::CDwztDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDwztDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDwztDlg)
	m_dataToSent = _T("");
	m_localPortNum = 60500;
	m_peerPortNum = 50500;
	m_filePath = _T("");
	m_recv = _T("接收文件");
	m_send = _T("发送文件");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//小图标

	m_pSocket = NULL;            //套接字的初始化
	m_bIsConnected = FALSE;      //连接状态

	m_file = NULL;  //初始化文件
	m_posting = false;   //是否发送
}

void CDwztDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDwztDlg)
	DDX_Control(pDX, IDC_PROGRESS_SEND, m_progress_s);
	DDX_Control(pDX, IDC_PROGRESS_RECV, m_progress_r);
	DDX_Control(pDX, IDC_PEERIPADDR, m_peerIPadd);
	DDX_Control(pDX, IDC_LOCALIPADDR, m_localIPadd);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON_FTP, m_btnFtp);
	DDX_Text(pDX, IDC_EDIT_MSG, m_dataToSent);
	DDX_Text(pDX, IDC_EDIT_LPORT, m_localPortNum);
	DDX_Text(pDX, IDC_EDIT_OPORT, m_peerPortNum);
	DDX_Text(pDX, IDC_FILE_PATH, m_filePath);
	DDX_Text(pDX, IDC_RECV, m_recv);
	DDX_Text(pDX, IDC_SENT, m_send);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDwztDlg, CDialog)
	//{{AFX_MSG_MAP(CDwztDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_FTP, OnButtonFtp)
	ON_BN_CLICKED(IDC_BTNCTRLCONN, OnBtnctrlconn)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_FIND_FILE, OnFindFile)
	ON_BN_CLICKED(IDC_SENT_FILE, OnSentFile)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDwztDlg message handlers

struct RECVPARAM
{
	HWND hWnd;   // 创建窗口句柄，通过句柄可以知道窗口的一些属性
	SOCKET sock;   //创建套接字
}; 

BOOL CDwztDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	pDlg=this;
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
	
	m_pSocket=NULL;            //套接字的初始化
	m_bIsConnected = FALSE;      //连接状态
	// TODO: Add extra initialization here
	m_peerIPadd.SetAddress(192,168,1,102);        //设置对端IP地址
	m_localIPadd.SetAddress(192,168,1,103);			//设置本地的IP地址
	
	//设置进度条的步进值
	m_progress_s.SetStep(1);
	m_progress_r.SetStep(1);


	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		AfxMessageBox("套接字创建失败");
		return FALSE;
	}

	//初始化地址结构
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(6800);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	int retval;
	retval = bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		AfxMessageBox("绑定失败");
		return FALSE;
	}
	//产生一个用于接收数据的线程
	struct RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hWnd=m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RECVpROC,(LPVOID)pRecvParam,0,NULL);
	CloseHandle(hThread);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDwztDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDwztDlg::OnPaint() 
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
		//CDialog::OnPaint();
		CPaintDC dc(this);                
		CBitmap m_bitmap;                
		m_bitmap.LoadBitmap(IDB_BITMAP6);         //位图资源标识                
		CDC memdc;                
		memdc.CreateCompatibleDC(&dc);                
		memdc.SelectObject(&m_bitmap);                
		int width,height;                
		BITMAP bmp;                
		m_bitmap.GetBitmap(&bmp);
		//获取位图的宽度，高度，                
		width= bmp.bmWidth;               
		height= bmp.bmHeight;                
		CRect rect;                
		this->GetClientRect(&rect);             
		//矩形。                
		dc.StretchBlt(rect.left,rect.top,rect.Width(),
			rect.Height(),&memdc,0,0,width,height,SRCCOPY);   
	}
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDwztDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDwztDlg::OnButtonSend() 
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
		nStr.Format("%s 对lzy说： \r\n%s\r\n","wzt",m_dataToSent);  //格式化
		m_listMsg.AddString(nStr);      //显示在列表框中
		UpdateData(FALSE);                      //更新对话框
	}
	
}



void CDwztDlg::OnButtonFtp() 
{
	// TODO: Add your control notification handler code here
	CWinThread* pThread=AfxBeginThread(RUNTIME_CLASS(CMyThread));
}



void CDwztDlg::OnBtnctrlconn() 
{
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

void CDwztDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	while(m_listMsg.GetCount()!=0)	m_listMsg.DeleteString(0);
}

void CDwztDlg::OnFindFile() 
{
	CFileDialog openFile(true);
	if (IDOK == openFile.DoModal())
	{
		m_filePath = openFile.GetPathName();
		UpdateData(false);
	}	
	
}

void CDwztDlg::OnSentFile() 
{
	if (m_posting)
	{
		MessageBox("数据发送中，请稍候再试。");
		return;
	}

	UpdateData();

	if (m_filePath == "")
	{
		MessageBox("请输入要发送的文件路径！");
		return;
	}
	
	if (m_localIPadd.IsBlank())
	{
		MessageBox("请添入接收者的IP地址。");
		return;
	}

	/*
	在用findfirst()和findnext()函数去查找磁盘文件时经常使用的一个数据结构WIN32_
	FIND_DATA的成员变量里包含了以上所有的文件属性，
	因此可以通过这个结构作为获取和更改文件属性的手段。
	*/
	WIN32_FIND_DATA FindFileData;

	if (INVALID_HANDLE_VALUE == FindFirstFile(m_filePath, &FindFileData))
	{
		MessageBox("文件路径错误或文件不存在!\n请重新指定文件路径。");
		return;
	}

	DWORD dwIP;
	m_peerIPadd.GetAddress(dwIP);

	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6800);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);

	char sendBuf[0x112];
	int i;


	//消息头
	sendBuf[0] = 'H';

	for (i = 1; i <= 0x100 && FindFileData.cFileName[i-1] != '\0'; i++)
		sendBuf[i] = FindFileData.cFileName[i-1];         
	sendBuf[i] = '\0';

	//将文件转换成十进制存入sendBuf
	_itoa(FindFileData.nFileSizeLow, &sendBuf[0x101], 10);
	sendBuf[0x111] = '\0';
	//发送数据块
	int s=sendto(m_socket, sendBuf, 0x112, 0,
		(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
	//打开文件，等待读取
	if (!(m_file = fopen(m_filePath, "rb")))
	{
		MessageBox("读取文件失败！");
	}
	m_nSend = 0;   //已发送的块数
	m_nFileSize_s = FindFileData.nFileSizeLow; //获取文件大小的低位双字
	m_progress_s.SetRange(0, m_nFileSize_s/0x100+1); //设置发送进度条
	m_posting = true;
	
	m_filePath.Empty();   //清空编辑框
	//CDialog::OnOK();
	
}

void CDwztDlg::OnReadyToRecv(WPARAM wParam, LPARAM lParam)
{
	char sendBuf[0x112];
	DWORD dwIP;
	m_peerIPadd.GetAddress(dwIP);

	//初始化地址结构！！
	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6800);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);

	int nRead;

	switch (*(char*)wParam)
	{
	//对方拒绝接收文件，关闭已打开的文件
	case 'D':
		MessageBox("对方拒绝接受你发送的文件！");
		fclose(m_file);
		m_posting = false;
		break;
	//对方同意接收文件
	case 'R':
		nRead = fread(&sendBuf[0x12], 1, 0x100, m_file);

		//读取的文件小于256字节，则读到文件尾
		if (nRead < 0x100)  //0x100=256(十进制)
		{
			sendBuf[0] = 'E';
			//把nRead按照10进制转换并存入sendBuf
			_itoa(nRead, &sendBuf[1], 10);
			//返回值：成功则返回实际传送出去的字符数, 失败返回－1, 错误原因存于errno 中
			//参数3：该参数是用来标定待发送的数据有多少个字节
			//参数5：指向的空间中地址数据所占用的字节个数
			sendto(m_socket, sendBuf, nRead+0x12, 0,
				(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
			fclose(m_file);
			m_progress_s.SetPos(m_nFileSize_s/0x100+1);
			m_posting = false;
			m_send = "发送进度：(100%)";
			CString nStr;
			m_listMsg.AddString("liuzeyu接收一个文件.");
			UpdateData(false);
			MessageBox("发送完毕！");
			m_progress_s.SetPos(0);
			m_send = "发送进度：";
			UpdateData(false);

		}
		 //读到文件等于256字节，则文件还未读完
		else
		{
			sendBuf[0] = 'F';
			sendto(m_socket, sendBuf, 0x112, 0,
				(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
			m_progress_s.StepIt();
			m_nSend++;
			m_send.Format("发送进度：(%.1f%%)", (float)m_nSend/(m_nFileSize_s/0x100+1)*100);
			UpdateData(false);
		}
		break;
		//同意接收对方文件
	case 'H':
		m_progress_r.SetRange(0, nFileSize/0x100+1);
		m_nRecv = 0;
	case 'F':
		sendto(m_socket, "R", 2, 0,
				(SOCKADDR*)lParam, sizeof(SOCKADDR));
		m_progress_r.StepIt();
		m_nRecv++;
		m_recv.Format("接收进度：(%.1f%%)", (float)m_nRecv/(nFileSize/0x100+1)*100);
		UpdateData(false);
		break;
	//接受完毕，提示用户
	case 'E':
		m_progress_r.SetPos(nFileSize/0x100+1);
		m_recv = "接收进度：(100%)";
		UpdateData(false);
		MessageBox("接收完毕！");
		m_recv = "接收进度：";
		m_progress_r.SetPos(0);
		UpdateData(false);
		break;
	//拒绝接收，通知对方
	case 'C':
		sendto(m_socket, "D", 2, 0,
				(SOCKADDR*)lParam, sizeof(SOCKADDR));
		break;
	}

}

DWORD WINAPI CDwztDlg::RECVpROC(LPVOID lpParameter)
{
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;
	HWND hWnd=((RECVPARAM*)lpParameter)->hWnd; //窗口句柄和SOCKET关联
	delete lpParameter;	

	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);
	char recvBuf[0x112];		//256+17字节的缓冲
	char fileName[0x100];
	int retval, i;
	FILE* file = NULL;

	while(TRUE)
	{
		retval=recvfrom(sock,recvBuf,0x112,0,(SOCKADDR*)&addrFrom,&len);
		
		if(SOCKET_ERROR == retval)
			break;

		////收到消息头为'R',即对方同意让你继续发送数据
		if (recvBuf[0] == 'R')
		{
			char wParam = 'R';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, 0);
		}
		////收到消息头为'D',即对方拒绝让你继续发送数据 
		else if (recvBuf[0] == 'D')
		{
			char wParam = 'D';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, 0);
		}
		////收到消息头为'H',即对方申请给你发送信息,并送来文件的信息 
		else if (recvBuf[0] == 'H')
		{
			
			for (i = 1; i <= 0x100 && recvBuf[i] != '\0'; i++)	//前256字节用于存储文件名
				fileName[i-1] = recvBuf[i];
			fileName[i-1] = '\0';
			 //从收到的数据中提取文件大小信息
			CString recvMsg;
			nFileSize = atoi(&recvBuf[0x101]);
			recvMsg.Format("收到来自于(%s)的文件：%s\n文件大小：%i字节\n是否接收？",
			inet_ntoa(addrFrom.sin_addr), fileName, nFileSize);
			//用消息框提示用户有人要发送文件
			if (IDOK == AfxMessageBox(recvMsg, MB_OKCANCEL))
			{
				//若用户同意接收，提供一个文件保存对话框用于设定保存的路径 
				CFileDialog saveDlg(false, NULL, fileName);
				
				if (IDOK == saveDlg.DoModal())
				{
					//创建一个文件用于复制接收的文件数据
					if (!(file = fopen(saveDlg.GetPathName(), "wb")))
					{
						AfxMessageBox("创建本地文件失败！");
						continue;
					}
					char wParam = 'H';
					::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);					
				}
				else
				{
					char wParam = 'C';
					::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
				}
			}
			else
			{
				//用户拒绝接收
				char wParam = 'C';
				::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
			}

		}
		//收到的消息头为'F',即对方发来的是文件数据 
		else if (recvBuf[0] == 'F')
		{
			//将文件数据写入本地文件中
			fwrite(&recvBuf[0x12], 1, 0x100, file);
			char wParam = 'F';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
		}
		//收到的消息头为'E',即对方发来最后一个数据块
		else if (recvBuf[0] == 'E')
		{
			int bufSize = atoi(&recvBuf[1]);
			fwrite(&recvBuf[0x12], 1, bufSize, file);
			fclose(file);
			char wParam = 'E';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
		}
		//收到未定义的数据头
		else
			AfxMessageBox("传送数据过程中出现错误！");
	}
	return (DWORD)NULL;
}

void CDwztDlg::OnClose() 
{
	// 在聊天对话框关闭窗口
	Dlg_Close dlg;
	dlg.DoModal();
}
