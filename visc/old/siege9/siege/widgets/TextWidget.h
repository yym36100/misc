#pragma once

#include "cdef.h"
#include "Widget.h"
#include ".\resources\simplefont.h"
#include "..\Surface.h"

namespace siege
{
	namespace widgets
	{
		class CTextWidget :
			public CWidget
		{
			resources::CSimpleFont *sf;
			u8 text[256];
		public:

			CTextWidget(graphics::CSurface *ss, u16 x, u16 y, u16 w, u16 h):
			  CWidget(x,y,w,h)
			  {
				  Focusable = false;
				  sf = new resources::CSimpleFont(ss,0xffffffff);
			  }
			  void SetText(u8 *t)
			  {
				  strcpy((char*)text,(char*)t);
			  }
			  virtual void Draw(void) const
			  {
				  if(Highlighted)
				  {
					  sf->Color = 0xffff0000;					  
				  }
				  else
				  {
					  sf->Color = 0xffffffff;
				  }
				  sf->DrawText(rect.x,rect.y,text);
			  }

			  virtual ~CTextWidget(void)
			  {
			  }


			  virtual u16 OnEvent(Events *e)
			  {
				  if(HitTest(e))
				  {
					  Highlighted = true;
					  switch(e->e)
					  {
					  case Events::mmove:

						  break;
					  case Events::mpress:
						  return 1;
						  break;
					  }	
				  }
				  else
				  {
					  Highlighted = false;
				  }
				  return 0;
			  }


		};

	};
};