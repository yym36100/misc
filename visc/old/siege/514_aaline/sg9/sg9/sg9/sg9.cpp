
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
	sg::Rect r(300u,300u,420u,420u);
	sg::Cmywindow *w = new sg::Cmywindow(r,WS_POPUPWINDOW|WS_CAPTION,NULL,(u16*)L"FFF test");
	res = w->Run();

	delete w;
	return res;
}