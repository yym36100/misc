// sfc2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "sfc2.h"
#include "SWindow.h"
#include "DummyWidget.h"
#include "PopupMenu.h"

// Global Variables:
HINSTANCE hInst;								// current instance

#define __ST(x) (u16*)L##x

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HACCEL hAccelTable;
	MSG msg;

	sg::SWindow *w = new sg::SWindow(100,100,400,300,WS_OVERLAPPEDWINDOW,NULL,__ST("SWindow"));
	
	//SetTimer(w->hWnd,1,100,NULL);

	//DummyWidget(Surface *s,i16 x, i16 y, u16 w, u16 h)
	//w->wg = new sg::DummyWidget(w->s,10,10,100,20);
	//w->wg->Add(new sg::DummyWidget(w->s,10,50,100,20));


	w->wg = (sg::Widget*)&(
		*new sg::DummyWidget(w->s,10,10,100,20,__ST("egy"),200)+
		*new sg::DummyWidget(w->s,10,50,100,20,__ST("ketto"),201)+
		*new sg::DummyWidget(w->s,10,90,100,20,__ST("harom"),202)+
		*new sg::DummyWidget(w->s,10,130,100,20,__ST("negy hosszu"),203)
		);


	/*w2->wg = (sg::Widget*)&(
		*new sg::DummyWidget(w2->s,10,10,100,20,__ST("egy"))+
		*new sg::DummyWidget(w2->s,10,50,100,20,__ST("ketto"))+
		*new sg::DummyWidget(w2->s,10,90,100,20,__ST("harom"))+
		*new sg::DummyWidget(w2->s,10,130,100,20,__ST("negy hosszu"))
		);*/
	u16 *texts[]={
		__ST("egy"),
		__ST("ketto"),
		__ST("harom"),
		__ST("ot"),
		__ST("hat"),
		__ST("het"),
		__ST("nyolc"),

	};
	u16 *texts2[]={
		__ST("one"),
		__ST("two"),
		__ST("three"),
		__ST("four"),
		__ST("five"),
		__ST("six"),
		__ST("seven"),

	};
#define TEXTSIZE(s) (sizeof(s)/sizeof(u16*))

	/*sg::SWindow *w2 = new sg::SWindow(300,300,100,TEXTSIZE(texts)*10,WS_POPUP,w->hWnd,(u16*)L"second window");

	for(u8 i=0;i<sizeof(texts)/sizeof(u16*);i++)
	{
		if(!w2->wg)
			w2->wg = new sg::DummyWidget(w2->s,0,0+i*10,100,10,texts[i]);
		else
			w2->wg->Add(new sg::DummyWidget(w2->s,0,0+i*10,100,10,texts[i]));		
	}*/
	sg::PopupMenu *p = new sg::PopupMenu(100,100,texts,TEXTSIZE(texts),w,100);
	sg::PopupMenu *p2 = new sg::PopupMenu(200,200,texts2,TEXTSIZE(texts2),w,101);
	sg::PopupMenu *p3 = new sg::PopupMenu(300,200,texts2,TEXTSIZE(texts2),w,102);
	sg::PopupMenu *p4 = new sg::PopupMenu(400,200,texts2,TEXTSIZE(texts2),w,103);
	sg::PopupMenu *p5 = new sg::PopupMenu(500,200,texts2,TEXTSIZE(texts2),w,104);


	
		SendMessage(w->hWnd,WM_USER,0,0);
		//SendMessage(p->hWnd,WM_USER,0,0);
	//UpdateWindow(w->hWnd);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SFC2));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//delete w;
	//delete p;
	return (int) msg.wParam;
}
