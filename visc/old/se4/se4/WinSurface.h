#pragma once
#include "surface.h"

class CWinSurface :
	public CSurface
{
public:

	CWinSurface(void)
	{
	}

	CWinSurface(u16 w, u16 h)
		:CSurface(w,h)
	{
		ZeroMemory(&m_bi24BitInfo,sizeof(m_bi24BitInfo));
		m_bi24BitInfo.bmiHeader.biBitCount = 32; // rgb 8 bytes for each component(3)
		m_bi24BitInfo.bmiHeader.biCompression = BI_RGB;// rgb = 3 components
		m_bi24BitInfo.bmiHeader.biPlanes = 1;
		m_bi24BitInfo.bmiHeader.biSize = sizeof(m_bi24BitInfo.bmiHeader); // size of this struct
		m_bi24BitInfo.bmiHeader.biWidth = w; // width of window
		m_bi24BitInfo.bmiHeader.biHeight = -h; // height of window

		m_iDC = CreateCompatibleDC(0);
		void *p;
		HBITMAP iBitmap = CreateDIBSection(m_iDC, &m_bi24BitInfo, DIB_RGB_COLORS, &p, 0, 0); // create a dib section for the dc
		pData = (char*)p;
		width = w;
		height = h;

		u32 *p2=(u32*)pData;
		for(int i=0;i<w*h;i++)
		{
			*p2++=0x00;
		}
		SelectObject(m_iDC, iBitmap); // assign the dib section to the dc
	}

	~CWinSurface(void)
	{
	}

	BITMAPINFO m_bi24BitInfo;
	HDC m_iDC;

};
