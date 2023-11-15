
#include "sg9.h"
#include "mywindow.h"

#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#include <tchar.h>


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	int res;
	sg::Rect r(300+60,300+90,1024+20+2,480-40);
	sg::Cmywindow *w = new sg::Cmywindow(r,WS_OVERLAPPEDWINDOW,NULL,(u16*)L"FFT test");
	res = w->Run();

	delete w;
	return res;
}