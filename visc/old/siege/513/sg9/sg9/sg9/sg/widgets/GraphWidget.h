#pragma once
#include <math.h>

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
			enum {siglen = 780-2};
		public:
			u32 gridcolor, centercolor,bgc;
			res::CSimpleFont *sf;
			char *title;

			double *sig;


			CGraphWidget(CSurface *ss, u16 x, u16 y, u16 w=400, u16 h=200, char *t=0,u32 c = white1):
			CWidget(ss,x,y,w,h),bgc(c),title(t)
			{				 
				gridcolor = 0xffd0d0d0;
				centercolor= 0xffa0a0a0;
				sf = new res::CSimpleFont(ss,0xffffffff);	

				//gen test signal
				sig = new double[siglen];
				for(int i=0;i<siglen;i++)
					//sig[i] = 0+ 80 * sin( 2*3.14159265 *10.3 * i / siglen + 2*3.14159265*45/360);
					sig[i] = -80;

				sig[4] = +80;
				//sig[5] = +40;
			}

			virtual ~CGraphWidget(void)	{}

			void DrawSignalLP() {}
			void DrawSignalMP() {}

			void DrawSignal(void) {
				/*if(siglen>rect.w-2) {
				DrawSignalMP();
				} else if (siglen == rect.w-2) {
				DrawSignal_11();
				} else {
				DrawSignalLP();
				}*/
				DrawSignal_11aa();
			}

			void DrawSignal_11(void) {
				s->lp.x = 1;
				s->lp.y = grect.h/2+sig[0];
				s->color = green;
				for(int i=1;i<grect.w-2;i++)
				{
					s->DrawTo(i+1,(u16)sig[i]+grect.h/2);
				}
			}

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
			void DrawSpan(u16 x, double y1, double y2) {

			}

			void DrawScanline( u16 x, double pc, double pp, double pn) {
				double dist, sgn,bf,bi;
				u32 c;
				if(/* same side */
					((pp>=pc) && (pn>=pc)) || ((pp<pc) && (pn<pc)) ) {
						// get the bigest distance
						double d1,d2;
						d1 = (int)pp-(int)pc; d2 = (int)pn-(int)pc;
						sgn = (d1+d2)>0.0?1.0:-1.0;
						dist = max(abs(d1),abs(d2));

						bf = 0;
						bi = 1/dist;

						for(int i=0;i<= dist;i+=1.0) {
						c = s->Blend(green,bgc,bf);
						bf+=bi;
						s->color = c;
						s->SetPixel(x,(u16)pc+i*sgn);
					}
				} else {
					/* middle current point */

					// prev to current
					dist = ((int)pc-(int)pp);
					if (dist == 0 )
					{

						c = s->Blend(green,bgc,1-(-(int)pc + pc));
						s->color = c;
						s->SetPixel(x,(u16)pc);

						c = s->Blend(green,bgc,(-(int)pc + pc));
						s->color = c;
						s->SetPixel(x,(u16)pc+1);
					} else {
						sgn = dist>0.0?1.0:-1.0;
						bf = 0;
						bi = 1/dist*sgn;
						for(int i=0;i<= dist*sgn;i+=1.0) {
							c = s->Blend(green,bgc,bf);
							bf+=bi;
							s->color = c;
							s->SetPixel(x,(u16)pp+i*sgn);
						}
						// current to next
						dist = ((int)pc-(int)pn);
						sgn = dist>0.0?1.0:-1.0;
						bf = 0;
						bi = 1/dist*sgn;
						for(int i=0;i<= dist*sgn;i+=1.0) {
							c = s->Blend(green,bgc,bf);
							bf+=bi;
							s->color = c;
							s->SetPixel(x,(u16)pn+i*sgn);
						}
					}
				}			

			}

			void DrawScanline2( u16 x, double pc, double pp, double pn) {
				double sgn;

				double ymin =  min(pc,pp);
				ymin = min(ymin,pn);

				double ymax = max(pc,pp);
				ymax = max(ymax,pn);

				if( (pc>ymin && pc<ymax) || ymin==ymax) {
					// midpoint

					//draw min - c-1 + c - max
					for(double i=ymin; i<pc;i+=1.0)
					{
						DrawPixel(x,i);
					}
					double i;
					for( i=pc; i<ymax;i+=1.0)
					{
						DrawPixel(x,i);
					}
					DrawPixelF(x,i-1);

				} else {
					// peakpoint
				}

				
				//DrawPixel(x,pc);
				//DrawPixelF(x,pc);
			}

			void DrawSignal_11aa(void) {
				double pc,pp,pn,f1,ff;
				u32 c1,c2,bg1,bg2;
				s->color = green;

				pp = sig[0]+grect.h/2;
				for(int i=1;i<grect.w-2-1;i++) {
					pc = sig[i]+grect.h/2;
					pn = sig[i+1]+grect.h/2;
					DrawScanline2(i,pc,pp,pn);
					pp = pc;
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
			}
		};


	};// wg
};// sg
