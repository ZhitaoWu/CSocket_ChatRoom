// Dlg_Close.cpp : implementation file
//

#include "stdafx.h"
#include "Dwzt.h"
#include "Dlg_Close.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Close dialog


Dlg_Close::Dlg_Close(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Close::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Close)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Close::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Close)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Close, CDialog)
	//{{AFX_MSG_MAP(Dlg_Close)
	ON_BN_CLICKED(IDC_BUTTON_STAY, OnButtonStay)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Close message handlers

void Dlg_Close::OnButtonStay() 
{
	// 取消退出
	CDialog::OnCancel();
	
}

void Dlg_Close::OnButtonClose() 
{
	// 退出
	PostMessageW(GetParent()->m_hWnd,WM_QUIT,0,0);
	CDialog::OnOK();
	
}
