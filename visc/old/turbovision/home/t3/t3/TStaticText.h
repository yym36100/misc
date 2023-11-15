#pragma once
#include "TWidget.h"


struct TStaticText : public TWidget {
    char *text;
    char attr;

    TStaticText(uint8_t x, uint8_t y, char *_text, char _attr = 0x7) : text(_text), attr(_attr) {        
        s.x = x;
        s.y = y;
    }

    ~TStaticText(){
        //if (text) delete[] text;
    }

    void Draw() {
        con->SetCurosrPos(lx + s.x, ly + s.y);
        con->SetColor(attr);
        con->Write(text);
    }
	uint16_t GetWidth() { return strlen(text);}
};

struct TSCTExt : public TStaticText {
    TSCTExt(uint8_t x, uint8_t y, char *_text, char _attr = 0x07) : TStaticText(x, y, _text, _attr) {}

    void Draw() {
        uint8_t len = strlen(text);
        char *ttext = new char[len];
        char *tattr = new char[len]; 

        char *pt = text;
        bool hl = false;
        int ii = 0;
        for (int i = 0; i < len; i++){
            if (*pt == '~') { hl ^= 1; pt++; continue; }
            ttext[ii] = *pt++;
            tattr[ii] = hl ? 0x0a : 0x07;
            hl = 0;
            ii++;
        }
        ttext[ii] = 0;

        con->SetCurosrPos(lx+s.x, ly+s.y);
        con->SetColor(~attr);
        con->Write(ttext,tattr);

        delete[] ttext;
        delete[] tattr;
    }
};