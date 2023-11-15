#pragma once
#include "Widget.h"
#include "..\Events.h"
#include "..\Surface.h"

namespace siege
{
	namespace widgets
	{
		class CGraphWidget :
			public CWidget
		{					
		public:						
			stRect rect;		
			i16 *pData;
			u32 size;
			u8 step;
			u32 gridcolor,plotcolor,centercolor,bordercolor;
			graphics::CSurface *surf;


			CGraphWidget(graphics::CSurface *ss, u16 x, u16 y, u16 w, u16 h):
			CWidget(x,y,w,h),
				rect(x,y,w,h),
				surf(ss)//,Highlighted(false),Focused(false),command(ccc) 
			{
				step=20;
				gridcolor = 0xff404040;
				centercolor = 0xff808080;
				plotcolor = 0xffff0000;
				bordercolor = 0xff606060;
				pData = NULL;
				size = 0;
			}
			virtual ~CGraphWidget(void){}
			virtual void Draw(void)const
			{
				//clear
				surf->FillRect(rect,0xff000000);

				//draw grid
				for(u16 xx=0;xx<rect.w;xx+=step)
				{
					surf->DrawVLine(rect.x+xx,rect.y,rect.y+rect.h,gridcolor);
				}
				for(u16 yy=0;yy<rect.h;yy+=step)
				{
					surf->DrawHLine(rect.x,rect.x+rect.w,rect.y+yy,gridcolor);						 
				}
				//draw centerline
				surf->DrawVLine(rect.x+rect.w/2,rect.y,rect.y+rect.h,centercolor);
				surf->DrawHLine(rect.x,rect.x+rect.w,rect.y+rect.h/2,centercolor);						


				//draw signal
				if(pData)
				{
					u16 len = rect.w>size? size:rect.w;
					i16 val,val2;

					u16 i=0;
					val = pData[i];
					val = val>rect.h/2-1?rect.h/2-1:val;
					val = val<-rect.h/2+1?-rect.h/2+1:val;
					for(i=1;i<len-1;i++)
					{
						val2 = pData[i+1];
						val2 = val2>rect.h/2-1?rect.h/2-1:val2;
						val2 = val2<-rect.h/2+1?-rect.h/2+1:val2;						
						surf->DrawLine(rect.x+i,rect.y+rect.h/2+val,rect.x+i+1,rect.y+rect.h/2+val2,plotcolor);
//
				/*		void DrawWuLine (u16 X0, u16 Y0, u16 X1, u16 Y1,
				u16 BaseColor, u8 NumLevels, u8 IntensityBits,u32 color)*/
				//		surf->DrawWuLine(rect.x+i,rect.y+rect.h/2+val,rect.x+i+1,rect.y+rect.h/2+val2,							0xffff,256,8,plotcolor);

						val = val2;
					}
				}

				//draw frame
				surf->DrawRect(rect,bordercolor);
			}
		};
	};
};