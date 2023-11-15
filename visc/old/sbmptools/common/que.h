#pragma once

namespace sg
{
	class QueItem
	{
	public:
		class QueItem *next;
		virtual void Proc(u8 a){}
		virtual u8 GetData()=0;
		virtual i8 Compare(QueItem *i)=0;
	};

	class Que
	{
	public:
		class QueItem *head;
		Que():head(NULL){}
		
		virtual ~Que()
		{
			u32 cnt=0;			
			QueItem *p = head,*dp;
			while(p)
			{
				dp = p;
				p = p->next;
				delete dp;
				cnt++;
			}
			printf("\n%d elems deleted\n",cnt);
		}

		void  Add(QueItem *i)
		{
			if(!head)
			{
				head = i;
				i->next=NULL;
			}
			else
			{
				i->next=head;
				head = i;
			}
		}
		QueItem* Pop(void)
		{
			QueItem *r = head;
			if(!head) return NULL;
			head = head->next;
			return r;
		}

		QueItem* GetLast(void)
		{
			QueItem *r = head;
			if(!r) return NULL;
			while(r->next)
			{
				r = r->next;
			}
			return r;
		}

		void ForEach(u8 a=0)
		{
			QueItem *p = head;
			while(p)
			{
				p->Proc(a);
				p=p->next;
			}
		}
		void BSort()
		{		
			bool done;
			printf("B sort start\n");
			u32 cnt=0;
			do{
				done = true;
				QueItem *c = (QueItem *)head;
				QueItem *n = (QueItem *)head->next;
				QueItem *p = NULL;
				printf("loop %d\n",cnt++);
				while(c && n)
				{
					//if(n->prio < c->prio)
					if(n->Compare(c)<0)
					{
						done = false;
						//swap
						printf("swap %c <> %c\n",n->GetData(),c->GetData());
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
					c = (QueItem *)c->next;
					if(!c)break;
					n = (QueItem *)c->next;
				}


			}while(!done);
			

		}
	};
}
