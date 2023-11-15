#pragma once
#include <stdlib.h>
#include <memory.h>

#include "cdef.h"
#include "counterque.h"
#include "bitstream.h"

namespace sg
{
	class HuffTreeItem : public PrioQueItem
	{
	public:
		HuffTreeItem *l,*r,*p;
		u8 symbol;
		u8 level;
		u32 code;
		bool empty;
		HuffTreeItem(u32 p, u8 s):empty(false),symbol(s),level(0),code(0),l(NULL),r(NULL),p(NULL){prio = p;}
		virtual u8 GetData()
		{
			return symbol;
		}

		virtual i8 Compare(QueItem *i)
		{
			if(symbol<((HuffTreeItem*)i)->symbol) return -1;
			return 1;
		}

		virtual void Proc(u8 a)
		{

			switch(a)
			{
			case 0:
				printf("H:%c(%d)  ",symbol,prio);
				break;

			case 1:
				printf("H:%c(%d)  ",symbol,level);
				break;

			}
		}
	};

	class HuffTree : public PrioQue
	{
	public:
		HuffTreeItem *root;
		HuffTree():root(NULL){}

		void Init(CounterQue *q)
		{
			if(head)return;
			while (q->head)
			{
				CounterQueItem *i =(CounterQueItem *)q->Pop();
				Add((PrioQueItem*)new HuffTreeItem(i->prio,i->GetData()));
				delete i;
			}
		}	

		void BuildTree()
		{
			while( head && head->next)
			{
				// pop the two smallest
				HuffTreeItem *i1 = (HuffTreeItem *)Pop();
				HuffTreeItem *i2 = (HuffTreeItem *)Pop();

				//merge to one
				HuffTreeItem *n = new HuffTreeItem(i1->prio+i2->prio,0);

				if(i1->prio > i2->prio)
				{
					HuffTreeItem *t = i1;
					i1 = i2;
					i2 = t;
				}
				n->l = i1;
				n->r = i2;
				n->empty = true;
				i1->p = n;
				i2->p = n;
				Add(n);
			}
			root = (HuffTreeItem *)Pop();
		}

		void PrintTree(HuffTreeItem *i,u8 l=0)
		{
			printf("level %d\n",l);
			printf("symbol=%c, prio=%d\n",i->symbol,i->prio);
			if(i->l)
			{
				printf("left ");
				PrintTree(i->l,l+1);
			}
			if(i->r)
			{
				printf("right ");
				PrintTree(i->r,l+1);
			}
		}

		u8 GetPrefixBit(HuffTreeItem *i)
		{
			if(i->p->r == i) return 1;
			return 0;
		}

		u8* GetPrefixCode(HuffTreeItem *i, u8 l)
		{

			u8 *buff = new u8[l+1];
			u8 j=l;
			memset(buff,0,l+1);
			if(l==0) return buff;
			if(i->l) return buff;
			while(l--)
			{
				buff[l] = '0'+GetPrefixBit(i);
				i = i->p;
			}


			return buff;
		}

		void PrintTree2(HuffTreeItem *i,u8 l=0)
		{
			if(!i) return;
			u8 l2=l;
			while(l2--)
			{
				putchar('-');
			}
			i->level=l;
			u8 *pc = GetPrefixCode(i,l);
			printf("(%c)->%d %20s [%d]\n",i->symbol,i->prio,pc,i->level);
			delete pc;
			if(i->l)
			{
				//printf2("left ");
				PrintTree2(i->l,l+1);
			}
			if(i->r)
			{
				//printf("right ");
				PrintTree2(i->r,l+1);
			}
		}

		~HuffTree()
		{
			//destroy tree
			printf("huff dtor");
		}
		HuffTreeItem* GetLefLeaf(HuffTreeItem* i)
		{
			if(!i) return NULL;
			if(i->l) return GetLefLeaf(i->l);
			if(i->r) return GetLefLeaf(i->r);
			return i;
		}
	};

	class CHuffTree : public HuffTree
	{
	public:		
		u8 symmin,symmax;
		u8 lenmin, lenmax;

		CHuffTree(){}
		void PrintCode(HuffTreeItem *i)
		{
			for(u8 j=0;j<i->level;j++)
			{
				printf("%d",(i->code>>(i->level-1-j))&1);
			}
		}
		void Init(HuffTree *t)
		{
			u16 totallen=0;
			u16 cnt=0;
			u16 max = 0;
			u16 min=0xffff;
			while(t->root)
			{
				HuffTreeItem *i = GetLefLeaf((HuffTreeItem *)t->root);
				//remove from tree
				if(!i->p) 
				{
					printf("dr %d\n",i->prio);
					delete i;
					break;
				}
				if(i->p->l) i->p->l=NULL;
				else if(i->p->r) i->p->r = NULL;

				// add symbol, delete intermediate nodes
				if(!i->empty)
				{
					i->prio = (i->level<<8)+i->symbol;	
					totallen+=i->level;
					if(i->level>max)max=i->level;
					if(i->level<min)min=i->level;

					cnt++;
					Add(i);
				}
				else
				{
					printf("dn %d\n",i->prio);
					delete i;
				}
			}
			{
				HuffTreeItem *i = (HuffTreeItem *)head;
				u32 c=0;
				u16 cbl,nbl;
				while(i)
				{
					cbl = i->level;
					if(!i->next)nbl=0;
					else nbl = ((HuffTreeItem *)i->next)->level;

					i->code=c;
					c=(c+1)<<(nbl-cbl);

					i=(HuffTreeItem *)i->next;
				}
			}
			printf(" avg bitlen = %f symbols = %d\n",totallen/(float)cnt,cnt);
			printf(" bitlen min=%d max=%d\n",min,max);
			lenmin=min;
			lenmax=max;


		}
		void PrintLengths(void)
		{
			HuffTreeItem *h = (HuffTreeItem *)head;
			u16 c = 0;
			HuffTreeItem *i;
			u16 r;
			u16 last = ((HuffTreeItem *)GetLast())->symbol;
			u16 first = h->symbol;
			c=first;
			//printf("\nrange=%d-%d\n",first,last);
			do{
				i = (HuffTreeItem *)Pop();
				/*if(i)r= i->symbol;
				else r=last;
				while(c<r)
				{
					printf(" %c(%d) len = %d\n",c,c,0);
					c++;
				}*/
				if(i)
				{
				printf(" %c(%d) len = %d code=",i->symbol,i->symbol,i->level);
				PrintCode(i);
				printf("\n");
				c++;
				}
			}while(i);
			head = h;
		}
		void PrintLengths2(void)
		{
			HuffTreeItem *h = (HuffTreeItem *)head;
			u16 c = 0;
			HuffTreeItem *i;
			u16 r;
			u16 last = ((HuffTreeItem *)GetLast())->symbol;
			u16 first = h->symbol;

			symmin=first;
			symmax=last;

			c=first;
			printf("\nrange=%d-%d\n last",first,last);
			do{
				i = (HuffTreeItem *)Pop();
				if(i)r= i->symbol;
				else r=last;
				while(c<r)
				{
					printf("skip %d\n",r-c);
					c=r;
				}
				if(i)
				{
				printf(" %c(%d) len = %d code=",i->symbol,i->symbol,i->level);
				PrintCode(i);
				printf("\n");
				c++;
				}
			}while(i);
			head = h;
		}
				
		void BuildTree(void)
		{
			HuffTreeItem *i = (HuffTreeItem *)head;
			while(i)
			{
				HuffTreeItem *t = root; 
				for(u8 j=0;j<i->level;j++)
				{
					if(!t) t = new HuffTreeItem(0,0);				
					if(!root) root = t;
					if((i->code>>(i->level-1-j))&1==1)
					{
						//right node						
						if(!t->r) 
							{
								t->r = new HuffTreeItem(0,0);
								t->r->p = t;
						}
						t=t->r;
					}
					else
					{
						//left node
						if(!t->l) 
							{
								t->l = new HuffTreeItem(0,0);
								t->l->p = t;
						}
						t=t->l;					
					}					
				}
				t->symbol = i->symbol;
				i = (HuffTreeItem *)i->next;
			}
		}

		HuffTreeItem *GetSymbol(u8 b)
		{
			HuffTreeItem *t = (HuffTreeItem *)head;
			while(t)
			{
				if(t->symbol==b) return t;
				t = (HuffTreeItem *)t->next;
			}
			return NULL;
		}

		void WriteCompByte(u8 b, BitStream *s)
		{
			HuffTreeItem *t = GetSymbol(b);
			if(!t) return;
			u32 code = t->code;
			u8 len = t->level;
			//u8 i=0;
			while(len--)
			{
				s->Write((code>>len)&1);
			}
		}
		void WriteBuffer(u8 *buff, u32 size,BitStream *s)
		{
			s->WriteBits(size,32);
			u32 i=0;
			while(i<size)
			{
				WriteCompByte(*buff++,s);
				i++;
			}			
		}

		u8 ReadCompByte(BitStream *s,u8 *er)
		{
			HuffTreeItem *t = root;
			while(t)
			{			
			u8 b= s->Read(er);
			if(*er==1) return 0;
			if(b)t=t->r;
			else t=t->l;

			if(!t->l)
				return t->symbol;
			}
		}
		void ReadBuffer(u8*buff, u32* size, BitStream *s)
		{
			
			u8 er=0,c;
			u32 is=*size;
			*size=0;
			while(*size<is)
			{
				c=ReadCompByte(s,&er);
				if(er==1)
					return;
				*buff++=c;
				(*size)++;
			}
		}

		u8 GetReqBits(u16 a)
		{
			u8 bits=0;
			while (a)
			{
				a= a >> 1;
				++bits;
			}
			return bits;
		}

		void WriteTreeInfo(BitStream *s)
		{			
			u8 *p = s->buffer;
			s->WriteB(lenmax);//*p++=lenmax;
			s->WriteB(symmin);//*p++=symmin;
			s->WriteB(symmax-symmin);//*p++=symmax-symmin;

			HuffTreeItem *h = (HuffTreeItem *)head;
			u16 c = 0;
			HuffTreeItem *i;
			u16 r;
				
			c=symmin;
			printf("\nrange=%d-%d\n",symmin,symmax);
			printf("lenmax=%d\n",lenmax);
			u8 bitmax = GetReqBits(lenmax+1);
			do{
				i = (HuffTreeItem *)Pop();
				if(i)r= i->symbol;
				else r=symmax;
				while(c<r)
				{
					printf(" %d, %d,",lenmax+1,r-c);
					//s->WriteB(lenmax+1);//*p++=lenmax+1;
					//s->WriteB(r-c);//*p++=r-c;

					s->WriteBits(lenmax+1,bitmax);//*p++=lenmax+1;
					s->WriteBits(r-c,7);//*p++=r-c;

					c=r;
				}
				if(i)
				{
				printf(" %d,",i->level);				
				//s->WriteB(i->level);//*p++=i->level;
				s->WriteBits(i->level,bitmax);//*p++=i->level;
				c++;
				}
			}while(i);
			head = h;
			printf("\n");

		}
		void ReadTreeInfo(BitStream *s, u32 *size)
		{			
			lenmax = s->ReadB();
			symmin = s->ReadB();
			symmax = s->ReadB() + symmin;

			u8 c;
			u16 o=symmin;
			u8 bitmax = GetReqBits(lenmax+1);
			while(o<=symmax)
			{
				c = s->ReadBits(bitmax);
				if(c<=lenmax)
				{
					HuffTreeItem *i = new HuffTreeItem((c<<8)+o,o);
					i->level = c;
					Add(i);
					o++;
				}
				else if(c==lenmax+1)
				{
					c = s->ReadBits(7);
					o+=c;
				}
			}
			*size = s->ReadBits(32);

			// generate prefixcodes
			{
				HuffTreeItem *i = (HuffTreeItem *)head;
				u32 c=0;
				u16 cbl,nbl;
				while(i)
				{
					cbl = i->level;
					if(!i->next)nbl=0;
					else nbl = ((HuffTreeItem *)i->next)->level;

					i->code=c;
					c=(c+1)<<(nbl-cbl);

					i=(HuffTreeItem *)i->next;
				}
			}
		}
	};
}
