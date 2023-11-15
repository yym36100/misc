#ifndef __bitmap_h__ 
#define __bitmap_h__

#include "cdef.h"

namespace Se{

	union color{
		enum {r,g,b,a};
		u8 rgba[4];
		u32 c;
	};

	class Bitmap{
	public:
		enum ver {v1};
		enum type {RGBA8888,RGB888,kRGBA888,rRGBA8888,rRGB888};		

		ver v;
		type t;
		u16 w,h;
		u32 size;
		u8 ckey[3];
		u8 misc[2];
		u8 *p;

		Bitmap(u16 ww, u16 hh, type tt)
			:w(ww),h(hh),t(tt)
		{			
			size = w*h*gets();
			p = new u8[size];
		}

		virtual ~Bitmap()
		{
			if(p) delete[] p;
			p = 0;
		}

		void SetPixel(u16 x, u16 y, color c) 
		{
			if(t != rRGBA8888 && t!=rRGB888)
			{
				if(x<w && y < h)
				{				
					u8 *pp = p + (y*w+x)*gets();
					*pp++=c.rgba[c.r]; *pp++=c.rgba[c.g]; *pp++=c.rgba[c.b]; *pp++=c.rgba[c.a];
				}
			}			
		}

		color GetPixel(u16 x, u16 y) const
		{
			if(t != rRGBA8888 && t!=rRGB888)
			{
				if(x<w && y < h)
				{
					color c;
					u8 *pp = p + (y*w+x)*gets();					
					c.rgba[c.r] = *pp++; c.rgba[c.g] = *pp++; c.rgba[c.b] = *pp++; c.rgba[c.a] = *pp++;
					return c;
				}
			}			
		}

		void Convert(type tt)
		{
			if(t==tt)return;
			switch(tt)
			{
			case RGB888:
				u8 *buff = new u8[w*h*3];
				u8 *pp=buff;
				for(u16 y=0;y<h;y++)
				{
					for(u16 x=0;x<w;x++)
					{
						color c = GetPixel(x,y);
						if(c.rgba[c.a]==0)
						{
							c.rgba[c.r] = 0;
							c.rgba[c.g] = 0;
							c.rgba[c.a] = 0;
						}
						*pp++=c.rgba[c.r];*pp++=c.rgba[c.g];*pp++=c.rgba[c.b];						
					}
				}
				size = w*h*3;
				delete [] p;
				p = buff;
				break;
			}
		}

	private:
		u8 gets(void) const
		{
			u8 s;
			if (t==RGBA8888 || t == rRGBA8888) s = 4; else s = 3;
			return s;
		}
	};

};

#endif //__bitmap_h__