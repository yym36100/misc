// sfc1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "windowsx.h"
#include "sfc1.h"

#include "ssystem.h"
#include "WinSurface.h"
#include "DummyWidget.h"

#define MAX_LOADSTRING 60

// Global Variables:
class mysystem:public sg::System
{
public:
	virtual void Init(void)
	{
		sg::Surface *s = new sg::WinSurface(400,300);
		pDisplay = new sg::Display(s);
		/*pEvents;*/
		pWidget = new sg::DummyWidget(s,200,200,3,3);
		for(u8 i=0;i<6;i++)
			for(u8 j=0;j<6;j++)
			pWidget->Add(new sg::DummyWidget(s,10+i*40,10+j*40,30,30));
		
	}
};
mysystem mysis;

HINSTANCE hInst;								// current instance
HWND hWnd;										// main window handle
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SFC1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SFC1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SFC1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SFC1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	hInst = hInstance; // Store instance handle in our global variable

	/*hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		200, 200, 400, 300, NULL, NULL, hInstance, NULL);*/
	hWnd = CreateWindowEx(WS_EX_DLGMODALFRAME,szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,200,200,400,300,NULL,NULL,hInstance,NULL);
	//WS_EX_TOOLWINDOW


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		mysis.Init();
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		mysis.Paint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		{
		sg::Events e;
		e.e=wParam==MK_LBUTTON?sg::Events::mpress:message==WM_LBUTTONUP?sg::Events::mrelease:sg::Events::mmove;
		e.x = GET_X_LPARAM(lParam);
		e.y = GET_Y_LPARAM(lParam);
		if(mysis.OnEvent(&e))
		{
			InvalidateRect(hWnd,NULL,false);
		}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

