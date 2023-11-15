#pragma once
#include "cdef.h"
#include "siegecfg.h"
#include "siegetypes.h"

#include "Widget.h"
#include "Screen.h"

namespace siege{
	class CRectWidget :
		public CWidget
	{
	public:
		enum {defsize=20};
		uint16 color;
		//CRectWidget(void);
		explicit CRectWidget(int16 xx, int16 yy,uint16 c=0xffff)
			:CWidget(xx,yy,defsize,defsize),color(c)
		{
		}
		virtual ~CRectWidget(void);

		/*virtual void HandleEvent(CSEvent &e)
		{
		}*/

		virtual uint16 Draw()
		{
			//uint8 *p = CScreen::instance->pBuffer;
			if(redraw)
			{
				siege_dbg(L"widget draw\n");
				CScreen::instance->color = focused? 0x00:color;
				CScreen::instance->FillRect(r.x1,r.y1,r.width(),r.height());
				redraw = false; //todo move this to a common location
				return 1;
			}
			return 0;
		}

	};
}
