#include <stdio.h>
#include <tchar.h>

#include <atlimage.h>
#include <Gdiplus.h>
using namespace Gdiplus;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

#include "cdef.h"

#include "bitmap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc!=3)
	{
		printf("PNG2C converter (SaDo 2013-11-28)\nUsage: png2c.exe <infile> <options>\n");
		return -1;
	}

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);	

	wchar_t name[256];
	wcscpy(name, argv[1]);
	name[wcslen(name)-4]=0;

	CImage image;
	image.Load(argv[1]);

	FILE *f;
	wchar_t cname[256];
	wcscpy(cname,name);
	wcscat(cname,L".c");
	f = _wfopen(cname,L"wt");
	fwprintf(f,L"// %s res = %dx%d size = %d format = %s\n",
		name,image.GetWidth(),image.GetWidth(),image.GetWidth()*image.GetHeight()*4,L"RGBA888");
	fwprintf(f,L"const unsigned char RES_%s[] = {\n",name);
	fprintf(f,"0x%02x, 0x%02x, 0x%02x, 0x%02x, ",image.GetWidth(),image.GetHeight(),0,0);

	u16 cnt = 2;		
	u8 r,g,b,a;
	const u8 *p;

	Se::Bitmap bm(image.GetWidth(),image.GetHeight(),Se::Bitmap::RGBA8888);

	for(int y=0;y<image.GetHeight();y++)
		for(int x=0;x<image.GetWidth();x++)
		{
			Se::color cc;
			p=(u8*)image.GetPixelAddress(x,y);
			r = *p++;g = *p++;b = *p++;a = *p++;
			cc.rgba[cc.r] = r;
			cc.rgba[cc.g] = g;
			cc.rgba[cc.b] = b;
			cc.rgba[cc.a] = a;
			bm.SetPixel(x,y,cc);
		}
		bm.Convert(Se::Bitmap::RGB888);

#if 0
		for(int y=0;y<bm.h;y++)
			for(int x=0;x<bm.w;x++)
			{
				Se::color c = bm.GetPixel(x,y);
				fprintf(f,"0x%02x, 0x%02x, 0x%02x, 0x%02x, ",c.rgba[c.r],c.rgba[c.g],c.rgba[c.b],c.rgba[c.a]);
				if(((cnt++)&0x03)==0)fprintf(f,"\n");

			}
#endif
#if 1
		for(int y=0;y<bm.h;y++)
			for(int x=0;x<bm.w;x++)
			{
				Se::color c = bm.GetPixel(x,y);
				fprintf(f,"0x%02x, 0x%02x, 0x%02x, ",c.rgba[c.r],c.rgba[c.g],c.rgba[c.b]);
				if(((cnt++)&0x03)==0)fprintf(f,"\n");

			}
#endif
			fprintf(f,"};\n");
			fclose(f);

			return 0;
}
