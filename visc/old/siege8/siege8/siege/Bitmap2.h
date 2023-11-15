#pragma once
#include "obj.h"
#include "..\Surface.h"

namespace siege{
	namespace graphics{

		class CBitmap :
			public CObj
		{
		public:
			u16 w,h;
			u32 *data;
			CSurface *s;


			CBitmap(void)
			{
			}
			virtual void Draw(u16 x, u16 y)const
			{
			}


			virtual ~CBitmap(void)
			{
			}
		};

	}
}
