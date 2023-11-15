#pragma once
#include "TWidget.h"
#include <stdio.h>

struct TValue : public TWidget {
	u32 *val;
	u32 copy;

	u8 w;
	char hotkey;

	TValue(u8 x, u8 y, u32 *pdata, char _hotkey = 0) : TWidget(x, y, focusable), val(pdata) {
		w = 10;//todo
		hotkey = _hotkey;
	}

	void UpdateData() { if (copy != *val){ s_redraw(1); copy = *val; } }

	void HandleEvent(TEvent &e) {
		if (e.what == TEvent::ekey){
			if (e.key.charcode == hotkey){
				(*val)++;
				e.Consume();

				//try to get focus
				e.type = TEvent::upward;
				e.what = TEvent::emsg;
				e.msg.msg = TMsgEvent::getfocus;
				e.msg.data = (u32)this;
				return;
			}
			if (e.what == TEvent::ekey &&
				e.type == TEvent::focused)
			{
				switch (e.key.charcode)
				{
				case 0:
					{
						switch (e.key.keycode)
						{
						case 33:(*val) += 10;/*s_redraw(1);*/break;
						case 34:(*val) -= 10;/*s_redraw(1);*/break;
						}
						break;
					}
				case '+': (*val)++;/* Draw(); */break;
				case '-': (*val)--; /*Draw();*/ break;
				case ' ':(*val) = 0;/* Draw();*/ break;
				case 13:
					break;
				}
			}
		}
		else if(e.what == TEvent::emouse){
			TPoint mp(e.mouse.x, e.mouse.y);
			makeLocal(mp);

			if (mp.x < w && mp.y < 1){
				if(e.mouse.buttons!=0){
					if(!g_focused()){
						//try to get focus
						e.type = TEvent::upward;
						e.what = TEvent::emsg;
						e.msg.msg = TMsgEvent::getfocus;
						e.msg.data = (u32)this;
						return ;
					}
				}
				if( e.mouse.buttons == 1)(*val)++;
				if( e.mouse.buttons == 2)(*val)--;
			}
		}
	}

	void Draw() {
		char text[20];
		TWidget::Draw();

		sprintf(text, "%d", *val);
		con->WriteAlign(text, w);
	}

	u8 GetWidth() const { return w; }
};
