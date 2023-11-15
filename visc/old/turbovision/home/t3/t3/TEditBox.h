#pragma once
#include "TWidget.h"

struct TEditBox : public TWidget {

private:
	typedef TWidget super;
public:
	char *text;
	char tmptext[50];
	uint8_t i;
	uint8_t state;
	enum {idle=0,focused, editing};
	enum {max_len=7};


	TEditBox(uint8_t x, uint8_t y, char *tt, char _hotkey = 0) : text(tt),state(idle) {
		s_focusable(1);
		hotkey = _hotkey;
		s.x = x;
		s.y = y;
		e.y = s.y;
		e.x = x+8;

		tmptext[0]=0;
		i = 0;
	}

	void s_focused(bool f){
		super::s_focused(f);
		if(f) state = focused;
		else state = idle;
	}

	void HandleEvent(TEvent &e) {		
		if(state == editing){

			if(e.charcode == 13 || e.charcode == 9/* enter or tab*/){
				strcpy(text, tmptext);
				tmptext[i=0]=0;
				state = focused;
			} else if( e.charcode == 27 /* escape */){
				tmptext[i=0]=0;
				state = focused;
			} else if( e.charcode >='a' && e.charcode <='z' /* numeric */) {
				if(i<=max_len){
				tmptext[i++]=e.charcode;
				tmptext[i]=0;
				}
			} else if (e.charcode ==  8 /*delete */)
			{
				if(i>0){
					tmptext[--i] = 0;
				}
			}

		}else{
			//handle enter
			if(e.charcode == 13 || e.charcode == ' '){
				state = editing;
				i = 0;
				tmptext[0]=0;
			}
		}
		/*Draw();*/
	}

	void Draw() {	
		super::Draw();		
		con->ShowCursor(state == editing);
		con->SetVisCurosrPos(s.x+i,s.y);
		
		con->Write("        ");
		con->SetCurosrPos(lx+s.x,ly+s.y);
		con->Write(state!=editing? text : tmptext);
	}

};

struct TValueEdit : public TEditBox{
	TValueEdit(uint8_t x, uint8_t y, char *tt, char _hotkey = 0) : TEditBox(x,y,tt,_hotkey) {}	
};