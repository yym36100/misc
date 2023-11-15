#pragma once
#include "window5.h"

//widgets
#include "textwidget.h"
#include "GraphWidget.h"
#include "slider.h"
#include "button.h"
#include "MySerialCass.h"

//#include "Sound.h"

namespace sg{

	class Cmywindow;

	class Cmywindow : public CWindow {
	public:
		com::CMySerialCass ser;
		wg::CWidget *w;
		wg::CWidget *w2f;
		wg::CWidget *w3;
		CRITICAL_SECTION cs;
		HANDLE threadHandle;
		int updatefreq;

		static DWORD WINAPI static_run(void *Param){
			Cmywindow *ct = (Cmywindow *)Param;
			return ct->MyThread();
		}

		virtual DWORD WINAPI MyThread(void){
			static sg::com::t_uartmsg data;
			static double gyro[3];
			static double gyro_avg[3];
			double accel[3];
			double fact = 0.9;
			

			while(1)
			{
				if(ser.GetData(&data))
				{
					updatefreq++;
					gyro[0] = data.gyro_data[0] +55 -3.49-1.59-0.02851;
					gyro[1] = data.gyro_data[1] - 2+0.34-1.85+0.04957;
					gyro[2] = data.gyro_data[2] + 16+3.266-0.868-0.15083							;

					gyro_avg[0] = gyro_avg[0] * fact + (1-fact)*gyro[0];
					gyro_avg[1] = gyro_avg[1] * fact + (1-fact)*gyro[1];
					gyro_avg[2] = gyro_avg[2] * fact + (1-fact)*gyro[2];

					accel[0] = data.accel_data[0];
					accel[1] = data.accel_data[1];
					accel[2] = data.accel_data[2];
					//accel[0] = data.temp_data/65535.0;

					((wg::CMultiAutoscaleGraphWidget*)w)->add_signals(gyro);
					((wg::CMultiAutoscaleGraphWidget*)w2f)->add_signals(accel);
			//		InvalidateRect(hWnd,0,0);
				}
			}
		}
				

		Cmywindow(Rect r, u32 style,HWND parent_hWnd,u16 *name) :
		CWindow( r, style, parent_hWnd, name),w(0)
		{
			updatefreq = 0;
			InitializeCriticalSection(&cs);

			w=(new wg::CMultiAutoscaleGraphWidget(surf,10,10,600+2,200+2,300,"t1"));		

			w2f=(new wg::CMultiAutoscaleGraphWidget(surf,10,200+2+10+10,600+2,200+2,300,"t2"));		
			w3 = new wg::CTextWidget(surf,10,450,40,20,"text");

			w->Add(w2f);
			w->Add(w3);
			((wg::CMultiAutoscaleGraphWidget*)w)->allocate_buffers(3);
			((wg::CMultiAutoscaleGraphWidget*)w2f)->allocate_buffers(3);

			ser.StartReceiveThread();
			

			//end ctor
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);

			SetTimer(hWnd,0x9600,16,0);

			threadHandle = CreateThread(0,0,static_run,this,CREATE_SUSPENDED,0);
			ResumeThread(threadHandle);

			{
				static char buff[20];
				sprintf(buff,"%d",updatefreq);
				((wg::CTextWidget*)w3)->SetText(buff);
			}
		}
		virtual void Paint(HDC dc) {			
			w->DrawAll();
			surf->Paint(dc);		
		}
		virtual LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam)
		{
			static bool playing = true;
			static double sig[5];
			static double sig2[1];
			static double amp = 10;
			static double inc = 2;
			LRESULT res = 0;
			switch(Msg)
			{
			case WM_TIMER:
				{
				static char buff[20];
				sprintf(buff,"%d ",updatefreq);
				((wg::CTextWidget*)w3)->SetText(buff);
				InvalidateRect(hWnd,0,0);	
				updatefreq = 0;
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

					wg::CWidget *tw = w;
					u16 res=0,res2;
					while(tw)
					{
						res=tw->OnEvent(&e);
						//if(res=tw->OnEvent(&e));//break;
						res2|=res;
						tw=(wg::CWidget*)tw->next;

						if(res == 11) {
							SetCapture(hWnd);
						}
						if(res == 22) {
							ReleaseCapture();
						}						
					}
					if(res2!=0)
					{
						InvalidateRect(hWnd,0,0);
					}
				}
				break;
			}
			return 0;
		}

	};
};// sg
