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
int CDwztDlg::nFileSize=0;	// ��ʼ���ļ���С
CDwztDlg::CDwztDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDwztDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDwztDlg)
	m_dataToSent = _T("");
	m_localPortNum = 60500;
	m_peerPortNum = 50500;
	m_filePath = _T("");
	m_recv = _T("�����ļ�");
	m_send = _T("�����ļ�");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//Сͼ��

	m_pSocket = NULL;            //�׽��ֵĳ�ʼ��
	m_bIsConnected = FALSE;      //����״̬

	m_file = NULL;  //��ʼ���ļ�
	m_posting = false;   //�Ƿ���
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
	HWND hWnd;   // �������ھ����ͨ���������֪�����ڵ�һЩ����
	SOCKET sock;   //�����׽���
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
	
	m_pSocket=NULL;            //�׽��ֵĳ�ʼ��
	m_bIsConnected = FALSE;      //����״̬
	// TODO: Add extra initialization here
	m_peerIPadd.SetAddress(192,168,1,102);        //���öԶ�IP��ַ
	m_localIPadd.SetAddress(192,168,1,103);			//���ñ��ص�IP��ַ
	
	//���ý������Ĳ���ֵ
	m_progress_s.SetStep(1);
	m_progress_r.SetStep(1);


	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		AfxMessageBox("�׽��ִ���ʧ��");
		return FALSE;
	}

	//��ʼ����ַ�ṹ
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(6800);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	int retval;
	retval = bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		AfxMessageBox("��ʧ��");
		return FALSE;
	}
	//����һ�����ڽ������ݵ��߳�
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
		m_bitmap.LoadBitmap(IDB_BITMAP6);         //λͼ��Դ��ʶ                
		CDC memdc;                
		memdc.CreateCompatibleDC(&dc);                
		memdc.SelectObject(&m_bitmap);                
		int width,height;                
		BITMAP bmp;                
		m_bitmap.GetBitmap(&bmp);
		//��ȡλͼ�Ŀ�ȣ��߶ȣ�                
		width= bmp.bmWidth;               
		height= bmp.bmHeight;                
		CRect rect;                
		this->GetClientRect(&rect);             
		//���Ρ�                
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
		AfxMessageBox(TEXT("��δ�򿪶˿�!"));
		return;
	}
	else if (m_dataToSent.IsEmpty())
	{
		AfxMessageBox(TEXT("���ڱ༭��������Ҫ���͵�����!"));
		return;
	}
	
    nSent=m_pSocket->SendTo(m_dataToSent, m_dataToSent.GetLength(),  //������Ϣ
		                     m_peerPortNum, m_strPeerIPaddr);
	if(nSent!=SOCKET_ERROR){
		GetDlgItem(IDC_EDIT_MSG)->GetWindowText(nStr);            //��ȡ�༭���ֵ��ֵ��nStr
		nStr.Format("%s ��lzy˵�� \r\n%s\r\n","wzt",m_dataToSent);  //��ʽ��
		m_listMsg.AddString(nStr);      //��ʾ���б����
		UpdateData(FALSE);                      //���¶Ի���
	}
	
}



void CDwztDlg::OnButtonFtp() 
{
	// TODO: Add your control notification handler code here
	CWinThread* pThread=AfxBeginThread(RUNTIME_CLASS(CMyThread));
}



void CDwztDlg::OnBtnctrlconn() 
{
	if (NULL!= m_pSocket)          //���׽���Ϊ��
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if (!m_bIsConnected)          
	{
		m_bIsConnected = TRUE;     //����״̬

		UpdateData(TRUE);
		
		BYTE field[4];
		
		m_peerIPadd.GetAddress(field[0], field[1], field[2], field[3]);	    //��ȡ�Զ˵�ַ	
		m_strPeerIPaddr.Format(TEXT("%d.%d.%d.%d"),     
		field[0], field[1], field[2], field[3]);       //��ʽ��
		
		m_pSocket = new CCSocket();
		m_pSocket->Create(m_localPortNum, SOCK_DGRAM);             //�������ݱ��׽���
		m_pSocket->Bind(m_peerPortNum, m_strPeerIPaddr);          //��

		GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("�Ͽ�����"));
	}
	else
	{
		m_bIsConnected = FALSE;                                         
		GetDlgItem(IDC_BTNCTRLCONN)->SetWindowText(TEXT("��������"));
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
		MessageBox("���ݷ����У����Ժ����ԡ�");
		return;
	}

	UpdateData();

	if (m_filePath == "")
	{
		MessageBox("������Ҫ���͵��ļ�·����");
		return;
	}
	
	if (m_localIPadd.IsBlank())
	{
		MessageBox("����������ߵ�IP��ַ��");
		return;
	}

	/*
	����findfirst()��findnext()����ȥ���Ҵ����ļ�ʱ����ʹ�õ�һ�����ݽṹWIN32_
	FIND_DATA�ĳ�Ա������������������е��ļ����ԣ�
	��˿���ͨ������ṹ��Ϊ��ȡ�͸����ļ����Ե��ֶΡ�
	*/
	WIN32_FIND_DATA FindFileData;

	if (INVALID_HANDLE_VALUE == FindFirstFile(m_filePath, &FindFileData))
	{
		MessageBox("�ļ�·��������ļ�������!\n������ָ���ļ�·����");
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


	//��Ϣͷ
	sendBuf[0] = 'H';

	for (i = 1; i <= 0x100 && FindFileData.cFileName[i-1] != '\0'; i++)
		sendBuf[i] = FindFileData.cFileName[i-1];         
	sendBuf[i] = '\0';

	//���ļ�ת����ʮ���ƴ���sendBuf
	_itoa(FindFileData.nFileSizeLow, &sendBuf[0x101], 10);
	sendBuf[0x111] = '\0';
	//�������ݿ�
	int s=sendto(m_socket, sendBuf, 0x112, 0,
		(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
	//���ļ����ȴ���ȡ
	if (!(m_file = fopen(m_filePath, "rb")))
	{
		MessageBox("��ȡ�ļ�ʧ�ܣ�");
	}
	m_nSend = 0;   //�ѷ��͵Ŀ���
	m_nFileSize_s = FindFileData.nFileSizeLow; //��ȡ�ļ���С�ĵ�λ˫��
	m_progress_s.SetRange(0, m_nFileSize_s/0x100+1); //���÷��ͽ�����
	m_posting = true;
	
	m_filePath.Empty();   //��ձ༭��
	//CDialog::OnOK();
	
}

void CDwztDlg::OnReadyToRecv(WPARAM wParam, LPARAM lParam)
{
	char sendBuf[0x112];
	DWORD dwIP;
	m_peerIPadd.GetAddress(dwIP);

	//��ʼ����ַ�ṹ����
	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6800);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);

	int nRead;

	switch (*(char*)wParam)
	{
	//�Է��ܾ������ļ����ر��Ѵ򿪵��ļ�
	case 'D':
		MessageBox("�Է��ܾ������㷢�͵��ļ���");
		fclose(m_file);
		m_posting = false;
		break;
	//�Է�ͬ������ļ�
	case 'R':
		nRead = fread(&sendBuf[0x12], 1, 0x100, m_file);

		//��ȡ���ļ�С��256�ֽڣ�������ļ�β
		if (nRead < 0x100)  //0x100=256(ʮ����)
		{
			sendBuf[0] = 'E';
			//��nRead����10����ת��������sendBuf
			_itoa(nRead, &sendBuf[1], 10);
			//����ֵ���ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ���, ʧ�ܷ��أ�1, ����ԭ�����errno ��
			//����3���ò����������궨�����͵������ж��ٸ��ֽ�
			//����5��ָ��Ŀռ��е�ַ������ռ�õ��ֽڸ���
			sendto(m_socket, sendBuf, nRead+0x12, 0,
				(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
			fclose(m_file);
			m_progress_s.SetPos(m_nFileSize_s/0x100+1);
			m_posting = false;
			m_send = "���ͽ��ȣ�(100%)";
			CString nStr;
			m_listMsg.AddString("liuzeyu����һ���ļ�.");
			UpdateData(false);
			MessageBox("������ϣ�");
			m_progress_s.SetPos(0);
			m_send = "���ͽ��ȣ�";
			UpdateData(false);

		}
		 //�����ļ�����256�ֽڣ����ļ���δ����
		else
		{
			sendBuf[0] = 'F';
			sendto(m_socket, sendBuf, 0x112, 0,
				(SOCKADDR*)&addrTo, sizeof(SOCKADDR));
			m_progress_s.StepIt();
			m_nSend++;
			m_send.Format("���ͽ��ȣ�(%.1f%%)", (float)m_nSend/(m_nFileSize_s/0x100+1)*100);
			UpdateData(false);
		}
		break;
		//ͬ����նԷ��ļ�
	case 'H':
		m_progress_r.SetRange(0, nFileSize/0x100+1);
		m_nRecv = 0;
	case 'F':
		sendto(m_socket, "R", 2, 0,
				(SOCKADDR*)lParam, sizeof(SOCKADDR));
		m_progress_r.StepIt();
		m_nRecv++;
		m_recv.Format("���ս��ȣ�(%.1f%%)", (float)m_nRecv/(nFileSize/0x100+1)*100);
		UpdateData(false);
		break;
	//������ϣ���ʾ�û�
	case 'E':
		m_progress_r.SetPos(nFileSize/0x100+1);
		m_recv = "���ս��ȣ�(100%)";
		UpdateData(false);
		MessageBox("������ϣ�");
		m_recv = "���ս��ȣ�";
		m_progress_r.SetPos(0);
		UpdateData(false);
		break;
	//�ܾ����գ�֪ͨ�Է�
	case 'C':
		sendto(m_socket, "D", 2, 0,
				(SOCKADDR*)lParam, sizeof(SOCKADDR));
		break;
	}

}

DWORD WINAPI CDwztDlg::RECVpROC(LPVOID lpParameter)
{
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;
	HWND hWnd=((RECVPARAM*)lpParameter)->hWnd; //���ھ����SOCKET����
	delete lpParameter;	

	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);
	char recvBuf[0x112];		//256+17�ֽڵĻ���
	char fileName[0x100];
	int retval, i;
	FILE* file = NULL;

	while(TRUE)
	{
		retval=recvfrom(sock,recvBuf,0x112,0,(SOCKADDR*)&addrFrom,&len);
		
		if(SOCKET_ERROR == retval)
			break;

		////�յ���ϢͷΪ'R',���Է�ͬ�����������������
		if (recvBuf[0] == 'R')
		{
			char wParam = 'R';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, 0);
		}
		////�յ���ϢͷΪ'D',���Է��ܾ���������������� 
		else if (recvBuf[0] == 'D')
		{
			char wParam = 'D';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, 0);
		}
		////�յ���ϢͷΪ'H',���Է�������㷢����Ϣ,�������ļ�����Ϣ 
		else if (recvBuf[0] == 'H')
		{
			
			for (i = 1; i <= 0x100 && recvBuf[i] != '\0'; i++)	//ǰ256�ֽ����ڴ洢�ļ���
				fileName[i-1] = recvBuf[i];
			fileName[i-1] = '\0';
			 //���յ�����������ȡ�ļ���С��Ϣ
			CString recvMsg;
			nFileSize = atoi(&recvBuf[0x101]);
			recvMsg.Format("�յ�������(%s)���ļ���%s\n�ļ���С��%i�ֽ�\n�Ƿ���գ�",
			inet_ntoa(addrFrom.sin_addr), fileName, nFileSize);
			//����Ϣ����ʾ�û�����Ҫ�����ļ�
			if (IDOK == AfxMessageBox(recvMsg, MB_OKCANCEL))
			{
				//���û�ͬ����գ��ṩһ���ļ�����Ի��������趨�����·�� 
				CFileDialog saveDlg(false, NULL, fileName);
				
				if (IDOK == saveDlg.DoModal())
				{
					//����һ���ļ����ڸ��ƽ��յ��ļ�����
					if (!(file = fopen(saveDlg.GetPathName(), "wb")))
					{
						AfxMessageBox("���������ļ�ʧ�ܣ�");
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
				//�û��ܾ�����
				char wParam = 'C';
				::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
			}

		}
		//�յ�����ϢͷΪ'F',���Է����������ļ����� 
		else if (recvBuf[0] == 'F')
		{
			//���ļ�����д�뱾���ļ���
			fwrite(&recvBuf[0x12], 1, 0x100, file);
			char wParam = 'F';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
		}
		//�յ�����ϢͷΪ'E',���Է��������һ�����ݿ�
		else if (recvBuf[0] == 'E')
		{
			int bufSize = atoi(&recvBuf[1]);
			fwrite(&recvBuf[0x12], 1, bufSize, file);
			fclose(file);
			char wParam = 'E';
			::PostMessage(hWnd, WM_READY_TO_RECEIVE, (WPARAM)&wParam, (LPARAM)&addrFrom);
		}
		//�յ�δ���������ͷ
		else
			AfxMessageBox("�������ݹ����г��ִ���");
	}
	return (DWORD)NULL;
}

void CDwztDlg::OnClose() 
{
	// ������Ի���رմ���
	Dlg_Close dlg;
	dlg.DoModal();
}
