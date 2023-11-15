// EchoServer.h
//

#if !defined(EchoServer_h_INCLUDED)
#define EchoServer_h_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CAsync.h"

class CWorkerApp : public CWinApp
{
public:
	void JobOnReceive();
	void JobOnClose();
	void JobOnAccept();

	int		m_port;
	CString	m_recieveddata;
	CString	m_status;

	virtual BOOL InitInstance();
	virtual int ExitInstance( );

	//declare the Message-Loop ========================================
	DECLARE_MESSAGE_MAP()

////empty Default Constructor, can be canceled
//	CWorkerApp(){}
//	~CWorkerApp(){}

private:
	CAsync m_sListener;
	CAsync m_sConnected;
};

#endif // !defined(EchoServer_h_INCLUDED)
