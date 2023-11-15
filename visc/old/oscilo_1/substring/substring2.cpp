// substring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

u32 in[]={1,2,3,1,1,};

#define lenbits		(11)
#define offsetbits	(13)

u32 codelen(u16 len, u16 offset, u8 lb)
{
	u32 res;
	u32 lenmask = pow(2.0,lb)-1;
	u32 offsetmask = pow(2.0,24-lb)-1;
	res = ((len & lenmask)<<(24-lb)) | (offset & offsetmask);
	return res;
}
void decodelen(u8 lb, u32 code, u16 *len, u16 *offset)
{
	u32 lenmask = pow(2.0,lb)-1;
	u32 offsetmask = pow(2.0,24-lb)-1;
	
	*len = (u16)((code >> (24-lb)) & lenmask);
	*offset = (u16)(code & offsetmask);	
}


u16 bruteforce(u8 *in, u8 *out)
{
	u32 complen = 0;
	u8 *c = in;
	u16 offset = 0;
	while(*c)
	{
		u8 *s = in;		
		u16 ml = 1;
		u16 o = 0;
		while(s < c)
		{			
			u16 l = 0;
			u8 *ss = s;
			u8 *cc = c;			

			while(*ss++ == *cc++)
			{
				l++;
				//if(l==999) break;
			}
			if(l>ml)
			{
				ml = l;
				o = s-in;
			}			
			s++;
		}		

		if(ml>1)
		{
			*out++='`';
			//*out++='0'+o;
			//*out++='0'+ml;
			out+=sprintf((char*)out,"%03d",o);
			out+=sprintf((char*)out,"%03d",ml);
			complen +=7;
		}
		else
		{
			*out++ = *c;
			complen++;
		}
		c+=ml;
	}
	return complen;
}

u16 inflate(u8 *in, u8*out)
{
	u32 declen = 0;
	u8 *i = in;
	u8 *os = out;
	while(*i)
	{
		if(*i=='`')
		{
			int o = 0,ml = 0;
			i++;
			sscanf((char*)i,"%3d",&o);i+=3;
			sscanf((char*)i,"%3d",&ml);i+=3;
			u8 *ii = os+o;
			while(ml>0)
			{
				*out++ =*ii++;
				declen++;
				ml--;
			}
		}
		else
		{
			*out++=*i++;
			declen++;
		}		
	}
	return declen;
}

u8 rec[300] = {0};
int _tmain(int argc, _TCHAR* argv[])
{
	u32 a1 = codelen(1,2,8);
	u16 len, offset;
	//	void decodelen(u8 lb, u32 code, u16 *len, u16 *offset)
	decodelen(8,a1,&len,&offset);

	return a1;
}

