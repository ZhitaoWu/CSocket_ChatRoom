// Dwzt.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Dwzt.h"
#include "DwztDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDwztApp

BEGIN_MESSAGE_MAP(CDwztApp, CWinApp)
	//{{AFX_MSG_MAP(CDwztApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDwztApp construction

CDwztApp::CDwztApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDwztApp object

CDwztApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDwztApp initialization

