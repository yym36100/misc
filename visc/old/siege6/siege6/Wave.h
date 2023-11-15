#pragma once
#include "cdef.h"
#include "math.h"

#include "nco.h"
#include "surface.h"

#define pi 3.14159265

class CWave
{
public:
	CNCO *pnco;
	u32 size;
	u32 amp,freq,phase;
	i16 *pBuff;
	siege::CSurface *pS;
	u8 *wd;
	u16 maxi;
		



	CWave(siege::CSurface *sr,u32 s,u16 amp, u32 freq,u32 freq2)
		:pS(sr),amp(amp),freq(freq),phase(phase)
	{
		pnco = new CNCO();
		wd = new u8[pS->w*pS->h];

		memset(wd,0,pS->w*pS->h);
		size = s;
		pBuff = new i16[size];

		CNCO c1,c2;
		c1.setFreq(freq);
		c2.setFreq(freq2);

		for(u32 i=0;i<size;i++)
		{
			//pBuff[i] = (i16)(amp * sin ( 2*pi*freq*i /(double)size + 2*pi/360) * sin ( 2*pi*freq2*i /(double)size + 2*pi/360));
			pBuff[i] = (i16)(amp *c1.getVal()/(double)c1.MAX_AMPL );//* c2.getVal()/(double)c2.MAX_AMPL);
		}
		maxi=0;

	}

	~CWave(void)
	{
		if(pBuff) delete[] pBuff;
		if(wd) delete[] wd;
		delete pnco;
	}

	void DrawGrid(void)
	{
		//pS->Clear(0);
		u32 gridcolor = 0xff303030;
		u32 centercolor= 0xff606060;
		u16 ystep =40;
		u16 xstep =40;
		u16 h = pS->h;
		u16 w = pS->w;
		u16 my = h/2;
		u16 mx = w/2;

		pS->DrawLine(0,my,w-1,my,centercolor);
		pS->DrawLine(mx,0,mx,h-1,centercolor);

		for(u16 y=ystep;y<h/2;y+=ystep)
		{

			//draw h lines
			pS->DrawLine(0,my+y,w-1,my+y,gridcolor);
			pS->DrawLine(0,my-y,w-1,my-y,gridcolor);

		}
		for(u16 x=xstep;x<w/2;x+=xstep)
		{
			//draw w lines
			pS->DrawLine(mx+x,0,mx+x,h-1,gridcolor);
			pS->DrawLine(mx-x,0,mx-x,h-1,gridcolor);
		}

	}
	void Display(void)
	{
		pS->Clear(0);
		u32 tracecolor = 0xffff80ff;
		

		u32 len = size;
		u16 mid = pS->h/2;

		double nrpp = size/(double)pS->w;
		
		u32 i=0;

		while(i<len)
		//for(u16 i=0;i<len-1;i+=nrpp)		
		{
			i+=1;
			pS->SetPixel(i/nrpp,mid+pBuff[i],tracecolor);
			//pS->DrawLine(i/nrpp,mid+pBuff[i],(i/nrpp)+1,mid+pBuff[i+1],tracecolor);
		}
		DrawGrid();
	}
	void Display3(void)
	{
		pS->Clear(0);
		u32 tracecolor = 0xffff80ff;
		

		u32 len = size;
		u16 mid = pS->h/2;

		double nrpp = size/(double)pS->w;
		
		u32 i=0;

		while(i<len)
		//for(u16 i=0;i<len-1;i+=nrpp)		
		{
			i+=1;
			//pS->SetPixel(i/nrpp,mid+pBuff[i],tracecolor);
			pS->DrawLine(i/nrpp,mid+pBuff[i],(i/nrpp)+1,mid+pBuff[i+1],tracecolor);
		}
		DrawGrid();
	}
	
	void SetPixel(u16 x, u16 y,u8 i)
	{		
		*(wd+x+y*pS->w)=i;
	}
	//void 
	void Display2(void)
	{
		pS->Clear(0);
		u32 tracecolor = 0xffff80ff;
		

		u32 len = size;
		u16 mid = pS->h/2;

		double nrpp = size/(double)pS->w;
		
		u32 i=0;
		volatile i16 intensity = 0;
		volatile u8 bp=0;
		u8 psi;
		u8 rr,gg,bb;
		float fsi;
		
		while(i<len)		
		{
			i+=1;
			intensity = pBuff[i] - pBuff[i+1];
			psi = intensity>0?intensity:-intensity;
			fsi = psi/2.5;

			rr = 0xff/(fsi+1);
			gg = 0x80/(fsi+1);
			bb = 0xff/(fsi+1);
			
		
			pS->DrawVLine(i/nrpp,mid+pBuff[i],mid+pBuff[i+1],
				(0xff<<24)|(rr<<16)|(gg<<8)|(bb<<0)
				);
		}
		DrawGrid();
	}
};
