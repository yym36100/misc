#pragma once
#include "cdef.h"

namespace sg
{
	class BitStream
	{
	public:
		u8 *buffer;
		u32 size;
		
		u8 rbi;
		u8 wbi;
		u32 ri;
		u32 wi;

		BitStream(u32 size=1024)
			:rbi(0),wbi(0),wi(0),ri(0)
		{
			buffer = new u8[size];
		}

		~BitStream()
		{
			if(buffer)
				delete[] buffer;
		}

		void Write( u8 bit)
		{
			if(wi<size)
			{
				if(bit)
					buffer[wi] |= (1<<wbi);
				else
					buffer[wi] &=~(1<<wbi);
				if(++wbi==8)
				{
					wi++;
					wbi=0;
				}
			}
		}
		void WriteB(u8 b)
		{
			if(wi<size)
			{
				buffer[wi++]=b;
			}
		}
		void WriteBits(u32 b,u8 n)
		{
			while(n--)
			{
				Write(b&1);
				b=b>>1;
			}
		}
		u8 Read(u8 *res = 0)
		{			
			if(ri<size)
			{
				u8 r;
				r = (buffer[ri]>>rbi)&1;
				if(++rbi==8)
				{
					ri++;
					rbi=0;
				}
				return r;
			}
			if(res)*res=1;
			return 0;
		}
		u8 ReadB(void)
		{
			if(ri<size)
			{
				return buffer[ri++];
			}
			return 0;
		}
		u32 ReadBits(u8 n)
		{
			u32 res=0;
			u8 i=0;
			while(n--)
			{
				res |= Read()<<(i++);
				if(n==0)break;				
			}
			return res;
		}

	};
}