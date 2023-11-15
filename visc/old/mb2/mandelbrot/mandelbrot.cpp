// mandelbrot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "mandelbrot.h"

#include <windows.h>

#include <atlimage.h>
#include <gdiplus.h>
#include <math.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef double db;

#define MAX_LOADSTRING 100

void drawset();
void drawset2(db sx,db ex, db sy, db ey);
void drawset3(db sx,db ex, db sy, db ey,u16 ssx, u16 eex, u16 ssy, u16 eey);
double sx,ex, sy,ey;

#define www 1920.0
#define hhh 720.0
#define limit 256.0*4.0
//#define limit 15.0

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
CImage image,image2;	

int pi ;
u8 *dpo,*dpo2 ;
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
volatile int  dummy = 0x1234;
volatile int  ssd = 0;

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

	image.Create(www,hhh,32,CImage::createAlphaChannel);
	image2.Create(www,hhh,32,CImage::createAlphaChannel);

	{
		u8 r,g,b,a;		
		pi =  image.GetPitch();
		dpo = (u8*)image.GetBits();
		dpo2 = (u8*)image2.GetBits();
		u8 *dp = dpo;
		ssd = 0;

		for(u16 y=0;y<hhh;y++)		
		{
			for(u16 x=0;x<www;x++)
			{
				a = 0xff;
				b = 0x00;
				g = 0x00;
				r = 0x00;

				*dp++ = b;
				*dp++ = g;
				*dp++ = r;
				*dp++ = 0xff;				
			}
			dp+=2*pi;
		}
	}

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

	//setpixel(200,200,0xffffffff);
	//setpixel(100,100,0xffff);
	//	drawset();
	//void drawset2(db sx,db ex, db sy, db ey)
	//double sx,ex, sy,ey;
	sx = -2, ex = 2; sy = -2*0.36, ey = 2*0.36;

	//1980 720 
	//			drawset2(-2,2,-2,2);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MANDELBROT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	SetTimer(gWnd,101,1000/50,0);

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

void setpixel2(u16 x, u16 y,u32 color)
{
	u8 *dp = dpo2 + y*pi + x*4;
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


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
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

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		500, 922, www+8, hhh+20, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	gWnd = hWnd;

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
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
			colorrotate++;
			if(tgo[0]==0)
			{
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
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
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
			image2.Draw(hdc,0,0);
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
		{
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




			/*drawset3(sx,ex,sy,ey,0,www,0,hhh);
			InvalidateRect(hWnd,0,true);*/
			tgo[0]=1;
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int x,y;
			x = LOWORD (lParam) ;
			y = HIWORD (lParam) ;

			u16 xp,yp;
			db dx,dy;
			// double the range

			/*sx*=divfac;ex*=divfac;
			sy*=divfac;ey*=divfac;*/

			dx=x/www*(ex-sx)+sx;
			dy=y/hhh*(ey-sy)+sy;

			cx=dx;
			cy=dy;

			/*sx = cx-(ex-sx)/2.0;ex = cx+(ex-sx)/2.0;
			sy = cy-(ey-sy)/2.0;ey = cy+(ey-sy)/2.0;*/

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
			//			drawset2(sx,ex,sy,ey);
			//InvalidateRect(hWnd,0,true);
			tgo[0]=1;

			fcx=x;fcy=y;

		}
		else{
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
			//	InvalidateRect(hWnd,0,false);
		}


		break;
	case WM_CHAR:
		if(wParam==115)
		{ 
			image.Save(L"image.png");
		}
		//cx++;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
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
	//}while(x<2.0 && y<2.0 && i<limit);
	return i;
}

inline u16 checkpoint2(double cx, double cy)
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
	//}while(x<2.0 && y<2.0 && i<limit);
	return i+1.0 - log(log(sqrt(xx+yy)))/log(2.0);
}

void drawset()
{
	u32 c;
	u8 cc;
	for(u16 y=0;y<400;y++)
	{
		for(u16 x=0;x<400;x++)
		{
			double cx,cy;
			u8 val;
			cx = x/400.0*4-2;
			cy = y/400.0*4-2;
			val = checkpoint(cx,cy);
			/*	if(val>150)
			c = 0xffffffff;
			else c = 0xff;*/

			cc = (1.0-val/200.0)*0xff;
			c = 0xff + (cc<<8)+(cc<<16)+(cc<<24);

			setpixel(x,y,c);
		}
	}
}
//24
static u8 Colors[] = {
	182,182,255, 198,182,255, 218,182,255, 234,182,255, 255,182,255,
	255,182,234, 255,182,218, 255,182,198, 255,182,182, 255,198,182,
	255,218,182, 255,234,182, 255,255,182, 234,255,182, 218,255,182,
	198,255,182, 182,255,182, 182,255,198, 182,255,218, 182,255,234,
	182,255,255, 182,234,255, 182,218,255, 182,198,255};

	u8 bitrev(u8 i)
	{
		return 
			((i&1)<<7)+
			((i&2)<<6)+
			((i&4)<<5)+
			((i&8)<<4)+
			((i&0x10)<<3)+
			((i&0x20)<<2)+
			((i&0x40)<<1)+
			((i&0x80)<<0);		
	}

	void drawset2(db sx,db ex, db sy, db ey)
	{
		u32 c;u8 cc;
		for(u16 y=0;y<400;y++)
		{
			for(u16 x=0;x<400;x++)
			{
				double cx,cy;
				u8 val;
				cx = x/400.0*(ex-sx)+sx;
				cy = y/400.0*(ey-sy)+sy;
				val = checkpoint(cx,cy);
				/*if(val>50)
				c = 0xffffffff;
				else c = 0xff;*/

				/*cc = (1.0-val/limit)*0xff;
				c = 0xff + (cc<<8)+(cc<<16)+(cc<<24);*/

				/*cc = (1.0-val/limit)*24*3;
				c = 0xff + (Colors[cc+0]<<8)+(Colors[cc+1]<<16)+(Colors[cc+2]<<24);*/

				cc = (1.0-val/limit)*0xff;
				//cc = bitrev(cc);
				c = 0xff + (cc<<8)+(cc<<16)+(cc<<24);

				setpixel(x,y,c);
			}
		}
	}
	void drawset3(db sx,db ex, db sy, db ey,u16 ssx, u16 eex, u16 ssy, u16 eey)
	{
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
				//cc = bitrev(cc);
				c = 0xff + (cc<<8)+(cc<<16)+(cc<<24);

				setpixel(x,y,c);
			}
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
				ResumeThread(threadhandles[1]);
				ResumeThread(threadhandles[2]);
				ResumeThread(threadhandles[3]);
				ResumeThread(threadhandles[4]);
				ResumeThread(threadhandles[5]);
				ResumeThread(threadhandles[6]);
				ResumeThread(threadhandles[7]);
				ResumeThread(threadhandles[8]);
				
			}

			if(tgo[0]==2&& tp==0)
			{

				tgo[0]=0;
				void colorize(void);
				colorize();
				InvalidateRect(gWnd,NULL,false);
			}
			if(tgo[1]==0 && tgo[2]==0 && tgo[3]==0 && tgo[4]==0 && tgo[5]==0 && tgo[6]==0 && tgo[7]==0 && tgo[8]==0 &&  tp==1)
			{
				void autolevel(void);
				autolevel();
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
			SuspendThread(threadhandles[1]);
			//Sleep(10);
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
			SuspendThread(threadhandles[2]);
			//Sleep(10);
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
			SuspendThread(threadhandles[3]);
			//Sleep(10);
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
			SuspendThread(threadhandles[4]);
			//Sleep(10);
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
			SuspendThread(threadhandles[5]);
			//Sleep(10);
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
			SuspendThread(threadhandles[6]);
			//Sleep(10);
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
			SuspendThread(threadhandles[7]);
			//Sleep(10);
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
			SuspendThread(threadhandles[8]);
			//Sleep(10);
		}
		return 0;
	}

	static u8 lmin,lmax=255;

	static u32 colors[256];

	void autolevel(void)
	{
		u8 min=0xff,max=0,p;
		u32 c,cc;		



		if(ssd == 0)
		{
			ssd =1;
			FILE *f;
			f=fopen("palette.raw","rb");
			if(!f)
			{
				for(int i=0;i<256;i++)
				{
					colors[i]=0xff+(i<<8)+(i<<16)+(i<<24);
				}
			}
			else
			{
				u8 buff[768];
				fread(buff,768,1,f);
				fclose(f);
				for(int i=0;i<256;i++)
				{
					colors[i]=0xff+(buff[i*3+0]<<8)+(buff[i*3+1]<<16)+(buff[i*3+2]<<24);
				}

			}
		}
		for(u16 y=0;y<hhh;y++)
			for(u16 x=0;x<www;x++)
			{
				p=getpixel(x,y);
				min=min<p?min:p;
				max=max>p?max:p;
			}

			if(max==0)max=1;
			if(max==min)max++;
			lmin=min;
			lmax=max;

			for(u16 y=0;y<hhh;y++)
				for(u16 x=0;x<www;x++)
				{
					p=getpixel(x,y);
					cc = (p-min)*255/(max-min);
					cc=cc>0xff?0xff:cc;
					//cc=p;
					c = colors[(cc)&0xff];
					setpixel2(x,y,c);
				}
	}

	void colorize(void)
	{
		u32 c,cc;	
		u8 p;
		for(u16 y=0;y<hhh;y++)
			for(u16 x=0;x<www;x++)
			{
				p=getpixel(x,y);
				cc = (p-lmin)*255/(lmax-lmin);
				cc=cc>0xff?0xff:cc;
				//cc=p;
				c = colors[(cc+colorrotate)&0xff];
				setpixel2(x,y,c);
			}
	}