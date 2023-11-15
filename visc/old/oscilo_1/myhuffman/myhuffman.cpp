// myhuffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#include "cdef.h"

#include "prioque.h"
#include "counterque.h"
#include "hufftree.h"
#include "bitstream.h"

using namespace sg;

class MyQueItem :  public CounterQueItem
{
public:
	u8 data;
	MyQueItem(u8 d):data(d){}
	virtual i8 Compare(QueItem *i)
		{
			return 1;
		}
	virtual void Proc(u8 a)
	{
		switch(a)
		{
		case 0:
			printf("%c(%d)  ",data,prio);
			break;

		case 1:

			break;

		}

	}
	virtual u8 CompareData(CounterQueItem *i)
	{
		if( data ==	((MyQueItem*)i)->data) return 0;
		return 1;
	}
	virtual u8 GetData(void){return data;}
};

int _tmain(int argc, _TCHAR* argv[])
{

	if(argc!=4)
	{
		printf(" -c/d in out\n");
		return 1;
	}
	FILE *f;
	u8 mode;
	if(argv[1][0]=='c') mode = 'c';
	else if(argv[1][0]=='d') mode = 'd';
	else 
	{
		printf("d/c\n");
		return 0;
	}

	if(!(f=_wfopen(argv[2],L"rb"))) return 2;

	u32 size;
	fseek(f,0,SEEK_END);
	size = ftell(f);
	fseek(f,0,SEEK_SET);

	u8 *buff = new u8[size];
	fread(buff,size,1,f);
	fclose(f);


	if(mode=='c')
	{
		
		u8 *p = buff;
		CounterQue q;
		u32 ii=size;
		while(ii--)
		{
			q.Add(new MyQueItem(*p++));		
		}

		q.Sort();
		q.ForEach();

		HuffTree h;
		h.Init(&q);
		h.ForEach();

		h.BuildTree();
		printf("\ntree\n");
		h.PrintTree2(h.root);
		CHuffTree ch;
		ch.Init(&h);

		printf("\nc tree\n");
		ch.ForEach(1);

		printf("\n code lengths \n");
		ch.PrintLengths();
		ch.BuildTree();

		// now the list can be resorted
		ch.BSort();
		ch.PrintLengths2();

		printf("\n reconstructed canonical huffman tree \n");
		ch.PrintTree2(ch.root);
		BitStream s(size*2);	

		ch.WriteTreeInfo(&s);
		ch.WriteBuffer(buff,size,&s);
		

		FILE *z;
		if(!(z=_wfopen(argv[3],L"wb"))) return 0;
		if(s.wbi!=0)s.wi++;
		fwrite(s.buffer,s.wi,1,z);
		fclose(z);
		/*
		u8 decbuff[100];
		CHuffTree rt;
		rt.ReadTreeInfo(&s);
		printf("----------------------\n");
		rt.PrintLengths2();
		rt.BuildTree();
		ch.BSort();
		rt.PrintTree2(rt.root);
		rt.ReadBuffer(decbuff,size,&s);
		decbuff[size]=0;
		printf("reconstructed string: %s\n",decbuff);*/
	}
	else if(mode=='d')
	{

		if(!(f=_wfopen(argv[2],L"rb"))) return 2;

		u32 size;
		fseek(f,0,SEEK_END);
		size = ftell(f);
		fseek(f,0,SEEK_SET);

		u8 *buff = new u8[size];
		fread(buff,size,1,f);
		fclose(f);



		
		CHuffTree rt;
		BitStream s(1);	
		s.buffer = buff;
		s.size = size;

		u32 dsize;
		rt.ReadTreeInfo(&s,&dsize);
		printf("----------------------\n");
		rt.PrintLengths2();
		rt.BuildTree();		
		rt.PrintTree2(rt.root);
		u8 *decbuff = new u8[dsize+1];
		rt.ReadBuffer(decbuff,&dsize,&s);
		decbuff[dsize]=0;
		printf("reconstructed string: %s\n",decbuff);

		FILE *uz;
		if(!(uz=_wfopen(argv[3],L"wb"))) return 0;
		fwrite(decbuff,dsize,1,uz);
		fclose(uz);
	}

	return 0;
}



