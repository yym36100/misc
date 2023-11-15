#pragma once
#include "thread.h"
namespace sg{

	DWORD WINAPI CThread::static_run(void *Param)
	{
		CThread *ct = (CThread *)Param;
		return ct->Run();
	}

}; // siege
