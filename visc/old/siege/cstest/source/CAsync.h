// CAsync.h
//

#if !defined(CAsync_h_INCLUDED)
#define CAsync_h_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAsync : private CAsyncSocket
{
	friend class CWorkerApp;
	// because of m_pParent it is closely tied to the corresponding Worker Class
	// and therefore it can't serve anyone else.
	// just take both as blueprint for similar issues.
private:
	CWorkerApp* m_pParent;
	void SetParentApp(CWorkerApp* pParent);

private:
	//my Overwrites of the Callbacks of the Socket-Events, I hook on by Create
	//		the Callbacks just redirect the call to m_pParent's Worker App
	virtual void OnReceive(int nErrorCode);	//FD_READ
	virtual void OnSend(int nErrorCode);	//FD_WRITE
	virtual void OnOutOfBandData(int nErrorCode);	//FD_OOB
	virtual void OnAccept(int nErrorCode);	//FD_ACCEPT
	virtual void OnConnect(int nErrorCode);	//FD_CONNECT
	virtual void OnClose(int nErrorCode);	//FD_CLOSE

	BOOL Create(
		UINT nSocketPort = 0,
		int nSocketType = SOCK_STREAM,
		long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
		LPCTSTR lpszSocketAddress = NULL 
		);

////empty Default Constructor, can be canceled
//	CAsync(){}
//	virtual ~CAsync(){}

};

#endif // !defined(CAsync_h_INCLUDED)
