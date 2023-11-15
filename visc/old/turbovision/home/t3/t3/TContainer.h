#pragma once
#include "TWidget.h"

//todo this is a lot like tgroup
struct TContainer : public TWidget{
	TWidget *focus, *first;

	bool focusable;	
	uint8_t ox, oy;

	TContainer(uint8_t x, uint8_t y,TObject &w) : first((TWidget*)&w), focus(0),focusable(0) {
		TWidget *p = find_first_focusable();
		if(p){ focusable = true;focus = p; }	
		s.x = x;
		s.y = y;
	}


	bool g_focusable() { 
			return focusable;
	}
	void s_focusable(bool b) {/* depends on child properties */}

	bool g_focused() { return focus->g_focused();}
	void s_focused(bool b) { 
		if(b) focus = find_first_focusable();
		focus->s_focused(b);
	}

	TWidget* find_first_focusable() {
		TWidget *p = first;
		while (p){
			if(p->g_focusable()) { return p;}
			p = (TWidget*)p->next;
		}
		return 0;
	}


	static int draw_help(TObject *w){ 
	/*	lx = ox + s.x;
		ly = oy + s.y;*/
		((TWidget*)w)->Draw();return 1;
	}
	void Draw(){ 
		ox = lx;
		oy = ly;
		lx +=s.x;
		ly +=s.y;
		first->ForEach(draw_help); 
		lx = ox;
		ly = oy;
	}
	void HandleEvent(TEvent &e) {
		focus->HandleEvent(e);
	}


	bool HandleFocusChange() {
		if (!focus->HandleFocusChange()) return FocusNext(); 
		return 1;
	}

	int FocusNext(){
		TWidget *p = focus;
		
		while (p){			
			if (p->g_focusable() && !p->g_focused()) {
				p->s_focused(1);
				focus->s_focused(0);
				focus = p;
				return 1;
			}
			p = (TWidget*)p->next;		
		}
		//loose focus allow upper widgets to realloc focus
		//focus->s_focused(0);
		return 0;
	}


		static int update_help(TObject* o){ ((TWidget*)o)->UpdateData(); return 1;}

	void UpdateData() {		
		first->ForEach(update_help);		
	}

	/* todo uint16_t GetWidth(){ }
	uint16_t GetHeight(){ }*/	
};
