#include "StdAfx.h"
#include "WinDbg.h"

CWinDbg CWinDbg::instance;

void CWinDbg::init(void)
{
	//create a console window
	AllocConsole();
	ch = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Siege debug");
	SetConsoleCtrlHandler(CWinDbg::HandlerRoutine,TRUE);
	//myfile = fopen("se.log","wt");
}

void CWinDbg::deinit()
{
	//fflush(myfile);
//	fclose(myfile);
	FreeConsole();
}
void CWinDbg::Msg(wchar_t *msg)
{
	if(!inited)init();
	DWORD nr;
	WriteConsole(ch,msg,wcslen(msg),&nr,NULL);
	//fwprintf(stdout,msg);
	//fflush(myfile);
}

BOOL WINAPI CWinDbg::HandlerRoutine( __in  DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		{
			ExitProcess(0);
		}break;
	default:break;
	}
	return TRUE;
}
