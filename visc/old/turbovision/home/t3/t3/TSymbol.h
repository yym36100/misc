#pragma once
#include "TWidget.h"

struct TSymElem : public TObject{    
    char *text;
    TSymElem(char *t) :text(t) {}
};

struct TSymbol : public TWidget {
    uint8_t *idx, noItems;
    TSymElem *first;

    TSymbol(uint8_t x, uint8_t y, uint8_t *_idx,TObject &ee, char _hotkey=0) : idx(_idx), first((TSymElem*)&ee) {
        s_focusable(1);
		hotkey = _hotkey;
        s.x = x;
        s.y = y;
		e.y = s.y;
		e.x = x+8;
        noItems = first->GetNoItems();
    }

    void HandleEvent(TEvent &e) {
        switch (e.charcode){
        case '+': (*idx)++; if (*idx >= noItems)*idx = 0; /*Draw();*/ break;
        case '-': (*idx)--; if (*idx >= noItems)*idx = noItems-1; /*Draw();*/ break;
        }
    }

    void Draw() {
        char text[50];
        con->SetCurosrPos(lx + s.x, ly + s.y);
        if (!g_focused()) con->SetColor(0x17);
        else con->SetColor(0x2e);
        
		char *p = ((TSymElem*)first->GetAt(*idx))->text;
		int len = strlen(p);			
		int i,w = GetWidth();
		for(i= 0;i<w;i++){
			if(i<(w-len)/2) text[i] = ' ';
			else if(i>=(len+(w-len)/2))text[i] = ' ';
			else text[i] = *p++;
		}
		text[i] = 0;
        con->Write(text);
    }
};
