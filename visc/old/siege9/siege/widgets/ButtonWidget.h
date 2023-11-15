#pragma once
#include "Widget.h"
#include "..\Surface.h"
#include "windows.h"

namespace siege
{
	namespace widgets
	{
		class CButtonWidget :
			public CWidget
		{
		public:
			graphics::CSurface *surf;
			resources::CSimpleFont *sf;
			u8 text[256];
			u32 handle;
		

			CButtonWidget(graphics::CSurface *ss, u16 x, u16 y, u16 w, u16 h):
			  surf(ss),CWidget(x,y,w,h)
			  {
				  handle = 0;
				  Focusable = true;
				  sf = new resources::CSimpleFont(ss,0xffffffff);
			  }
			  void SetText(u8 *t)
			  {
				  strcpy((char*)text,(char*)t);
			  }
			  void Draw()const
			  {
				  if(Highlighted)
				  {
					  sf->Color = 0xff000000;

					  surf->FillRect(rect,0xff54c212);
				  }
				  else
				  {
					  sf->Color = 0xffffffff;
					  surf->FillRect(rect,0xff000000);
				  }
				  surf->DrawRect(rect,0xffffffff);
				  if(Focused)
				  {
					  surf->DrawRect(rect.x+3,rect.y+3,rect.w-6,rect.h-6,0xffff0000);
				  }
				  sf->DrawText(rect.x+(rect.w - 6*(u16)strlen((char*)text))/2,rect.y+(rect.h-6)/2,text);
			  }

			  virtual ~CButtonWidget(void)
			  {
			  }
			  virtual u16 OnEvent(Events *e)
			  {
				  if(e->e == Events::keypress)
				  {
					 /* if(e->key == '1')
					  {
						  Focused ^= 1;
						  return 1;
					  }*/
				  }
				  else if(e->e == Events::keydown)
				  {
					   if(e->key == 38)
					  {
						 // Focused ^= 1;
						  return 2;
					  }
					   if(e->key == 40)
					  {
						 // Focused ^= 1;
						  return 2;
					  }
					   if(Focused)
					   {
						   if(e->key == 0x0d || e->key == 0x20)
						   {
							   if(handle)  SendMessage((HWND)handle,0x1122,command,0);
							   return 1;
						   }
					   }
				  }
				  else
				  {
					  if(HitTest(e))
					  {
						  if(Highlighted==false)
						  {
							  if(handle)  SendMessage((HWND)handle,0x1123,command,0);
						  }
						  Highlighted = true;
						  switch(e->e)
						  {
						  case Events::mmove:	
							  return 1;
						  case Events::mpress:
							  {
								  if(handle)  SendMessage((HWND)handle,0x1122,command,0);
							  return 1;
							  }
							  break;
						  }	
					  }
					  else
					  {
						  Highlighted = false;
					  }
				  }
				  return 0;
			  }
		};

	};
};