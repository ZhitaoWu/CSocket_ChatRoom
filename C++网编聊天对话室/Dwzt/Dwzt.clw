; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDwztDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Dwzt.h"

ClassCount=10
Class1=CDwztApp
Class2=CDwztDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_DWZT_DIALOG
Resource2=IDR_MAINFRAME
Class4=CMySocket
Class5=CMyThread
Resource3=IDIGNORE
Class6=CMyDlg
Class7=CCSocket
Class8=RECVPARAM
Resource4=IDc
Class9=Dlg_login
Resource5=IDYES
Class10=Dlg_Close
Resource6=IDD_LOGIN_DIALOG
Resource7=IDD_ABOUTBOX
Resource8=IDD_MY_DIALOG
Resource9=IDD_CLOSE_DIALOG

[CLS:CDwztApp]
Type=0
HeaderFile=Dwzt.h
ImplementationFile=Dwzt.cpp
Filter=N

[CLS:CDwztDlg]
Type=0
HeaderFile=DwztDlg.h
ImplementationFile=DwztDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_MSG

[CLS:CAboutDlg]
Type=0
HeaderFile=DwztDlg.h
ImplementationFile=DwztDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DWZT_DIALOG]
Type=1
Class=CDwztDlg
ControlCount=24
Control1=IDC_STATIC_LNAME,static,1342308352
Control2=IDC_STATIC_LPORT,static,1342308352
Control3=IDC_EDIT_LPORT,edit,1350631552
Control4=IDC_STATIC_ONAME,static,1342308352
Control5=IDC_STATIC_OPORT,static,1342308352
Control6=IDC_EDIT_OPORT,edit,1350631552
Control7=IDC_STATIC_MSG,static,1342308352
Control8=IDC_EDIT_MSG,edit,1350631552
Control9=IDC_LIST_MSG,listbox,1352728835
Control10=IDC_BUTTON_SEND,button,1342242816
Control11=IDC_BUTTON_FTP,button,1342242816
Control12=IDC_BTNCTRLCONN,button,1342242816
Control13=IDC_LOCALIPADDR,SysIPAddress32,1342242816
Control14=IDC_PEERIPADDR,SysIPAddress32,1342242816
Control15=IDC_PROGRESS_RECV,msctls_progress32,1350565888
Control16=IDC_STATIC_FILE,static,1342308352
Control17=IDC_FILE_PATH,edit,1350631552
Control18=IDC_PROGRESS_SEND,msctls_progress32,1350565888
Control19=IDC_FIND_FILE,button,1342242816
Control20=IDC_SENT_FILE,button,1342242816
Control21=IDC_BUTTON_CLEAR,button,1342242816
Control22=IDC_RECV,edit,1350631552
Control23=IDC_SENT,edit,1350631552
Control24=IDC_STATIC_CHATNOTES,static,1342308352

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=IDC_EDIT_MSG

[CLS:CMyThread]
Type=0
HeaderFile=MyThread.h
ImplementationFile=MyThread.cpp
BaseClass=CWinThread
Filter=N

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=12
Control1=IDC_BUTTON_QUERY,button,1342242817
Control2=IDC_BUTTON_DOWNLOAD,button,1342242816
Control3=IDC_BUTTON_UPLOAD,button,1342242816
Control4=IDC_BUTTON_CANCLE,button,1342242816
Control5=IDC_LIST_FILE,listbox,1352728835
Control6=IDC_STATIC_FTP,static,1342308352
Control7=IDC_EDIT_FTP,edit,1350631552
Control8=IDC_EDIT_PWD,edit,1350631552
Control9=IDC_STATIC_NAME,static,1342308352
Control10=IDC_STATIC_FILE,static,1342308352
Control11=IDC_STATIC_PWD,static,1342308352
Control12=IDC_EDIT_NAME,edit,1350631552

[CLS:CMyDlg]
Type=0
HeaderFile=MyDlg.h
ImplementationFile=MyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_CANCLE

[CLS:CCSocket]
Type=0
HeaderFile=CSocket.h
ImplementationFile=CSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:RECVPARAM]
Type=0
HeaderFile=RECVPARAM.h
ImplementationFile=RECVPARAM.cpp
BaseClass=CSocket
Filter=N

[CLS:Dlg_login]
Type=0
HeaderFile=Dlg_login.h
ImplementationFile=Dlg_login.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_BITMAP

[CLS:Dlg_Close]
Type=0
HeaderFile=Dlg_Close.h
ImplementationFile=Dlg_Close.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Dlg_Close

[DLG:IDIGNORE]
Type=1
Class=Dlg_login
ControlCount=9
Control1=IDC_BUTTON_LOGIN,button,1342242817
Control2=IDC_BUTTON_CANCEL,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_PWD,edit,1350631552
Control5=IDC_STATIC_NAMEPWD,static,1342308352
Control6=IDC_STATIC_NAME,static,1342308352
Control7=IDC_STATIC_PWD,static,1342308352
Control8=IDC_STATIC_BITMAP,static,1342308352
Control9=IDC_STATIC,static,1342177287

[DLG:IDc]
Type=1
Class=?
ControlCount=9
Control1=IDC_BUTTON_LOGIN,button,1342242817
Control2=IDC_BUTTON_CANCEL,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_PWD,edit,1350631552
Control5=IDC_STATIC_NAMEPWD,static,1342308352
Control6=IDC_STATIC_NAME,static,1342308352
Control7=IDC_STATIC_PWD,static,1342308352
Control8=IDC_STATIC_BITMAP,static,1342308352
Control9=IDC_STATIC,static,1342177287

[DLG:IDD_LOGIN_DIALOG]
Type=1
Class=?
ControlCount=9
Control1=IDC_BUTTON_LOGIN,button,1342242817
Control2=IDC_BUTTON_CANCEL,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_PWD,edit,1350631552
Control5=IDC_STATIC_NAMEPWD,static,1342308352
Control6=IDC_STATIC_NAME,static,1342308352
Control7=IDC_STATIC_PWD,static,1342308352
Control8=IDC_STATIC_BITMAP,static,1342308352
Control9=IDC_STATIC,static,1342177294

[DLG:IDYES]
Type=1
Class=Dlg_Close
ControlCount=3
Control1=IDC_BUTTON_STAY,button,1342242817
Control2=IDC_BUTTON_CLOSE,button,1342242816
Control3=IDC_STATIC,static,1342177287

[DLG:IDD_CLOSE_DIALOG]
Type=1
Class=?
ControlCount=3
Control1=IDC_BUTTON_STAY,button,1342242817
Control2=IDC_BUTTON_CLOSE,button,1342242816
Control3=IDC_STATIC,static,1342177806

