#include "StdAfx.h"
#include "PopupMenu.h"
#include "DummyWidget.h"

namespace sg
{

#define TEXTSIZE(s) (sizeof(s)/sizeof(u16*))



	PopupMenu::PopupMenu(void)
	{
	}

	u16 PopupMenu::GetWidth(u16 *texts[], u8 nritem)
	{
		u16 w=0,cw;

		for(u8 i=0;i<nritem;i++)
		{
			cw = wcslen((wchar_t*)texts[i]);
			if(cw>w)w = cw;
		}
		return 16+cw*6;
	}
	PopupMenu::PopupMenu(u16 x, u16 y,u16 *texts[], u8 nritem,SWindow *w,u16 code)
		:SWindow(x,y,GetWidth(texts,nritem)+2,nritem*10+2,WS_POPUP,w->hWnd,(u16*)L"second window"),code(code)
	{
		//sg::SWindow *w2 = new SWindow(300,300,100,nritem*10,WS_POPUP,w->hWnd,(u16*)L"second window");
		u16 wi = GetWidth(texts,nritem);
		for(u8 i=0;i<nritem;i++)
		{
			if(!wg)
				wg = new DummyWidget(s,1,1+i*10,wi,10,texts[i],10+i);
			else
				wg->Add(new DummyWidget(s,1,1+i*10,wi,10,texts[i],10+i));		
		}
		SendMessage(hWnd,WM_USER,0,0);
	}

	PopupMenu::~PopupMenu(void)
	{
		//delete w2;
	}
}
