// wavegen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"
#include "math.h"

typedef unsigned long u32;
typedef unsigned short u16;

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

void wave_gen(short *buff, int amp, int freq, int len)
{
	short *p = buff;
	for(int i=0;i<len;i++)
	{
		*p++ = amp * sin(2*3.1415*(float)freq*i/(float)44100.0);
		*p++ = amp * sin(2*3.1415*(float)freq*i/(float)44100.0);
	}
}

#define wlen	(256*100)
int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f = fopen("freq.wav","wb");
	short buff[wlen*2];
	if(!f) return 1;
	writeWaveHeader(f,wlen*2*2);
	wave_gen(buff,500,50,wlen);
	fwrite(buff,wlen*2,2,f);
	fclose(f);
	return 0;
}

