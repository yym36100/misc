#pragma once
#include "cdef.h"
#include "siegecfg.h"
#include "siegetypes.h"

#include "Widget.h"
#include "Screen.h"
#include "math.h"

namespace siege
{
	class SBWidget : public CWidget
	{
	public:
		bool loaded;
		u8 *buff;
		double angle;

		SBWidget(i16 x,i16 y,u16 w,u16 h, u8 *name)
			:CWidget(x,y,w,h),loaded(false),buff(NULL)
		{
			FILE *f;
			f = fopen((char*)name,"rb");
			if(!f) return;
			buff = new u8[w*h*4];
			fread(buff,w*h*4,1,f);
			fclose(f);
		}

		virtual ~SBWidget(void)
		{
			if(buff) 
			{
				delete buff;
				buff = NULL;
			}
		}
		u32 GetPixel(u16 x, u16 y)
		{
			u32 ccc;
			if(x>this->r.width()) return 0;
			if(y>this->r.height()) return 0;
			u8 r,g,b;
			u8*p = buff;
			p+=(y*this->r.width()+x)*4;
			
			r = *p++;g =*p++;b = *p++; p++;			
			ccc=((r)<<16)|((g)<<8)|(b);
			return ccc;
		}

		virtual uint16 Draw()
		{
			//uint8 *p = CScreen::instance->pBuffer;
			if(redraw && buff)
			{

				//rotate
				//int angle=45;        //45° for example 
				//Convert degrees to radians 
				double radians=(2*3.1416*angle)/360; 

				double cosine=(double)cos(radians); 
				double sine=(double)sin(radians); 

				double Point1x=(-this->r.height()*sine); 
				double Point1y=(this->r.height()*cosine); 
				double Point2x=(this->r.width()*cosine-this->r.height()*sine); 
				double Point2y=(this->r.height()*cosine+this->r.width()*sine); 
				double Point3x=(this->r.width()*cosine); 
				double Point3y=(this->r.width()*sine); 

				double minx=min(0,min(Point1x,min(Point2x,Point3x))); 
				double miny=min(0,min(Point1y,min(Point2y,Point3y))); 
				double maxx=max(0,max(Point1x,max(Point2x,Point3x))); 
				double maxy=max(0,max(Point1y,max(Point2y,Point3y))); 

				int DestBitmapWidth=(int)ceil(maxx-minx); 
				int DestBitmapHeight=(int)ceil(maxy-miny); 

				CScreen *s = CScreen::instance;

				
				for(int x=0;x<DestBitmapWidth;x++) 
				{ 
					int y=0;
					

					for(y=0;y<DestBitmapHeight;y++) 
					{ 						
						int SrcBitmapx=(int)((x+minx)*cosine+(y+miny)*sine); 
					int SrcBitmapy=(int)((y+miny)*cosine-(x+minx)*sine); 
						if(SrcBitmapx>=0&&SrcBitmapx<this->r.width()&&SrcBitmapy>=0&& 
							SrcBitmapy<this->r.height()) 
						{ 
							s->color= GetPixel(SrcBitmapx,SrcBitmapy);
							s->SetPixel(x,y);
						} 						
					} 
				} 

				/*double cosT,sinT;
				cosT = cosine;
				sinT = sine;
				i16 xp,yp;
				i16 x1p=0,y1p=0;
				i16 x1=0,y1=0;
				for (u16 y = 0; y <= DestBitmapHeight; y++)
				{ 
					xp = (minx-x1) * cosT + (y-y1) * sinT + x1p;
					yp = (y-y1) * cosT - (minx-x1) * sinT + y1p;

					for (u16 x = 0; x <= DestBitmapWidth; x++)
					{ 
						if (xp>=0&&xp<this->r.width()&&yp>=0&& 
							yp<this->r.height())
						{
							s->color= GetPixel(xp,yp);
							s->SetPixel(x,y);
						}
						xp += cosT;
						yp -= sinT;
					}
				}*/




//				CScreen *s = CScreen::instance;
				//siege_dbg(L"widget draw\n");
				//u8 *p = buff;
				//u8 r,g,b;
				//for(u16 y=0;y<this->r.height();y++)
				//	for(u16 x=0;x<this->r.width();x++)
				//	{
				//		//r = *p++;g =*p++;b = *p++;
				//		//s->color=((r&0x1f)<<11)+((g&0x3f)<<5)+(b&0x1f);
				//		//s->color=((r>>3)<<11)+((g>>2)<<5)+(b>>3);
				//		//s->color = (0xff)&0x3f;
				//		s->color= GetPixel(x,y);
				//		s->SetPixel(x,y);
				//	}				
				redraw = false; //todo move this to a common location
				return 1;
			}
			return 0;
		}
	};
}