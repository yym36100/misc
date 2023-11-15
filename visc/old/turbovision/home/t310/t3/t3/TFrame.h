#pragma once
#include "TStaticText.h"

#define funky "-O|ooO  "
#define funky2 "\xb2\xb2\xb2\xb2\xb2\xb2  "
#define funky21 "\xb1\xb1\xb1\xb1\xb1\xb1  "
#define funky22 "\xb0\xb0\xb0\xb0\xb0\xb0  "
#define funky3 "-O|ooO  "
#define basic "xxxxxx  "
#define simple "\xc4\xbf\xb3\xd9\xc0\xda  "
#define doublel "\xcd\xbb\xba\xbc\xc8\xc9  "

struct TFrame : public TWidget {
    char *title;
    u8 attr;

    TPoint size;

    static const char *art_set[];
    u8 arti;

    TFrame(u8 x, u8 y, u8 w, u8 h, char *_title = 0, char _arti = 6, u8 _attr = 0x07) : TWidget(x, y), size(w, h), title(_title), arti(_arti), attr(_attr) {}

    void Draw(){
        u16 w = size.x;
        u16 h = size.y;
        u16 x = s.x, y = s.y;
        char linebuff[80 + 1];
        con->SetCurosrPos(lx + s.x, ly + s.y);
        con->SetColor(attr);

        const char *border = art_set[arti];

        for (int i = 1; i < w - 1; i++) { linebuff[i] = border[0]; }
        linebuff[0] = border[5]; linebuff[w - 1] = border[1]; linebuff[w] = 0;
        char linebuff_a[80 + 1];
        memset(linebuff_a, attr, w + 1);
        if (title) {

            int tl = ctext::strlen(title);
            ctext::Draw(attr, (attr&0xf0) + 0x0a, title);
            char  *pt = ctext::ttext;
            char  *pa = ctext::tattr;
            if (tl > w - 4) tl = w - 4;

            int offs = ((w - 4) - tl) / 2;
            for (int i = 0; i < tl; i++) {
                linebuff[2 + offs + i] = *pt++;
                linebuff_a[2 + offs + i] = *pa++;
            }
            linebuff[2 + offs - 1] = border[6];
            linebuff[2 + offs + tl] = border[7];
        }
        con->Write(linebuff, linebuff_a);

        con->SetCurosrPos(lx + x, ly + y + h - 1);
        for (int i = 1; i < w - 1; i++) { linebuff[i] = border[0]; }
        linebuff[0] = border[4]; linebuff[w - 1] = border[3]; linebuff[w] = 0;
        con->Write(linebuff);

        linebuff[1] = 0;
        for (int i = 1; i < h - 1; i++) {
            linebuff[0] = border[2];
            con->SetCurosrPos(lx + x, ly + y + i);
            con->Write(linebuff);
            con->SetCurosrPos(lx + x + w - 1, ly + y + i);
            con->Write(linebuff);
        }
    }

    u8 GetWidth() const { return size.x; }
    u8 GetHeight()const { return size.y; }
};
