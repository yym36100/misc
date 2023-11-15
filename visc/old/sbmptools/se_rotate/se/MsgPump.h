#pragma once
#include "SContainer.h"
#include "SEvent.h"
#include "Widget.h"

#define siege_event(ev){\
	siege::MsgPump *pMsgPump = siege::MsgPump::getinstance();\
	pMsgPump->AddMsg(ev);}

namespace siege{

	class MsgPump
	{
	public:
		static MsgPump* getinstance()
		{
			return &instance;
		}
		CSContainer *pEvent;
		CSContainer *pChild;

		mode m;
		CWidget *modechild;

		void deinit();
		void init();
		void AddMsg(CSEvent &p)
		{
			if(!inited){init();inited=true;}
			pEvent->AddLast(p);
		}
		void AddChild(CWidget &w)
		{
			if(!inited){init();inited=true;}
			pChild->AddLast(w);
		}
		bool IsEvent()
		{
			return pEvent->i!=0;
		}

		mode GetFirstHit(CSEvent &e)
		{
			mode res = enNone;
			CSObject *t = pChild->f;
			while(t)
			{
				res =((CWidget*)t)->HitTest(e);
				if(res!=enNone)
				{
					modechild = (CWidget*)t;
					return res;
				}

				t=t->n;
			}
		}

		void PumpMsg()
		{
			if(IsEvent())
			{
				CSObject *t = pEvent->f;
				while(t)
				{
					m = GetFirstHit((CSEvent &)t);
					switch (m)
					{
					case enNone:
						//dispatch it to all messages
						{
							CSObject *w = pChild->f;
							while(w)
							{
								((CWidget*)w)->HandleEvent((CSEvent &)t);
								w=w->n;
							}
						}
						break;
					case enMove:
						break;
					default:
						break;
					}

					CSObject *o=&pEvent->RemoveFirst();
					delete o;// don't forget this
					o=NULL;

					t=t->n;
				}
			}
		}

	private:
		bool inited;
		MsgPump(void){inited=false;pEvent=NULL;pChild=NULL;}
		~MsgPump(void){}
		MsgPump(MsgPump&); //cc
		MsgPump& operator=(MsgPump&);//as op
		static MsgPump instance;
	};

}