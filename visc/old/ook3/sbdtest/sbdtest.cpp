// sbdtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

extern "C"
{
#include "cdef.h"
	void sbd_decode(u16 time);
}

u8 text[] = "12345678";

#define noise_amp	(100)

int _tmain(int argc, _TCHAR* argv[])
{
	u16 t;
	sbd_decode(2000+rand()%3000);
	for(u8 i=0;i<160;i++)
	{
		sbd_decode(rand()%4000);
	}

	sbd_decode(2000);
	for(u8 i=0;i<8;i++)
		for(u8 j=0;j<8;j++)
		{
			if(text[i]&(1<<(7-j)))
				t = 1000;
			else
				t = 500;

			t+=rand()%noise_amp-noise_amp/2;
			sbd_decode(t);
		}
		return 0;
}

