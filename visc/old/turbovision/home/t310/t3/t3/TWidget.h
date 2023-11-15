#pragma once

#include "TObject.h"
#include "TConsole.h"

struct TWidget : public TObject {

    enum { focusable = 1 << 0, focused = 1 << 1, redraw = 1 << 2, always_redraw = 1 << 3 };
	typedef enum enfocus{first,last, current};

    static TConsole *con;
    TPoint s;

    u8 flags;

    static u8 lx, ly;

    static bool showCursor;
    static bool gredraw;
    static bool fredraw;

    TWidget() : flags(0) {}
    TWidget(u8 x, u8 y, u8 f = 0) : s(x, y), flags(f) {}

    //virtual char getHotkey() const { return 0; }

    virtual bool DrawNeeded(){ return fredraw || g_always_redraw() || g_redraw(); } //remove


    virtual bool g_redraw() { return (flags&redraw) != 0; }
    virtual void s_redraw(bool b) { flags &= ~redraw; if (b){ flags |= redraw; gredraw = 1; } }

    virtual bool g_always_redraw() { return (flags&always_redraw) != 0; }

    virtual bool g_focusable() { return (flags&focusable) != 0; }
    virtual void s_focusable(bool b) { flags &= ~focusable; if (b)flags |= focusable; }

    virtual bool g_focused() { return (flags&focused) != 0; }
    virtual void s_focused(bool b, enfocus t = current) { if (b != g_focused()) { s_redraw(1); flags ^= focused; } } // duplicate this

    virtual void UpdateData() {}
    virtual void HandleEvent(TEvent &e) {}

    virtual void Draw(){
        con->SetCurosrPos(lx + s.x, ly + s.y);
        if (g_focusable()){
            if (!g_focused()) con->SetColor(0xf0);
            else con->SetColor(0x72);
        }
    }

    virtual u8 GetWidth() const { return 1; }
    virtual u8 GetHeight()const { return 1; }

    void makeLocal(TPoint &p){
        p.x -= s.x + lx;
        p.y -= s.y + ly;
    }
};
