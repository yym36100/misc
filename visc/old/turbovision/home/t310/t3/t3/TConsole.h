#pragma once

#define WIN32_LEAN_AND_MEAN
#include "stdint.h"

#include <windows.h>
#include <stdio.h>

#include "TObject.h"

extern char mousetext[100];


class TConsole {
public:
    enum align{ left = 0, right, center };
    u8 w, h, x, y, fg, bg;
    u8 vx, vy;
    HANDLE hcsb, hStdOut, hStdIn;
    u16 saveScreenWidth, saveScreenHeight;
    DWORD saveScreenConsoleMode;
    CONSOLE_CURSOR_INFO savecurosrinfo;
    bool insert;

    TConsole(u8 ww = 80, u8 hh = 25) : w(ww), h(hh), x(0), y(0), bg(0), fg(7) {
        insert = 0;

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        hStdIn = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hStdIn, &saveScreenConsoleMode);

        GetConsoleCursorInfo(hStdOut, &savecurosrinfo);

        CONSOLE_SCREEN_BUFFER_INFO inf;
        GetConsoleScreenBufferInfo(hStdOut, &inf);
        saveScreenWidth = inf.dwSize.X;
        saveScreenHeight = inf.dwSize.Y;


        hcsb = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hcsb);
        SetConsoleMode(hStdIn, ENABLE_MOUSE_INPUT);
        //SetConsoleMode(hStdIn, 0);

        COORD max = GetLargestConsoleWindowSize(hcsb);
        CONSOLE_SCREEN_BUFFER_INFO info2;
        GetConsoleScreenBufferInfo(hcsb, &info2);


        COORD newSize = { w, h };
        SMALL_RECT r = { 0, 0, newSize.X - 1, newSize.Y - 1 };

        SetConsoleScreenBufferSize(hcsb, newSize);
        SetConsoleWindowInfo(hcsb, TRUE, &r);
        SetConsoleScreenBufferSize(hcsb, newSize);

        SetConsoleTitle((LPSTR)"Hello");
    }

    int KbHit(void) {
        DWORD cEvents;
        INPUT_RECORD inpRec;

        while (PeekConsoleInput(hStdIn, &inpRec, 1, &cEvents) && cEvents == 1) {
            if (inpRec.EventType != KEY_EVENT) {
                ReadConsoleInput(hStdIn, &inpRec, 1, &cEvents);
                continue;
            }
            if (!inpRec.Event.KeyEvent.bKeyDown) ReadConsoleInput(hStdIn, &inpRec, 1, &cEvents);
            else return 1;
        }
        return 0;
    }

    void GetKeyEvent(TEvent &e){
        DWORD cEvents;
        INPUT_RECORD inpRec;
        static u8 lx = 255, ly = 255;
        static INPUT_RECORD previnpRec = { 0 };
        PeekConsoleInput(hStdIn, &inpRec, 1, &cEvents);
        if (cEvents == 1){
            ReadConsoleInput(hStdIn, &inpRec, 1, &cEvents);
            if (inpRec.EventType == KEY_EVENT &&
                inpRec.Event.KeyEvent.bKeyDown == 1) {
                e.key.charcode = inpRec.Event.KeyEvent.uChar.AsciiChar;
                e.key.keycode = (u8)inpRec.Event.KeyEvent.wVirtualKeyCode;
                e.what = TEvent::ekey;
            }
            if (inpRec.EventType == MOUSE_EVENT){
                //if(previnpRec.Event.MouseEvent==inpRec.Event.MouseEvent) return;
                if (memcmp(&previnpRec.Event.MouseEvent, &inpRec.Event.MouseEvent, sizeof(inpRec.Event.MouseEvent)) == 0)
                    return;
                previnpRec = inpRec;

                if ((inpRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED) &&
                    (inpRec.Event.MouseEvent.dwMousePosition.X == lx) &&
                    (inpRec.Event.MouseEvent.dwMousePosition.Y == ly))
                {
                    inpRec.Event.MouseEvent.dwEventFlags = 0;
                }

                e.what = TEvent::emouse;
                if (inpRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED){
                    i16 delta = inpRec.Event.MouseEvent.dwButtonState >> 16;

                    if (delta > 0)
                        e.mouse.event = 0x40;
                    else
                        e.mouse.event = 0x80;


                    e.mouse.x = lx;
                    e.mouse.y = ly;
                }
                else {
                    e.mouse.event = inpRec.Event.MouseEvent.dwEventFlags;

                    e.mouse.x = inpRec.Event.MouseEvent.dwMousePosition.X;
                    e.mouse.y = inpRec.Event.MouseEvent.dwMousePosition.Y;
                }



                e.mouse.buttons = inpRec.Event.MouseEvent.dwButtonState & 0xff;
                e.mouse.ctrlkeys = inpRec.Event.MouseEvent.dwControlKeyState;

                lx = e.mouse.x;
                ly = e.mouse.y;


                sprintf(mousetext, "x:%d y:%d b:%d c:%x e:%d ",
                    e.mouse.x,
                    e.mouse.y,
                    e.mouse.buttons,
                    e.mouse.ctrlkeys,
                    e.mouse.event
                    );


                //key states
                // caps 80
                // scroll 40
                // num 20
                // shift 10
                // ctrl left 8 right 4
                // alt l 2 r 1
                // https://docs.microsoft.com/en-us/windows/console/mouse-event-record-str
            }
        }
    }

    void SetCrtModeRes(unsigned w, unsigned h) {
        CONSOLE_SCREEN_BUFFER_INFO info;

        if (!GetConsoleScreenBufferInfo(hStdOut, &info)) return;

        if (info.dwSize.X == (int)w && info.dwSize.Y == (int)h) return;

        COORD max = GetLargestConsoleWindowSize(hStdOut);
        COORD newSize = { w, h };
        if (newSize.X > max.X) newSize.X = max.X;
        if (newSize.Y > max.Y) newSize.Y = max.Y;


        COORD newBufSize = newSize;
        if (info.dwMaximumWindowSize.X > newBufSize.X) newBufSize.X = info.dwMaximumWindowSize.X;
        if (info.dwMaximumWindowSize.Y > newBufSize.Y) newBufSize.Y = info.dwMaximumWindowSize.Y;

        if (!SetConsoleScreenBufferSize(hStdOut, newBufSize)) return;

        SMALL_RECT r = { 0, 0, newSize.X - 1, newSize.Y - 1 };
        if (!SetConsoleWindowInfo(hStdOut, TRUE, &r)) {
            newSize.X = info.dwMaximumWindowSize.X;
            newSize.Y = info.dwMaximumWindowSize.Y;
            SetConsoleScreenBufferSize(hStdOut, newSize);
            return;
        }

        SetConsoleScreenBufferSize(hStdOut, newSize);
    }

    ~TConsole(){
        SetCrtModeRes(saveScreenWidth, saveScreenHeight);
        SetConsoleActiveScreenBuffer(hStdOut);
        SetConsoleMode(hStdIn, saveScreenConsoleMode);
        savecurosrinfo.dwSize = 10;
        SetConsoleCursorInfo(hStdOut, &savecurosrinfo);
    }

    void SetCursorMode(bool _insert = false){
        insert = _insert;
    }
    void ShowCursor(bool show = true) {
        CONSOLE_CURSOR_INFO curinfo = { insert ? 100 : 10, show };
        SetConsoleCursorInfo(hcsb, &curinfo);
    }

    void Clear(){
        DWORD written;
        COORD dwBufferCoord = { 0, 0 };
        FillConsoleOutputCharacter(hcsb, ' ', w*h, dwBufferCoord, &written);
        FillConsoleOutputAttribute(hcsb, (bg << 4) + fg, w * h, dwBufferCoord, &written);
    }

    void SetCurosrPos(u8 xx, u8 yy){ x = xx; y = yy; }


    void SetVisCurosrPos(u8 xx, u8 yy){ vx = xx; vy = yy; }
    void RestoreCursor(){ COORD cp = { vx, vy }; SetConsoleCursorPosition(hcsb, cp); }

    void SetColor(u8 bb, u8 ff) { fg = ff; bg = bb; }
    void SetColor(u8 attr){ bg = attr >> 4; fg = attr & 0x0f; }

    void WriteAlign(char *t, u8 length, align a = center) {
        char text[80 + 1];
        memset(text, ' ', length);
        text[length] = 0;

        int len = strlen(t);
        int coffset = (int)(length - len) / 2;

        switch (a){
        case right:
            strcpy(text + length - len, t);
            break;
        case center:
            strcpy(text + coffset, t);
            if ((coffset + len) < length) text[coffset + len] = ' ';
            break;
        case left:
        default:
            strcpy(text, t);
            if (len < length) text[len] = ' ';
            break;
        }
        Write(text);
    }

    void Write(char *t) {
        int len = strlen(t);

        COORD dwBufferCoord = { 0, 0 };
        SMALL_RECT rcWriteRegion = { x, y, w, h };
        COORD dwBufferSize = { len, 1 };

        CHAR_INFO data[81];
        for (int i = 0; i < len; i++) {
            data[i].Char.AsciiChar = *t++;
            data[i].Attributes = (bg << 4) + fg;
        }
        WriteConsoleOutput(hcsb, data, dwBufferSize, dwBufferCoord, &rcWriteRegion);
        //Sleep(4);
    }

    void Write(char *t, char *a) {
        int len = strlen(t);

        COORD dwBufferCoord = { 0, 0 };
        SMALL_RECT rcWriteRegion = { x, y, w, h };
        COORD dwBufferSize = { len, 1 };

        CHAR_INFO data[81];
        for (int i = 0; i < len; i++) {
            data[i].Char.AsciiChar = *t++;
            data[i].Attributes = *a++;
        }
        WriteConsoleOutput(hcsb, data, dwBufferSize, dwBufferCoord, &rcWriteRegion);
    }

};
