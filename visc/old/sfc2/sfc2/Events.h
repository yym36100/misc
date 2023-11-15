#pragma once
#include "sbase.h"
namespace sg
{
	class Events :
		public Base
	{
	public:
		enum event{mmove,mpress,mrelease};
		event e;
		u16 x,y;

		Events(void)
		{
		}

		~Events(void)
		{
		}
	};
}