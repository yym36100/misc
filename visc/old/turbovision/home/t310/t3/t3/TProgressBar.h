#pragma once
#include "TWidget.h"
#include "TValue.h"

struct TProgressBar : public TWidget {

    u8 *data;
    u8 copy;
    u8 w;

    static const char *art_set[];
    u8 arti;

    TProgressBar(u8 x, u8 y, u8 *pdata, u8 _w = 30, char _arti = 0) :TWidget(x, y), arti(_arti), data(pdata) {
        w = _w;
        copy = *data;
    }

    void UpdateData() { if (copy != *data){ s_redraw(1); copy = *data; } }

    void DrawBar(char* text, u8 start, u8 mid, u8 stop) {
        int ii = 0;
        const char *art = art_set[arti];

        for (; ii < start; ii++)text[ii] = ' ';
        for (; ii < mid; ii++)  text[ii] = art[0];
        for (; ii < stop; ii++) text[ii] = art[1];
        text[ii] = 0;
    }

    void Draw() {
        TWidget::Draw();
        con->SetColor(0x17);

        u8 barw, to;
        u16 i;
        char text[100];
        char text2[5];
        const char *art = art_set[arti];

        switch (art[2]){
        case 'l':
            barw = w - 4;
            i = barw* *data / 255;
            to = 0;
            DrawBar(text, 4, i + 4, w);
            break;
        case 'r':
            barw = w - 4;
            i = barw* *data / 255;
            to = i;
            DrawBar(text, 0, i, w);
            break;
        case 'c':
        default:
            barw = w;
            i = barw* *data / 255;
            to = (barw) / 2;
            DrawBar(text, 0, i, barw);
            break;
        }
        sprintf(text2, "%d%%", 100 * *data / 255);
        if (art[2] == 'c')to -= strlen(text2) / 2;
        if (art[2] != 'n'){
            for (u8 i = 0; i < strlen(text2); i++){
                *(text + to + i) = text2[i];
            }
        }
        con->Write(text);
    }

    u8 GetWidth() const { return w; }
};
