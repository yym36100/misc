#pragma once
#include "TWidget.h"

//todo fix keys
struct TLineInput : public TWidget {

public:
    static char tmptext[50];

    char *text;
    u8 i;
    u8 state;
    u8 w;
    bool insert;

    enum { idle = 0, focused, editing };


    TLineInput(u8 x, u8 y, char *tt, char _hotkey = 0) : TWidget(x, y, focusable), text(tt), state(idle) {

        w = 8;
        memset(tmptext, 0, 50);
        i = 0;
        insert = 0;
    }

    void s_focused(bool f){
        TWidget::s_focused(f);
        if (f) state = focused; else state = idle;
    }

    void HandleEvent(TEvent &e) {
        if (e.what == TEvent::ekey){
            if (state == editing){
                //consume everything while editing
                e.what = TEvent::nothing;

                if (e.key.keycode == 45) {
                    //toggle insert mode
                    insert ^= 1;
                    con->SetCursorMode(insert);
                    s_redraw(1);
                }
                if (e.key.keycode == 46) {
                    //delete
                }
                //36 35 home end
                if (e.key.keycode == 36){
                    i = 0;
                    s_redraw(1);
                }
                if (e.key.keycode == 35){
                    i = strlen(tmptext);
                    s_redraw(1);
                }
                // 37 <<< 39>>>
                if (e.key.keycode == 37){
                    if (i > 0)i--;
                    s_redraw(1);
                }
                if (e.key.keycode == 39){
                    if (i < w)i++;
                    s_redraw(1);
                }

                if (e.key.charcode == 13 || e.key.charcode == 9/* enter or tab*/){
                    strcpy(text, tmptext);
                    tmptext[i = 0] = 0;
                    state = focused;
                    s_redraw(1);
                }
                else if (e.key.charcode == 27 /* escape */){
                    tmptext[i = 0] = 0;
                    state = focused;
                    s_redraw(1);
                }
                else if (e.key.charcode >= ' ') { // todo add filtering
                    if (strlen(tmptext) <= w){
                        if (insert == 0)
                            memmove(&tmptext[i] + 1, &tmptext[i], strlen(&tmptext[i]));
                        tmptext[i++] = e.key.charcode;
                        //tmptext[i]=0;
                        s_redraw(1);
                    }
                }
                else if (e.key.charcode == 8 /*delete */)
                {
                    if (i > 0){
                        tmptext[--i] = 0;
                        s_redraw(1);
                    }
                }

            }
            else{
                //handle enter
                if (e.key.charcode == 13 || e.key.charcode == ' '){
                    state = editing;
                    i = 0;
                    //tmptext[0]=0;
                    memset(tmptext, 0, 50);
                    s_redraw(1);
                }
            }
        }
    }

    void Draw() {
        TWidget::Draw();

        con->ShowCursor(state == editing);
        if (state == editing){
            showCursor = 1;
            con->SetVisCurosrPos(lx + s.x + i, ly + s.y);
        }

        con->SetCurosrPos(lx + s.x, ly + s.y);
        con->WriteAlign(state != editing ? text : tmptext, w, TConsole::left);
    }
    u8 GetWidth() const { return w; }
};
