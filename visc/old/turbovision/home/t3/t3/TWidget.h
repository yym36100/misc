#pragma once

#include "TObject.h"
#include "TConsole.h"

struct TWidget : public TObject {

	static TConsole *con;
	TPoint s, e;

	uint8_t flags;
	char hotkey;

	static uint8_t lx,ly;

	TWidget() : flags(0) {}

	virtual bool HandleFocusChange() { return 0;}

	virtual bool g_focusable() { return (flags&focusable)!=0;}
	virtual void s_focusable(bool b) {flags &=~focusable; if(b)flags|=focusable;}

	virtual bool g_focused() { return (flags&focused)!=0;}
	virtual void s_focused(bool b) {flags &=~focused; if(b)flags|=focused;}
	virtual void UpdateData() {}

	virtual void Draw(){
		con->SetCurosrPos(lx + s.x, ly + s.y);
		if(g_focusable()){
			if (!g_focused()) con->SetColor(0x17);
			else con->SetColor(0x2e);
		}
	}
	virtual void HandleEvent(TEvent &e) {}



	virtual uint16_t GetWidth(){ return e.x - s.x + 1; }
	virtual uint16_t GetHeight(){ return e.y - s.y + 1; }


	enum {focusable = 1<<0, focused = 1<<1};

};
