#pragma once
#include "TSymbol.h"

struct TList : public TSymbol {


	TList(uint8_t x, uint8_t y,uint8_t w, uint8_t h, uint8_t *_idx,TObject &ee, char _hotkey=0) : TSymbol(x,y,_idx,ee,_hotkey) {        
		e.y = s.y + h;
		e.x = s.x+ w;    
	}

	void Draw() {

		uint8_t i;
		for( i=0;i<noItems;i++){
			con->SetCurosrPos(lx+s.x,ly+s.y+i);
			if(lx!=0){
				e.x = e.x;
		}
			if(i != *idx) con->SetColor(0x17);
			else {
				if (g_focused()) con->SetColor(0x2e);
				else con->SetColor(0x4e);
			}
			con->WriteAlign(((TSymElem*)first->GetAt(i))->text,GetWidth());
		}		
	}
};
