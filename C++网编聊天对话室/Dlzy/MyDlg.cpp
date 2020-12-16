// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dlzy.h"
#include "MyDlg.h"
#include "MyThread.h"
#include "Afxinet.h"
#include "mt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog


CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_strFtp = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
}


void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btnQuery);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, IDC_BUTTON_CANCLE, m_btnCancle);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, OnButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, OnButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

void CMyDlg::OnButtonCancle() 
{
	// 向对话框发送关闭消息
	SendMessage(WM_CLOSE);
	
}

void CMyDlg::OnButtonDownload() 
{
	// 获取控件变量值
	//UpdateData(TRUE);
	//禁用相关的控件
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);
	m_btnQuery.EnableWindow(FALSE);
	m_btnUpload.EnableWindow(FALSE);
	m_btnCancle.EnableWindow(FALSE);

	FTP_INFO* pp=new FTP_INFO;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
    pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtDownload,pp);

	// 启用相应控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);
	m_btnUpload.EnableWindow(TRUE);
	m_btnCancle.EnableWindow(TRUE);
	
}

void CMyDlg::OnButtonQuery() 
{
	UpdateData(TRUE);
	FTP_INFO* pp=new FTP_INFO;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
    pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtQuery,pp);
	
}

void CMyDlg::OnButtonUpload() 
{
	UpdateData(TRUE);
	// 禁用相应的控件
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);
	m_btnQuery.EnableWindow(FALSE);
	m_btnDownload.EnableWindow(FALSE);
	m_btnCancle.EnableWindow(FALSE);

	FTP_INFO* pp=new FTP_INFO;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
    pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtUpload,pp);

	// 启用相应的控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);
	m_btnDownload.EnableWindow(TRUE);
	m_btnCancle.EnableWindow(TRUE);
	
}




