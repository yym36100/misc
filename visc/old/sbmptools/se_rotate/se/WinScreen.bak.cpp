#include "StdAfx.h"
#include "WinScreen.h"
#include "SiegeWnd.h"

namespace siege{
	CWinScreen::CWinScreen(void)
	{
	}

	CWinScreen::CWinScreen(uint16 w, uint16 h)
	{
		pWnd = new CSiegeWnd();
		if(pWnd)
		{
			width = w;
			height = h;
			CString strMyClass;
			strMyClass = AfxRegisterWndClass(
				CS_VREDRAW | CS_HREDRAW,
				::LoadCursor(NULL, IDC_ARROW),
				(HBRUSH) ::GetStockObject(WHITE_BRUSH),
				::LoadIcon(NULL, IDI_APPLICATION)); 

			RECT r = {0,0,width,height};

			// adjusts window rect so the client area has the desired size
			::AdjustWindowRectEx(&r,WS_CAPTION,FALSE,0); 
			CRect rr = r;
			rr.MoveToXY(100,100);

			// create backbuffer
			pWnd->m_bi24BitInfo.bmiHeader.biBitCount = 16; // rgb 8 bytes for each component(3)
			pWnd->m_bi24BitInfo.bmiHeader.biCompression = BI_RGB;// rgb = 3 components
			pWnd->m_bi24BitInfo.bmiHeader.biPlanes = 1;
			pWnd->m_bi24BitInfo.bmiHeader.biSize = sizeof(pWnd->m_bi24BitInfo.bmiHeader); // size of this struct
			pWnd->m_bi24BitInfo.bmiHeader.biWidth = w; // width of window
			pWnd->m_bi24BitInfo.bmiHeader.biHeight = -h; // height of window

			pBuffer = new uint8[pWnd->m_bi24BitInfo.bmiHeader.biWidth * -pWnd->m_bi24BitInfo.bmiHeader.biHeight * 2]; // create enough room. all pixels * each color component

			pWnd->m_iDC = CreateCompatibleDC(0); // create dc to store the image
			HBITMAP iBitmap = CreateDIBSection(pWnd->m_iDC, &(pWnd->m_bi24BitInfo), DIB_RGB_COLORS, 0, 0, 0); // create a dib section for the dc
			SelectObject(pWnd->m_iDC, iBitmap); // assign the dib section to the dc

				memset(pBuffer,0x00,h*w*2);

			pWnd->CreateEx(0,strMyClass,L"Test",WS_CAPTION,rr,NULL,0,0);
			pWnd->ShowWindow(1);
			pWnd->UpdateWindow();

			SetDIBitsToDevice(pWnd->m_iDC,
				0, 0, pWnd->m_bi24BitInfo.bmiHeader.biWidth, pWnd->m_bi24BitInfo.bmiHeader.biHeight,
				0, 0, 0, pWnd->m_bi24BitInfo.bmiHeader.biHeight, pBuffer, &(pWnd->m_bi24BitInfo), DIB_RGB_COLORS); // set the new dibs to the dc

			pWnd->Invalidate(false);
		}
	}

	CWinScreen::~CWinScreen(void)
	{
	}

}
