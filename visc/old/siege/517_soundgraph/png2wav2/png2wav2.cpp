// png2wav2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <afx.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

typedef unsigned long int u32;
typedef unsigned short int u16;
typedef unsigned char u8;
char filename[255];

void writeWaveHeader(FILE *f,u32 samplelen){
	//header
	fwrite("RIFF",4,1,f);
	//chunk size
	u32 cksize = 4+24+8+ 2*2*samplelen; /*header size + 1sample len in bytes * no channels * no samples */ 
	fwrite(&cksize,4,1,f);
	//wave id ckid
	fwrite("WAVEfmt ",8,1,f);
	cksize = 16;
	fwrite(&cksize,4,1,f);
	//format tag
	u16 t16 = 1;
	fwrite(&t16,2,1,f);
	//no channels
	t16 = 2;
	fwrite(&t16,2,1,f);
	//samples/sec
	u32 t32 = 44100;
	fwrite(&t32,4,1,f);
	// average bytes/sec
	t32 = 44100*2*2;
	fwrite(&t32,4,1,f);
	// block align
	t16 = 2*2;
	fwrite(&t16,2,1,f);
	//bits/sample
	t16 = 8*2;
	fwrite(&t16,2,1,f);
	//ckid
	fwrite("data",4,1,f);
	//chunk size
	cksize = 2*2*samplelen;
	fwrite(&cksize,4,1,f);

	// and now follows the data...
}
void writeWaveData(FILE *f, u32 samplelen, u16 *samples){
	u16 sample;
	for(u32 i=0;i<samplelen;i++){
		sample = samples[i];
		fwrite(&sample,2,1,f);
		fwrite(&sample,2,1,f);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	{
		Bitmap i2(L"e:\\Untitled2.png ");
		u16 w = i2.GetWidth();
		u16 h = i2.GetHeight();
		u32 size = w*h;

		u8 *pixels = new u8[size];
		u8 *p = pixels;
		u32 color;

		for(u16 y=0;y<h;y++) {
			for(u16 x=0;x<w;x++) {					
				i2.GetPixel(x,y,(Color*)&color);
				*p++ = (color>>0)  & 0xff;					
			}
		}


#define samplelen	(512 * 512)
		///////////////////
		u16 *samples = new u16[samplelen];

		double val;
		u8 *p2 = pixels,*p3, cv;



#define sss	(1024)
		short fr[sss*1];
		short fi[sss*1];
		int scale;

		for(u32 j=0;j<samplelen;j+=512){				
			// synh one line

			//copy samples to fft buffer
			for(u16 i=0;i<sss/2;i++) {				
				fr[i] = (short)128*p2[j+i];
				fr[sss-1-i] = (short)128*p2[j+i];

				fi[i] = (short)128*p2[j+i];
				fi[sss-1-i] = (short)128*p2[j+i];		
			}		

			int fix_fft(short fr[], short fi[], short m, short inverse);

			// do ifft and scaling
			scale = fix_fft(fr,fi,10,1);
			for(u16 i=0;i<sss/2;i++){
				fr[i]<<=scale;			
			}
			//copy samples to fft buffer
			for(u16 i=0;i<sss/2;i++) {				
				samples[j+i] = fr[i];						
			}		


		}

		//3 write file
		FILE *o;
		o = fopen("synth.wav","wb");
		writeWaveHeader(o,samplelen);
		writeWaveData(o,samplelen,samples);


	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

