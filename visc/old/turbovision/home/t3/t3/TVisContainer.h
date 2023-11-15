#pragma once
#include "TWidget.h"

//todo this is a lot like tgroup
struct TVisContainer : public TWidget{
	TWidget *first, *visw;	
	uint8_t *vis, vis_old;

	TVisContainer(uint8_t *_vis,TObject &w) : vis(_vis),vis_old(*_vis) , first((TWidget*)&w){
		visw = (TWidget *)first->GetAt(*vis);		
	}


	bool g_focusable() { return visw->g_focusable(); }
	//void s_focusable(bool b) {/* depends on child properties */}

	bool g_focused() { return visw->g_focused();}
	void s_focused(bool b) { visw->s_focused(b);}
	
	void Draw(){ visw->Draw();}
	void HandleEvent(TEvent &e) {visw->HandleEvent(e);}

	bool HandleFocusChange() {return visw->HandleFocusChange();}

	virtual void UpdateData() {
		if (*vis != vis_old){
			vis_old = *vis;
			visw = (TWidget *)first->GetAt(*vis);		
		}
	}

	/* todo uint16_t GetWidth(){ }
	uint16_t GetHeight(){ }*/	
};
 