#pragma once
#include "TWidget.h"
#include "TFrame.h"
#include "TBackground.h"

struct TWindow : public TFrame {

    TWindow(u8 x, u8 y, u8 w, u8 h, char *_title = 0, char _art = 6, u8 _attr = 0xf0) : TFrame(x, y, w, h, _title, _art, _attr) {}

    void Draw() {
        TFrame::Draw();
        // clear interior		
        u8 xs = lx + s.x + 1, ys = ly + s.y + 1;
        char linebuff[80];
        memset(linebuff, ' ', size.x - 2);
        linebuff[size.x - 2] = 0;

        //con->SetColor(rand());		
        con->SetColor(attr);

        for (int i = 0; i < size.y - 2; i++){
            con->SetCurosrPos(xs, ys + i);
            con->Write(linebuff);
        }
    }
};
