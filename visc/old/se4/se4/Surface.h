#pragma once
#include "stdafx.h"
#include "Siege.h"

class CSurface: public CSiege
{
public:

	CSurface(void)
	{
	}

	CSurface(u16 w, u16 h)
	{
		width=w; height=h;
	}

	virtual ~CSurface(void)
	{
	}

	void SetPixel(u16 x, u16 y) const
	{
		u32 *p = (u32*)pData;
		*(p+y*width+x) = color;
	}

	void blend(CSurface *pDest)
	{
		char *source, *dest;
		source = pData;
		dest = pDest->pData;
		u8 nAlpha;

		for(u16 y=0;y<height;y++)
			for(u16 x=0;x<width;x++)
			{
				nAlpha = *(source+3);				
				
				if( 0 == nAlpha )
				{
					dest+=4;
					source+=4;
					continue;
				}
				if( 255 == nAlpha )
				{
					*dest++ = *source++;
					*dest++ = *source++;
					*dest++ = *source++;
					*dest++ = *source++;
					continue;
				}

				BYTE nInvAlpha = 255-nAlpha;
				
				BYTE nSrcRed   = *source++ ;
				BYTE nSrcGreen = *source++ ; 
				BYTE nSrcBlue  = *source++ ;
				source++;

				
				BYTE nDestRed   = *dest++ ; 
				BYTE nDestGreen = *dest++ ; 
				BYTE nDestBlue  = *dest++ ;

				dest-=3;

				*dest++ = ( nSrcRed   * nAlpha + nDestRed * nInvAlpha   )>>8;
				*dest++ = ( nSrcGreen * nAlpha + nDestGreen * nInvAlpha )>>8;
				*dest++  = ( nSrcBlue  * nAlpha + nDestBlue * nInvAlpha  )>>8;

				dest++;								
			}
	}

	u16 width, height;
	char *pData;
	u32 color;
};
