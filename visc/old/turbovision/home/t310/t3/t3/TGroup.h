#pragma once
#include "TContainer.h"



struct TGroup : public TContainer{

    TGroup(TObject &w) : TContainer(0, 0, w)  {
        fredraw = 1;
        if (fc != 0xff)focus()->s_focused(1);
    }

	 bool FocusPrev(){
        if (!TContainer::FocusPrev()){
            //cycle around focus
			fc = find_last_focusable();
			focus()->s_focused(1);
        }
        return 1;
    }

    bool FocusNext(){
        if (!TContainer::FocusNext()){
            //cycle around focus            
			fc = find_first_focusable();
			focus()->s_focused(1);            
        }
        return 1;
    }

    void DrawUpdate(void){
        first->ForEach(update);
        if (gredraw || fredraw){
            lx = ly = 0;
			TContainer::Draw();
            gredraw = 0;
            fredraw = 0;
            con->RestoreCursor();
        }
    }

    bool Run() {

        lx = ly = 0;
        showCursor = 0;
        TEvent e;
        e.what = TEvent::nothing;
        con->SetColor(7);
        while (1){
            con->GetKeyEvent(e);
            
            if (e.what != TEvent::nothing) break;// return 1;
            if (e.what == TEvent::nothing)  return 1;
        }
        
        //1. key focus
		if(e.what==TEvent::ekey)e.type = TEvent::focused;
		if(e.what==TEvent::emouse)e.type = TEvent::broadcast;

        HandleEvent(e);

        //2. consume it?
        if (e.what == TEvent::ekey){
            if (e.key.charcode == 'k') { con->Clear(); e.Consume(); }
            if (e.key.charcode == 'q') return 0;
        }

        //3. if still not consumed broadcast to all (hotkey)
        if (e.what == TEvent::ekey)
        {
            e.type = TEvent::broadcast;
            HandleEvent(e);
        }

        con->ShowCursor(showCursor);
        con->RestoreCursor();
        return 1;
    }
};
