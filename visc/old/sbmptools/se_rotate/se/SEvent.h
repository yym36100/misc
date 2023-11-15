#pragma once
#include "cdef.h"
#include "SObject.h"
#include "siegetypes.h"

namespace siege{
	class CSEvent :
		public CSObject
	{
	public:
	//	CSEvent(void);
		CSEvent(uint16 xx, uint16 yy, bool press)
			:pp(xx,yy),pressed(press){}
		virtual ~CSEvent(void);
		//uint16 x, y;
		point pp;
		bool pressed;
		mode m;
	};
}
