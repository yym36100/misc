#pragma once

#include "cdef.h"
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <math.h>

#include "obj.h"
#include "surface.h"
#include "winsurface.h"
//#include ".\widgets\widget.h"
#include ".\widgets\TextWidget.h"
#include ".\widgets\ButtonWidget.h"
#include ".\widgets\BitmapWidget.h"
#include ".\widgets\Container.h"
#include ".\widgets\GraphWidget.h"
#include ".\resources\gimphead.h"

#include "Events.h"

#include "..\resource.h"



#define FFT_SIZE  1024
#define log2FFT   10
#define N         (2 * FFT_SIZE)
#define log2N     (log2FFT + 1)


int fix_fftr(short f[], int m, int inverse);

namespace siege{

	class CWindow
	{
	public:
		graphics::CWinSurface *surf;
		//widgets::CTextWidget *widget;
		//widgets::CButtonWidget *bw;

		widgets::CWidget *widgetlist;
		Events *e;

		u32 style;
		HWND hWnd,parent_hWnd;
		static u8 cnt;

		BITMAPINFO BitInfo;
		HDC hDC;
		HBITMAP hBitmap;

		u8 mode ;
		u8 pause;

		u8 data;
		static u16 const graphlen = 2048;
		i16 graphdata[graphlen];
		i16 fx[graphlen];

		double pulse(double i)
		{
			i = fmod(i,2*3.1415);
			if(i<3.1415) return 1.0;
				return 0.0;

		}
		void siggen(u16 amp)
		{
			for(u16 i=0;i<graphlen;i++)
			{
				graphdata[i] =  +20*sin(2*3.1415*2*i*90/(graphlen)+0) ;//+ 60*rand()/32768.0;
				graphdata[i] +=  +60*sin(2*3.1415*2*i*amp/(graphlen*10)+0) ;//+ 60*rand()/32768.0;
				//graphdata[i] +=  +60*pulse(2*3.1415*2*i*amp/(graphlen*10)+0) ;//+ 60*rand()/32768.0;
				//graphdata[i] =  150*rand()/32768.0-70;
				
			}
		}
		void scale_fft(void)
		{
			i16 maxval = 0;
			i16 dessize = 150;
			for(u16 i =0;i<graphlen;i++)
			{
				if(fx[i]>maxval) maxval = fx[i];
			}
			double scalefact = dessize/(double)maxval;
			for(u16 i =0;i<graphlen;i++)
			{
				fx[i] = (fx[i] * scalefact)+dessize/2;
			}


		}

		CWindow(void)
		{
		}
		void copyfft(void)
		{
			for (u16 i=0; i<N; i++){			
				if (i & 0x01)
					fx[(N+i)>>1] = graphdata[i];
				else
					fx[i>>1] = graphdata[i];
				//memcpy(fx,graphdata,graphlen);

			}
		}

		CWindow(stRect r, u32 style,HWND parent_hWnd,u16 *name)
			:mode(1),pause(0)
		{
			data = 0;
			surf = new graphics::CWinSurface(r.w,r.h);
			ATOM res;
			this->parent_hWnd = parent_hWnd;
			widgetlist = NULL;

			//memset(graphdata,0,400);
			siggen(60);
			copyfft();			
			fix_fftr(fx, log2N, 0);
			scale_fft();


			HINSTANCE hInstance=GetModuleHandle(NULL);
			if(cnt==0)
			{
				WNDCLASSEX	WndClsEx;
				WndClsEx.cbSize        = sizeof(WNDCLASSEX);
				WndClsEx.style         = 0;
				WndClsEx.lpfnWndProc   = WndProcedure;
				WndClsEx.cbClsExtra    = 0;
				WndClsEx.cbWndExtra    = 0;
				WndClsEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
				WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
				WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);				
				WndClsEx.lpszMenuName  = NULL;
				WndClsEx.lpszClassName = _T("siege");
				WndClsEx.hInstance     = hInstance;
				WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
				res = RegisterClassEx(&WndClsEx);			
			}	
			RECT rr={0,0,r.w,r.h};
			AdjustWindowRect(&rr,style,FALSE);
			hWnd = CreateWindow(_T("siege"),(LPCWSTR)name,	style,r.x,r.y,rr.right-rr.left,rr.bottom-rr.top,parent_hWnd,NULL,hInstance,this);

			/*err = GetLastError();
			LPVOID lpMsgBuf;
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, err,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,	0, NULL );*/


			/*--------------------*/
			widgets::CTextWidget *tw,*tw2;
			widgets::CButtonWidget *bw1,*bw2,*bw3;//,*bw4,*bw5;
			//			widgets::CBitmapWidget *bw,*biw2,*biw3,*biw4,*biw5;
			widgets::CContainer *cc;
			widgets::CGraphWidget *gw,*gw2;

			bw1 = new widgets::CButtonWidget(surf,20,10,160,20);
			bw1->SetText((u8*)"OK");
			bw1->Focused = true;
			bw1->handle = (u32)hWnd;
			bw1->command = 0x1;

			bw2 = new widgets::CButtonWidget(surf,20,50,160,20);
			bw2->SetText((u8*)"Inc");
			bw2->handle = (u32)hWnd;
			bw2->command = 0x2;

			bw3 = new widgets::CButtonWidget(surf,20,90,160,20);
			bw3->SetText((u8*)"Dec");
			bw3->handle = (u32)hWnd;
			bw3->command = 0x3;

			tw = new widgets::CTextWidget(surf,20,130,160,20);
			tw->SetText((u8*)"Val = 3");

			tw2 = new widgets::CTextWidget(surf,20,360,360,20);
			tw2->SetText((u8*)"helper text");


			cc = new widgets::CContainer(surf,0,0,200,170);


			gw = new widgets::CGraphWidget(surf,220,20,400,150);
			gw->pData = graphdata;
			gw->size = graphlen;
			gw->plotcolor = 0xff00ffff;
			//gw->plotcolor = 0xffff00ff;//

			gw2 = new widgets::CGraphWidget(surf,220,240-50,400,150);
			gw2->pData = fx;
			gw2->size = graphlen;
			gw2->plotcolor = 0xffff00ff;
			//gw2->plotcolor = 0xffff8080;


			widgetlist = cc;
			cc->child = bw1;
			bw1->Add(bw2);			
			bw1->Add(bw3);
			bw1->Add(tw);
			bw1->Add(tw2);
			bw1->Add(gw);
			bw1->Add(gw2);

			/*-----------------------*/
			//SetTimer(hWnd,0x1000,3000,0);

			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
			cnt++;
		}

		virtual ~CWindow(void)
		{
			delete widgetlist;
			widgetlist = NULL;
			cnt--;
		}

		static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		virtual LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam)
		{
			LRESULT res = 0;
			char buffer[100];

			sprintf(buffer,"msg = %x wparam = %x  lparam = %d (%d,%d)",Msg,wParam,lParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));		
			if(widgetlist && Msg!=15/*paint*/ && Msg!=127/*geticon*/)
			{
			((widgets::CTextWidget*)((widgets::CContainer*)widgetlist)->child->next->next->next->next)->SetText((u8*)buffer);


			data++;
				sprintf(buffer,"Val = %d",data);
				siggen(data);
				copyfft();		
				fix_fftr(fx, log2N, 0);
				scale_fft();

			InvalidateRect(hWnd,0,0);
			}
			switch(Msg)
			{
			case 0x1122:
				{
					//user messages
					switch(wParam)
					{
					case 0x01:
						data = 0;						
						break;
					case 0x2:
						data++;						
						break;
					case 0x3:
						data--;						
						break;
					}
					cnt++;
					sprintf(buffer,"Val = %d",data);
					siggen(data);
					copyfft();		
					fix_fftr(fx, log2N, 0);
					scale_fft();
					((widgets::CTextWidget*)((widgets::CContainer*)widgetlist)->child->next->next->next)->SetText((u8*)buffer);
				}
				break;
			case 0x1123:
				{
					//user messages
					switch(wParam)
					{
					case 0x01:
						sprintf(buffer,"sets val to 0");			
						break;
					case 0x2:
						sprintf(buffer,"inrements val");			
						break;
					case 0x3:
						sprintf(buffer,"decrements val");			
						break;
					}
					cnt++;

					((widgets::CTextWidget*)((widgets::CContainer*)widgetlist)->child->next->next->next->next)->SetText((u8*)buffer);
				}
				break;
				/* mouse events*/
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
				{
					Events e;
					e.e=wParam==MK_LBUTTON?Events::mpress:Msg==WM_LBUTTONUP?Events::mrelease:Events::mmove;
					e.x = GET_X_LPARAM(lParam);
					e.y = GET_Y_LPARAM(lParam);

					widgets::CWidget *w = widgetlist;
					u16 res=0;
					while(w)
					{
						if(res|=w->OnEvent(&e))
						{
							break;
						}
						w=(widgets::CWidget*)w->next;
					}			
					if(res!=0)
					{
						InvalidateRect(hWnd,0,0);
					}

				}
				break;

			case WM_DESTROY:						
				if(parent_hWnd==NULL)
				{
					KillTimer(hWnd,1982);
					PostQuitMessage(0);				
				}
				delete this;
				break;
			case WM_TIMER:
				data++;
				sprintf(buffer,"Val = %d",data);
				siggen(data);
				copyfft();		
				fix_fftr(fx, log2N, 0);
				scale_fft();
				((widgets::CTextWidget*)((widgets::CContainer*)widgetlist)->child->next->next->next)->SetText((u8*)buffer);
				InvalidateRect(hWnd,0,0);
				break;			
			case WM_KEYDOWN: // up 38 down 40 left 37 right 39
				//case WM_KEYUP:		
				{					
					Events e;
					e.e=Events::keydown;
					e.key = (u8)wParam;

					widgets::CWidget *w = widgetlist;
					u16 res=0;
					while(w)
					{
						if(res|=w->OnEvent(&e))
						{
							;//break;
						}
						w=(widgets::CWidget*)w->next;
					}			
					if(res!=0)
					{
						InvalidateRect(hWnd,0,0);
					}
				}
				break;
			case WM_CHAR:
				{
					Events e;
					e.e=Events::keypress;
					e.key = (u8)wParam;

					widgets::CWidget *w = widgetlist;
					u16 res=0;
					while(w)
					{
						if(res|=w->OnEvent(&e))
						{
							;//break;
						}
						w=(widgets::CWidget*)w->next;
					}			
					if(res!=0)
					{
						InvalidateRect(hWnd,0,0);
					}
				}				
				break;
			}
			return res;
		}

		virtual WPARAM Run(void)
		{
			HACCEL hAccelTable;
			MSG msg;
			HINSTANCE hInstance=GetModuleHandle(NULL);
			hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIEGE8));

			while (GetMessage(&msg, NULL, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			return msg.wParam;
		}
		void Resize(u16 w, u16 h)
		{
			delete surf;
			surf = new graphics::CWinSurface(w,h);
			InvalidateRect(hWnd,0,0);
		}

		void Paint(HDC dc)
		{
			surf->Clear(0xff202020);
			widgetlist->DrawAll();
			//surf->DrawLine(10,10,100,100,0x11223344);
			surf->Paint(dc);		
		}

	}; // end class

};




