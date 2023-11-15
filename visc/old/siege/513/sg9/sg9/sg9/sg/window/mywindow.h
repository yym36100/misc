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
			w=(new wg::CGraphWidget(surf,10,10,800-20,200, "Some boring text about graph widget"));			

			//end ctor
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
		}
		virtual void Paint(HDC dc) {			
			w->DrawAll();
			surf->Paint(dc);		
		}


	};
};// sg
