#pragma once
#include "sbase.h"
#include "stypes.h"

#include "simplefont.h"

#define rgba32(r,g,b,a) ((a<<24)|(r<<16)|(b<<8)|(g))
#define gray rgba32(128,128,128,255)
#define white rgba32(255,255,255,255)

#define red rgba32(255,0,0,255)
#define green rgba32(0,255,0,255)
#define blue rgba32(0,0,255,255)

namespace sg
{
	class SimpleFont;
	class Surface :
		public Base
	{
	public:
		u16 w,h;
		u8 *pData;
		u32 color;
		SimpleFont *f;

		Surface(u16 w, u16 h)
			:w(w),h(h)
		{
			f= new SimpleFont(this);
		}
		virtual void Paint(HDC hdc)=0;
		virtual void Clear()
		{
			u32 *p=(u32*)pData;
			for(int i=0;i<w*h;i++)
			{
				*p++=rgba32(0,0,0,255);
			}
		}

		~Surface(void)
		{
		}

		void SetPixel(u16 x, u16 y) const
		{
			u32 *p = (u32*)pData;
			*(p+y*w+x) = color;
		}

		void FillRect(i16 x, i16 y, u16 w, u16 h)
		{
			x=x<0?0:x;
			y=y<0?0:y;
			w=x+w<this->w?w:this->w-x;
			h=y+h<this->h?h:this->h-y;
			for(u16 i=y;i<y+h;i++)
				for(u16 j=x;j<x+w;j++)
					SetPixel(j,i);

		}
	};
}
