#pragma once
#include "TWidget.h"

struct TGroup : public TWidget{
	TWidget *focus, *first;

	TGroup(TObject &w) : first((TWidget*)&w), focus(0) {}

	void Draw(){}
	
	static int draw_help(TObject* o){ ((TWidget*)o)->Draw(); return 1;}
	static int update_help(TObject* o){ ((TWidget*)o)->UpdateData(); return 1;}

	void DrawAll() {		
//		lx = ly = 0;
		first->ForEach(update_help);
		first->ForEach(draw_help);
		con->RestoreCursor();
	}

	void Init() {
		// set first one to focused		
		TWidget *p = first;
		while (p){
			if (p->g_focusable()){
				p->s_focused(1);
				focus = p;
				break;
			}
			p = (TWidget*)p->next;
		}
	}
	void AllHandleEvent(TEvent &e){
		if(focus) focus->HandleEvent(e);
		DrawAll();
		
	}
	void FocusNext(){
		TWidget *p = focus;
		uint8_t cnt=1;
		while (p){			
			if (p->g_focusable() && !p->g_focused()) {
				p->s_focused(1);
				focus->s_focused(0);
				focus = p;
				break;
			}
			p = (TWidget*)p->next;
			if (!p){
				p = first;
				if(cnt--==0)break;
			}
		}
	}

	bool AllHandleHotkey(TEvent& e){
		TWidget *p = first;
		while (p){
			if(p->g_focusable()) {
				if( p->hotkey == e.charcode){
				focus->s_focused(0);
				p->s_focused(1);
				focus = p;
				return true;		
				}
			}
			p = (TWidget*)p->next;
		}
		return false;
	}

	void Run() {
		Init();
		DrawAll();

		TEvent e;
		while (1){
			
			lx = ly = 0;
			e.charcode = 255;
			e.keycode= 255;
			con->GetKeyEvent(e);
			con->SetColor(7);
			
			if(e.charcode ==255 && e.keycode==255) continue;
			con->Clear();
			if(AllHandleHotkey(e)){
				DrawAll();
				continue;
			}

			switch (e.charcode){
			case 'q': return;
			case '\t':	
				if(focus)
				if (!focus->HandleFocusChange()) FocusNext(); 
				DrawAll();
				
				break;
			default: AllHandleEvent(e);
				Sleep(20);
			}
			con->RestoreCursor();

		}
	}
};
