#pragma once
#include "Widget.h"
#include ".\resources\simplefont.h"
#include "..\Surface.h"
#include "..\gBitmap.h"
#include ".\resources\gimphead.h"

namespace siege
{
	namespace widgets
	{
		class CBitmapWidget :
			public CWidget
		{
			resources::CSimpleFont *sf;
			graphics::CGmpBitmap *bmp;
			graphics::CSurface *s;

			u8 text[256];
		public:

			CBitmapWidget(graphics::CSurface *ss, u16 x, u16 y, u16 w, u16 h):
			  CWidget(x,y,w,h),s(ss)
			  {
				  bmp = NULL;
				  
			  }
			  void SetPicture(gimphead const *h,bool blend = false)
			  {
				  bmp = new graphics::CGmpBitmap(s,h,blend);

			  }

			  virtual void Draw(void) const
			  {
				  bmp->Draw(rect.x,rect.y);
			  }

			  virtual ~CBitmapWidget(void)
			  {
			  }

			  virtual u16 OnEvent(Events *e)
			  {
				  return 0;

			  }


		};

	};
};