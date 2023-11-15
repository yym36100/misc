#pragma once
#include "Bitmap2.h"
#include ".\resources\gimphead.h"
#include "..\Surface.h"

namespace siege{
	namespace graphics{

		class CGmpBitmap :
			public siege::graphics::CBitmap
		{
		public:
			gimphead const *h;
			bool blend;

			CGmpBitmap(void){}
			CGmpBitmap(CSurface *ss,gimphead const *hh,bool bb=false):h(hh),blend(bb){s=ss;}
			void Draw(u16 x, u16 y)const
			{
				u32 color;
				u8 r,g,b,a;

				if(!h)return;

				u8 *p = h->pixel_data;

				if(h->bytes_per_pixel ==4)
				{
					for(u16 yy = 0; yy < h->height ; yy++)
						for(u16 xx = 0; xx < h->width ; xx++)
						{					
							r= *p++;
							b= *p++;
							g= *p++;
							a= *p++;
							color = rgba32(r,g,b,0xff);
							if(blend)
							{
								if(a!=0)
								{
									if(a==0xff)
									{
										s->SetPixel(xx+x,yy+y,color);
									}
									else
									{
										//do blending
										u32 dcolor = s->GetPixel(xx+x,yy+y);
										u8 dr,dg,db;

										dr = (u8)(dcolor>>16);
										dg = (u8)(dcolor>>8);
										db = (u8)(dcolor);
										u8 tr,tg,tb;

										tr = (u8)(((u32)r * a + (u32)dr*(256-a))/256);
										tg = (u8)(((u32)g * a + (u32)dg*(256-a))/256);
										tb = (u8)(((u32)b * a + (u32)db*(256-a))/256);
										color =  rgba32(tr,tg,tb,0xff);
										s->SetPixel(xx+x,yy+y,color);								
									}
								}
							}
							else if(a!=0)
							{
								s->SetPixel(xx+x,yy+y,color);
							}

						}
				}
				else if(h->bytes_per_pixel ==3)
				{
					for(u16 yy = 0; yy < h->height ; yy++)
						for(u16 xx = 0; xx < h->width ; xx++)
						{					
							r= *p++;
							b= *p++;
							g= *p++;					
							color = rgba32(r,g,b,0xff);
							s->SetPixel(xx+x,yy+y,color);
						}
				}
			}

			virtual ~CGmpBitmap(void)
			{
			}
		};

	}
}
