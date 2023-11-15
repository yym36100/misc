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
			struct dp {
				double x,y;
				double sx,sy;
				double size;
			};

			u32 gridcolor, centercolor,bgc;
			res::CSimpleFont *sf;
			char *title;
			float f1; /* = 1.0/2.0;*/
			float f2; /*= 1.0/2.0;*/
			float ph1,ph2;
			u8 o;
			double time ;
			enum {
				nrpoints = 14,
				dotsize = 250,
			};
			dp pts[nrpoints];


			CGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, char *t=0,u32 c = white1):
			CWidget(ss,x,y,w,h),bgc(c),title(t),f1(1),f2(1),ph1(0),ph2(0),o(o), time(0)
			{				 
				gridcolor = 0xffd0d0d0;
				centercolor= 0xffa0a0a0;
				sf = new res::CSimpleFont(ss,0xffffffff);	

				for(int i=0;i<nrpoints;i++) {
					pts[i].x = rand()%400;
					pts[i].y = rand()%400;
					pts[i].sx = rand()%4+1;
					pts[i].sy = rand()%4+1;
					pts[i].size = rand()%dotsize+10;

				}

			/*	pts[0].x = 0;
				pts[0].y = 0;				

				pts[1].x = 200;
				pts[1].y = 200;

				pts[2].x = 0;
				pts[2].y = 100;

				pts[3].x = 300;
				pts[3].y = 64;

				pts[0].sx = 1;
				pts[1].sx = 2;
				pts[2].sx = 3;
				pts[3].sx = 4;

				pts[0].sy = 1;
				pts[1].sy = 3;
				pts[2].sy = 2;
				pts[3].sy = 1;*/
			}

			virtual ~CGraphWidget(void)	{}

			void UpdatePoints(void) {
				for(int i=0;i<nrpoints;i++) {
					pts[i].x += pts[i].sx;
					pts[i].y += pts[i].sy;

					if((pts[i].x <= 0)||(pts[i].x >= grect.w) ) {
						pts[i].sx = -pts[i].sx;
					}
					if((pts[i].y <= 0)||(pts[i].y >= grect.h) ) {
						pts[i].sy = -pts[i].sy;
					}

				}
			}

			virtual void Draw(void){
				super::Draw(); 
				s->color = bgc;				
				s->FillRect(grect);

				s->color = 0xffa0a0a0;
				s->DrawRRect(grect);

				u16 c;

#define dist(a, b, c, d) sqrt(double((a - c) * (a - c) + (b - d) * (b - d)))
				UpdatePoints();

				for(u16 yy = 0;yy<grect.h;yy++)
					for(u16 xx = 0;xx<grect.w;xx++)
					{			
						double value = 1;
						double d;
						for(int i = 0;i<nrpoints;i++) {
							d = dist(xx, yy, pts[i].x, pts[i].y );
							if(d>pts[i].size) {											
							} else { 
								d = d*3.14159265358/(pts[i].size*2.0);								
								value *=sin(d);
							}
							

							
						}						
						c  = value*255.0;
						if(c>255) c = 255;
						if(c >= 30 && c<=65) ; else c = 255;

						s->color = rgba32(c,c,c,255);
						s->SetPixel(xx,yy);
					}
			}

		};


	};// wg
};// sg
