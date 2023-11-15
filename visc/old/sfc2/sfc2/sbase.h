#pragma once
#include "sbase.h"

namespace sg
{
	class Base
	{
	public:
		Base *next;
		void Add(Base *o)
		{
			Base *p=this;
			while(p->next)p=p->next;
			p->next=o;
		}

		Base(void)
			:next(NULL)
		{
		}

		virtual ~Base(void)
		{
			if(this->next) delete this->next;			
		}
		Base* operator+( Base &r)
		{
			Add(&r);
			return this;
		}		

	};
}
