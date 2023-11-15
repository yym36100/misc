// rgb_bgr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f;
	f=fopen(argv[1],"rb");
	if(!f)return 1;

#define size	(800*480*4)
	static unsigned char buff[size],t;

	fread(buff,size,1,f);
	fclose(f);

	for(int i=0;i<(size-4);i+=4){
		t = buff[i+0];
		 buff[i+0] = buff[i+2];
		 buff[i+2] = t;
	}
	char name2[256] = {0};
	strcpy(name2,argv[1]);
	strcat(name2,".r");

	f= fopen(name2,"wb");
	if(!f) return 2;
	fwrite(buff,size,1,f);
	fclose(f);


	return 0;
}

