#pragma once

#include "cdef.h"

namespace siege{

	enum mode{enSize,enMove,enNone};

	struct point
	{
		int16 x,y;
		point(int16 xx, int16 yy):x(xx),y(yy){}
	};

	struct rect
	{
		int16 x1,y1,x2,y2;
		rect(int16 xx1, int16 yy1, int16 xx2, int16 yy2)
			:x1(xx1),x2(xx2),y1(yy1),y2(yy2){}
		bool inside(point &p)
		{
			return (p.x>=x1)&&(p.x<=x2)&&(p.y>=y1)&&(p.y<=y2);
		}
		uint16 width() throw(){return x2-x1;}
		uint16 height() throw(){return y2-y1;}
	};

}