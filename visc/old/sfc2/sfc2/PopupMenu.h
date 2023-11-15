#pragma once
#include "SWindow.h"

namespace sg
{
	class PopupMenu: public SWindow
	{
	public:
		u16 code;
		PopupMenu(void);

		u16 PopupMenu::GetWidth(u16 *texts[], u8 nritem);
		PopupMenu(u16 x,u16 y,u16 *texts[],u8 nritem, SWindow *w,u16 code);

		virtual ~PopupMenu(void);
	};
}
