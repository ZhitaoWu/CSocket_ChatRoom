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
	//Ҫ�ж�Զ���Ƿ�رգ�ֱ���жϵ�ǰ�����m_hSocket�Ƿ�ΪINVALID_SOCKET���ɡ� 
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
		int nRect = ReceiveFrom(s,sizeof(s),szIP,nPort);   //������Ϣ,����ֵΪ���յ����ֽ���	
		if(nRect<=0)		
			return ;	
		s[nRect] = 0;     //β������
		CString str;	
		str.Format("%s ��liuzeyu˵�� \r\n%s\r\n","wuzhitao",s);  //��ʽ��
		CWnd * pDlg = AfxGetMainWnd();	 ///�õ������ڵ�ָ��
		CListBox * pList = (CListBox *)pDlg->GetDlgItem(IDC_LIST_MSG);	  //�õ��б��Ķ���
		pList->AddString(str);	    //��ʾ����	

		CSocket::OnReceive(nErrorCode);
}
