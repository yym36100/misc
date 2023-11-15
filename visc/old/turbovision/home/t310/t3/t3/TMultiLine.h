#pragma once
#include "TWidget.h"

struct TMultiLine : public TWidget {
	char *text;
	u8 attr;
	char hotkey;
	u8 yoffset;
	TPoint size;

	TMultiLine(u8 x, u8 y, u8 w, u8 h, char *_text, u8 _attr = 0xf0, char _hotkey = 0)
		: TWidget(x, y, focusable), size(w, h), text(_text), attr(_attr), yoffset(0), hotkey(_hotkey) {}

	char* GetLine(u8 line){
		char *p = text;
		while (line--) while (*p) if (*p++ == '\n') break;
		return p;
	}

	u8 GetNoLines(){
		char *p = text;
		u8 res = 0;
		u8 cnt = 0;
		while (*p) {
			if (*p++ == '\n') { cnt = 0; res++; }
			if (cnt++ == size.x) res++;
		}
		return res;
	}

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

		if (e.what == TEvent::ekey){
			switch (e.key.keycode){
		case 33: /*pg up*/
		case 36:/* home */ yoffset = 0; s_redraw(1);e.Consume(); break;

		case 34:/*pg dn*/
		case 35:/* end */ yoffset = GetNoLines() - size.y; s_redraw(1);e.Consume();; break;

		case 107: /*+*/
		case 39: /* righ*/
		case 40:/*down*/
			if (yoffset < (GetNoLines() - size.y)){ yoffset++; s_redraw(1);}e.Consume(); break;

		case 38:/*up  */
		case 37:/*left*/
		case 109: /*-*/
			if (yoffset > 0){ yoffset--; s_redraw(1); } e.Consume();break;
			}
		}
		if (e.what == TEvent::emouse && 
			(e.mouse.event >= 0x40)
			){
				TPoint mp(e.mouse.x, e.mouse.y);
				makeLocal(mp);

				if (mp.x < size.x && mp.y < size.y){				
					if(e.mouse.event==0x80){ if (yoffset < (GetNoLines() - size.y)){ yoffset++; s_redraw(1); e.Consume();}return;}
					if(e.mouse.event==0x40){if (yoffset > 0){ yoffset--; s_redraw(1); e.Consume();} return;}
				}
		}
	}


	void Draw() {
		char linebuff[81];
		char *p = GetLine(yoffset);

		if (g_focused()) con->SetColor(0x70);
		else con->SetColor(0xf0);

		int x, y;
		for (y = 0; y < size.y && *p; y++){
			for (x = 0; x < size.x && *p; x++){
				if (*p == '\n') { p++; break; }
				linebuff[x] = *p++;
			}
			for (; x < size.x; x++) linebuff[x] = ' ';
			linebuff[x] = 0;
			con->SetCurosrPos(lx + s.x, ly + s.y + y);
			con->Write(linebuff);
		}

		for (; y < size.y; y++){
			for (x = 0; x < size.x; x++) linebuff[x] = ' ';
			linebuff[x] = 0;
			con->SetCurosrPos(lx + s.x, ly + s.y + y);
			con->Write(linebuff);
		}
	}

	u8 GetWidth() const { return size.x; }
	u8 GetHeight()const { return size.y; }
};
