#include "StdAfx.h"
#include "MySocket.h"
#include "resource.h"
#include "cstestdlg.h"

//CMySocket::CMySocket(void)
//{
//}

CMySocket::~CMySocket(void)
{
}
void CMySocket::OnReceive(int nErrorCode) {
	pDlg->m_list.AddString(L"on receive");
}

void CMySocket::OnConnect( int nErrorCode) {
	pDlg->m_list.AddString(L"Connected");
	Accept(client);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket:: OnAccept(){
	pDlg->m_list.AddString(L"Accepted");
}

int CMySocket::Send( const void* lpBuf, int nBufLen, int nFlags  ){
	if(boServer) {
		pDlg->m_list.AddString(L"Server send");
		client.Send(lpBuf,nBufLen,nFlags);
	}
	else {
		pDlg->m_list.AddString(L"Client send");
		CAsyncSocket::Send(lpBuf,nBufLen,nFlags);
	}
	return 0;
}	
