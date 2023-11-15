#pragma once
#include "cdef.h"
#include "siegecfg.h"
#include "SObject.h"


namespace siege{
	class CSContainer
	{
	public:
#if siege_debug==1
		uint16 i;
#endif
		CSObject *f,*l;
		CSContainer(void);
		virtual ~CSContainer(void);

		void AddFirst(CSObject &o);
		void AddLast(CSObject &o);
		CSObject& GetFirst();
		CSObject& RemoveFirst();

		void foreach(void (CSObject::*ff)(void))
		{
			CSObject *t = f;
			while(t)
			{
				(t->*ff)();
				t=t->n;
			}
		}
		void foreach(void (*ff)(CSObject &r))
		{
			CSObject *t = f;
			while(t)
			{
				(*ff)(*t);
				t=t->n;
			}
		}
	};
}