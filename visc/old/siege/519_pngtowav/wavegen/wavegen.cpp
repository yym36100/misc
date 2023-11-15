// wavegen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <Windows.h>
#include <afx.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <string.h>
#include <math.h>

#include "thread.h"

using namespace Gdiplus;

typedef unsigned long int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

char filename[255];
	#define nothreads	(8)

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
void sigGen(u32 samples, u16 *out){
	double freq = 440;
	for(u32 i=0;i<samples;i++){
		out[i] = 10000*sin(2*3.14159265 * freq * i / 44100.0 + 0.0);
		out[i] += 10000*sin(2*3.14159265 * (freq+1) * i / 44100.0 + 0.0);
	}
}

class synth {
public:
	double freq;
	double phase;
	synth():freq(0),phase(0){}
	double getVal(double amp, u32 i){
		phase += 2*3.14159265358 * freq / 44100;
		return amp * sin (phase);
	}
};

#define samplelen	(1024*600)
int _tmain(int argc, _TCHAR* argv[]) {

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	if (argc!=2) return 1;
	strcpy(filename, argv[1]);

	////////////////////
	Bitmap i2(L"d:\\Untitled copy.png");
	u16 w = i2.GetWidth();
	u16 h = i2.GetHeight();
	u32 size = w*h;

	u8 *pixels = new u8[size];
	u8 *p = pixels;
	u32 color;

	for(u16 y=0;y<h;y++)
	{
		for(u16 x=0;x<w;x++)
		{					
			i2.GetPixel(x,y,(Color*)&color);

			//*p++;// = (color>>16) & 0xff;
			//*p++;// = (color>>8)  & 0xff;
			*p++ = (color>>0)  & 0xff;					
		}
	}


	////////////////////
	//init synths
	synth synths[nothreads][256];
	for(int f=0;f<nothreads;f++)
	for(u32 i = 0;i<256;i++){
		synths[f][i].freq = i * 20000.0/256.0;
	}


	///////////////////

	FILE *f;
	f = fopen(filename,"wb");
	if(!f) return 2;
	writeWaveHeader(f,samplelen);

	u16 *samples = new u16[samplelen];
	//memset(samples,0,1024*2);
	//sigGen(samplelen, samples);

	// gen some signals
	/////////////////
#if 0
	double val;
	u8 *p2 = pixels,*p3, cv;

	for(u32 i=0;i<samplelen;i++){
		val = 0;
		p3=p2;
		for(u16 j=0;j<256;j++){		
			cv = 10*(255-*p3);
			if(cv!=0)
				val+= synths[j].getVal(cv,i);
			p3+=4;
		}
		if((i!=0) && ((i&1023)==0) )
			p2+=1024;
		samples[i] = val;		
	}
#else
	//multithreaded version
	class workthread : public sg::CThread {
	public:
		u32  start;
		u32 len;
		synth *psynth;
		u16 *out;
		u8 *pixels;
		workthread( u32 s, u32 l, synth *ps, u8 *p, u16*ou):start(s),len(l),psynth(ps),pixels(p),out(ou) {
			;
		}
		DWORD WINAPI Run(void){
			double val;
			u8 *p2 = pixels,*p3, cv;
			p2+=start;
			for(u32 i=0;i<len;i++){
				val = 0;
				p3=p2;
				for(u16 j=0;j<256;j++){		
					cv = 10*(255-*p3);
					if(cv!=0)
						val+= psynth[j].getVal(cv,start+i);
					p3+=4;
				}
				if((i!=0) && ((i&1023)==0) )
					p2+=1024;
				out[start+i] = val;		
			}
			end = 1;
			return 1;			
		}
	};

	workthread *apthread[nothreads];
	for(int i=0;i<nothreads;i++){
		apthread[i] = new workthread(i*samplelen/nothreads,samplelen/nothreads,&synths[i][0],pixels,samples );
		apthread[i]->Start();
	}
	u8 done;
	while(1){
		done = 0;
		for(int i=0;i<nothreads;i++){
			if(apthread[i]->end!=0) done++;
		}
		if(done == nothreads) break;
		Sleep(100);
	}

#endif


	writeWaveData(f,samplelen,samples);

	fclose(f);

	//Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

