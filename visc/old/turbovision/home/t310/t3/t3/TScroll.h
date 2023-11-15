#pragma once
#include "TWidget.h"
#include "TValue.h"

#define sb_simple "<-*->"
#define sb_simple1 "\x11\xc4\xf0\xc4\x10"
#define sb_simple2 "\x11\xcd\xf0\xcd\x10"

#define sb_classic1 "\x11\xb0\xfe\xb0\x10"
#define sb_classic1f "\x11\xdb\xdb\xb0\x10"
#define sb_classic2 "\x11\xb1\xfe\xb1\x10"
#define sb_classic3 "\x11\xb2\xfe\xb2\x10"
#define sb_arrowy   "\x1b\xc4\x7f\xc4\x1a"

struct TScroll : public TValue {

    static const char *art_set[];
    u8 arti;
    //char* art;

    TScroll(u8 x, u8 y, u32 *pdata, char _hotkey = 0, char ai = 3) :TValue(x, y, pdata, _hotkey), arti(ai) {
        w = 30; //todo
    }

    void Draw() {
        TWidget::Draw();
        if (g_focused())con->SetColor(0x02);
        else con->SetColor(0x12);

        u32 val2 = *val % 100;
        u16 i = 30 * val2 / 100;
        if (i > 30) i = 30;

        char text[81];
        const char *art = art_set[arti];

        text[0] = art[0];
        for (int ii = 1; ii < i; ii++) text[ii] = art[1];
        text[i] = art[2];
        for (int ii = i + 1; ii < w; ii++) text[ii] = art[3];
        text[w - 1] = art[4];
        text[w] = 0;

        con->Write(text);
    }
    u8 GetWidth() const { return w; }
};
