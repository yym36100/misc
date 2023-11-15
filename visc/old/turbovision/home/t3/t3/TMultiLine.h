
#pragma once
#include "TWidget.h"


struct TMultiLine : public TWidget {
	char *text;
	char attr;
	uint8_t yoffset;

	TMultiLine(uint8_t x, uint8_t y,uint8_t w, uint8_t h, char *_text, char _attr = 0x1e)
		:text(_text), attr(_attr),yoffset(0) {        
			s_focusable(1);
			s.x = x; s.y = y;
			e.x = x + w - 1;
			e.y = y + h - 1;
	}
	char* GetLine(uint8_t line){
		char *p = text;
		while(line--){
			while(*p){
				if(*p++=='\n') {break;}
			}
		}
		return p;
	}

	void HandleEvent(TEvent &e) {
		switch (e.charcode){
		case '+': yoffset++; /*Draw(); */break;
		case '-': if(yoffset>0){yoffset--; /*Draw();*/} break;
		}        
	}

	void Draw() {
		char *linebuff = new char[GetWidth()];
		char *p = GetLine(yoffset);

		if(g_focused())
			con->SetColor(0x1e);
		else
			con->SetColor(0x07);

		int x, y;
		for(y=0;y<GetHeight() && *p;y++){

			for(x=0;x<GetWidth() && *p;x++){
				if(*p == '\n') { p++;break; }
				linebuff[x] = *p++;
			}
			for(;x<GetWidth()-1;x++)
				linebuff[x] = ' ';
			linebuff[x] = 0;
			con->SetCurosrPos(lx+s.x, lx+s.y+y);		
			con->Write(linebuff);
		}		
	}
};