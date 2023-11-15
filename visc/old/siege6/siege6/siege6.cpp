// siege6.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "window3.h"

#include "siege6.h"
#include "Wave.h"




int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	siege::stRect r = {600,600,512,400};
	siege::CWindow *w = new siege::CWindow(r,WS_OVERLAPPEDWINDOW,NULL,__ST("Test"));
	
	return w->Run();
}