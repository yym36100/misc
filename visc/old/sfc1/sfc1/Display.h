#pragma once
#include "stypes.h"
#include "surface.h"
#include "sbase.h"


namespace sg
{
	class Display :
		public Base
	{
	public:				
		Surface *pSurface;

		Display(Surface *s)
			:pSurface(s){}
		//virtual void Init(void)=0;

		~Display(void)
		{
		}

		virtual void Paint(HDC hdc)
		{
			pSurface->Paint(hdc);			
		}
		void Clear()
		{
			pSurface->Clear();
		}
	};
}
