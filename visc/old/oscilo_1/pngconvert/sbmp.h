#pragma once
#include "cdef.h"

namespace sbmp{

	enum consts{
		sbmp_version = 0x03,
		rleARGB8888Escape = 0x80-1,
	};

	enum type{RGB888,RGBA8888,rleRGBA888,YUVA8888};

#pragma pack(1)
	typedef struct{
		u8 ver;
		u8 type;
		u16 width, height;		
		u8 noFrames;
		u32 fsize;
	}thead;

	class csbmp{
	public:
		thead head;
		u32 size;
		u8 *buffer;	
		void create(u16 w, u16 h, u8 t, u8 f);
		~csbmp()
		{
			if(buffer)
			{
				delete [] buffer;
				buffer  = 0;
			}
		}
		void savetofile(wchar_t *name);
		void compress(void);
	};

};