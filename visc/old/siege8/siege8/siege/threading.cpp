#include "stdafx.h"
#include "threading.h"

DWORD WINAPI CThread::threadFunc(LPVOID lpParam)
{
	CThread *pThread = (CThread*)(lpParam);
	
	if (pThread)
		pThread->run();

	return 0;
}