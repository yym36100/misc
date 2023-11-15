#include "StdAfx.h"

#include "windowsx.h"

#include "SWindow.h"
#include "PopupMenu.h"
#include "WinSurface.h"
#include "DummyWidget.h"

namespace sg
{
	u16 SWindow::Cnt = 0;

	LRESULT CALLBACK SWindow::WndProcedure(HWND hWnd, UINT Msg,
		WPARAM wParam, LPARAM lParam)
	{
		SWindow *self = (SWindow*) GetWindowLongPtr(hWnd, GWL_USERDATA);
		switch(Msg)
		{
		case WM_NCCREATE:
			SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR) ((CREATESTRUCT*)lParam)->lpCreateParams);
			break;

		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			{
				sg::Events e;
				e.e=wParam==MK_LBUTTON?sg::Events::mpress:Msg==WM_LBUTTONUP?sg::Events::mrelease:sg::Events::mmove;
				e.x = GET_X_LPARAM(lParam);
				e.y = GET_Y_LPARAM(lParam);

				Widget *w = self->wg;
				u16 res=0;
				while(w)
				{
					if(res|=w->OnEvent(&e));//break;
					w=(Widget*)w->next;
				}			
				if(res!=0)
				{
					InvalidateRect(hWnd,NULL,FALSE);
				}
				if(res>1)
				{
					SendMessage(hWnd,WM_USER+1,res,0);
				}
			}
			break;
		case WM_USER+1:
			SendMessage(self->parent_hWnd,WM_USER+2,((sg::PopupMenu*)self)->code,wParam);
			DestroyWindow(hWnd);
			break;
		case WM_USER+2:
			{
				//slef->wg->name = 0;
				static wchar_t value[22];
				wsprintf(value,L"w=%d l=%d",wParam,lParam);
				((sg::DummyWidget*)self->wg)->name=(u16*)(value);
				self->wg->Draw();
				InvalidateRect(hWnd,NULL,FALSE);

			}
			break;

		case WM_USER:
		case WM_TIMER:
			{			
				if (self)
				{
					InvalidateRect(hWnd,NULL,FALSE);
					self->s->color=rand();
					self->s->FillRect(0,0,400,300);

					Widget *p = self->wg;
					while(p)
					{
						p->Draw();
						p=(Widget*)p->next;
					}					
				}				
				break;
			}

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc;
				hdc = BeginPaint(hWnd, &ps);				
				self->s->Paint(hdc);
				EndPaint(hWnd, &ps);
			}
			break;
		default:
			if(self)
				self->WndProc(Msg,wParam,lParam);
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	LRESULT CALLBACK SWindow::WndProc(UINT Msg,WPARAM wParam, LPARAM lParam)
	{
		switch(Msg)
		{

		case WM_DESTROY:						
			if(parent_hWnd==NULL)
				PostQuitMessage(0);// quit app if main window is closed (?!??)

			Cnt--;
			if(wg){
				//delete wg;
				//wg = NULL;
			}
			delete this;
			break;
		}
		return 0;
	}

	SWindow::SWindow(void)
	{
	}

	SWindow::~SWindow(void)
	{
		delete s;
		delete wg;
	}

	SWindow::SWindow(u16 x, u16 y, u16 w, u16 h, u32 style, HWND parent_hWnd, u16 *name)
		:x(x),y(y),w(w),h(h),style(style),parent_hWnd(parent_hWnd),wg(0)
	{
		HINSTANCE hInstance=GetModuleHandle(NULL);
		if(Cnt==0)
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
			//WndClsEx.hbrBackground = NULL;
			WndClsEx.lpszMenuName  = NULL;
			WndClsEx.lpszClassName = _T("SWindow");
			WndClsEx.hInstance     = hInstance;
			WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassEx(&WndClsEx);			
		}	


		s = new WinSurface(w,h);
		RECT r={0,0,w,h};
		AdjustWindowRect(&r,style,FALSE);
		hWnd = CreateWindow(_T("SWindow"),
			(LPCWSTR)name,
			style/*WS_POPUP*/,
			x,
			y,
			r.right-r.left,
			r.bottom-r.top,
			parent_hWnd,
			NULL,
			hInstance,
			this);

		
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
		Cnt++;
	}
}

