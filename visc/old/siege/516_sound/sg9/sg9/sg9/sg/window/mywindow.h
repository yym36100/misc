#pragma once
#include "window5.h"
#include "textwidget.h"
#include "GraphWidget.h"


namespace sg{

	class Cmywindow : public CWindow {
	public:
		wg::CWidget *w;
		Cmywindow(Rect r, u32 style,HWND parent_hWnd,u16 *name) :
		CWindow( r, style, parent_hWnd, name),w(0)
		{
			w=(new wg::CGraphWidget(surf,10,10,400,400, "Some boring text about graph widget"));			

			//end ctor
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
			SetTimer(hWnd,9000,0,0);
		}
		virtual void Paint(HDC dc) {			
			w->DrawAll();
			surf->Paint(dc);		
		}

		virtual LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam) {
			LRESULT res = 0;
			switch(Msg) {
				case WM_TIMER:
					((sg::wg::CGraphWidget*)w)->f1=3;
					((sg::wg::CGraphWidget*)w)->f2=3;
					((sg::wg::CGraphWidget*)w)->ph1+=0.1;
					//((sg::wg::CGraphWidget*)w)->ph2+=0.1;
					((sg::wg::CGraphWidget*)w)->o=0;
					((sg::wg::CGraphWidget*)w)->time+=0.51;
					InvalidateRect(hWnd,0,false);
					break;
				/* mouse events*/
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP: 
				{
					Events e;
					e.e=wParam==MK_LBUTTON?Events::mpress:Msg==WM_LBUTTONUP?Events::mrelease:Events::mmove;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);

					wg::CWidget *p = w;
					u16 res=0;
					while(p)
					{
						if(res|=p->OnEvent(&e))break;
						p = (wg::CWidget*)p->next;
					}	
					if(res == 2) SetCapture(hWnd);
					if(res == 3) ReleaseCapture();
					if(res!=0)
					{
						InvalidateRect(hWnd,0,0);
					}
				} break;
			}
			return 0;
		}

	};
};// sg
