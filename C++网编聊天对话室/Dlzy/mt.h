BOOL Upload(CString strFtp,CString strName,CString strPwd,CString strFileName, CString strPathName);
BOOL Download(CString strFtp,CString strName,CString strPwd,CString strFileName, CString strPathName);
UINT mtQuery(LPVOID pParam)
{
	if(pParam==NULL) AfxEndThread(NULL);
	FTP_INFO* pp=(FTP_INFO*)pParam;
	CListBox* pList=pp->pList;
	CString strFtp=pp->strFtp;
    CString strName=pp->strName;
	CString strPwd=pp->strPwd;
	CInternetSession* pSession;
	CFtpConnection* pConnection;
	CFtpFileFind* pFileFind;

    pSession=NULL;
	pConnection=NULL;
	pFileFind=NULL;

	while(pList->GetCount()!=0) pList->DeleteString(0);
    pSession=new CInternetSession(NULL,1,PRE_CONFIG_INTERNET_ACCESS);

    try
	{
        pConnection=pSession->GetFtpConnection(strFtp,strName,strPwd);
	}catch(CInternetException* e)
	{
		e->Delete();
		pConnection=NULL;
		AfxMessageBox("连接类创建失败！");
		return 1;
	}
	BOOL bContinue;
	CString strFileName;
	if(pConnection!=NULL)
	{
         pFileFind=new CFtpFileFind(pConnection);
		 bContinue=pFileFind->FindFile("*");
		 if(!bContinue)
         {
			 pFileFind->Close();
			 delete pFileFind;
			 pFileFind=NULL;     
		 }
		 while(bContinue)
         {
			 bContinue=pFileFind->FindNextFile();
			 strFileName=pFileFind->GetFileName();
			 if(pFileFind->IsDirectory()) strFileName="["+strFileName+"]";
			 pList->AddString(strFileName);
		 }
		if(pFileFind!=NULL)
        {
			pFileFind->Close();
			delete pFileFind;
			pFileFind=NULL;
		}
        pConnection->Close();
		delete pConnection;
		pConnection=NULL;

	}
	delete pSession;

	return 0;
}






UINT mtUpload(LPVOID pParam)
{
    if(pParam==NULL) AfxEndThread(NULL);
	FTP_INFO* pp=(FTP_INFO*)pParam;
	CListBox* pList=pp->pList;
	CString strFtp=pp->strFtp;
    CString strName=pp->strName;
	CString strPwd=pp->strPwd;

	CFileDialog dlg(TRUE,NULL,"*.*");
	if(dlg.DoModal()==IDOK)
	{
		CString strFileName;
        CString strPathName;
        strFileName=dlg.GetFileName();
		strPathName=dlg.GetPathName();
		if(Upload(strFtp,strName,strPwd,strFileName,strPathName))
		{
			AfxMessageBox("上传成功!");
		}else
		{
            AfxMessageBox("上传失败!");
		}
	}
	return 0;

}


UINT mtDownload(LPVOID pParam)
{
    if(pParam==NULL) AfxEndThread(NULL);
	FTP_INFO* pp=(FTP_INFO*)pParam;
	CListBox* pList=pp->pList;
	CString strFtp=pp->strFtp;
    CString strName=pp->strName;
	CString strPwd=pp->strPwd;

	int nSel;
	nSel=pList->GetCurSel();
	if(nSel==-1)
	{
		AfxMessageBox("请选择下载文件！");
		return 1;
	}
	CString strFileName;
	pList->GetText(nSel,strFileName);

	if(strFileName.GetAt(0)!='[')
	{
		CFileDialog dlg(FALSE,NULL,strFileName);
        if(dlg.DoModal()==IDOK)
		{
             CString strPathName;
			 strPathName=dlg.GetPathName();
			 if(Download(strFtp,strName,strPwd,strFileName,strPathName))
			 {
                 AfxMessageBox("下载成功！");    
			 }else
			 {
             AfxMessageBox("下载失败！");
			 }
		}
	}else
	{
        AfxMessageBox("不能选择下载文件！"); 
	}
	return 0;

}
BOOL Download(CString strFtp,CString strName,CString strPwd,CString strFileName, CString strPathName)
{
	
	CInternetSession* pSession;
	CFtpConnection* pConnection;
    
    pSession=NULL;
	pConnection=NULL;

	pSession=new CInternetSession(NULL,1,PRE_CONFIG_INTERNET_ACCESS);

    try
	{
        pConnection=pSession->GetFtpConnection(strFtp,strName,strPwd);
	}catch(CInternetException* e)
	{
		e->Delete();
		pConnection=NULL;
		AfxMessageBox("连接类创建失败！");
		return FALSE;
	}
	
	if(pConnection!=NULL)
	{
        
		 if(!pConnection->GetFile(strFileName,strPathName))
         {
			 pConnection->Close();
			 delete pConnection;
			 pConnection=NULL;     
		     pSession->Close();
			delete pSession;
			pSession=NULL;
			return FALSE;	 
		 }
        pConnection->Close();
		delete pConnection;
		pConnection=NULL;
	}
	pSession->Close();
	delete pSession;
	pSession=NULL;
	return TRUE;	 

}



BOOL Upload(CString strFtp,CString strName,CString strPwd,CString strFileName, CString strPathName)
{
    
	CInternetSession* pSession;
	CFtpConnection* pConnection;
    
    pSession=NULL;
	pConnection=NULL;

	pSession=new CInternetSession(NULL,1,PRE_CONFIG_INTERNET_ACCESS);

    try
	{
        pConnection=pSession->GetFtpConnection(strFtp,strName,strPwd);
	}catch(CInternetException* e)
	{
		e->Delete();
		pConnection=NULL;
		AfxMessageBox("连接类创建失败！");
		return FALSE;
	}
	
	if(pConnection!=NULL)
	{
        
		 if(!pConnection->PutFile(strPathName,strFileName))
         {
			 pConnection->Close();
			 delete pConnection;
			 pConnection=NULL;     
		     pSession->Close();
			delete pSession;
			pSession=NULL;
			return FALSE;	 
		 }
        pConnection->Close();
		delete pConnection;
		pConnection=NULL;
	}
	pSession->Close();
	delete pSession;
	pSession=NULL;
	return TRUE;	 
}
