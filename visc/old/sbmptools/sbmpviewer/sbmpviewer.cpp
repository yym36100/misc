// sbmpviewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "sbmpviewer.h"

#include "sbmp.h"
#include "zlib.h"

#include <GdiPlus.h>

#define MAX_LOADSTRING 100
using namespace Gdiplus;
Bitmap *i;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

sg::tsBmp sBmp;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	sizeCheck();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	LPWSTR *szArglist;
	int nArgs;


	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	FILE *f;
	if(!(f=_wfopen(szArglist[1],L"rb"))) 
	{
		assert(false);
		return 0;
	}

	
	fread(&sBmp,sizeof(sBmp.head),1,f);
	u32 size = sBmp.head.size;
	u8 *pixels = new u8[size];
	fread(pixels,size,1,f);
	sBmp.pixels = pixels;
	i = new Bitmap(sBmp.head.w,sBmp.head.h,PixelFormat32bppARGB);

	u16 w = sBmp.head.w;
	u16 h = sBmp.head.h;
	u32 color;
	u8 *p = sBmp.pixels;
	u8 r,g,b,a;
	u8 *pix = NULL;

	if(sBmp.head.type==sg::rleARGB8888)
	{
		u8 *pix = new u8[w*h*4];
		u32 *w = (u32*)pix;
		u32 color;
		u32 i=0;
		u16 cnt;
		while(i<sBmp.head.size)
		{
			a = *p++;
			i++;
			if(a==sg::rleARGB8888Escape)
			{
				cnt = (*p++)<<8;
				cnt += *p++;
				cnt++;

				a = *p++;r = *p++;g = *p++;b = *p++;
				color = (b<<24)|(g<<16)|(r<<8)|(a<<0);	
				i+=6;
				while(cnt--)
				{
					*w++=color;
				}
			}
			else
			{
				r = *p++;g = *p++;b = *p++;
				color = (b<<24)|(g<<16)|(r<<8)|(a<<0);			
				i+=3;
				*w++=color;
			}
		}	
		delete [] sBmp.pixels;
		sBmp.pixels=pix;
		p = sBmp.pixels;
	}
	if(sBmp.head.type==sg::zARGB8888)
	{
		u32 size = w*h*4;
		u8 *pix = new u8[size];
		int res2 = uncompress(pix,&size,sBmp.pixels,sBmp.head.size);

		delete [] sBmp.pixels;
		sBmp.pixels=pix;
		p = sBmp.pixels;
	}
	for(u16 y=0;y<h;y++)
	{
		for(u16 x=0;x<w;x++)
		{				
			if(sBmp.head.type == sg::RGB888)
				a = 0xff;
			else
				a = *p++;
			r = *p++;g = *p++;b = *p++;
			color = (a<<24)|(r<<16)|(g<<8)|(b<<0);


			i->SetPixel(x,y,color);
		}
	}

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SBMPVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SBMPVIEWER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	delete[] sBmp.pixels;
	delete i;
	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SBMPVIEWER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SBMPVIEWER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{	
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			Graphics g(hdc);
			g.DrawImage(i,10,10);

			WCHAR string[200];
			u32 size;
			switch (sBmp.head.type)
			{
			case sg::RGB888:
				size = sBmp.head.w*sBmp.head.h*3;
				break;
			default:
				size = sBmp.head.w*sBmp.head.h*4;
			}

			float perc =(sBmp.head.size/(double)size)*100.0;
			wchar_t *texts[] = {L"ARGB8888",L"RGB888",L"rleARGB8888",L"zARGB8888"};

			swprintf(string,L"%dx%d (%s)\nsize = %d \ncompsize = %d compression = %.1f %%",
				i->GetWidth(),i->GetHeight(),texts[sBmp.head.type],
				size,sBmp.head.size,perc);

			FontFamily   fontFamily(L"Arial");
			Font         font(&fontFamily, 14, FontStyleRegular, UnitPixel);
			RectF        rectF(10.0+i->GetWidth(), 10.0f, 200.0f, 122.0f);
			SolidBrush   solidBrush(Color(255, 0, 0, 0));

			g.DrawString(string, -1, &font, rectF, NULL, &solidBrush);

			Pen pen(Color(255, 0, 0, 0));
			g.DrawRectangle(&pen, rectF);


			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
