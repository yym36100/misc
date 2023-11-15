#pragma once

#define siege_debug (1)

#define screen_w	(800)
#define screen_h	(600)

#if siege_debug==1
#include "WinDbg.h"
#define siege_dbg(s){	\
	siege::CDebugMsg *pDbgMsg = CWinDbg::getInstance();\
	pDbgMsg->Msg(s);\
	}
#else
#define siege_dbg(s)
#endif



