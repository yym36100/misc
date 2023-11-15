// EchoServer.cpp
//

#include "stdafx.h"
#include "EchoServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//default Message-Loop of CWinApp =====================================
BEGIN_MESSAGE_MAP(CWorkerApp, CWinApp)
END_MESSAGE_MAP()

CWorkerApp theApp;

BOOL CWorkerApp::InitInstance()
{
	//I allocate a Console for CWinApp-Output =========================
	BOOL R = AllocConsole();
	if (!R)
	{
		AfxMessageBox("No Console");
		return FALSE;
	}
	_cprintf_s("InitInstance()\n");

	//prevent CWinApp from stopping without CWnd ======================
	AfxOleSetUserCtrl(FALSE);

	//initialize Windows Socket =======================================
    if(AfxSocketInit()==FALSE)
	{
		_cprintf_s("Sockets Could Not Be Initialized");
		return FALSE;
	}

	m_sListener.SetParentApp(this); 
	m_sConnected.SetParentApp(this);
	m_port=12345;
//	m_port=0; //Listen on all Ports does not work!

	//I start the Listener here ==========================================
	m_sListener.Create(m_port); 
	if(m_sListener.Listen()==FALSE)
	{
		_cprintf_s("Unable to Listen on that port,please try another port");
		m_sListener.Close(); 
		return FALSE;			
	}
	_cprintf_s("++>Server is listening...\n");

	return TRUE; //TRUE to start CWinApp::Run() -the MFC Message Loop- ===
}
int CWorkerApp::ExitInstance()
{
	_cprintf_s("ExitInstance: press ENTER to close App...");
	char cb[256];
	size_t sRead;
	errno_t err = _cgets_s(cb, 255, &sRead);

	//Cleanup ============================================================
	BOOL R = FreeConsole();
	if (!R)
	{
		//error
		return 1;
	}
	return 0;
}

void CWorkerApp::JobOnAccept()
{
	CString strIP;
	UINT port;
	if(m_sListener.Accept(m_sConnected))
	{
		m_sConnected.GetSockName(strIP,port);
		m_status="Client Connected,IP :"+ strIP;
			_cprintf_s("++>%s Port:%d\n", m_status, port);
	}
	else
	{
		_cprintf_s("Can not Accept Connection");
	}
}
void CWorkerApp::JobOnClose()
{
	_cprintf_s("++>post WM_QUIT\n");
	AfxPostQuitMessage(0); //send WM_QUIT Message
}
void CWorkerApp::JobOnReceive()
{
	char pBuf[1024];
	CString strData;
	int iLen;
	iLen=m_sConnected.Receive(pBuf,1023);
	if(iLen==SOCKET_ERROR)
	{
		_cprintf_s("Could not Recieve");
	}
	else
	{
		pBuf[iLen]=NULL;
		strData=pBuf;
		m_recieveddata.Insert(m_recieveddata.GetLength(),strData);   //store in class
			_cprintf_s("++>%s\n", strData);
		m_sConnected.Send(pBuf,iLen); //echo
		//m_sConnected.ShutDown(0);  
	}

}
