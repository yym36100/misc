#pragma once
#include "..\cdef.h"
#include "..\Surface.h"

namespace siege
{
	namespace resources
	{
		class CSimpleFont
		{		
		public:
			graphics::CSurface *s;
			u32 Color;

			static u8 const TABLE5[];
			CSimpleFont(graphics::CSurface *ss,u32 cc):s(ss),Color(cc){}
			~CSimpleFont(void){}

			void DrawChar( u16 x, u16 y, u8 c) const;
			void DrawText(u16 x, u16 y, u8 const *t) const;

		};
	}
}