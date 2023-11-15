#pragma once
#include "sbase.h"
#include "Surface.h"
#include "Events.h"

namespace sg
{
	class Widget :
		public Base
	{
	public:
		Surface *pS;
		enum estate{normal, hover, press};

		estate state;
		i16 x,y;
		u16 w,h;
		virtual void Draw()=0;

		Widget(Surface *s,
			i16 x,i16 y, u16 w, u16 h)
			:pS(s),x(x),y(y),w(w),h(h),state(normal){}

		~Widget(void)
		{
		}
		virtual u16 OnEvent(Events *e)
		{
			return 0;
		}
		bool HitTest(Events *e)
		{
			return (e->x>x)&&(e->y>y)&&(e->x<x+w)&&(e->y<y+h);
		}
	};
}