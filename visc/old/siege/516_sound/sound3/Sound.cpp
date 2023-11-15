#include "StdAfx.h"
#include "Sound.h"

DWORD WINAPI CSound::static_run(void *Param)
	{
		CSound *ct = (CSound *)Param;
		return ct->Run();
	}
