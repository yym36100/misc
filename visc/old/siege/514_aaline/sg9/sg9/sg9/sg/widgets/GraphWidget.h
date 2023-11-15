#pragma once
#include <math.h>
#include <stdio.h>

#include "Widget.h"
#include "simplefont.h"
#include "Surface.h"


namespace sg
{
	namespace wg
	{

		class CGraphWidget : public CWidget {
		private:
			typedef CWidget super;		
		public:
			//enum {xstep = 40.0, ystep = 40.0};
			enum{hsize = 10, nrpoints = 2};
			
			const double xstep, ystep;
			struct dpoint{
				double x,y;
			};
			dpoint points[nrpoints];
			u8 sel;
			bool locked;


			u32 gridcolor, centercolor,bgc;
			res::CSimpleFont *sf;
			char *title;


			CGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, char *t=0,u32 c = white1):
			CWidget(ss,x,y,w,h),bgc(c),title(t),xstep(25),ystep(25)
			{				 
				gridcolor = 0xffd0d0d0;
				centercolor= 0xffa0a0a0;
				sf = new res::CSimpleFont(ss,0xffffffff);	
				for(int i=0;i<nrpoints;i++) {
					points[i].x = i+1;
					points[i].y = 1;
				}

				points[0].x  =1; points[0].y  =1;
				points[1].x  =3; points[1].y  =6;
				//points[2].x  =7; points[2].y  =4;

				sel = 0xff; 

				locked = false;
			}

			virtual ~CGraphWidget(void)	{}

			void DrawPixel(double x, double y) {
				double fx,fy;
				fx  = x-(int)x;
				fy = y - (int)y;
				s->color = s->Blend(green,bgc,(1-fx)*(1-fy));
				s->SetPixel(x,y);
			}
			void DrawPixelF(double x, double y) {
				double fx,fy;
				fx  = x-(int)x;
				fy = y - (int)y;
				s->color = s->Blend(green,bgc,1-(1-fx)*(1-fy));
				s->SetPixel(x,y+1);
			}			

			void DrawGrid(void) const {
				u16 my = grect.h/2;
				u16 mx = grect.w/2;

				s->color = gridcolor;
				s->pattern = 0x33333333;

				for(u16 y=(u16)ystep;y<grect.h;y+=(u16)ystep) {					
					s->DrawHLineP(1,grect.w-2,y);					
				}
				for(u16 x=(u16)ystep;x<grect.w;x+=(u16)xstep) {					
					s->DrawVLineP( x,1,grect.h-2);					
				}				
			}

			void DrawLine(double x1, double y1, double x2, double y2)
			{
				double dx = x2 - x1;
				double dy = y2 - y1;
				double d = sqrt(dx*dx + dy*dy);

				dx = 0.5 * (y2 - y1) / d;
				dy = 0.5 * (x2 - x1) / d;

				s->color = gridcolor;
				
				//long				
				s->DrawLine((x1 - dx - dy+0.5)*xstep,  (y1 + dy - dx +0.5)*ystep, (x2 - dx + dy +0.5)*xstep,  (y2 + dy + dx +0.5)*ystep);
				s->DrawLine((x2 + dx + dy+0.5)*xstep,  (y2 - dy + dx +0.5)*ystep, (x1 + dx - dy +0.5)*xstep,  (y1 - dy - dx +0.5)*ystep);

				//short
				s->DrawLine((x1 - dx - dy +0.5)*xstep,  (y1 + dy - dx +0.5)*ystep, (x1 + dx - dy +0.5)*xstep,  (y1 - dy - dx +0.5)*ystep);
				s->DrawLine((x2 - dx + dy +0.5)*xstep,  (y2 + dy + dx +0.5)*ystep, (x2 + dx + dy +0.5)*xstep,  (y2 - dy + dx +0.5)*ystep);

				// draw main line				
				s->color = black;
				s->DrawLine((x1-dy+0.5) * xstep,(y1-dx+0.5) * ystep, (x2+dy+0.5) * xstep,(y2+dx+0.5) * ystep);
			}
			void DrawLines(void) {								
				for(int i=1;i<nrpoints;i++) {
					DrawLine(
					points[i-1].x,points[i-1].y,
					points[i].x,points[i].y);

				}
			}
			void DrawHandle(double x, double y, u16 size) {
				
				Rect r  = Rect((u16)((x+0.5)*xstep-hsize/2), (u16)((y+0.5)*ystep-hsize/2), hsize,hsize);
				s->FillRect(r);
			}

			void DrawHandles(void) {
				for(int i=0;i<nrpoints;i++) {
					s->color = sel ==i?red:gray;
					DrawHandle(points[i].x, points[i].y,10);
				}
			}

			void DrawBB(void) {
				double xm,xM,ym,yM;
				xM = yM = -100;
				xm = ym = 10000;
				u16 xxm,yym,xxM,yyM;
				for(int i=0;i<nrpoints;i++) {
					xM = max(xM,points[i].x);
					yM = max(yM,points[i].y);
					xm = min(xm,points[i].x);
					ym = min(ym,points[i].y);					
				}
				//snap to gridbox
				xxm = (u16)xm*xstep; yym=(u16)ym*xstep;xxM=(u16)(xM+1.99)*xstep;yyM=(u16)(yM+1.99)*xstep;
				s->color = white3; 
				s->FillRect(xxm,yym,xxM,yyM);
				s->color = gray; 
				s->DrawRect2(xm*xstep+xstep/2,ym*ystep+ystep/2,xM*xstep+xstep/2,yM*ystep+ystep/2);
			}
			void DrawDist(double x, double y) {
				double m0 = (points[1].y - points[0].y) / (points[1].x - points[0].x);
				double c0 = points[1].y - m0*points[1].x;

				double m1 = -1/m0;
				double c1 = y-m1*x;
				
				double xi = (c1-c0)/(m0-m1);
				double yi = xi*m0+c0;

				double xm = min(points[0].x,points[1].x);
				double xM = max(points[0].x,points[1].x);

				double ym = min(points[0].y,points[1].y);
				double yM = max(points[0].y,points[1].y);

				double dx = x - xi;
				double dy = y - yi;
				double d = sqrt(dx*dx + dy*dy);

				char buf[20];
				sprintf(buf,"%1.1f",d);
			

				if(xi>=xm && xi<=xM && yi>=ym && yi<=yM) {					
					if (d<=1.0) {
						s->color = s->Blend(white,black,d);
					s->FillRect(x*xstep,y*ystep,(x+1)*xstep,(y+1)*xstep);

					s->color = green;
					s->DrawLine((x+0.5)*xstep,(y+0.5)*xstep,(xi+0.5)*xstep,(yi+0.5)*xstep);
				

					s->color = d<0.5?white:black;					 					
					sf->DrawT(x*xstep+4,y*xstep+4,(u8*)buf);
					} else {  
						/*s->color = black;		 								
						sf->DrawT(x*xstep+4,y*xstep+4,(u8*)buf);*/
					}

				}
				
			}

			virtual void Draw(void){
				super::Draw(); 
				s->color = bgc;				
				s->FillRect(grect);

				DrawBB();
				//DrawDist(2,1);
				for(int i=0;i<grect.w/xstep;i++)
					for(int j=0;j<grect.h/ystep;j++)
						DrawDist(i,j);
			
				DrawGrid();
				DrawLines();
				DrawHandles();
				s->color = 0xffa0a0a0;
				s->DrawRRect(grect);
			}

			bool HitTestHandle(u16 h,u16 x, u16 y) const {
				bool res = false;
				if((x>=(points[h].x+0.5)*xstep+hsize/2 )&&(x<(points[h].x+0.5)*xstep+hsize/2+hsize ))
					if((y>=(points[h].y+0.5)*ystep+hsize/2 )&&(y<(points[h].y+0.5)*ystep+hsize/2+hsize ))					
					res = true;
				return res;
			}
			virtual bool HitTest(Events *e){
				bool t,res = false;
				sel = 0xff;
				for(int i=0;i<nrpoints;i++) {
					t= HitTestHandle(i,e->x, e->y);
					 if(t)sel = i;
					 res |=t;
				}
				return res;
			}

			virtual u16 OnEvent(Events *e) {
				u16 res = 0;
				if(locked || HitTest(e)) {
					if(!Focused) res = 1;					
					Focused = true;
				} else {
					if(Focused) res = 1;					
					Focused = false;					
				}	
				if(Focused)
				{
					res = 1;
					if(e->e == Events::mpress) {
						locked = true;
						res = 2;
					}
					if(e->e == Events::mrelease) {
						locked = false;
						res = 3;
					}
					if(locked) {
						//set new pos
						e->x = e->x>10000?0:e->x;
						e->y = e->y>10000?0:e->y;
						e->x = (e->x-hsize>xstep)?e->x:(u16)xstep+hsize;
						e->x = (e->x-hsize<grect.w-xstep)?e->x:grect.w-(u16)xstep+hsize;

						e->y = (e->y-hsize>ystep)?e->y:(u16)ystep+hsize;
						e->y = (e->y-hsize<grect.h-ystep)?e->y:grect.h-(u16)ystep + hsize;

						points[sel].x = ((e->x-hsize)/(double)xstep-0.5);
						points[sel].y = ((e->y-hsize)/(double)ystep-0.5);
					}
				}
				return res;
			}

		};


	};// wg
};// sg
