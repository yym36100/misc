#pragma once
#include "stypes.h"
#include "WinSurface.h"
//#include "Widget.h"
//#include "DummyWidget.h"

extern HWND hWnd;										// main window handle

namespace sg
{
	class Widget;

	class SWindow
	{
	public:
		u16 x,y,w,h;
		static bool init;
		HWND       hWnd;
		Surface *s;
//		Widget *w;

		SWindow(void){}
		SWindow(u16 x, u16 y, u16 w, u16 h)
			:x(x),y(y),w(w),h(h)
		{
			HINSTANCE hInstance=GetModuleHandle(NULL);

			if(!init)
			{
			WNDCLASSEX	WndClsEx;
			WndClsEx.cbSize        = sizeof(WNDCLASSEX);
			WndClsEx.style         = CS_DROPSHADOW;
			WndClsEx.lpfnWndProc   = WndProcedure;
			WndClsEx.cbClsExtra    = 0;
			WndClsEx.cbWndExtra    = 0;
			WndClsEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
			WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
			WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			//WndClsEx.hbrBackground = NULL;
			WndClsEx.lpszMenuName  = NULL;
			WndClsEx.lpszClassName = _T("SWindow");
			WndClsEx.hInstance     = hInstance;
			WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassEx(&WndClsEx);
			init = true;
			}
			/*CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\*/

			RECT rect;
			GetWindowRect(::hWnd,&rect);
			hWnd = CreateWindow(_T("SWindow"),
			  _T("test"),
			  WS_POPUP,
			  rect.left+x,
			  rect.top+y,
			  w,
			  h,
			  ::hWnd,
			  NULL,
			  hInstance,
			  this);
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
		}

		static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg,
			   WPARAM wParam, LPARAM lParam);

		LRESULT CALLBACK WndProc(UINT Msg,
			WPARAM wParam, LPARAM lParam)
		{
			switch (Msg)
			{
			case WM_CREATE:
				s = new WinSurface(w,h);

				break;
			case WM_PAINT:
				{
					HDC hdc;
					PAINTSTRUCT ps;
					hdc = BeginPaint(hWnd, &ps);							
					s->Paint(hdc);
					EndPaint(hWnd, &ps);
				}
				break;
			case WM_ERASEBKGND:
				break;
			}
			return 0;
		}


		~SWindow(void){}
	};
}
