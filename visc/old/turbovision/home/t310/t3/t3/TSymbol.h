#pragma once
#include "TWidget.h"

struct TSymElem : public TObject{
    char *text;
    TSymElem(char *t) :text(t) {}
};

struct TSymbol : public TWidget {

    TSymElem *first;
    u8 *idx;
    u8 copy;
    u8 w;
    char hotkey;

    TSymbol(u8 x, u8 y, u8 *_idx, TObject &ee, char _hotkey = 0) : TWidget(x, y, focusable), idx(_idx), first((TSymElem*)&ee) {
        w = 8;
        copy = *idx;
		hotkey = _hotkey;
    }
    ~TSymbol(){
        delete first;
        first = 0;
    }

    u8 noItems() const { return first->GetNoItems(); }
    void UpdateData() { if (copy != *idx){ s_redraw(1); copy = *idx; } }

    void HandleEvent(TEvent &e) {

		if (e.what == TEvent::ekey){
			if (e.key.charcode == hotkey){				
				
				//try to get focus
				e.type = TEvent::upward;
				e.what = TEvent::emsg;
				e.msg.msg = TMsgEvent::getfocus;
				e.msg.data = (u32)this;
				return;
			}
		}

		 if (e.what == TEvent::emouse && 
			(e.mouse.event >= 0x40 || e.mouse.buttons!=0)
			){
            TPoint mp(e.mouse.x, e.mouse.y);
            makeLocal(mp);

            if (mp.x < w && mp.y < 1){		

				if(e.mouse.event==0x80 || e.mouse.buttons == 1){(*idx)++; if (*idx >= noItems())*idx = 0; /*Draw();*/e.Consume();}
				if(e.mouse.event==0x40 ||e.mouse.buttons == 2){(*idx)--; if (*idx >= noItems())*idx = noItems() - 1; /*Draw();*/e.Consume(); return;}
				if(e.mouse.buttons==1 && g_focused()==0)
				{
					//try to get focus
						e.type = TEvent::upward;
						e.what = TEvent::emsg;
						e.msg.msg = TMsgEvent::getfocus;
						e.msg.data = (u32)this;
						return ;
				}
            }
        }

        if (e.what == TEvent::ekey)
        {
            u8 no_items = noItems();
            switch (e.key.keycode){
            case 33: /*pg up*/
            case 36:/* home */ *idx = 0; e.Consume(); return;

            case 34:/*pg dn*/
            case 35:/* end */ *idx = no_items - 1; e.Consume(); return;

            case 107: /*+*/
            case 39: /* righ*/
            case 40:/*down*/
                (*idx)++; if (*idx >= no_items)*idx = 0; /*Draw();*/e.Consume(); return;

            case 38:/*up  */
            case 37:/*left*/
            case 109: /*-*/
                (*idx)--; if (*idx >= no_items)*idx = no_items - 1; /*Draw();*/e.Consume(); return;

            case ' ':
            case 13: if (no_items == 2) *idx ^= 1; e.Consume(); return;
            }
        }
    }

    void Draw() {
        TWidget::Draw();
        char *p = ((TSymElem*)first->GetAt(*idx))->text;
        con->WriteAlign(p, GetWidth());
    }
    u8 GetWidth() const { return w; }
};
