#pragma once
#include "stypes.h"
//#include "Surface.h"
namespace sg
{
	class Surface;
	class SimpleFont
	{
	public:
		Surface *s;
		static i8 const TABLE5[];

		SimpleFont(Surface *s):s(s){}
		~SimpleFont(void){}

		void DrawChar( i16 x, i16 y, u16 c);
		void DrawText(i16 x, i16 y, u16 *t);

		
	};
}