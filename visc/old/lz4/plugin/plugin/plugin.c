// plugin.cpp : Defines the entry point for the DLL application.
//

#include "wcxhead.h"
#include <stdlib.h>
#include <stdio.h>
#include ".\lz4\lz4.h"


BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	return TRUE;
}

FILE *gcf;
char gfilename[255];
char gcnt = 0;

static void extract_name(char *src, char * dest)
{
	char *p;
	int len = strlen(src);
	p = src + len;
	while(*p!='\\')
	{
		if(p == src) return;
		p--;
	}
	p++;
	while(*p!='.')
	{
		*dest++=*p++;
	}
	*dest++=*p++;
	while(*p!='.')
	{
		*dest++=*p++;
	}
	*dest = 0;
}


HANDLE __declspec(dllexport) __stdcall OpenArchive (tOpenArchiveData *ArchiveData)
{
	gcf = fopen(ArchiveData->ArcName,"rb");
	if(!gcf)
	{
		ArchiveData->OpenResult = E_EOPEN;
		return (HANDLE)0;
	}
	strcpy(gfilename,ArchiveData->ArcName);
	gcnt = 0;
	return (HANDLE)4;// unique handle
}

int __declspec(dllexport) __stdcall ReadHeader (HANDLE hArcData, tHeaderData *HeaderData)
{
	static char buff[260];
	extract_name(gfilename,buff);
	strcpy(HeaderData->ArcName,buff);
	strcpy(HeaderData->FileName,buff);
	//HeaderData->FileAttr = 0x3f;
	//HeaderData->HostOS = 0;
	HeaderData->PackSize = 500;
	HeaderData->UnpSize = 1000;
	//HeaderData->FileTime = 1 << 21 | 1 << 16; 
	HeaderData->FileTime = (2014 - 1980) << 25 | 11 << 21 | 1 << 16 | 1 << 11 | 1 << 5 | 1/2;
	gcnt++;
	if(gcnt==1)	return 0;
	else
		return E_END_ARCHIVE;
}

int __declspec(dllexport) __stdcall  ProcessFile (HANDLE hArcData, int Operation, char *DestPath, char *DestName)
{
	return 0;
}

int __declspec(dllexport) __stdcall  CloseArchive (HANDLE hArcData)
{
	if(!gcf) return E_ECLOSE;
	fclose(gcf);
	gcf=NULL;
	gcnt = 0;
	return 0;
}

void  __declspec(dllexport) __stdcall SetChangeVolProc (HANDLE hArcData, tChangeVolProc pChangeVolProc1)
{
}

void  __declspec(dllexport) __stdcall SetProcessDataProc (HANDLE hArcData, tProcessDataProc pProcessDataProc)
{
}

int  __declspec(dllexport) __stdcall GetPackerCaps()
{
	return PK_CAPS_NEW;
}

int __declspec(dllexport) __stdcall PackFiles (char *PackedFile, char *SubPath, char *SrcPath, char *AddList, int Flags)
{
	/*FILE *pF;
	pF = fopen(PackedFile,"wt");
	if(!pF) return E_ECREATE;
	fprintf(pF,"Archive name: %s\n",PackedFile);
	fprintf(pF,"Orig file name: %s\n",AddList);
	fclose(pF);*/

	unsigned long size,compsize,csize;
	FILE *f, *cf;
	char *ib,*ob;
	char head[]="LZ4";
	char ifn[255];
	strcpy(ifn,SrcPath);
	strcat(ifn,AddList);

	f = fopen(ifn,"rb");
	if(!f) return E_EOPEN;
	fseek(f,0,SEEK_END);
	size = ftell(f);
	fseek(f,0,SEEK_SET);


	compsize = LZ4_compressBound(size);
	ib = (char*)malloc(size);
	ob = (char*)malloc(compsize);

	fread(ib,size,1,f);
	fclose(f);

	csize=LZ4_compressHC(ib,ob,size);
	cf=fopen(PackedFile,"wb+");
	if(!cf) return E_ECREATE;
	fwrite(head,3,1,cf);
	fwrite(&size,4,1,cf);
	fwrite(ob,csize,1,cf);
	fclose(cf);

	free(ib);
	free(ob);	

	return 0;
}