#pragma once
#include "DebugMsg.h"

class CWinDbg :
	public siege::CDebugMsg
{
public:
	HANDLE ch;
	FILE *myfile;

	virtual void Msg(wchar_t *msg);

	static BOOL WINAPI HandlerRoutine( __in  DWORD dwCtrlType);

	static CWinDbg *CWinDbg::getInstance()
	{
		return &instance;
	}
	void init(void);
	void deinit();


private:
	bool inited;
	CWinDbg(void):inited(false){}
	~CWinDbg(void){}
	static CWinDbg instance;

	CWinDbg(const CWinDbg &);             // intentionally undefined
	CWinDbg & operator=(const CWinDbg &); // intentionally undefined



};
