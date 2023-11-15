// synth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

char *buffer;
unsigned long buflen,samplelen;
char *start;

typedef unsigned long int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

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
int main(int argc, char* argv[])
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
	//fft
#define sss	(1024)
	short fr[sss*1];
	short fi[sss*1];
	int scale;
	u16 *p2 = samples;

	int fix_fft(short fr[], short fi[], short m, short inverse);

	printf("total len = %d",samplelen/1024);
	for(u32 j=0;j<samplelen;j+=1024){
		printf("%d \n",j);

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
		// quick and dirty low pass filter
		u16 startf = 0.0 * 512.0 / 22100.0  ;
		u16 stopf =  600.0 * 512.0 / 22100.0 ;
		u16 halflen = sss/2;
		for(u16 i = startf;i < stopf;i++){
			fr[i]=0;
			fi[i]=0; 
			// mirror image
			fr[sss-i]=0;
			fi[sss-i]=0; 
		}

		 startf = 6000.0 * 512.0 / 22100.0  ;
		 stopf =  22100.0 * 512.0 / 22100.0 ;
		
		for(u16 i = startf;i < stopf;i++){
			fr[i]=0;
			fi[i]=0; 
			// mirror image
			fr[sss-i]=0;
			fi[sss-i]=0; 

		}
		
		

		// do ifft and scaling
		scale = fix_fft(fr,fi,10,1);
		for(u16 i=0;i<sss;i++){
			fr[i]<<=scale;			
		}

		//copy samples to fft buffer
		for(u16 i=0;i<sss*1;i++)
		{				
			p2[j+i] = fr[i];			
			//p2[j+i] = 0;
		}		
	}

	//3 write file
	FILE *o;
	o = fopen("out.wav","wb");
	writeWaveHeader(o,samplelen);
	writeWaveData(o,samplelen,samples);


	return 0;
}

