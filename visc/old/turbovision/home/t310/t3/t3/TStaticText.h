#pragma once
#include "TWidget.h"


struct TStaticText : public TWidget {
    char *text;
    u8 attr;

    TStaticText(u8 x, u8 y, char *_text, u8 flgs = 0, u8 _attr = 0xf0) : TWidget(x, y, flgs), text(_text), attr(_attr) {}

    void Draw() {
        con->SetCurosrPos(lx + s.x, ly + s.y); //todo add this offset inside the func
        con->SetColor(attr);
        con->Write(text);
    }

    u8 GetWidth() const { return strlen(text); }
};

struct ctext {
    static char ttext[80 + 1];
    static char tattr[80 + 1];

    static void Draw(u8 an, u8 as, char *text) {
        u8 len = ::strlen(text);

        char *pt = text;
        bool hl = false;
        int ii = 0;
        for (int i = 0; i < len; i++){
            if (*pt == '~') { hl ^= 1; pt++; continue; }
            ttext[ii] = *pt++;
            tattr[ii] = hl ? as : an;
            ii++;
        }
        ttext[ii] = 0;
        tattr[ii] = 0;
    }
    static u8 strlen(char*s) {
        u8 res = 0;
        while (*s)
            if (*s++ != '~') res++;
        return res;
    }
};

struct TSCTExt : public TStaticText {
    TSCTExt(u8 x, u8 y, char *_text, char _attr = 0xf0) : TStaticText(x, y, _text, 0, _attr) {}

    void Draw() {

        ctext::Draw(0xf0, 0xfa, text);

        con->SetCurosrPos(lx + s.x, ly + s.y);
        con->Write(ctext::ttext, ctext::tattr);
    }

    u8 GetWidth() const { return ctext::strlen(text); }

};
