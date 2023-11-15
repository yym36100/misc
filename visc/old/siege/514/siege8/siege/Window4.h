#pragma once
#define sss (1024*32)
#define log2sss	(10+5)
#define speed	(0)
#define yys	(10)
#define sweeps	(20)

#include "cdef.h"
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#include "obj.h"
#include "surface.h"
#include "winsurface.h"
//#include ".\widgets\widget.h"
#include ".\widgets\TextWidget.h"
#include ".\widgets\ButtonWidget.h"
#include ".\widgets\BitmapWidget.h"
#include ".\widgets\GraphWidget.h"
#include ".\resources\gimphead.h"


#include "Thread.h"


#include "Events.h"

#include "..\resource.h"

#include "..\mydft.h"

extern u32 mypalette[256];
namespace siege{

	class CWindow;

	class CMyThread : public CThread
	{
	public:
		CWindow *pW;
		enum tenfft{fft_int,dft,myfft2,myfft4};
		tenfft enfft;
		float *din,*dout;

		CMyThread(CWindow *p,tenfft t =myfft4 ):pW(p),enfft(t)
		{
		}

		void fft_integer(void)
		{
			int fix_fft(short fr[], short fi[], short m, short inverse);
			short fr[sss*1];
			short fi[sss*1];
			u16 scale;
			for(u16 i=0;i<sss*1;i++)
			{				
				fr[i] = (short)din[i];
				fi[i] = 0;				
			}			
			scale = fix_fft(fr,fi,log2sss,0);			
			for(u16 i=0;i<sss/1;i++)
			{
				fr[i]<<=scale;
				fi[i]<<=scale;
				dout[i]= -sqrt((float)(fr[i]*fr[i]+fi[i]*fi[i]));				
			}
		}

		void fft_dft(void)
		{
			arr<cmp<double>,sss> in,out,powph;
			//1 input format adaptation
			for(u16 i=0;i<sss*1;i++)
			{
				in[i].re = din[i];
				//in[i].im = 0;
			}
			//2 calc fft
			dft1<double,sss>(in,out);
			powph = powphase<double,sss>(out);
			//3 out format adaptaiton			
			for(u16 i=0;i<sss*1;i++)
			{
				dout[i] =  -powph[i].re/(double)sss;
			}
		}
		void fft_myfft2(void)
		{
			arr<cmp<float>,sss> in,powph;
			//1 input format adaptation
			for(u16 i=0;i<sss*1;i++)
			{
				in[i].re = din[i];
				in[i].im = 0;
			}
			// 2 do job
			fft2<float,sss>(in,0,sss);
			in.bitrev(log2sss);
			powph = powphase<float,sss>(in);

			// 3 out adaptation
			for(u16 i=0;i<sss*1;i++)
			{
				dout[i] = -powph[i].re/(double)sss;
			}
		}
		void fft_myfft4(void)
		{
			double i[sss],r[sss];
			//1 input format adaptation
			for(u16 n=0;n<sss*1;n++)
			{
				r[n] = din[n];
				i[n] = 0;
			}
			// 2 do job
			fft2_2_fast(r,i,0,sss);
			
			bitrev(r,i,log2sss,sss);
			//bitrev2(r,i,sss);
			powphase(r,i,sss);			

			// 3 out adaptation
			for(u16 i=0;i<sss*1;i++)
			{
				dout[i] = -r[i]/(double)sss;
			}
		}


		DWORD WINAPI Run(void)
		{			
			while(1)
			{
				runs++;
				MStart();
				// execute job
				switch(enfft)
				{
				case fft_int: fft_integer(); break;
				case dft: fft_dft(); break;
				case myfft2: fft_myfft2(); break;
				case myfft4: fft_myfft4(); break;
				}

				// job done sleep now
				MStop();
				if(end) break;
				Suspend();
			}
			return 0;
		}
	};

	class CWindow
	{
	public:
		CWinSurface *surf;
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

		widgets::CGraphWidget *gw1;
		widgets::CSignal::tsig sigt;

		widgets::CSignal *mysignal;


		CMyThread *t1,*t2,*t3,*t4;
		float fft4_out[sss];
		float fft2_out[sss];
		float dft_out[sss];
		float fft_int_out[sss];

		widgets::CTextWidget *tew[4];

		CWindow(void)
		{
		}

		CWindow(stRect r, u32 style,HWND parent_hWnd,u16 *name)
			:mode(1),pause(0),sigt(widgets::CSignal::ensin)
		{
			surf = new CWinSurface(r.w,r.h);
			ATOM res;
			this->parent_hWnd = parent_hWnd;
			widgetlist = NULL;




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

			{
				FILE *f;
				u8 buff[1024];
				f=fopen("gold.raw","rb");
			
				//mypalette =0;
				if(f)
				{		
						fread(buff,768,1,f);
				fclose(f);
					for(int i=0;i<256;i++)
					{
						mypalette[i]=0+(buff[i*3+2]<<0)+(buff[i*3+1]<<8)+(buff[i*3+0]<<16);
					}
				}
				else
				{
					for(int i=0;i<256;i++)
					{
						mypalette[i]=0xff+(i<<8)+(i<<16)+(i<<24);
					}
				}
			}

			
			/*--------------------*/
			widgets::CTextWidget *tw,*tw2;
			widgets::CButtonWidget *bw1,*bw2,*bw3,*bw4,*bw5,*bw6;
			widgets::CBitmapWidget *bw;
			widgets::CGraphWidget *gw3,*gw4,*gw6;

			tw = new widgets::CTextWidget(surf,20,400,100,100);
			tw->SetText((u8*)"0");
			tw->setsize(2);

			tw2 = new widgets::CTextWidget(surf,10,210,100,100);
			tw2->SetText((u8*)"Voltage threshold: 10.43V");
			//tw->Draw();

			//delete tw;
			bw1 = new widgets::CButtonWidget(surf,20,10,160,20);
			bw1->SetText((u8*)"rect");
		
			bw1->handle = (u32)hWnd;
			bw1->command = 0x1;

			bw2 = new widgets::CButtonWidget(surf,20,50,160,20);
			bw2->SetText((u8*)"sin");
			bw2->handle = (u32)hWnd;
			bw2->command = 0x2;

			bw3 = new widgets::CButtonWidget(surf,20,90,160,20);
			bw3->SetText((u8*)"clip+");
			bw3->handle = (u32)hWnd;
			bw3->command = 0x3;

			bw4 = new widgets::CButtonWidget(surf,20,130,160,20);
			bw4->SetText((u8*)"clip-");
			bw4->handle = (u32)hWnd;
			bw4->command = 0x4;

			bw5 = new widgets::CButtonWidget(surf,20,170,160,20);
			bw5->SetText((u8*)"Mittudomain");
			bw5->handle = (u32)hWnd;
			bw5->command = 0x5;

			bw6 = new widgets::CButtonWidget(surf,20,170+40,160,20);
			bw6->SetText((u8*)"Play/Pause");
			bw6->handle = (u32)hWnd;
			bw6->command = 0x6;

			bw = new widgets::CBitmapWidget(surf,100,100,40,40);

			gw1 = new widgets::CGraphWidget(surf,200,10,1400/2,200/2);
			
			//bw->Draw();
			//delete bw;

			widgetlist = tw;
			widgetlist->Add(bw1);
			widgetlist->Add(bw2);
			widgetlist->Add(bw3);
			widgetlist->Add(bw4);
			widgetlist->Add(bw5);
			widgetlist->Add(bw6);
			//widgetlist->Add(tw2);
			widgetlist->Add(gw1);

			

				//CSignal(float a = 80, float f = 2, float ph =3.14/3.0,float offs = 0,u16 l = 50, tsig sig = ensin):
					//gw1->sig = new widgets::CSignal(80,2,len++/100.0,0,512);

			widgetlist->Add( new widgets::CGraphWidget(surf,200,10+200/2+20,1400/2,200/2) );
			gw1->sig = new widgets::CSignal(80,2,0,100,sss*1);
			strcpy((char*)((widgets::CGraphWidget*)(gw1))->title,"signal time");
			strcpy((char*)((widgets::CGraphWidget*)(gw1->next))->title,"PIC integer FFT");

			//gw3 = new widgets::CGraphWidget2(surf,200,10+200*2+20*2,1400,400);
			gw3 = new widgets::CGraphWidget(surf,200,10+200+20+20,1400/2,200/2);
			strcpy((char*)((widgets::CGraphWidget*)(gw3))->title,"my DFT");
			gw3->yscale = yys;
			widgetlist->Add(gw3);

			gw4 = new widgets::CGraphWidget(surf,200,10+200*0+200*2+20*0+20*0-40,1400/2,200/2);
			strcpy((char*)((widgets::CGraphWidget*)(gw4))->title,"my FFT v2");
			widgetlist->Add(gw4);
			gw4->yscale = yys;
			gw4->palette = mypalette;
			
			gw6 = new widgets::CGraphWidget(surf,200,10+100*1+200*2+20*0+20*1-40,1400/2,200/2);
			strcpy((char*)((widgets::CGraphWidget*)(gw6))->title,"V3 fft");
			widgetlist->Add(gw6);
			gw6->yscale = yys;
			gw6->palette = mypalette;

			bw = new widgets::CBitmapWidget(surf,0,500,10,10);
			widgetlist->Add( bw);
			gimphead const test1;
			bw->SetPicture((gimphead*)&test1);

			//gw1->clip = 64;
			//((widgets::CGraphWidget*)(gw1->next))->style = widgets::CGraphWidget::enbar;

			{			
			widgets::CTextWidget *t;
			t = new widgets::CTextWidget(surf,20,170+40+50,160,20);
			t->SetText((u8*)"sado");
			t->setsize(2);
			widgetlist->Add(t);

			t = new widgets::CTextWidget(surf,20,170+40+50+2*8+2,160,20);
			t->SetText((u8*)"T E C H");
			t->setsize(1);
			widgetlist->Add(t);
			}

			for(int i=0;i<4;i++)
			{
				tew[i] = new widgets::CTextWidget(surf,200+1400/2+20,140+i*120,50,10);
				tew[i]->SetText((u8*)"NA");
				tew[i]->setsize(2);
				widgetlist->Add(tew[i]);
			}


			/// THREADS
			t1 = new CMyThread(this);
			t1->din = gw1->sig->pdata;
			t1->dout = fft4_out;
			t1->Start();

			t2 = new CMyThread(this,CMyThread::myfft2);
			t2->din = gw1->sig->pdata;
			t2->dout = fft2_out;
			t2->Start();

			t3 = new CMyThread(this,CMyThread::dft);
			t3->din = gw1->sig->pdata;
			t3->dout = dft_out;
			t3->Start();

			t4 = new CMyThread(this,CMyThread::fft_int);
			t4->din = gw1->sig->pdata;
			t4->dout = fft_int_out;
			t4->Start();


			
			fft();



			//widgetlist->DrawAll();
			
			/*-----------------------*/


			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
			cnt++;
			SetTimer(hWnd,1982,speed,0);

		}

		void fft(void)
			{
//				int fix_fftr(short f[], int m, int inverse);
				//int fix_fft(short fr[], short fi[], short m, short inverse);

			
				//short fr[sss*1];
				//short fi[sss*1];
				//u16 scale;
				//for(u16 i=0;i<sss*1;i++)
				//{
				//	//should do some windowing
				//	fr[i] = (short)gw1->sig->pdata[i];
				//	fi[i] = 0;
				///*	if (i & 0x01)
				//		f[(sss*2+i)>>1] = (short)gw1->sig->pdata[i];
				//	else
				//		f[i>>1] = (short)gw1->sig->pdata[i];*/
				//}
				////scale = fix_fftr(f,log2N,0);
				//scale = fix_fft(fr,fi,log2sss,0);
				//float *ff = new float[sss*2];
				//for(u16 i=0;i<sss/1;i++)
				//{
				//	fr[i]<<=scale;
				//	fi[i]<<=scale;
				//	ff[i]= -(fr[i]*fr[i]+fi[i]*fi[i]);				
				//}
				((widgets::CGraphWidget*)(gw1->next))->sig = new widgets::CSignal(0,0,0,0,sss/2,siege::widgets::CSignal::enext,fft_int_out);
				
				//delete[] ff;


				///
				//arr<cmp<float>,sss> in,out,powph;
				////1 input format adaptation
				//for(u16 i=0;i<sss*1;i++)
				//{
				//	in[i].re = gw1->sig->pdata[i];
				//	in[i].im = 0;
				//}
				////2 calc fft
				//dft1<float,sss>(in,out);
				//powph = powphase<float,sss>(out);
				////3 out format adaptaiton
				//float *myf = new float[sss];
				//for(u16 i=0;i<sss*1;i++)
				//{
				//	myf[i] =  -powph[i].re;
				//}
				((widgets::CGraphWidget*)(gw1->next->next))->sig = new widgets::CSignal(0,0,0,0,sss/2,siege::widgets::CSignal::enext,dft_out);
				//1 input format adaptation
				// reuse prev data

				//2 calc fft
				//fft2<float,sss>(in,0,sss);
				//in.bitrev(log2sss);
				//powph = powphase<float,sss>(in);
				////3 out format adaptaiton
				//float *myf2 = new float[sss];
				//for(u16 i=0;i<sss*1;i++)
				//{
				//	myf2[i] =  -powph[i].re;
				//}
				((widgets::CGraphWidget*)(gw1->next->next->next))->sig = new widgets::CSignal(0,0,0,0,sss/2,siege::widgets::CSignal::enext,fft2_out);

				//4 v3
				//1 input format adaptation
				/*for(u16 i=0;i<sss*1;i++)
				{
					in[i].re = gw1->sig->pdata[i];
					in[i].im = 0;
				}
				fft4<float,sss>(in,0,sss);
				in.bitrev(log2sss);
				powph = powphase<float,sss>(in);

				float *myf4 = new float[sss];
				for(u16 i=0;i<sss*1;i++)
				{
					myf4[i] = -powph[i].re;
				}*/
				((widgets::CGraphWidget*)(gw1->next->next->next->next))->sig = new widgets::CSignal(0,0,0,0,sss/2,siege::widgets::CSignal::enext,fft4_out);


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
			switch(Msg)
			{
			case 0x1122:
				{
					//user messages
					switch(wParam)
					{
					case 0x01:
						//data = 0;			
						sigt = widgets::CSignal::enrect;
						break;
					case 0x2:
						sigt = widgets::CSignal::ensin;
						//data++;						
						break;
					case 0x5:
						sigt = widgets::CSignal::ennoise;
						//data++;						
						break;
					case 0x3:
						gw1->clip=0;
						//data--;						
						break;
						case 0x4:
						gw1->clip=256;
						//data--;						
						break;

						case 0x6:
						pause^=1;
						//data--;						
						break;
					}					
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
						if(res|=w->OnEvent(&e));//break;
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
				if(pause==0)
				{
					delete gw1->sig;
					//delete ((widgets::CGraphWidget*)(gw1->next))->sig;
				{
					static float freq = 1;
					char buffer[100];
					//CSignal(float a = 80, float f = 2, float ph =3.14/3.0,float offs = 0,u16 l = 50, tsig sig = ensin):
					mysignal = new widgets::CSignal(1000,freq,0.0,0,sss*1,sigt);
					gw1->sig = mysignal;

					//update statistics
					CThread *t[4] = {t4,t3,t2,t1 };
					for(int i=0;i<4;i++)
					{					
						u8 buffer[256];
						//sprintf((char*)buffer,"avg = %.3f min = %.2f max = %.2f  ",t[i]->avg,t[i]->min,t[i]->max);
						sprintf((char*)buffer,"avg = %.3f  ",t[i]->avg);
						tew[i]->SetText(buffer);						
					}

					t1->din = mysignal->pdata;
					t1->Resume();

					t2->din = mysignal->pdata;
					t2->Resume();

					t3->din = mysignal->pdata;
					t3->Resume();

					t4->din = mysignal->pdata;
					t4->Resume();

					freq+=0.01*sweeps;
					if(freq>3*sss/4)freq = 0.1;
					fft();
					sprintf(buffer,"f=%03.2f",freq);
					((widgets::CTextWidget*)widgetlist)->SetText((u8*)buffer);
					InvalidateRect(hWnd,0,0);
				}
				}
				break;
		/*	case WM_CHAR:
				InvalidateRect(hWnd,0,0);
				switch (wParam)
				{
				case '1':
					mode = 1;
					break;
				case '2':
					mode = 2;
					break;
				case '3':
					mode = 3;
					break;
				case 'p':
					pause^=1;
					break;
				}				
				break;*/
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
			surf = new CWinSurface(w,h);
			InvalidateRect(hWnd,0,0);
		}

		void Paint(HDC dc)
		{

			widgetlist->DrawAll();
			//surf->DrawLine(10,10,100,100,0x11223344);
			surf->Paint(dc);		
		}

	}; // end class

};









