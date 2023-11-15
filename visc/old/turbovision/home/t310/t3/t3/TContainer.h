#pragma once
#include "TWidget.h"

//todo this is a lot like tgroup, should rework tgroup
// todo consume event concept and broadcast

struct TContainer : public TWidget{
    TWidget *first;
    u8 fc;

    TContainer(u8 x, u8 y, TObject &w) :TWidget(x, y), first((TWidget*)&w) {
        fc = find_first_focusable();

    }
    TContainer(u8 x, u8 y) : TWidget(x, y), first(0) {};
    virtual void build(){}
    ~TContainer() { destroy(); }
    virtual void destroy(){ delete first; /*((void**)this->__vfptr),10 */ first = 0; }

    bool focusable() { return find_first_focusable() != 0xff; }
	TWidget* focus() { return first ? (TWidget*)first->GetAt(fc): 0; } //todo handle no focusable

    bool g_focusable() { return focusable(); }
    void s_focusable(bool b) {/* depends on child properties */ }

    bool g_focused() { return focus()->g_focused(); }

	void s_focused(bool b, enfocus f) {		
		if(f == enfocus::first) fc = find_first_focusable();
		else if(f == enfocus::last) fc = find_last_focusable();
		else if(fc==0xff) fc = find_first_focusable();			
		focus()->s_focused(b,f);
	}

    bool DrawNeeded(){ return 1; }
    bool g_redraw() { return 1; }

    static int s_redrawh(TObject *w){ ((TWidget*)w)->s_redraw(1); return 1; }
    void s_redraw(bool b){ if (b){ if (first)first->ForEach(s_redrawh); } }

    u8 find_first_focusable() {
        TWidget *p = first;
        u8 f = 0;
        while (p){
            if (p->g_focusable()) { return f; }
            p = (TWidget*)p->next;
            f++;
        }
        return 0xff;
    }

	u8 find_last_focusable() {
        TWidget *p = first;
        u8 f = 0,lf=0xff;
        while (p){
            if (p->g_focusable()) { lf = f; }
            p = (TWidget*)p->next;
            f++;
        }
        return lf;
    }

    static bool draw_help(TWidget *w, void *args){
        hs *ss= (hs*)args;
        if (w->DrawNeeded()) { w->Draw(); w->s_redraw(0); }
		ss->w->UpdateChildLocalPos(w);
        return 1;
    }

    void Draw() {
        if (!first)return;
        u8 ox, oy;
        ox = lx; oy = ly;
        lx += s.x; ly += s.y;
		hs ss(this,0);
        forEach(draw_help,&ss);
        lx = ox; ly = oy;
    }
       
	virtual void GetFocusOffset(){}
	virtual void UpdateChildLocalPos(TWidget *w){}

	struct hs{
		TContainer *w;
		TEvent *e;
		hs(TContainer *ww, TEvent *ee):w(ww),e(ee){}
	};
    void HandleEvent(TEvent &e) {
        if (e.type == TEvent::focused)
        {
            //1. give event to focus
            u8 ox, oy;
            ox = lx; oy = ly;
            lx += s.x; ly += s.y;
			if (fc != 255) {
				GetFocusOffset();
				focus()->HandleEvent(e);
			}
            lx = ox; ly = oy;

            //1.1 e could be changed by now

            if (e.type == TEvent::focused)
            {
                //2. try to handle it		
                if (e.isKey() && e.key.charcode == '\t'){ if (FocusNext()) { e.Consume(); } }
                if (e.isKey() && e.key.charcode == 'a'){ if (FocusPrev()) { e.Consume(); } }
            }
        }

		if (e.type == TEvent::broadcast)
		{
			if((e.what == TEvent::emouse && e.mouse.buttons !=0) ||
				e.what == TEvent::ekey
				){
				//3. give to all
				if (!first)return;
				u8 ox, oy;
				ox = lx; oy = ly;
				lx += s.x; ly += s.y;

				hs ss(this,&e);
				forEach(handle_event_help, &ss);
				lx = ox; ly = oy;
			}
		}


        //3. check upward msg
        if (e.type == TEvent::upward)
        {
            if (e.msg.msg == TMsgEvent::getfocus)
            {
                u8 i = GetIndexOf(first, (TWidget*)e.msg.data);
				if(i!=0xff)
				{
					if(g_focused()){
						// already focused just set the new focus
						focus()->s_focused(0);
						fc = i;
						focus()->s_focused(1);
						e.what = TEvent::nothing;
						e.type = TEvent::focused;
					}
					else
					{
						//propagate the event upword that we need to get focused
						fc = i;

						//try to get focus
						e.type = TEvent::upward;
						e.what = TEvent::emsg;
						e.msg.msg = TMsgEvent::getfocus;
						e.msg.data = (u32)this;
					}
				}
            }
        }
    }

    static bool handle_event_help(TWidget* o, void *args) {
		hs *ss = (hs*)args;
		TEvent* e = ss->e;		
        ((TWidget*)o)->HandleEvent(*e);
		ss->w->UpdateChildLocalPos(o);
        if (e->what == TEvent::nothing) return 0;
        if (e->type == TEvent::upward) return 0;
        return 1;
    }

	virtual bool FocusPrev(){
		TWidget *p = (TWidget *)focus()->prev(first);
        u8 i = fc - 1;

		 while (p){
            if (p->g_focusable() && !p->g_focused()) {
				p->s_focused(1,enfocus::last);
                focus()->s_focused(0);
                //focus = p;
                fc = i;
                return 1;
            }
            p = (TWidget*)p->prev(first);
            i--;
        }
        //loose focus allow upper widgets to realloc focus		
        focus()->s_focused(0);
		fc = find_last_focusable();
        return 0;
	}
    virtual bool FocusNext(){
        TWidget *p = (TWidget *)focus()->next;
        u8 i = fc + 1;

        while (p){
            if (p->g_focusable() && !p->g_focused()) {
				p->s_focused(1,enfocus::first);
                focus()->s_focused(0);
                //focus = p;
                fc = i;
                return 1;
            }
            p = (TWidget*)p->next;
            i++;
        }
        //loose focus allow upper widgets to realloc focus		
        focus()->s_focused(0);
        fc = find_first_focusable();
        return 0;
    }

    static int update(TObject* o){ ((TWidget*)o)->UpdateData(); return 1; }
    void UpdateData() { if (first)first->ForEach(update); }

    void forEach(bool(*func)(TWidget*, void *), void *args) {
        TWidget *p = first;        
        while (p){
            if ((*func)(p,args) == 0) break;
            p = (TWidget *)p->next;
        }
    }
};
