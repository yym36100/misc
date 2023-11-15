// szlib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>



#include "zlib.h"


#define CHUNK 200
// zlib stuff ======================================================

char data[CHUNK]="some text to compress not a lot just enough to test the inflate and delflate algorithms"
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccc";
char out[CHUNK];
unsigned outsize=0;


char reko[CHUNK];
int _tmain(int argc, _TCHAR* argv[])
{

		unsigned long dsize = CHUNK;
	unsigned long dsize2 = CHUNK;
	compress2((Bytef*)out,&dsize,(Bytef*)data,strlen(data),9);
	uncompress((Bytef*)reko,&dsize2,(Bytef*)out,dsize);
	return 0;
}

