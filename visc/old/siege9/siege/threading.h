#pragma once
#include "windows.h"

class CThread
{
public:

	HANDLE handle;

	CThread(void)
	{
		handle = CreateThread( NULL, 0, 
			&CThread::threadFunc, this, 0, NULL);  
	}

	virtual ~CThread(void)
	{		
		if(handle)
			CloseHandle(handle);
	}
	//void handleevent(u16 e){}
	void resume(void){ResumeThread(handle);}
	void suspend(void){SuspendThread(handle);}
	virtual void run() = 0;

private:
	static DWORD WINAPI threadFunc(LPVOID lpParam);
};
