#pragma once
#include "cdef.h"
#include <windows.h>

#include "surface.h"

namespace siege{
	namespace graphics{
		class CWinSurface : public CSurface
		{
		public:

			BITMAPINFO BitInfo;
			HDC hDC;
			HBITMAP hBitmap;


			CWinSurface(void)
			{
			}

			CWinSurface(u16 w, u16 h)
			{
				maxweight = 0;
				this->w = w; 
				this->h = h;
				ZeroMemory(&BitInfo,sizeof(BitInfo));
				BitInfo.bmiHeader.biBitCount = 32;			// rgb 8 bytes for each component(3)
				BitInfo.bmiHeader.biCompression = BI_RGB;	// rgb = 3 components
				BitInfo.bmiHeader.biPlanes = 1;
				BitInfo.bmiHeader.biSize = sizeof(BitInfo.bmiHeader); // size of this struct
				BitInfo.bmiHeader.biWidth = w;		// width of window
				BitInfo.bmiHeader.biHeight = -h;	// height of window

				hDC = CreateCompatibleDC(0);
				void *p;
				hBitmap = CreateDIBSection(hDC, &BitInfo, DIB_RGB_COLORS, &p, 0, 0); // create a dib section for the dc
				pData = (u32*)p;

				u32 *p2=(u32*)pData;
				for(int i=0;i<w*h;i++)
				{
					//*p2++=0xff202020;
					//*p2++=0xff0000ff;//blue
					//*p2++=0xff00ff00;//green
					//*p2++=0xffff0000;//red
					//*p2++=0xffd0d0d0;
					*p2++=0xffffffff;
					//*p2++=0xff000000;
				}
				SelectObject(hDC, hBitmap); // assign the dib section to the dc


				TextOut(hDC,0,0,L"alma",4);
				//TextOut(hDC,w-30,h-30,L"alma",4);

			}

			void Paint(HDC hdc)
			{						
				BitBlt(hdc, 0, 0, w, h, hDC, 0, 0, SRCCOPY); // copy hdc to their hdc	
			}

			~CWinSurface(void)
			{
				DeleteObject(hBitmap);
				DeleteDC(hDC);
				pData = NULL;
			}
		};

	};
}