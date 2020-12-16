// CSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Dlzy.h"
#include "CSocket.h"
#include "DlzyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSocket

CCSocket::CCSocket()
{
}

CCSocket::~CCSocket()
{
	//要判断远程是否关闭，直接判断当前对象的m_hSocket是否为INVALID_SOCKET即可。 
	if (INVALID_SOCKET != this->m_hSocket)
	{
		Close();
	}
}
// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCSocket, CSocket)
	//{{AFX_MSG_MAP(CCSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCSocket member functions

void CCSocket::OnReceive(int nErrorCode) 
{
		char s[2048]; 	
		CString szIP;	
		UINT nPort; 	
		int nRect = ReceiveFrom(s,sizeof(s),szIP,nPort);   //接收消息,返回值为接收到的字节数	
		if(nRect<=0)		
			return ;	
		s[nRect] = 0;     //尾部清零
		CString str;	
		str.Format("%s 对liuzeyu说： \r\n%s\r\n","wuzhitao",s);  //格式化
		CWnd * pDlg = AfxGetMainWnd();	 ///得到主窗口的指针
		CListBox * pList = (CListBox *)pDlg->GetDlgItem(IDC_LIST_MSG);	  //得到列表框的对象
		pList->AddString(str);	    //显示出来	

		CSocket::OnReceive(nErrorCode);
}
