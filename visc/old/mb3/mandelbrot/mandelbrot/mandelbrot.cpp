// mandelbrot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "mandelbrot.h"

#include <windows.h>

#include <atlimage.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


typedef unsigned char u8;
typedef unsigned short u16;
typedef  signed short i16;
typedef unsigned long u32;
typedef double db;


void drawset3(db sx,db ex, db sy, db ey,u16 ssx, u16 eex, u16 ssy, u16 eey);
double sx,ex, sy,ey;

#define ww 1920
#define hh 1080
#define www ((double)ww)
#define hhh ((double)hh)
#define limit  256.0*2

u8 manset[ww*hh];
u8 pause =0;
i16 zl=0,zz=1;

u8 min=0xff,max=0,p;
static u32 colors1[256];
static u32 colors2[256];
static u32 colors3[256];
static u32 colors4[256];
static u32 colors5[256];
static u32 colors6[256];
u32 *colp=colors1;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szWindowClass[50];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
CImage image;	

int pi ;
u8 *dpo ;
void setpixel(u16 x, u16 y,u32 color);
u8 colorrotate=0;

HANDLE threadhandles[9]={0};
DWORD WINAPI Thread_no_0( LPVOID lpParam );

DWORD WINAPI Thread_no_1( LPVOID lpParam );
DWORD WINAPI Thread_no_2( LPVOID lpParam );
DWORD WINAPI Thread_no_3( LPVOID lpParam );
DWORD WINAPI Thread_no_4( LPVOID lpParam );
DWORD WINAPI Thread_no_5( LPVOID lpParam );
DWORD WINAPI Thread_no_6( LPVOID lpParam );
DWORD WINAPI Thread_no_7( LPVOID lpParam );
DWORD WINAPI Thread_no_8( LPVOID lpParam );

volatile int tgo[9];
HWND gWnd;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//image.Create(ww,hh,32,CImage::createAlphaChannel);
	image.Create(ww,hh,32,0);

	pi =  image.GetPitch();
	dpo = (u8*)image.GetBits();


	threadhandles[0] = CreateThread( NULL, 0, 
		Thread_no_0, NULL, 0, NULL);  

	threadhandles[1] = CreateThread( NULL, 0, 
		Thread_no_1, NULL, 0, NULL);  
	threadhandles[2] = CreateThread( NULL, 0, 
		Thread_no_2, NULL, 0, NULL);  
	threadhandles[3] = CreateThread( NULL, 0, 
		Thread_no_3, NULL, 0, NULL);  
	threadhandles[4] = CreateThread( NULL, 0, 
		Thread_no_4, NULL, 0, NULL);


	threadhandles[5] = CreateThread( NULL, 0, 
		Thread_no_5, NULL, 0, NULL);  
	threadhandles[6] = CreateThread( NULL, 0, 
		Thread_no_6, NULL, 0, NULL);  
	threadhandles[7] = CreateThread( NULL, 0, 
		Thread_no_7, NULL, 0, NULL);  
	threadhandles[8] = CreateThread( NULL, 0, 
		Thread_no_8, NULL, 0, NULL);  


	sx = -2, ex = 2; sy = -2*hhh/www, ey = 2*hhh/www;

	LoadString(hInstance, IDC_MANDELBROT, szWindowClass, 50);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	SetTimer(gWnd,101,20,0);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MANDELBROT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}

void setpixel(u16 x, u16 y,u32 color)
{
	u8 *dp = dpo + y*pi + x*4;
	*dp++ = (color>>24)&0xff;
	*dp++ = (color>>16)&0xff;
	*dp++ = (color>>8)&0xff;				
	*dp++ = color&0xff;
}

u8 getpixel(u16 x, u16 y)
{
	u8 *dp = dpo + y*pi + x*4;
	return((*dp) )&0xff;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MANDELBROT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;//MAKEINTRESOURCE(IDC_MANDELBROT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, L"Mandelbrot", WS_OVERLAPPEDWINDOW,
		500, 22, www+10, hhh+20, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	gWnd = hWnd;

	return TRUE;
}


u16 fcx,fcy;
double cx, cy;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_TIMER:
		{
#define zzz 1.001
			if(tgo[0]==0 && zz ==0)
			{
				sx*=zzz;ex*=zzz;
				sy*=zzz;ey*=zzz;
				tgo[0]=1;

			}
			if(tgo[0]==0 && pause ==0){
				colorrotate++;
			tgo[0]=2;
			}
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			image.Draw(hdc,0,0);
			/*RECT r={0,0,500,100};
			char sss[100];
			wchar_t wsss[100];
			sprintf(sss,"sx %f ex %f\nsy %f ey %f \n cx %f cy %f",sx,ex,sy,ey,cx,cy);
			u8 i=0;
			while(wsss[i]=sss[i])i++;
			DrawText(hdc,wsss,i,&r,0);*/

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		{zl++;

			int x,y;
			x = LOWORD (lParam) ;
			y = HIWORD (lParam) ;

			u16 xp,yp;
			db dx,dy;
			// double the range
			dx=x/www*(ex-sx)+sx;
			dy=y/hhh*(ey-sy)+sy;
			cx=dx;
			cy=dy;

			sx+=dx;ex+=dx;
			sy+=dy;ey+=dy;

#define divfac 2
			sx/=divfac;ex/=divfac;
			sy/=divfac;ey/=divfac;

			tgo[0]=1;
		}
		break;
	case WM_RBUTTONDOWN:
		{
			zl--;
			int x,y;
			x = LOWORD (lParam) ;
			y = HIWORD (lParam) ;

			u16 xp,yp;
			db dx,dy;
			// double the range


			dx=x/www*(ex-sx)+sx;
			dy=y/hhh*(ey-sy)+sy;

			cx=dx;
			cy=dy;

			dx/=2;dy/=2;
			sx-=dx;ex-=dx;
			sy-=dy;ey-=dy;
			sx*=divfac;ex*=divfac;
			sy*=divfac;ey*=divfac;


			tgo[0]=1;
		}
		break;
	case WM_MBUTTONDOWN:
		{
			/*	sx=-2;ex=+2;
			sy=-2;ey=+2;
			drawset2(sx,ex,sy,ey);
			InvalidateRect(hWnd,0,true);*/
			fcx = LOWORD (lParam) ;
			fcy = HIWORD (lParam) ;
		}
		break;
	case WM_MOUSEMOVE:

		if(wParam & MK_MBUTTON)
		{
			u16 x = LOWORD (lParam) ;
			u16 y = HIWORD (lParam) ;
			db dx, dy;
			dx=(fcx-x)/www*(ex-sx);
			dy=(fcy-y)/hhh*(ey-sy);
			cx=dx;
			cy=dy;
			sx+=dx;ex+=dx;
			sy+=dy;ey+=dy;

			tgo[0]=1;

			fcx=x;fcy=y;

		}
		else{
			int x,y;
			x = LOWORD (lParam) ;
			y = HIWORD (lParam) ;

			u16 xp,yp;
			db dx,dy;
			dx=x/www*(ex-sx)+sx;
			dy=y/hhh*(ey-sy)+sy;
			cx=dx;
			cy=dy;
			//	InvalidateRect(hWnd,0,false);
		}


		break;
	case WM_CHAR:
		switch(wParam)
		{
		case 49:
			colp=colors1;
			break;
				case 50:
			colp=colors2;
			break;
			case 51:
			colp=colors3;
			break;
			case 52:
			colp=colors4;
			break;
			case 53:
			colp=colors5;
			break;
			case 54:
			colp=colors6;
			break;
		case 115:
			image.Save(L"image.png");
			break;
				case 'p':
		pause ^= 1;

		break;
case 'z':
		zz ^= 1;

		break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



inline u16 checkpoint(double cx, double cy)
{
	u16 i = 0;
	register double x=cx,y=cy,xx,yy,xy;
	do{
		xx= x*x;
		yy = y*y;
		xy = x*y;
		x = xx-yy+cx;
		y = 2*xy+cy;
		i++;
	}while((xx+yy)<4.0 && i<limit);
	return i;
}


void drawset3(db sx,db ex, db sy, db ey,u16 ssx, u16 eex, u16 ssy, u16 eey)
{
	u8 *mp=manset+ssx+ww*ssy;
	u32 c;u8 cc;
	double cx,cy,cxi,cyi;;
	u8 val;
	u16 y=ssy;

	cy = y/hhh*(ey-sy)+sy;
	cyi = 1/hhh*(ey-sy);

	for(y=ssy;y<eey;y++)
	{
		u16 x=ssx;

		cx = x/www*(ex-sx)+sx;

		cxi = 1/www*(ex-sx);
		for(x=ssx;x<eex;x++)
		{
			val = checkpoint(cx,cy);cx += cxi;		
			cc = (1.0-val/limit)*0xff;

			//setpixel(x,y,c);
			*mp++ = cc;
		}
		mp+=ww-eex+ssx;
		cy +=cyi;
	}

}

DWORD WINAPI Thread_no_0( LPVOID lpParam )
{
	int tp=0;
	while(1)
	{
		Sleep(10);
		if(tgo[0]==1&& tp==0)
		{
			tgo[1]=1;tgo[2]=1;
			tgo[3]=1;tgo[4]=1;
			tgo[5]=1;tgo[6]=1;
			tgo[7]=1;tgo[8]=1;
			tgo[0]=0;
			tp=1;
		}

		if(tgo[0]==2&& tp==0)
		{

			tgo[0]=0;
				void colorize(void);
			//';'autolevel();
			colorize();
			InvalidateRect(gWnd,NULL,false);
		}
		if(tgo[1]==0 && tgo[2]==0 && tgo[3]==0 && tgo[4]==0 && tgo[5]==0 && tgo[6]==0 && tgo[7]==0 && tgo[8]==0 &&  tp==1)
		{
			void autolevel(void);
			void colorize(void);
			autolevel();
			colorize();
			InvalidateRect(gWnd,NULL,false);
			tp=0;
		}			
	}
	return 0;
}

DWORD WINAPI Thread_no_1( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[1])
		{
			drawset3(sx,ex,sy,ey,0,www/2,0,hhh/4);
			tgo[1]=0;
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI Thread_no_2( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[2])
		{
			drawset3(sx,ex,sy,ey,0,www/2,hhh/4,2*hhh/4);
			tgo[2]=0;
		}
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI Thread_no_3( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[3])
		{
			drawset3(sx,ex,sy,ey,0,www/2,2*hhh/4,3*hhh/4);
			tgo[3]=0;
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI Thread_no_4( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[4])
		{
			drawset3(sx,ex,sy,ey,0,www/2,3*hhh/4,4*hhh/4);
			tgo[4]=0;
		}
		Sleep(10);
	}
	return 0;
}


DWORD WINAPI Thread_no_5( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[5])
		{
			drawset3(sx,ex,sy,ey,www/2,www,0,hhh/4);
			tgo[5]=0;
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI Thread_no_6( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[6])
		{
			drawset3(sx,ex,sy,ey,www/2,www,hhh/4,2*hhh/4);
			tgo[6]=0;
		}
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI Thread_no_7( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[7])
		{
			drawset3(sx,ex,sy,ey,www/2,www,2*hhh/4,3*hhh/4);
			tgo[7]=0;
		}
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI Thread_no_8( LPVOID lpParam )
{
	while(1)
	{
		if(tgo[8])
		{
			drawset3(sx,ex,sy,ey,www/2,www,3*hhh/4,4*hhh/4);
			tgo[8]=0;
		}
		Sleep(10);
	}
	return 0;
}


void autolevel(void)
{
	
	u32 c,cc;
	u8 *mp=manset;
	static int palette = 0;
	

	if(palette ==0)
	{
		palette =1;
		FILE *f;
		f=fopen("palette.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors1[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors1[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}

		f=fopen("gold.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors2[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors2[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}

		f=fopen("coolblue.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors3[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors3[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}

		f=fopen("kekrozsda.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors4[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors4[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}

		f=fopen("blueredyellow.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors5[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors5[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}

		f=fopen("skyland.raw","rb");
		if(!f)
		{
			for(int i=0;i<256;i++)
			{
				colors6[i]=0xff+(i<<8)+(i<<16)+(i<<24);
			}
		}
		else
		{
			u8 buff[768];
			fread(buff,768,1,f);
			fclose(f);
			for(int i=0;i<256;i++)
			{
				colors6[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
			}

		}
	}
	for(u16 y=0;y<hhh;y++)
		for(u16 x=0;x<www;x++)
		{
			//p=getpixel(x,y);
			p=*mp++;
			min=min<p?min:p;
			max=max>p?max:p;
		}
		if(max==0)max=1;
		if(max==min)max++;

		mp=manset;
		for(u16 y=0;y<hhh;y++)
			for(u16 x=0;x<www;x++)
			{
				//p=getpixel(x,y);
				p=*mp;
				cc = (p-min)*255/(max-min);
				cc=cc>0xff?0xff:cc;
				//cc=p;
				//c = colors[(cc+colorrotate)&0xff];
				//setpixel(x,y,c);
				*mp++=cc;
			}
}
void colorize(void)
{
	u8 *mp=manset;
	u32 c,cc;
		for(u16 y=0;y<hhh;y++)
			for(u16 x=0;x<www;x++)
			{
				cc=*mp++;
				c = colp[(cc+colorrotate)&0xff];
				setpixel(x,y,c);
			}
}
