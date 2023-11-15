#include "sbmp.h"
#include <stdio.h>

namespace sbmp{
	void csbmp::create(u16 w, u16 h, u8 t, u8 f)
	{
		head.ver = sbmp_version;
		head.width = w;
		head.height = h;
		head.type = t;
		head.noFrames = f;
		size = w*h*4*f;
		buffer = new u8[size];
		buffer[0] = 'S';
		buffer[1] = 'D';
	}
	void csbmp::compress(void)
	{
		if(head.type == rleRGBA888)
		{
			//compress pixel data

			// rle compression : escape byte is 0x80-1 next byte noPixels next 4 bytes = pixel value, otherwise uncompressed
			u32 *r = (u32*)buffer;
			u8 *wbuff = new u8[size]; // hopefully the compressed data doesn't exceed the size of the uncompressed data
			u8 *w = wbuff;
			u32 i=0;
			u32 j=0;
			u32 cnt;
			u32 color;
			while(i<size)
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
					if ((color&0xff)==rleARGB8888Escape)
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
					*w++ = rleARGB8888Escape;
					*w++ = (cnt>>8)&0xff;
					*w++ = (cnt>>0)&0xff;

					*w++ = (color>>0)  & 0xff;		
					*w++ = (color>>8)  & 0xff;
					*w++=  (color>>16) & 0xff;
					*w++ = (color>>24) & 0xff;

					j+=7;
				}					
			}
			head.fsize = j;
			delete [] buffer;
			buffer = wbuff;
		} // end rle compression
	}
	void csbmp::savetofile(wchar_t *name)
	{
		FILE *f;

		if(f = _wfopen(name,L"wb"))
		{
			if(head.type == rleRGBA888)
			{
				compress();
			}
			else
			{
				head.fsize = size;
			}

			fwrite(&head,sizeof(head),1,f);
			fwrite(buffer,head.fsize,1,f);
			fflush(f);
			fclose(f);
		}
	}
};