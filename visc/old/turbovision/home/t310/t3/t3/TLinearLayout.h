#pragma once
#include "TContainer.h"

struct TLinearLayout : public TContainer {
	//u8 w; lrc layouts
	TLinearLayout(u8 x, u8 y, TObject &w) : TContainer(x, y, w) {}

	void GetFocusOffset() {
		TWidget *p = first;
		TWidget *f = focus();
		while(p){
			if(p == f) break;
			lx += p->GetWidth() + p->s.x;
			p=(TWidget*)p->next;
		}
	}

	void UpdateChildLocalPos(TWidget* w) {
		lx += w->GetWidth() + w->s.x;
	}    
};
