#pragma once
#include "TContainer.h"

struct TVertLayout : public TContainer {
	//u8 w; lrc layouts
	TVertLayout(u8 x, u8 y, TObject &w) : TContainer(x, y, w) {}

	void GetFocusOffset() {
		TWidget *p = first;
		TWidget *f = focus();
		while(p){
			if(p == f) break;
			ly +=p->GetHeight()+ p->s.y;
			p=(TWidget*)p->next;
		}
	}

	void UpdateChildLocalPos(TWidget* w) {
		ly +=w->GetHeight()+ w->s.y;
	}    
};
