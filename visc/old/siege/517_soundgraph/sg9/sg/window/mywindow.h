#pragma once
#include "window5.h"

//widgets
#include "textwidget.h"
#include "GraphWidget.h"
#include "slider.h"
#include "button.h"

#include "Sound.h"

namespace sg{

	class Cmywindow;
	class CFFTSound : public  snd::CWaveSound {
	private:
		typedef snd::CWaveSound super;
	public:
		Cmywindow *w;
		double skval;

		CFFTSound()
			:CWaveSound(),skval(200) {}

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
		wg::CSlider *ws;
		wg::CTextWidget *wt;
		wg::CButton *wb;
		CFFTSound *snd;

		Cmywindow(Rect r, u32 style,HWND parent_hWnd,u16 *name) :
		CWindow( r, style, parent_hWnd, name),w(0)
		{
			w=(new wg::CGraphWidget(surf,10,10,1024+2,100+2,1024,"Wave"));		
			//w2=(new wg::CGraphWidget(surf,10,100+2+10+10,1024+2,100+2,512,"Spectrum"));		
			w2=(new wg::SpectroGraph(surf,10,100+2+10+10,1024+2,100+2,512,"Spectrum"));		
			((wg::CGraphWidget*)w2)->style  = wg::CGraphWidget::filled;
			w->Add(w2);

			ws = new wg::CSlider(surf,10+30,100+22+100+2+8+5,1024+2-100);
			w->Add(ws);

			wt = new wg::CTextWidget(surf,1024-25,100+22+100+2+8+5,8*5,8,"00:00",gray);
			w->Add(wt);

			wb = new wg::CButton(surf,10,100+22+100+2+8,20,20);
			wb->SetText((u8*)"P");
			w->Add(wb);

			snd = new CFFTSound();
			snd->Init();			
			snd->w = this;

			//slider data connection
			ws ->oval = &snd->skval;

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
					if(res == 11) {
						SetCapture(hWnd);
					}
					if(res == 22) {
						ReleaseCapture();
					}
					if(res == 33) {
						snd->Puase();
					}
					if(res == 44) {
						snd->Resume();
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
