#pragma once
#include "sbase.h"
#include "stypes.h"
#include "surface.h"
#include "events.h"
#include "widget.h"

namespace sg
{	
	class SWindow
	{
	public:
		u16 x,y,w,h;
		u32 style;
		HWND hWnd, parent_hWnd;
		static u16 Cnt;

		Surface *s;
		Events *e;
		Widget *wg;

		SWindow(void);
		SWindow(u16 x, u16 y, u16 w, u16 h, u32 style,HWND parent_hWnd,u16 *name);
		virtual ~SWindow(void);

		static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam);
	};
}
