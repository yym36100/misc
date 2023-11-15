#pragma once

#include "stypes.h"

namespace sg
{
	
	enum esBmpConsts
	{
		sBmpVer = 2,
		rleARGB8888Escape = 0x80-1,

	};

	enum esBmpTypes
	{
		ARGB8888=0,
		RGB888,
		rleARGB8888,
		zARGB8888,
		noBmpTypes
	};
	u8 const sBmpPixelSize[]=
	{
		4,
		3,
		4,
		4,
	};

	struct tsBmpHead
	{
		u8 tag[2];
		u8 ver, type;						
		u16 w,h;
		u32 size;
	};

	struct tsBmp
	{
		tsBmpHead head;
		u8 *pixels;
	};

#define sizeCheck()	{ u8 a[sizeof(sg::tsBmpHead)==12?1:-1];}
	
}