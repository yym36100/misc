
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
	sg::Rect r(300,300,800,480);
	sg::Cmywindow *w = new sg::Cmywindow(r,WS_OVERLAPPEDWINDOW,NULL,(u16*)L"FFF test");
	res = w->Run();

	delete w;
	return res;
}