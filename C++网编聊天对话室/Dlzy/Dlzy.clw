; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Dlzy.h"

ClassCount=6
Class1=CDlzyApp
Class2=CDlzyDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DLZY_DIALOG
Resource2=IDR_MAINFRAME
Class4=CCSocket
Resource3=IDD_ABOUTBOX
Class5=CMyDlg
Class6=CMyThread
Resource4=IDD_MY_DIALOG

[CLS:CDlzyApp]
Type=0
HeaderFile=Dlzy.h
ImplementationFile=Dlzy.cpp
Filter=N

[CLS:CDlzyDlg]
Type=0
HeaderFile=DlzyDlg.h
ImplementationFile=DlzyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_THREAD

[CLS:CAboutDlg]
Type=0
HeaderFile=DlzyDlg.h
ImplementationFile=DlzyDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DLZY_DIALOG]
Type=1
Class=CDlzyDlg
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC_CNAME,static,1342308352
Control3=IDC_STATIC_CPORT,static,1342308352
Control4=IDC_EDIT_LOCALPORTNUM,edit,1350631552
Control5=IDC_STATIC_SNAME,static,1342308352
Control6=IDC_STATIC_SPORT,static,1342308352
Control7=IDC_EDIT_PEERPORTNUM,edit,1350631552
Control8=IDC_STATIC_MSG,static,1342308352
Control9=IDC_EDIT_MSG,edit,1350631552
Control10=IDC_BUTTON_SENT,button,1342242816
Control11=IDC_LIST_MSG,listbox,1352728835
Control12=IDC_BTNCTRLCONN,button,1342242816
Control13=IDC_LOCALIPADDR,SysIPAddress32,1342242816
Control14=IDC_PEERIPADDR,SysIPAddress32,1342242816
Control15=IDC_BUTTON_THREAD,button,1342242816

[CLS:CCSocket]
Type=0
HeaderFile=CSocket.h
ImplementationFile=CSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=12
Control1=IDC_BUTTON_CANCLE,button,1342242817
Control2=IDC_BUTTON_QUERY,button,1342242816
Control3=IDC_BUTTON_DOWNLOAD,button,1342242816
Control4=IDC_BUTTON_UPLOAD,button,1342242816
Control5=IDC_LIST_FILE,listbox,1352728835
Control6=IDC_STATIC_FTP,static,1342308352
Control7=IDC_EDIT_FTP,edit,1350631552
Control8=IDC_STATIC_NAME,static,1342308352
Control9=IDC_EDIT_NAME,edit,1350631552
Control10=IDC_STATIC_PWD,static,1342308352
Control11=IDC_EDIT_PWD,edit,1350631552
Control12=IDC_STATIC_FILE,static,1342308352

[CLS:CMyDlg]
Type=0
HeaderFile=MyDlg.h
ImplementationFile=MyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_QUERY

[CLS:CMyThread]
Type=0
HeaderFile=MyThread.h
ImplementationFile=MyThread.cpp
BaseClass=CWinThread
Filter=N

