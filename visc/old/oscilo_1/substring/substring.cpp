// substring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

char hash[65535] = {0};

void subs(u8 *in, u8 *out)
{
	u8 *i = in;
	u16 offset = 0;
	while(*i)
	{
		if(i+1)
		{
			u16 index = ((*i)<<8)|(*(i+1));
			if(hash[index] == 0)
			{
				//not found, just add to hash
				hash[index] = offset +1;
				*out++ = *i;
			}
			else
			{
				// hash found, add reference
				//get match length
				u16 l = 0;
				u8 *ii =in + hash[index] - 1, *cc = i;
				while(*ii++ == *cc++)
				{
					l++;
				}
				*out++='#';
				*out++='0'+hash[index]-1;
				*out++='0'+l;
				i+=l-1;
			}
		}

		offset++;
		i++;
	}
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
	u8 in[] = "ab ab abc ab ab abc abc abc ab ab abc";
	u8 out[300] = {0};
	

	bruteforce(in,out);
	printf("0123456789012345678901234567890123456789\n");
	printf("%s\n",in);
	printf("%s\n",out);
	inflate(out,rec);
	printf("rec\n");
	printf("%s\n",in);
	printf("%s\n",rec);
	return 0;

	/*FILE *inFile,*outFile;

	if( argv[1][0] == 'c')
	{
		inFile = fopen(argv[2],"rb");
		unsigned long inFileSize;
		fseek(inFile,0,SEEK_END);
		inFileSize = ftell (inFile);
		fseek(inFile,0,SEEK_SET);

		u8 *in = new u8[inFileSize+1];
		in[inFileSize] = 0;
		u8 *out = new u8[inFileSize*2];
		fread(in,inFileSize,1,inFile);
		u16 len;
		len = bruteforce(in,out);
		outFile = fopen(argv[3],"wb");
		fwrite(out,len,1,outFile);
		fclose(inFile);
		fclose(outFile);
	}
	else
	{
		inFile = fopen(argv[2],"rb");
		unsigned long inFileSize;
		fseek(inFile,0,SEEK_END);
		inFileSize = ftell (inFile);
		fseek(inFile,0,SEEK_SET);

		u8 *in = new u8[inFileSize+1];
		in[inFileSize] = 0;
		u8 *out = new u8[inFileSize*2];
		fread(in,inFileSize,1,inFile);
		u16 len;
		len = inflate(in,out);
		outFile = fopen(argv[3],"wb");
		fwrite(out,len,1,outFile);
		fclose(inFile);
		fclose(outFile);
	}*/
}

