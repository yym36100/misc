#pragma once
#include "Obj.h"
#include "Widget.h"
#include "..\Events.h"
#include "..\Surface.h"


namespace siege
{
	namespace widgets
	{
		class CContainer :
			public CWidget
		{					
		public:
			CWidget *child;
			graphics::CSurface *surf;
			u32 handle;

			CContainer( graphics::CSurface *ss,u16 x, u16 y, u16 w, u16 h):
			CWidget(x,y,w,h),surf(ss){}
			virtual ~CContainer(void){}

			virtual u16 OnEvent(Events *e)
			{
				u16 res = 0;
				CWidget *i = child;
				while(i)
				{
					res|=i->OnEvent(e);
					i=(CWidget*)i->next;
				}	

				//handle focus change
				if(res == 2)
				{
					//handle key in container
					if(e->e == Events::keydown)
					{
						if(e->key==38)
						{
							//handle focus change
							CWidget *i = child;
							if(i->Focused)
							{
								i->Focused = false;
								while(i->next)
								{
									i = (CWidget *)i->next;
								}
								i->Focused = true;
							}
							else
							{
								while(i)
								{
									if(i->next)
									{
										if( ((CWidget *)i->next)->Focused == true)
										{
											((CWidget *)i->next)->Focused = false;
											i->Focused = true;
										}
									}
									i=(CWidget*)i->next;
								}	
							}

						}

						else
						{
							if(e->key==40)
							{
								//handle focus change
								CWidget *i = child;
								while(i)
								{
									if(i->Focused)
									{
										i->Focused = false;
										if(i->next)
										{
											((CWidget *)i->next)->Focused = true;
											break;
										}
										else
										{
											child->Focused = true;
										}
									}
									i=(CWidget*)i->next;
								}	
							}

						}
					}
				}			
			return res;
		}

		void Draw()const
		{
			//for debug only
			surf->DrawRect(rect,0xffff0000);
			CWidget *i = child;
			while(i)
			{
				i->Draw();
				i=(CWidget*)i->next;
			}			
		}

	};

};
};