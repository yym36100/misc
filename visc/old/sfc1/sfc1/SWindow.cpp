#include "stdafx.h"
#include "SWindow.h"

namespace sg
{
	bool SWindow::init = false;
	LRESULT CALLBACK SWindow::WndProcedure(HWND hWnd, UINT Msg,
		WPARAM wParam, LPARAM lParam)
	{
		SWindow *self = (SWindow*) GetWindowLongPtr(hWnd, GWL_USERDATA);
		switch(Msg)
		{
		case WM_NCCREATE:
			SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR) ((CREATESTRUCT*)lParam)->lpCreateParams);
			break;
		default:
			if(self)
				self->WndProc(Msg,wParam,lParam);
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
}