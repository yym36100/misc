#pragma once

#include "cdef.h"
#include <windows.h>

#include "obj.h"
#include "surface.h"
#include "winsurface.h"
#include "Wave.h"


#include "resource.h"

namespace siege{

	class CWindow
	{
	public:
		CWinSurface *surf;
		u32 style;
		HWND hWnd,parent_hWnd;
		static u8 cnt;

		BITMAPINFO BitInfo;
		HDC hDC;
		HBITMAP hBitmap;

		u8 mode ;
		u8 pause;

		CWindow(void)
		{
		}

		CWindow(stRect r, u32 style,HWND parent_hWnd,u16 *name)
			:mode(1),pause(0)
		{
			surf = new CWinSurface(r.w,r.h);
			ATOM res;
			this->parent_hWnd = parent_hWnd;

			HINSTANCE hInstance=GetModuleHandle(NULL);
			if(cnt==0)
			{
				WNDCLASSEX	WndClsEx;
				WndClsEx.cbSize        = sizeof(WNDCLASSEX);
				WndClsEx.style         = 0;
				WndClsEx.lpfnWndProc   = WndProcedure;
				WndClsEx.cbClsExtra    = 0;
				WndClsEx.cbWndExtra    = 0;
				WndClsEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
				WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
				WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);				
				WndClsEx.lpszMenuName  = NULL;
				WndClsEx.lpszClassName = _T("siege");
				WndClsEx.hInstance     = hInstance;
				WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
				res = RegisterClassEx(&WndClsEx);			
			}	
			RECT rr={0,0,r.w,r.h};
			AdjustWindowRect(&rr,style,FALSE);
			hWnd = CreateWindow(_T("siege"),(LPCWSTR)name,	style,r.x,r.y,rr.right-rr.left,rr.bottom-rr.top,parent_hWnd,NULL,hInstance,this);

			/*err = GetLastError();
			LPVOID lpMsgBuf;
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, err,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,	0, NULL );*/

			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
			cnt++;
			SetTimer(hWnd,1982,20,0);

		}

		virtual ~CWindow(void)
		{
			cnt--;
		}

		static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		virtual LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam)
		{
			LRESULT res = 0;
			switch(Msg)
			{
			case WM_DESTROY:						
				if(parent_hWnd==NULL)
				{
					KillTimer(hWnd,1982);
					PostQuitMessage(0);				
				}
				delete this;
				break;
			case WM_TIMER:
				if(pause==0)
					InvalidateRect(hWnd,0,0);
				break;
			case WM_CHAR:
				InvalidateRect(hWnd,0,0);
				switch (wParam)
				{
				case '1':
					mode = 1;
					break;
				case '2':
					mode = 2;
					break;
				case '3':
					mode = 3;
					break;
				case 'p':
					pause^=1;
					break;
				}				
				break;
			}
			return res;
		}

		virtual WPARAM Run(void)
		{
			HACCEL hAccelTable;
			MSG msg;
			HINSTANCE hInstance=GetModuleHandle(NULL);
			hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIEGE6));

			while (GetMessage(&msg, NULL, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			return msg.wParam;
		}
		void Resize(u16 w, u16 h)
		{
			delete surf;
			surf = new CWinSurface(w,h);
			InvalidateRect(hWnd,0,0);
		}

		void Paint(HDC dc)
		{
			static double i=0;
			static int inc=0;
			static int nrp=48000;
			i+=0.01;//inc/100.0;
			if(i>=(nrp/15-100))
			{
				i=0;
				inc = 0;
			}
			if(inc<1000) 
			{

				inc++;
			}
			CWave *pw;
			pw = new CWave(surf,nrp,100,(CNCO::NR_SAMPLES*4*i/(double)nrp*65535),(CNCO::NR_SAMPLES*4/(double)1)*65535);
			//pw->pS = surf;

			switch(mode)
			{
			case 1:
				pw->Display();
				break;
			case 2:
				pw->Display2();
				break;
			case 3:
				pw->Display3();
				break;
			}

			surf->Paint(dc);
			delete pw;
			//todo
		}

	}; // end class

};