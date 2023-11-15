#pragma once
#include "TWidget.h"

struct TVisContainer : public TWidget{
	TContainer *first;
	u8 *vis, vis_old;

	TVisContainer(u8 *_vis, TObject &w) : vis(_vis), vis_old(*_vis), first((TContainer*)&w) {
		visw()->build();
	}

	TContainer* visw() { return (TContainer*)first->GetAt(*vis); }
	bool g_focusable() { return visw()->g_focusable(); }
	//void s_focusable(bool b) {/* depends on child properties */}

	bool g_focused() { return visw()->g_focused(); }
	void s_focused(bool b, enfocus f) { visw()->s_focused(b,f); }

	void Draw(){ visw()->Draw(); }
	void HandleEvent(TEvent &e) { 
		visw()->HandleEvent(e);

		//propagate focus request
		if (e.type == TEvent::upward &&
			e.msg.msg == TMsgEvent::getfocus
			) {
				//try to get focus, overwrite this
				e.msg.data = (u32)this;
		}
	}

	bool g_redraw() { return TWidget::g_redraw() || visw()->g_redraw(); }

	void UpdateData() {
		if (*vis != vis_old) {
			((TContainer*)first->GetAt(vis_old))->destroy();
			vis_old = *vis;
			visw()->build();
			visw()->s_redraw(1);
			s_redraw(1);
			fredraw = 1;
			//todo maybe destroy old, create new
		}
		visw()->UpdateData();
	}
};
