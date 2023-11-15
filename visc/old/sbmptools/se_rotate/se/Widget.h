#pragma once
#include "cdef.h"
#include "siegecfg.h"
#include "siegetypes.h"

#include "SObject.h"
#include "SEvent.h"

namespace siege{
	class CWidget :
		public CSObject
	{
	public:
		//int16 x,y;
		//uint16 w,h;
		rect r;
		bool focused;
		bool redraw;
		//CWidget(void);
		CWidget(int16 xx, int16 yy, uint16 ww, uint16 hh)
			:r(xx,yy,xx+ww,yy+hh),focused(false),redraw(true){}
		virtual ~CWidget(void);

		virtual mode HitTest(CSEvent &e)
		{
			return r.inside(e.pp)? enMove : enNone;
		}

		virtual void HandleEvent(CSEvent &e)
		{
			bool old=focused;
			focused = r.inside(e.pp)?true:false;
			redraw = old!=focused;
		}
		virtual uint16 Draw()=0;
	};
}
