#pragma once
#include "Widget.h"
#include "Surface.h"

#include "SWindow.h"

namespace sg
{

	class SWindow;

	class DummyWidget :
		public Widget
	{
	public:
		enum dstate{dnormal,dpressed};
		dstate ds;
		bool lock;
		i16 lx,ly;

		DummyWidget(Surface *s,i16 x, i16 y, u16 w, u16 h)
			:Widget(s,x,y,w,h),ds(dnormal),lock(false){lx=ly=0;}					

		~DummyWidget(void){}

		virtual void Draw()
		{
			u32 color = 0;
			switch(state)
			{
			case normal: 
				if (ds == dpressed)
					color = blue;
				else
					color = red;
				break;
			case hover: color = green; break;
			case press: color = blue; break;
			}
			pS->color = color;
			pS->FillRect(x,y,w,h);
			pS->color = rgba32(255,255,255,255);
			pS->f->DrawText(x+w/2-6*4/2,y+h/2-4,(u8*)"Wdgt");
		}

		virtual u16 OnEvent(Events *e)
		{
			Widget::OnEvent(e);
			estate os = state;
			state= normal;
			if(HitTest(e))
			{
				switch(e->e)
				{
				case Events::mmove:
					if(ds==dnormal)
						state = hover;
					else
						state = press;

					break;
				case Events::mpress:
					state = press;

					if (lock==0)
					{
						SWindow *p = new SWindow(x,y,100,100);
					}

					if(lock==0)
					{
						lx=e->x-x;
						ly=e->y-y;
					}
					lock=1;
					x=e->x-lx;
					y=e->y-ly;

					break;
				case Events::mrelease:state = press;
					if(lock==1)
					{
						lock=0;
						lx=ly=0;
						ds = ds == dnormal?dpressed:dnormal;
					}
					break;
				}
				return 1;
			}
			if (state !=os ) return 1;
			return 0;
		}
	};
}
