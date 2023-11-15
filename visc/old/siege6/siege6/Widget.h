#pragma once
#include "cdef.h"

#include "surface.h"

namespace siege{

	
	class CWidget :
		public CObj
	{
	public:
		stRect rect;
		u32 *pData;

		CWidget(void):pData(NULL)
		{
		}

		~CWidget(void)
		{
			if(pData) delete[] pData;
		}

		void Create(u16 w, u16 h)
		{
			if(pData) return;

			rect.w = w;
			rect.h = h;
			pData = new[] u32[w*h*4];
		}

		void SetPixel(u16 x, u16 y)
		{
		}

	};
};