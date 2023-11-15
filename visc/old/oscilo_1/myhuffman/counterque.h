#pragma once
#include "cdef.h"
#include "prioque.h"

namespace sg
{
	class CounterQueItem : public PrioQueItem
	{
	public:
		virtual u8 CompareData(CounterQueItem *i) = 0;
		//virtual u8 GetData(void)=0;
		CounterQueItem()
		{
			prio=1;
		}
	};

	class CounterQue : public PrioQue
	{
	private:
		typedef PrioQue super;
	public:
		void Add(CounterQueItem *i)
		{
			CounterQueItem *c = (CounterQueItem *)head;
			PrioQueItem *p = NULL;
			if(!c)
			{				
				super::Add(i);
			}
			else
			{
				while(c)
				{
					if(i->CompareData(c)==0)
					{
						delete i;
						c->prio++;
						return;
					}
					else
					{
						p =c;
						c = (CounterQueItem *)c->next;						
					}					
				}
				p->next = i;
				i->next = NULL;
			}
		}
		void Sort()
		{		
			bool done;
			printf("sort start\n");
			u32 cnt=0;
			do{
				done = true;
				CounterQueItem *c = (CounterQueItem *)head;
				CounterQueItem *n = (CounterQueItem *)head->next;
				CounterQueItem *p = NULL;
				printf("loop %d\n",cnt++);
				while(c && n)
				{
					if(n->prio < c->prio)
					{
						done = false;
						//swap
						printf("swap %d <> %d\n",n->GetData(),c->GetData());
						if(p)
						{
							p->next = n;
						}
						else
						{
							head = n;
						}
						c->next = n->next;
						n->next = c;
						c=n;
					}

					p = c;
					c = (CounterQueItem *)c->next;
					if(!c)break;
					n = (CounterQueItem *)c->next;
				}


			}while(!done);
			

		}
	};
}