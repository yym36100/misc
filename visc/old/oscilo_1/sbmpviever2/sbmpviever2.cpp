// sbmpviewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <atlimage.h>
#include <GdiPlus.h>

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <windows.h>
#include <stdio.h>
#include <shellapi.h>
#include "resource.h"


#include "sbmp.h"



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

sbmp::csbmp sBmp;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{


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
	u32 size = sBmp.head.width*sBmp.head.height * 4 * sBmp.head.noFrames;

	u8 *pixels = new u8[size];
	fread(pixels,size,1,f);
	sBmp.buffer = pixels;
	i = new Bitmap(sBmp.head.width,sBmp.head.height,PixelFormat32bppARGB);

	u16 w = sBmp.head.width;
	u16 h = sBmp.head.height;

	u8 r,g,b,a;
	u8 *p = sBmp.buffer;
	////////////
	if(sBmp.head.type==sbmp::rleRGBA888)
	{
		u8 *pix = new u8[w*h*4];
		u32 *w = (u32*)pix;
		u32 color;
		u32 i=0;
		u16 cnt;
		while(i<sBmp.head.fsize)
		{
			a = *p++;
			i++;
			if(a==sbmp::rleARGB8888Escape)
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
		delete [] sBmp.buffer;
		sBmp.buffer=pix;	
	}
	////////////
	u32 color;
	p = sBmp.buffer;


	//u8 *pix = NULL;

	for(u16 y=0;y<h;y++)
	{
		for(u16 x=0;x<w;x++)
		{				

			a = *p++;
			r = *p++;g = *p++;b = *p++;
			color = (a<<24)|(r<<16)|(g<<8)|(b<<0);
			i->SetPixel(x,y,color);
		}
	}

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SBMPVIEVER2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SBMPVIEVER2));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//delete[] sBmp.pixels;
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SBMPVIEVER2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SBMPVIEVER2);
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

			size = sBmp.head.width*sBmp.head.height*4;


			float perc =(sBmp.head.fsize/(double)size)*100.0;
			wchar_t *texts[] = {L"ARGB8888",L"RGB888",L"rleARGB8888",L"zARGB8888"};

			swprintf(string,L"%dx%d (%s)\nsize = %d \ncompsize = %d compression = %.1f %%",
				i->GetWidth(),i->GetHeight(),texts[sBmp.head.type],
				size,sBmp.head.fsize,perc);

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