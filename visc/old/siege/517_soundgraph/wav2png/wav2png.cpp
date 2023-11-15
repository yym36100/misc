// wav2png.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <afx.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;


char *buffer;
unsigned long buflen,samplelen;
char *start;

typedef unsigned long int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

int fix_fft(short fr[], short fi[], short m, short inverse);

void readFileData(char *szFilename) {
	FILE *fp = fopen(szFilename, "rb");
	long len;		
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = (char*) calloc(1, len+1);
	fread(buffer, 1, len, fp);
	fclose(fp);
	buflen = len;		
	start = buffer+44;
	samplelen = (buflen-44)/4;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc!=2) return 0;

	//1 read file
	readFileData(argv[1]);

	//2 do some processing
	u16 *samples;
	samples = new u16[samplelen];
	char *p = start;
	//copy first channel
	for(u32 i=0;i<samplelen;i++){
		samples[i] = p[0] + (p[1]<<8);
		p+=4;
	}

#define sss	(1024)
	short fr[sss*1];
	short fi[sss*1];
	int scale;
	u16 *p2 = samples;

	for(u32 j=0;j<samplelen;j+=1024){
		//copy samples to fft buffer
		for(u16 i=0;i<sss*1;i++)
		{				
			fr[i] = (short)p2[j+i];
			fi[i] = 0;				
		}		

		// do fft and scaling
		scale = fix_fft(fr,fi,10,0);
		for(u16 i=0;i<sss;i++){
			fr[i]<<=scale;
			fi[i]<<=scale; 
		}
	}

	return 0;
}

