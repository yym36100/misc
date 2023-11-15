#pragma once
#include "Widget.h"
#include "Surface.h"

#include "SWindow.h"
#include "Simplefont.h"

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
		bool over;
		i16 lx,ly;
		u16 *name;
		u32 color;
		u16 code;

		DummyWidget(Surface *s,i16 x, i16 y, u16 w, u16 h, u16 * name,u16 code)
			:Widget(s,x,y,w,h),name(name),ds(dnormal),lock(false),color(rgba32(255,255,255,255)),over(false),code(code){lx=ly=0;}					

		~DummyWidget(void){}

		virtual void Draw()
		{		
			pS->color = color;
			pS->FillRect(x,y,w,h);			
			SimpleFont f(pS);		
			pS->color=0;
			//f.DrawText(x+w/2-6*wcslen((wchar_t*)name)/2,y+h/2-4,name);
			f.DrawText(x+(w-6*wcslen((wchar_t*)name))/2,y+h/2-4,name);
		}

		virtual u16 OnEvent(Events *e)
		{
			if(HitTest(e))
			{
				switch(e->e)
				{
				case Events::mmove:
					color = rgba32(255,0,0,255);
					over = true;
					Draw();
					return 1;
					break;
				case Events::mpress:
					{
						return code;
					}
					break;
				}	
			}
			else
			{
				if(over == true)
				{
					over = false;
					color = rgba32(255,255,255,255);
					Draw();
					return 1;
				}
			}
			return 0;
		}

		/*DummyWidget* operator+( DummyWidget &r)
		{
		Add(&r);
		return this;
		}*/
		DummyWidget& operator+( DummyWidget &r)
		{
			Add(&r);
			return *this;
		}

	};
}
