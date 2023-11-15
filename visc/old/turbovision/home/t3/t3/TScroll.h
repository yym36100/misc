 #pragma once
#include "TWidget.h"
#include "TValue.h"

#define sb_simple "<-*->"
#define sb_simple1 "\x11\xc4\xf0\xc4\x10"
#define sb_simple2 "\x11\xcd\xf0\xcd\x10"

#define sb_classic1 "\x11\xb0\xfe\xb0\x10"
#define sb_classic1f "\x11\xdb\xdb\xb0\x10"
#define sb_classic2 "\x11\xb1\xfe\xb1\x10"
#define sb_classic3 "\x11\xb2\xfe\xb2\x10"

struct TScroll : public TValue {
	
	char *art;
	TScroll(uint8_t x, uint8_t y, uint32_t *pdata, char _hotkey = 0,char *_art = sb_classic1f) :art(_art), TValue(x,y,pdata,_hotkey) {		
		e.x = x+10;
		//s_focusable(0);
	}

	void Draw() {
		TWidget::Draw();
		if(g_focused())con->SetColor(0x02);
		else con->SetColor(0x12);
//		char text[50] = "\x11--------\x10";
		uint16_t i = 7* *val/100;
		if(i>7) i=7;
		i++;
		//text[1+i] = 0xf0;
		char text[11];

		text[0] =  art[0];		
		for(int ii=1;ii<i;ii++) text[ii] = art[1];
		text[i] = art[2];
		for(int ii=i+1;ii<10;ii++) text[ii] = art[3];
		text[9] =  art[4];
		text[10] = 0;

		con->Write(text);
	}

};
