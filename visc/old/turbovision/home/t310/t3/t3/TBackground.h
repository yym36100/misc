#pragma once
#include "TWidget.h"

#define pattern2 "\xb0\xb1\xb2\xb1"
#define pattern ".   ,    .   ,.   "

struct TBackground : public TWidget {
    char *pat;
    u8 attr;

    TPoint size;
    TBackground(u8 x, u8 y, u8 w, u8 h, char *_pat = pattern2, u8 _attr = 0x08) : TWidget(x, y), pat(_pat), attr(_attr), size(w, h) {}

    void Draw(){
        u16 w = size.x;
        u16 h = size.y;
        u16 xs = lx + s.x, ys = ly + s.y;
        char linebuff[81];

        //con->SetColor(rand());
        con->SetColor(attr);

        char *pp = pat;
        int pl = strlen(pat);
        int pi = 0;

        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                linebuff[j] = pp[pi++];
                if (pi == pl) pi = 0;
            }
            linebuff[w] = 0;
            con->SetCurosrPos(xs, ys + i);
            con->Write(linebuff);
        }
    }
    u8 GetWidth() const { return size.x; }
    u8 GetHeight()const { return size.y; }
};
