#include "stdafx.h"

#include ".\siege\window4.h"
#include ".\siege\threading.h"

#include "siege8.h"

class CMyThread :public CThread
{
public:
	CMyThread():CThread(){a=0;}
private:
	int a;
	void run()
	{
		while(1)
		{
			a++;
			Sleep(1000);
		}
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	CMyThread t1;
	siege::stRect r(600,600,700,400);
	siege::CWindow *w = new siege::CWindow(r,WS_OVERLAPPEDWINDOW,NULL,(u16*)L"Test");
	
	return (int)w->Run();
}