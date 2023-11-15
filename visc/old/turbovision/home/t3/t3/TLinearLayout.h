#pragma once
#include "TContainer.h"

struct TLinearLayout : public TContainer {	
	TLinearLayout(uint8_t x, uint8_t y,TObject &w) : TContainer(x,y,w) {} 

	static int draw_help(TObject *w){ 

		((TWidget*)w)->Draw();
		lx +=((TWidget*)w)->GetWidth()+((TWidget*)w)->s.x;
		return 1;
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
};
