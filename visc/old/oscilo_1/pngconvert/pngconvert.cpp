// pngconvert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <atlimage.h>
#include <gdiplus.h>
#include <Gdiplusimaging.h>

#include "sbmp.h"

using namespace Gdiplus;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<3)
	{
		printf("pngconvert.exe <pngname> <type>\n");
		return 0;
	}
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	//open png
	//CImage image;	
	//image.Load("d:\\small.png");
	{
		Bitmap image(argv[1]);

		sbmp::csbmp i;
		sbmp::type t;
		switch(argv[2][0])
		{
		case '0':
			t = sbmp::RGB888;
			break;
		case '1':
			t = sbmp::RGBA8888;
			break;
		case '2':
			t = sbmp::rleRGBA888;
			break;
		case '3':
			t = sbmp::YUVA8888;
			break;
		}

		i.create(image.GetWidth(),image.GetHeight(),t,1);

		u8 a,r,g,b;
		u8 *d = i.buffer;
		u32 color;

		for(u16 y = 0; y<i.head.height;y++)
		{		
			for(u16 x = 0; x<i.head.width;x++)
			{
				image.GetPixel(x,y,(Color*)&color);
				switch(t)
				{
				case sbmp::RGBA8888:
				case sbmp::rleRGBA888:
					{
						*d++ = (color>>24) & 0xff;
						*d++ = (color>>16) & 0xff;
						*d++ = (color>>8)  & 0xff;
						*d++ = (color>>0)  & 0xff;		
					}
					break;
				case sbmp::YUVA8888:
					{
						//Y = 0.299R´ + 0.587G´ + 0.114B´
						//U= – 0.147R´ – 0.289G´ + 0.436B´
						//= 0.492 (B´ – Y)
						//V = 0.615R´ – 0.515G´ – 0.100B´
						//= 0.877(R´ – Y)
						u8 r,g,b,a;
						a = (color>>24) & 0xff;
						r = (color>>16) & 0xff;
						g = (color>>8) & 0xff;
						b = (color>>0) & 0xff;

						double y = 0.299*r + 0.587*g + 0.114*b;
						double u = 0.492 * (b - y);
						double v = 0.877 * (r - y);

						*d++ = a;
						*d++ = 0xff;//u8(y);
						*d++ = u8(u);
						*d++ = 0xff;//u8(v);
					}

					break;
				}
			}		
		}

		wchar_t filename[255];
		wcscpy(filename,argv[1]);
		wcscat(filename,L".sbmp");
		i.savetofile(filename);
	}


	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return 0;
}

