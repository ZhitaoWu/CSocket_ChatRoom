// MyThread.cpp : implementation file
//

#include "stdafx.h"
#include "Dlzy.h"
#include "MyThread.h"
#include "MyDlg.h"
//#include "mt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	m_dlg.Create(IDD_MY_DIALOG);	// ������ID�ŵĶԻ��򴰿�
	m_dlg.ShowWindow(SW_SHOW);		// ��ʾ����
	m_pMainWnd = &m_dlg;			// ��ȡ�Ի��򴰿�ָ��
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	m_dlg.DestroyWindow;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
	//{{AFX_MSG_MAP(CMyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyThread message handlers
