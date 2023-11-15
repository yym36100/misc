#pragma once

#include "que.h"

namespace sg
{
	class PrioQueItem : public QueItem
	{
	public:
		u16 prio;
	};

	class PrioQue : public Que
	{
	private:
		typedef Que super;
	public:
		void Add(PrioQueItem *i)
		{
			if(!head)
				// first item in prio que
				super::Add((QueItem*)i);
			else
			{
				PrioQueItem *c = (PrioQueItem *)head;
				PrioQueItem *p = NULL;
				while(c)
				{
					if(i->prio < c->prio)
					{
						PrioQueItem *t=c;
						if(!p)
						{
							// highest prio
							head = (QueItem*)i;
							head->next = (QueItem*)c;
						}
						else
						{
							//middle
							p->next = (QueItem*)i;
							i->next = (QueItem*)c;
						}
						return;
					}
					else
					{
						p =c;
						c = (PrioQueItem *)c->next;
					}
				}
				// last item
				p->next = i;
				i->next = NULL;
			}
		}
	};
}