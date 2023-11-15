#pragma once
#include "TWidget.h"

struct TValue : public TWidget {
	uint32_t *val;

	TValue(uint8_t x, uint8_t y, uint32_t *pdata, char _hotkey = 0) : val(pdata) {
		s_focusable(1);
		hotkey = _hotkey;
		s.x = x;
		s.y = y;
		e.y = s.y;
		e.x = x+8;
	}

	void HandleEvent(TEvent &e) {		
		switch (e.charcode)
		{
		case 0:
			{
				switch(e.keycode)
				{
				case 33:(*val)+=10;/* Draw(); */break;
				case 34:(*val)-=10; /*Draw();*/ break;
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

	void Draw() {
		char text[50];
		con->SetCurosrPos(lx + s.x, ly + s.y);
		if (!g_focused()) con->SetColor(0x17);
		else con->SetColor(0x2e);

		sprintf(text, "%d", *val);
		
		con->WriteAlign(text,GetWidth());
	}

};