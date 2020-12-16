// Dlg_login.cpp : implementation file
//

#include "stdafx.h"
#include "Dwzt.h"
#include "Dlg_login.h"
#include "DwztDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_login dialog

BOOL CDwztApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	Dlg_login dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

Dlg_login::Dlg_login(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_login::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_login)
	m_strLoginName = _T("");
	m_strLoginPwd = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_login)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strLoginName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strLoginPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_login, CDialog)
	//{{AFX_MSG_MAP(Dlg_login)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_login message handlers

void Dlg_login::OnButtonLogin() 
{
	// TODO: Add your control notification handler code here
		this->UpdateData(true);
      CWnd *pWnd = NULL;
      // ��֤�û����������Ƿ���ȷ
      if(this->m_strLoginName != "wzt")
      {
          AfxMessageBox("�û����������������룡");
         m_strLoginName = "";
         pWnd = GetDlgItem(IDC_EDIT_NAME); //��ȡIDC_USER�Ŀؼ�ָ��
         //pWnd->SetFocus(); // ���ý���
         UpdateData(false);
     }
     else if (this->m_strLoginPwd != "123")
     {
         AfxMessageBox("����������������룡");
         m_strLoginPwd = "";
         pWnd = GetDlgItem(IDC_EDIT_PWD);
         pWnd->SetFocus();
         UpdateData(false);
     }
     else
     {
		 this->ShowWindow(SW_HIDE);
         CDwztDlg dlg;   //��Ҫ��Ӹ�C***Dlg.hͷ�ļ����������ͨ����
         dlg.DoModal();
		 this->ShowWindow(SW_SHOW);

    }
	
}

void Dlg_login::OnButtonCancel() 
{
	AfxGetMainWnd()->PostMessage(WM_QUIT); // ����WM_QUIT��Ϣ�˳�����
	CDialog::OnCancel();
	
}

void Dlg_login::OnPaint()
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
