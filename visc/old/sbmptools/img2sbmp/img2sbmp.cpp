#include "stdafx.h"
#include <Windows.h>
#include <gdiplus.h>

#include "stypes.h"
#include "sbmp.h"


#include "zlib.h"



using namespace Gdiplus;

int _tmain(int argc, _TCHAR* argv[])
{
	 sizeCheck();

	if(argc<3)
	{
		printf("usage img2sbmp.exe <im_image> <out_image.sbmp> [type]\n"
			"type = 0  ARGB8888(default)\n"
			"type = 1  RGB888\n"
			"type = 2  rleARGB8888\n"
			"type = 3  zARGB8888\n"
			);		
	}
	else
	{
		u8 type =0;
		if (argc>3)
		{
			type = _wtoi(argv[3]);
		}
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR           gdiplusToken;

		// Initialize GDI+.
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		FILE *f;
		if(!(f=_wfopen(argv[2],L"wb")))
		{
			printf("error creating sbmp file: %s\n",argv[2]);		
		}
		else
		{
			Bitmap i(argv[1]);
			u16 w = i.GetWidth();
			u16 h = i.GetHeight();
			u32 size = w*h*sg::sBmpPixelSize[type];

			u8 *pixels = new u8[size];
			u8 *p = pixels;
			u32 color;

			for(u16 y=0;y<h;y++)
			{
				for(u16 x=0;x<w;x++)
				{
					//color ARGB888 assumed
					i.GetPixel(x,y,(Color*)&color);
					if(type == sg::ARGB8888 || type == sg::rleARGB8888 || type==sg::zARGB8888)
					{
						*p++ = (color>>24) & 0xff;

						if( (color) & 0xff == 0)
						{
							//if fully transparent set all pixels components to 0 for better rle compression
							color = 0;
						}
					}
					*p++ = (color>>16) & 0xff;
					*p++ = (color>>8)  & 0xff;
					*p++ = (color>>0)  & 0xff;					
				}
			}

			sg::tsBmp sBmp;
			sBmp.head.tag[0]='s';
			sBmp.head.tag[1]='d';
			sBmp.head.ver = sg::sBmpVer;
			sBmp.head.type = type;
			sBmp.head.w = w;
			sBmp.head.h = h;
			sBmp.head.size = size;
			sBmp.pixels=pixels;

			if(type == sg::rleARGB8888)
			{
				//compress pixel data

				// rle compression : escape byte is 0x80-1 next byte noPixels next 4 bytes = pixel value, otherwise uncompressed
				u32 *r = (u32*)sBmp.pixels;
				u8 *wbuff = new u8[sBmp.head.size]; // hopefully the compressed data doesn't exceed the size of the uncompressed data
				u8 *w = wbuff;
				u32 i=0;
				u32 j=0;
				u32 cnt;
				u32 color;
				while(i<sBmp.head.size)
				{
					cnt=0;
					color = *r++;
					i+=4;
					while( color == *r)
					{
						cnt++;						
						r++;
						i+=4;
						if(cnt==0xffff)
						{
							break;
						}
					}					
					if(cnt==0)
					{
						//make sure escape byte is not found in the uncompressed pixels
						if ((color&0xff)==sg::rleARGB8888Escape)
						{
							color+=1;
						}
						
						// this is inverted because of u32 lit end
						*w++ = (color>>0)  & 0xff;		
						*w++ = (color>>8)  & 0xff;
						*w++=  (color>>16) & 0xff;
						*w++ = (color>>24) & 0xff;
						j+=4;
					}
					else
					{
						*w++ = sg::rleARGB8888Escape;
						*w++ = (cnt>>8)&0xff;
						*w++ = (cnt>>0)&0xff;

						*w++ = (color>>0)  & 0xff;		
						*w++ = (color>>8)  & 0xff;
						*w++=  (color>>16) & 0xff;
						*w++ = (color>>24) & 0xff;

						j+=7;
					}					
				}
				sBmp.head.size = j;
				delete sBmp.pixels;
				sBmp.pixels = wbuff;
			} // end rle compression

			if(type == sg::zARGB8888)
			{
				u32 ret,size = compressBound(sBmp.head.size);
				ret = size;
				u8 *cbuff = new u8[size];
				//u8 *rbuff = new u8[size];
				int res = compress2(cbuff,&ret,sBmp.pixels,sBmp.head.size,9);
				//int res2 = uncompress(rbuff,&size,cbuff,ret);
				delete sBmp.pixels;
				sBmp.head.size = ret;
				sBmp.pixels = cbuff;

			}// end zlib compression


			fwrite(&sBmp.head,sizeof(sBmp.head),1,f);
			fwrite(sBmp.pixels,sBmp.head.size,1,f);

			delete[] sBmp.pixels;
			fclose(f);
		}
		GdiplusShutdown(gdiplusToken);
	}
	return 0;
}




