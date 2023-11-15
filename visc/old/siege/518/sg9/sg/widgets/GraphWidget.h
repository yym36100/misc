#pragma once
#include <math.h>

#include "Widget.h"
#include "simplefont.h"
#include "Surface.h"
#include "stdio.h"


namespace sg
{
	namespace wg
	{

		class CGraphWidget : public CWidget {
		private:
			typedef CWidget super;
			
		public:
			enum {normal, filled};
			u8 style;
			int siglen;
			u32 gridcolor, centercolor,bgc;
			res::CSimpleFont *sf;
			char *title;
			double *sig;
			double *hsig;
			Events lastevent;

			CGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, u16 len = 1024,char *t=0,u32 c = white1):
			CWidget(ss,x,y,w,h),bgc(c),title(t)
			{	
				style = normal;
				siglen = len;
				gridcolor = 0xffd0d0d0;
				centercolor= 0xffa0a0a0;
				sf = new res::CSimpleFont(ss,0xffffffff);	

				//gen test signal
				sig = new double[siglen];
				hsig = new double[siglen];
				for(int i=0;i<siglen;i++) {
					sig[i] = 0;//+ 100 * sin( 2*3.14159265 *10.3 * i / siglen + 2*3.14159265*45/360);				
					hsig[i] = 0;
				}
			}

			virtual ~CGraphWidget(void)	{}
		
			void DrawSignal(void) {		
				switch(style) {
					case normal:
						DrawSignal_11();				
						break;
					case filled:
						DrawSignal_fil_h();
						DrawSignal_fil();	
						//DrawSignal_11();		
						break;
				}
				
			}

			void DrawSignal_11(void) {
				s->lp.x = 1;
				s->lp.y = grect.h/2+sig[0];
				s->color = green;
				double ss = siglen/(double)grect.w;
				for(int i=1;i<siglen;i++)
				{
					s->DrawTo(1+i/ss,(u16)sig[i]+grect.h/2);
				}
			}

			void DrawSignal_fil(void) {
				s->lp.x = 1;
				s->lp.y = grect.h/2+sig[0];
				s->color = green;
				double ss = siglen/(double)grect.w;
				for(int i=1;i<siglen;i++)
				{
					hsig[i] = hsig[i]<sig[i]?sig[i]:hsig[i];
					//sig[i] = 20;
					Rect r;
					r.x = 1+i/ss;
					r.y = grect.h-(u16)sig[i]; 
					r.w = 1.0/ss;
					r.h = (u16)sig[i];		 	
					s->FillRect(r);					
				}
			}

			void DrawSignal_fil_h(void) {
				s->lp.x = 1;
				s->lp.y = grect.h/2+hsig[0];
				s->color = white5;
				double ss = siglen/(double)grect.w;
				for(int i=1;i<siglen;i++)
				{
					//hsig[i] = hsih[i]<sig[i]?sig[i]:hsig[i];
					//sig[i] = 20;
					hsig[i]= hsig[i]>0?hsig[i]-0.5:0;
					if(hsig[i]<0)hsig[i] = 0;
					Rect r;
					r.x = 1+i/ss;
					r.y = grect.h-(u16)hsig[i]; 
					r.w = 1.0/ss;
					r.h = (u16)hsig[i];		 	
					s->FillRect(r);					
				}
			}

			void DrawGrid(void) const {				

				u16 ystep =40;
				u16 xstep =40;			
				u16 my = grect.h/2;
				u16 mx = grect.w/2;

				s->color = gridcolor;
				s->pattern = 0x33333333;

				for(u16 y=ystep;y<grect.h/2;y+=ystep) {					
					s->DrawHLineP(1,grect.w-2,my+y);					
					s->DrawHLineP( 1,grect.w-2,my-y);
				}

				for(u16 x=xstep;x<grect.w/2;x+=xstep) {					
					s->DrawVLineP( mx+x,1,grect.h-2);
					s->DrawVLineP(mx-x,1,grect.h-2);
				}

				s->color = centercolor;
				s->pattern = 0x55555555;

				s->DrawHLineP(0, grect.w-1,my);
				s->DrawVLineP(mx,0,grect.h-1);
			}
			void PPrint(char *buf, float val) {
				if(val<1000){
				sprintf(buf,"(%6.0f Hz)", val);
				} else
				{
					val/=1000;
					sprintf(buf,"(%6.2f k)", val);
				}

			}

			void DrawCursor(void) 
			{
				if(Highlighted)				
				{
					char buffer[220];
					float j = 44100/2/(float)grect.w;
					
					float yy = (lastevent.y-grect.y);
					//sprintf(buffer,"(%6.2f,%6.2f)", (float)(lastevent.x - rect.x)*j,yy);
					PPrint(buffer, (float)(lastevent.x - rect.x)*j);

					s->color = 0xffff;
					s->pattern = 0xffff8080;
					s->DrawVLineP(lastevent.x-rect.x,0,grect.h);
					s->DrawHLineP(0,grect.w,lastevent.y-rect.y);

					sf->Color = 0xff808080;
					sf->DrawTB(lastevent.x+4-rect.x, lastevent.y+4-rect.y,(u8*)buffer);
				}			
			}

			virtual void Draw(void){
				super::Draw();
				s->color = bgc;				
				s->FillRect(grect);
				s->color = 0xffa0a0a0;
				s->DrawRRect(grect);

				DrawGrid();
				DrawSignal();				

				sf->Color = black;
				sf->bgc = bgc;
				sf->DrawTB(6,6,(u8*)title);
				DrawCursor();
			}
			
			virtual u16 OnEvent(Events *e)
			{
				lastevent = *e;
				if(HitTest(e))
				{
					if(!Highlighted)
						ShowCursor (FALSE);
					Highlighted = true;
					switch(e->e)
					{
					case Events::mmove:
						break;
					case Events::mpress:
						return 1;
						break;
					}	
					return 1;
				}
				else
				{
					if(Highlighted)
						ShowCursor (TRUE);
					Highlighted = false;
				}
				return 0;
			}
		};


	};// wg
};// sg
