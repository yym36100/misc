#pragma once
#include "afxsock.h"

class CcstestDlg;
class CMySocket :
	public CAsyncSocket
{
public:
	bool boServer;	
	//	CMySocket(void);
	~CMySocket(void);

	CcstestDlg *pDlg;
	CAsyncSocket client;

	CMySocket():boServer(false){}

	void OnConnect( int nErrorCode);
	void OnReceive(int nErrorCode);

	void OnAccept();

	int Send( const void* lpBuf, int nBufLen, int nFlags = 0  );

};
