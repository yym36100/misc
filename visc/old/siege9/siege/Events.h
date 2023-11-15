#pragma once
#include "obj.h"

namespace siege
{
	class Events :
		public CObj
	{
	public:
		enum event{mmove,mpress,mrelease,keypress,keydown};
		event e;
		u16 x,y;
		u8 key;
		u8 keystate;

		Events(void)
		{
		}

		~Events(void)
		{
		}
	};

}