// CAsync.cpp
//

#include "stdafx.h"
#include "CAsync.h"
#include "EchoServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CAsync::SetParentApp(CWorkerApp *pParent)
{
	m_pParent=pParent;
}

void CAsync::OnAccept(int nErrorCode) 
{
	_cprintf_s("==> OnAccept ++++++++++++++\n");
	if(nErrorCode==0)
	{
		m_pParent->JobOnAccept();
	}
	CAsyncSocket::OnAccept(nErrorCode);
}

void CAsync::OnClose(int nErrorCode) 
{
	_cprintf_s("==> OnClose ++++++++++++++\n");
	if(nErrorCode==0)
	{
		m_pParent->JobOnClose(); 
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void CAsync::OnConnect(int nErrorCode) 
{
	_cprintf_s("==> OnConnect ++++++++++++++\n");
	CAsyncSocket::OnConnect(nErrorCode);
}

void CAsync::OnOutOfBandData(int nErrorCode) 
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CAsync::OnReceive(int nErrorCode) 
{
	_cprintf_s("==> OnReceive ++++++++++++++\n");
	if(nErrorCode==0)
	{
		m_pParent->JobOnReceive(); 
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CAsync::OnSend(int nErrorCode) 
{
	_cprintf_s("==> OnSend ++++++++++++++\n");
	CAsyncSocket::OnSend(nErrorCode);
}

BOOL CAsync::Create(UINT nSocketPort, int nSocketType, long lEvent, LPCTSTR lpszSocketAddress)
{
	return CAsyncSocket::Create(nSocketPort, nSocketType, lEvent, lpszSocketAddress);
}
