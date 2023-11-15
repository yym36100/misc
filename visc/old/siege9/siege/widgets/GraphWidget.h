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
			void *pData;
			u32 size;
			u8 step;
			u8 mode;
			u32 gridcolor,plotcolor,centercolor,bordercolor;
			graphics::CSurface *surf;


			CGraphWidget(graphics::CSurface *ss, u16 x, u16 y, u16 w, u16 h, u8 m = 0):
			CWidget(x,y,w,h),
				rect(x,y,w,h),
				surf(ss),//,Highlighted(false),Focused(false),command(ccc) 
				mode(m)
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
					switch(mode)
					{
					case 0 :
						{
							u16* pd = (u16*)pData;
							u16 len = rect.w>size? size:rect.w;
							i16 val,val2;

							u16 i=0;
							val = pd[i];
							val = val>rect.h/2-1?rect.h/2-1:val;
							val = val<-rect.h/2+1?-rect.h/2+1:val;
							for(i=1;i<len-1;i++)
							{
								val2 = pd[i+1];
								val2 = val2>rect.h/2-1?rect.h/2-1:val2;
								val2 = val2<-rect.h/2+1?-rect.h/2+1:val2;						
								surf->DrawLine(rect.x+i,rect.y+rect.h/2+val,rect.x+i+1,rect.y+rect.h/2+val2,plotcolor);
								val = val2;
							}					
							break;
						}
						case 1 :
						{
							float* pd = (float*)pData;
							u16 len = rect.w>size? size:rect.w;
							i16 val,val2;

							u16 i=0;
							val = pd[i];
							val = val>rect.h/2-1?rect.h/2-1:val;
							val = val<-rect.h/2+1?-rect.h/2+1:val;
							for(i=1;i<len-1;i++)
							{
								val2 = pd[i+1];
								val2 = val2>rect.h/2-1?rect.h/2-1:val2;
								val2 = val2<-rect.h/2+1?-rect.h/2+1:val2;						
								surf->DrawLine(rect.x+i,rect.y+rect.h/2+val,rect.x+i+1,rect.y+rect.h/2+val2,plotcolor);
								val = val2;
							}					
							break;
						}

					}
				}

				//draw frame
				surf->DrawRect(rect,bordercolor);
			}
		};
	};
};