#pragma once
#include "window5.h"
#include "textwidget.h"
#include "GraphWidget.h"
#include "Sound.h"

namespace sg{

	class Cmywindow;
	class CFFTSound : public  snd::CWaveSound {
	private:
		typedef snd::CWaveSound super;
	public:
		Cmywindow *w;

		void SigGen2(char *buf,double freq = 600.0/4.0) {
				static double phase = 0.0;
				static double fi = 1.0;
				short val;
				for(int i=0;i<bufsize*2;i+=4) {
					fi+= 0.0001;
					phase += 2*3.14159265 * freq *fi/ wf.nSamplesPerSec;

					val = 32765 * sin(phase);
					buf[i] = val&0xff;
					buf[i+1] = (val>>8)&0xff;
					buf[i+2] = buf[i]; 
					buf[i+3] = buf[i+1]; 
				}
			}
		virtual bool GetSignal(void) {
			bool res = true;
				
			//SigGen2(playp);
				
			UpdateGraph();
			//playp+=bufsize*2;
			res = super::GetSignal();			
			return res;
		}

		void UpdateGraph(void);		
	};

	class Cmywindow : public CWindow {
	public:
		wg::CWidget *w;
		wg::CWidget *w2;
		CFFTSound *snd;

		Cmywindow(Rect r, u32 style,HWND parent_hWnd,u16 *name) :
		CWindow( r, style, parent_hWnd, name),w(0)
		{
			w=(new wg::CGraphWidget(surf,10,10,1024+2,100+2,1024,"Wave"));		
			w2=(new wg::CGraphWidget(surf,10,100+2+10+10,1024+2,300+2,512,"Spectrum"));		
			((wg::CGraphWidget*)w2)->style  = wg::CGraphWidget::filled;
			w->Add(w2);

			snd = new CFFTSound();
			snd->Init();			
			snd->w = this;

			//end ctor
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);

			snd->Open();
			snd->Play();
		}
		virtual void Paint(HDC dc) {			
			w->DrawAll();
			surf->Paint(dc);		
		}
		virtual LRESULT CALLBACK WndProc(UINT Msg,WPARAM wParam, LPARAM lParam)
		{
			LRESULT res = 0;
			switch(Msg)
			{
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
					u16 res=0;
					while(tw)
					{
						if(res|=tw->OnEvent(&e));//break;
						tw=(wg::CWidget*)tw->next;
					}	
					if(res!=0)
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
