#include "StdAfx.h"
#include "cdef.h"
#include "siegecfg.h"

#include "SContainer.h"

namespace siege{
	CSContainer::CSContainer(void)
		:f(NULL),l(NULL)
	{
#if siege_debug==1
		i=0;
#endif
	}

	CSContainer::~CSContainer(void)
	{
		CSObject *t=f;
		CSObject *tt=f;
		uint16 i=0;
		while(t)
		{
			tt=t->n;
			delete t;
			t = tt;
			i++;
		}
#if siege_debug==1
		wchar_t s[80];
		swprintf(s,L"CScontainer %d elements deleted\n",i);
		siege_dbg(s);
#endif
	}

	void CSContainer::AddFirst(CSObject &o)
	{
		o.n=f;
		o.p=NULL;
		f=&o;
	}
	void CSContainer::AddLast(CSObject &o)
	{
		if(!f)
			f=&o;
		o.p=l;
		if(l)
			l->n=&o;

		o.n=NULL;
		l=&o;
#if siege_debug==1
		i++;
		wchar_t s[80];
		swprintf(s,L"Add last %d\n",i);
		siege_dbg(s);
#endif
	}

	CSObject& CSContainer::GetFirst()
	{
		return *f;
	}

	CSObject& CSContainer::RemoveFirst()
	{
		//remove the first element from the container
		CSObject& t=*f;
		if(f)
		{
			f->p=NULL;
			f=f->n;
			if(!f)
				l=NULL;
#if siege_debug==1
		i--;
		wchar_t s[50];
		swprintf(s,L"remove first rem=%3d\n",i);
		siege_dbg(s);
#endif
		}
		return t;
	}
}
