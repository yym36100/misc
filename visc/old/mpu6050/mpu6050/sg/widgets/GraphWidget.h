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
			bool updatedata;
			//			Events lastevent;

			CGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, u16 len = 1024,char *t=0,u32 c = white1):
			CWidget(ss,x,y,w,h),bgc(c),title(t),updatedata(false)
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
				for(int i=0;i<siglen-1;i++)
				{
					hsig[i] = hsig[i]<sig[i]?sig[i]:hsig[i];
					//sig[i] = 20;
					Rect r;
					r.x = 1+i/ss;
					r.y = -1+grect.h -(u16)sig[i]; 
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
				for(int i=0;i<siglen-1;i++)
				{
					//hsig[i] = hsih[i]<sig[i]?sig[i]:hsig[i];
					//sig[i] = 20;aa
					if(updatedata) {
						hsig[i]= hsig[i]>0?hsig[i]-0.5:0;
						if(hsig[i]<0)hsig[i] = 0;
					}
					Rect r;
					r.x = 1+i/ss;
					r.y = -1+grect.h -(u16)hsig[i]; 
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
					sprintf(buf,"(%6.2f kHz)", val);
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
					//PPrint(buffer, (float)(lastevent.x - rect.x)*j);

					s->color = 0xffff9a9a;
					s->pattern = 0xffff8080;
					s->DrawVLineP(lastevent.x-rect.x,0,grect.h);
					s->DrawHLineP(0,grect.w,lastevent.y-rect.y);

					sf->Color = 0xff808080;
					//sf->DrawTB(lastevent.x+4-rect.x, lastevent.y+4-rect.y,(u8*)buffer);
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
				updatedata = false;
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

		class CMultiAutoscaleGraphWidget : public CGraphWidget{
		public:

			u8 nosignals;
			u16 buffsize;
			double *sig;
			double mmin,mmax, abs_max;
			u16 iw;
			bool full;
			u16 *lastvals;

			void allocate_buffers(u8 nsig, u16 size=0)
			{
				full = 0;
				if(size==0) size = grect.w-2;
				buffsize = size;
				nosignals = nsig;
				sig = new double[size*nsig];
				lastvals = new u16[nsig*2];//xy
			}

			void add_signals(double *s){
				for(u8 i = 0;i<nosignals;i++)
				{
					if(iw == buffsize*nosignals) 
					{
						iw = 0;
						full = 1;
					}
					sig[iw++] = s[i];
				}
				getminmax();
			}

			void getminmax(void)
			{
				double M=-100000, mm = +100000;
				u16 sig_l = full?buffsize*nosignals:iw;
				for(int i=1;i<sig_l;i+=1)
				{					
						if(sig[i] < mm ) mm = sig[i];
						if(sig[i] > M ) M = sig[i];
				}
				abs_max = M;
				mmin = mm;
				mmax = M;
				if((-mm) > abs_max) abs_max = -mm;
			}


			/*u8 nosignals;
			u16 buffsize;
			double *sig;
			double min,max;
			u16 iw;
			bool full;*/

			CMultiAutoscaleGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, u16 len = 1024,char *t=0,u32 c = white1):
			CGraphWidget(ss,x,y,w,h,len,t,c),
				nosignals(0),buffsize(0),sig(NULL),mmin(0),mmax(0),iw(0),full(0)  {	
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
			virtual void Draw(void){
				static char buffer[50];
				CWidget::Draw();
				s->color = bgc;				
				s->FillRect(grect);
				s->color = 0xffa0a0a0;
				s->DrawRRect(grect);

				DrawGrid();
				DrawSignal();				

				// draw title
				sf->Color = black;
				sf->bgc = bgc;
				sprintf(buffer,"min = %3.2f, max = %3.2f",mmin,mmax);
				//sf->DrawTB(6,6,(u8*)buffer);
				sf->s->color = black;
				sf->DrawT(6,6,(u8*)buffer);

				DrawCursor();
				updatedata = false;
			}

			void DrawSignal(void) {
				s->lp.x = 1;
				s->lp.y = grect.h/2+sig[0];
				s->color = blue;
				double ss = siglen/(double)grect.w;
				double scale = (grect.h/2-1)/abs_max;
				u16 sig_l = full?buffsize: iw/nosignals;
				i16 ypos;
				u16 idx;
				if(full) idx = iw+nosignals;
				else idx = 0;

				for(u16 j=0;j<nosignals;j++){
					lastvals[j*2] = 1;
					lastvals[j*2+1] = grect.h/2;
				}

				for(int i=1;i<sig_l;i+=1)
				{
					for(u16 j=0;j<nosignals;j++){
												
						ypos = (i16)sig[idx+j];		
						ypos*=scale;

						if(ypos>=(grect.h/2-1)) ypos = grect.h/2-1;
						if(ypos<=-(grect.h/2-1)) ypos = -(grect.h/2-1);
						switch(j)
						{
						case 0:s->color = green; break;
						case 1:s->color = blue; break;
						case 2:s->color = red; break;
						case 3:s->color = green2; break;
						case 4:s->color = black; break;
						}

					s->lp.x = lastvals[j*2];
					s->lp.y = lastvals[j*2+1];

					s->DrawTo(1+i,ypos+grect.h/2);

					lastvals[j*2] = 1+i;
					lastvals[j*2+1] = ypos+grect.h/2;
					}
					idx+=nosignals;
					if(idx>=buffsize*nosignals) 
						idx = 0;
				}
			}

		};



	};// wg
};// sg
