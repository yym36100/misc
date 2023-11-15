#pragma once
#include "TSymbol.h"

struct TList : public TSymbol {
	//    u8 h;

	TList(u8 x, u8 y, u8 _w, u8 _h, u8 *_idx, TObject &ee, char _hotkey = 0) : TSymbol(x, y, _idx, ee, _hotkey) {
		w = _w;
		//h = _h;
	}

	void HandleEvent(TEvent &e) {
		if(e.what == TEvent::ekey) TSymbol::HandleEvent(e);
		if (e.what == TEvent::emouse && 
			(e.mouse.event >= 0x40 || e.mouse.buttons!=0)
			){
				TPoint mp(e.mouse.x, e.mouse.y);
				makeLocal(mp);

				if (mp.x < w && mp.y < noItems()){
					if(g_focused() == 1){
						if(e.mouse.buttons == 1) {*idx = mp.y;e.Consume(); return;}
						if(e.mouse.event==0x80){(*idx)++; if (*idx >= noItems())*idx = 0; /*Draw();*/e.Consume();}
						if(e.mouse.event==0x40){(*idx)--; if (*idx >= noItems())*idx = noItems() - 1; /*Draw();*/e.Consume(); return;}

					} else
					{
						//if(e.mouse.buttons == 1) {*idx = mp.y;}
						if(e.mouse.buttons == 1) {
							//try to get focus
							e.type = TEvent::upward;
							e.what = TEvent::emsg;
							e.msg.msg = TMsgEvent::getfocus;
							e.msg.data = (u32)this;
							return ;
						}
					}
				}
		}
	}
	void Draw() {
		u8 i;
		for (i = 0; i < noItems(); i++){
			con->SetCurosrPos(lx + s.x, ly + s.y + i);
			con->SetColor(i != *idx ? 0xf0 : g_focused() ? 0xd0 : 0x80);
			con->WriteAlign(((TSymElem*)first->GetAt(i))->text, w, TConsole::right);
		}
	}

	u8 GetWidth() const { return w; }
	u8 GetHeight() const { return noItems(); }
};
