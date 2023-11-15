#pragma once
#include "stypes.h"
#include "surface.h"
#include "sbase.h"


namespace sg
{
	class WinSurface :
		public Surface
	{
	public:
		BITMAPINFO BitInfo;
		HDC hDC;

		WinSurface(u16 w, u16 h)
			:Surface(w,h)
		{
			ZeroMemory(&BitInfo,sizeof(BitInfo));
			BitInfo.bmiHeader.biBitCount = 32;			// rgb 8 bytes for each component(3)
			BitInfo.bmiHeader.biCompression = BI_RGB;	// rgb = 3 components
			BitInfo.bmiHeader.biPlanes = 1;
			BitInfo.bmiHeader.biSize = sizeof(BitInfo.bmiHeader); // size of this struct
			BitInfo.bmiHeader.biWidth = w;		// width of window
			BitInfo.bmiHeader.biHeight = -h;	// height of window

			hDC = CreateCompatibleDC(0);
			void *p;
			HBITMAP hBitmap = CreateDIBSection(hDC, &BitInfo, DIB_RGB_COLORS, &p, 0, 0); // create a dib section for the dc
			pData = (u8*)p;

			u32 *p2=(u32*)pData;
			for(int i=0;i<w*h;i++)
			{
				*p2++=gray;
			}
			SelectObject(hDC, hBitmap); // assign the dib section to the dc
		}
		virtual void Paint(HDC hdc)
		{
			BitBlt(hdc, 0, 0, w, h, hDC, 0, 0, SRCCOPY); // copy hdc to their hdc
		}
	
		

		~WinSurface(void)
		{
		}
	};
}