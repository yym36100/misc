#pragma once

#include "cdef.h"

namespace siege{
	class CScreen
	{
	public:
		static CScreen *instance;
		uint8 *pBuffer;
		uint16 width, height;
		uint32 color;
		bool redraw;

		CScreen(void);
		explicit CScreen(uint16 width, uint16 height);
		virtual ~CScreen(void);

		virtual void SetPixel(int16 x, int16 y) const=0;
		virtual i16 GetPixel(i16 x, i16 y)const=0;
		virtual void vDrawLine(i16 x1,i16 y1,i16 x2,i16 y2)const=0;
		virtual void FillRect(int16 x, int16 y, uint16 w, uint16 h)const=0;
		virtual void FlodFill(i16 x, i16 y,i16 c)const=0;


		virtual void blit()=0;
		

	};


}
