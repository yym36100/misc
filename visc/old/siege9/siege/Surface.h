#pragma once
#include "cdef.h"
#include "obj.h"


#define rgba32(r,g,b,a) ((a<<24)|(r<<16)|(b<<8)|(g))
#define gray rgba32(128,128,128,255)
#define white rgba32(255,255,255,255)

#define red rgba32(255,0,0,255)
#define green rgba32(0,255,0,255)
#define blue rgba32(0,0,255,255)

namespace siege{
	namespace graphics{

		class CSurface :
			public CObj
		{
		public:
			u16 w,h;
			u32 *pData;
			u16 maxweight;

			CSurface(void):pData(NULL)
			{
			}

			~CSurface(void)
			{
				if(pData) delete[] pData;
			}

			CSurface(u16 w, u16 h)
			{
				this->w = w;
				this->h = h;
				pData = new u32[w*h*4];
				maxweight = 0;
			}

			virtual void Clear(u32 color)
			{
				u32 *p= pData;
				for(u32 i=0;i<(u32)w*h;i++)
				{
					*p++=color;
				}
			}
			/*void clear(u32 color)
			{
			for(u16 y=0;y<h;y++)
			for(u16 x=0;x<w;x++)

			}*/

			void SetPixel(u16 x, u16 y,u32 color)
			{
				if(x>=w || y>=h) return;
				u32 *p = pData + x + y*w;
				*p = color;
			}

			void BlendPixel(u16 x, u16 y,u32 color)
			{
				// destination alpha is ignored
				if(x>=w || y>=h) return;
				u32 *p = pData + x + y*w;
				u32 dcolor = GetPixel(x,y);

				
				u8 sr,sg,sb,a;
				u8 dr,dg,db;

				a  = (u8)(color>>24);
				sr = (u8)(color>>16);
				sg = (u8)(color>>8);
				sb = (u8)(color);

				dr = (u8)(dcolor>>16);
				dg = (u8)(dcolor>>8);
				db = (u8)(dcolor);

				u8 tr,tg,tb;

				tr = (u8)(((u32)sr * a + (u32)dr*(256-a))/256);
				tg = (u8)(((u32)sg * a + (u32)dg*(256-a))/256);
				tb = (u8)(((u32)sb * a + (u32)db*(256-a))/256);
				if((tb<20) && (a>20))
				{
					color++;
				}
				color =  rgba32(tr,tb,tg,0xff);
				SetPixel(x,y,color);				
			}

			u32 GetPixel(u16 x, u16 y)const
			{
				if(x>=w || y>=h) return 0;
				u32 *p = pData + x + y*w;
				return *p;
			}

			void DrawVLine(u16 x,u16 y1,u16 y2, u32 color)
			{
				if(x>=w || y1>=h ||y2>=h) return;
				u32 *p = pData + x + y1*w;			
				for(u16 y=y1;y<=y2;y++)
				{
					*p=color;
					p+=w;
				}
			}
			void DrawHLine(u16 x1,u16 x2,u16 y, u32 color)
			{
				if(y>=h || x1>=w ||x2>=w) return;
				u32 *p = pData + x1 + y*w;			
				for(u16 x=x1;x<=x2;x++)
				{
					*p=color;
					p++;
				}
			}
			void DrawRect(u16 x, u16 y, u16 w, u16 h, u32 color)
			{
				DrawVLine(x,y,y+h,color);
				DrawVLine(x+w,y,y+h,color);

				DrawHLine(x,x+w,y,color);
				DrawHLine(x,x+w,y+h,color);
			}
			void DrawRect(stRect r,u32 color)
			{
				DrawRect(r.x,r.y,r.w,r.h,color);
			}
			void FillRect(stRect r, u32 color)
			{
				for(u16 h=r.y;h<r.y+r.h;h++)
					DrawHLine(r.x,r.x+r.w,h,color);
			}


#define MYABS(x) x<0?-x:x;
			void DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u32 color)
			{
				static u32 errcnt = 0;
				if(x1>=w || x2 >=w || y1>=h || y2>=h) 
				{
					errcnt++;
					return;
				}
				u32 * p = pData;			
				i16 dx=(x2-x1);
				i16 dy=(y2-y1);

				i16 sx,sy;

				int sa;
				if(dx<0) sx=-1;else sx=1;
				if(dy<0) {sy=-1;sa = -w;}else {sy=1;sa = w;}

				p+=(y1*w+x1);

				dx=MYABS(dx);dy=MYABS(dy);
				if(dx>dy)
				{
					i16 e=dy-(dx>>1);
					for(;x1!=x2;)
					{					
						*p=color;
						if(e>0)
						{
							e-=dx;y1+=sy;
							p+=sa;
						}
						x1+=sx;
						p+=sx;
						e+=dy;
					}
				}
				else
				{
					i16 e=dx-(dy>>1);
					for(;y1!=y2;)
					{					
						*p=color;
						if(e>0)
						{
							e-=dy;x1+=sx;p+=sx;
						}
						y1+=sy;p+=sa;
						e+=dx;
					}
				}

			}

			///////////
			// http://www.codeproject.com/Articles/13360/Antialiasing-Wu-Algorithm
			/////////////////

			void DrawWuLine (u16 X0, u16 Y0, u16 X1, u16 Y1,
				u16 BaseColor, u8 NumLevels, u8 IntensityBits,u32 color)
			{
				u16 IntensityShift, ErrorAdj, ErrorAcc;
				u16 ErrorAccTemp;//, Weighting, WeightingComplementMask;
				i16 DeltaX, DeltaY, Temp, XDir;
				u32 color2, color3;
				u8 Weighting,WeightingComplementMask;

				/* Make sure the line runs top to bottom */
				if (Y0 > Y1) {
					Temp = Y0; Y0 = Y1; Y1 = Temp;
					Temp = X0; X0 = X1; X1 = Temp;
				}
				/* Draw the initial pixel, which is always exactly intersected by
				the line and so needs no weighting */
				//DrawPixel(pDC,X0, Y0, BaseColor);
				SetPixel(X0,Y0,color);

				if ((DeltaX = X1 - X0) >= 0) {
					XDir = 1;
				} else {
					XDir = -1;
					DeltaX = -DeltaX; /* make DeltaX positive */
				}
				/* Special-case horizontal, vertical, and diagonal lines, which
				require no weighting because they go right through the center of
				every pixel */
				if ((DeltaY = Y1 - Y0) == 0) {
					/* Horizontal line */
					while (DeltaX-- != 0) {
						X0 += XDir;
						//DrawPixel(pDC,X0, Y0, BaseColor);
						SetPixel(X0,Y0,color);
					}
					return;
				}
				if (DeltaX == 0) {
					/* Vertical line */
					do {
						Y0++;
						//DrawPixel(pDC,X0, Y0, BaseColor);
						SetPixel(X0,Y0,color);
					} while (--DeltaY != 0);
					return;
				}
				if (DeltaX == DeltaY) {
					/* Diagonal line */
					do {
						X0 += XDir;
						Y0++;
						//DrawPixel(pDC,X0, Y0, BaseColor);
						SetPixel(X0,Y0,color);
					} while (--DeltaY != 0);
					return;
				}
				/* Line is not horizontal, diagonal, or vertical */
				ErrorAcc = 0;  /* initialize the line error accumulator to 0 */
				/* # of bits by which to shift ErrorAcc to get intensity level */
				IntensityShift = 16 - IntensityBits;
				/* Mask used to flip all bits in an intensity weighting, producing the
				result (1 - intensity weighting) */
				WeightingComplementMask = NumLevels - 1;
				/* Is this an X-major or Y-major line? */
				if (DeltaY > DeltaX) {
					/* Y-major line; calculate 16-bit fixed-point fractional part of a
					pixel that X advances each time Y advances 1 pixel, truncating the
					result so that we won't overrun the endpoint along the X axis */
					ErrorAdj = ((unsigned long) DeltaX << 16) / (unsigned long) DeltaY;
					/* Draw all pixels other than the first and last */
					while (--DeltaY) {
						ErrorAccTemp = ErrorAcc;   /* remember currrent accumulated error */
						ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
						if (ErrorAcc <= ErrorAccTemp) {
							/* The error accumulator turned over, so advance the X coord */
							X0 += XDir;
						}
						Y0++; /* Y-major, so always advance Y */
						/* The IntensityBits most significant bits of ErrorAcc give us the
						intensity weighting for this pixel, and the complement of the
						weighting for the paired pixel */
						Weighting = ErrorAcc >> IntensityShift;

						/*DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
						DrawPixel(pDC,X0 + XDir, Y0,
							BaseColor + (Weighting ^ WeightingComplementMask));*/
						
						color2 = (Weighting<<24) | (color&0x00ffffff);
						color3 = ((u8)(Weighting ^ WeightingComplementMask)<<24) | (color&0x00ffffff);
						BlendPixel(X0,Y0,color3);
						BlendPixel(X0 + XDir,Y0,color2);
						
						
					}
					/* Draw the final pixel, which is 
					always exactly intersected by the line
					and so needs no weighting */
					//DrawPixel(pDC,X1, Y1, BaseColor);
					SetPixel(X1,Y1,color);
					return;
				}
				/* It's an X-major line; calculate 16-bit fixed-point fractional part of a
				pixel that Y advances each time X advances 1 pixel, truncating the
				result to avoid overrunning the endpoint along the X axis */
				ErrorAdj = ((unsigned long) DeltaY << 16) / (unsigned long) DeltaX;
				/* Draw all pixels other than the first and last */
				while (--DeltaX) {
					ErrorAccTemp = ErrorAcc;   /* remember currrent accumulated error */
					ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
					if (ErrorAcc <= ErrorAccTemp) {
						/* The error accumulator turned over, so advance the Y coord */
						Y0++;
					}
					X0 += XDir; /* X-major, so always advance X */
					/* The IntensityBits most significant bits of ErrorAcc give us the
					intensity weighting for this pixel, and the complement of the
					weighting for the paired pixel */
					Weighting = ErrorAcc >> IntensityShift;
					/*DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
					DrawPixel(pDC,X0, Y0 + 1,
						BaseColor + (Weighting ^ WeightingComplementMask));*/
					color2 = (Weighting<<24) | (color&0x00ffffff);
						color3 = ((u8)(Weighting ^ WeightingComplementMask)<<24) | (color&0x00ffffff);


					SetPixel(X0,Y0,color3);
					SetPixel(X0,Y0+1,color2);
				
				}
				/* Draw the final pixel, which is always exactly intersected by the line
				and so needs no weighting */
				//DrawPixel(pDC,X1, Y1, BaseColor);
				SetPixel(X0,Y0,color);
			}
			///////////

		};
	}
}