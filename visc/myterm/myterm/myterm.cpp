// myterm.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include "myterm.h"

#define www	800
#define hhh	600
#define zzz 1

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H


#include "specialchars.h"
#include "typelib.h"


HDC hDC;
void *pb;


HINSTANCE hInst;							// current instance
TCHAR szTitle[] = "Title";					// The title bar text
TCHAR szWindowClass[] = "myClass";			// the main window class name

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
HWND ghWnd;
typelib *pl;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow) {

	MSG msg;
	FT_Face     face;
	int error = 36100;
	int glyph_index;
	int charcode = 0x2560;

#define lh (14)
	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow)) { return FALSE; }


	typelib tl;
	pl = &tl;
	tl.init("c:/Fonts/DejaVuSans.ttf");		    
	tl.setSurface((unsigned char*)pb);

	//https://unicode-table.com/ro/#miscellaneous-symbols

	int xx=40,yy=40;
	tl.drawText(xx,yy,L"X >\x256c\x256c\x256c\x256c< \x2502 Nyári piros alma iiiWWWXXXjjj\x20ac \x2502");
	xx=50;yy=50+lh;
	tl.drawText(xx,yy,L"\x2502 Bugázott réz a padláson \x258a f");

	xx=50;yy=50+lh*2;
	tl.drawText(xx,yy,L"\x2502 \x2581\x2582\x2583\x2584\x2585\x2586\x2587\x2588\x2588\x2588 \x2588\x2589 \x2588\x258a \x2588\x258b \x2588\x258c \x2588\x258d \x2588\x258e \x2588\x258f");

	xx=50;yy=50+lh*3;
	tl.drawText(xx,yy,L" \x2600 alma \x2500\x2510");
	xx=50;yy=50+lh*4;
	tl.drawText(xx,yy,L" \x2639 D\x01ce-te la o parte m\x0203nca-\x021bi-a\x0219 Pi\x03b2wasser \x03c0");

	ShowWindow(ghWnd, nCmdShow);
	UpdateWindow(ghWnd);
	//InvalidateRect(ghWnd,0,false);
	SetTimer(ghWnd,36100,100,0);

	while (GetMessage(&msg, NULL, 0, 0)) {	
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {

	HMENU sysmenu;

	hInst = hInstance; // Store instance handle in our global variable

	RECT r={0,0,www,hhh};
	DWORD ws = WS_TILED | WS_CAPTION | WS_SYSMENU |WS_MINIMIZEBOX ;
	//DWORD ws = WS_OVERLAPPEDWINDOW ;
	AdjustWindowRect(&r,ws,false);

	ghWnd = CreateWindow(szWindowClass, szTitle, ws,
		CW_USEDEFAULT, 0, 
		r.right - r.left, r.bottom - r.top, 
		NULL, NULL, hInstance, NULL);

	if (!ghWnd) { return FALSE; }
	sysmenu = GetSystemMenu(ghWnd,false);
	AppendMenu(sysmenu,MF_SEPARATOR,36100,"MyMenu");
	AppendMenu(sysmenu,MF_STRING,36100,"MyMenu");

	return TRUE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			BITMAPINFO BitInfo;

			HBITMAP hBitmap;


			ZeroMemory(&BitInfo,sizeof(BitInfo));
			BitInfo.bmiHeader.biBitCount = 32;			// rgb 8 bytes for each component(3)
			BitInfo.bmiHeader.biCompression = BI_RGB;	// rgb = 3 components
			BitInfo.bmiHeader.biPlanes = 1;
			BitInfo.bmiHeader.biSize = sizeof(BitInfo.bmiHeader); // size of this struct
			BitInfo.bmiHeader.biWidth = www;		// width of window
			BitInfo.bmiHeader.biHeight = -hhh;		// height of window

			hDC = CreateCompatibleDC(0);



			hBitmap = CreateDIBSection(hDC, &BitInfo, DIB_RGB_COLORS, &pb, 0, 0); // create a dib section for the dc
			memset(pb,0xff ,www*hhh*4);

			SelectObject(hDC, hBitmap); // assign the dib section to the dc
		}
	case WM_TIMER:
		InvalidateRect(ghWnd,0,false);
		break;

	case WM_PAINT:
		{
		static int n=0;
		hdc = BeginPaint(hWnd, &ps);

		if(pl){
		pl->drawVbar(200,200,n++);
		if(n==8)n=0;
		}
		StretchBlt(hdc,0,0,www*zzz,hhh*zzz,hDC,0,0,www,hhh,SRCCOPY);

		EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSCOMMAND:
		if(wParam == 36100){
			MessageBox(hWnd,"text","title",0);
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

