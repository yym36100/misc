#pragma once
#include "sbase.h"
#include "Display.h"
#include "Events.h"
#include "Widget.h"

namespace sg
{
	class System :
		public Base
	{
	public:
		Display *pDisplay;
		Events *pEvents;
		Widget *pWidget;
		System(void)
		{
		}
		virtual void Init()=0;
		virtual void Paint(HDC hdc)
		{
			Widget *w = pWidget;
			pDisplay->Clear();
			while(w)
			{
				w->Draw();
				w=(Widget*)w->next;
			}
			pDisplay->Paint(hdc);
		}
		virtual u16 OnEvent(Events *e)
		{
			Widget *w = pWidget;
			u16 res;
			while(w)
			{
				if(res=w->OnEvent(e))return res;
				w=(Widget*)w->next;
			}			
		}

		~System(void)
		{
		}
	};
}