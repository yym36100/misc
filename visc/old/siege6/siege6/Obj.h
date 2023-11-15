#pragma once

#define __ST(x) (u16*)L##x

namespace siege{

	struct stPoint
	{
		u16 x,y;
	};

	struct stRect
	{
		u16 x,y,w,h;
	};

	class CObj
	{
	public:

		CObj *next;

		CObj(void):next(NULL)
		{
		}

		virtual ~CObj(void)
		{
			if(next) delete next;
		}

		void Add(CObj *o)
		{
			CObj *self = this;
			while(self->next)self=self->next;
			self->next = o;
		}

		CObj* operator+(CObj &r)
		{
			Add(&r);
			return this;
		}
	};

};