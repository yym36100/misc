#pragma once
#include "stdint.h"

struct TPoint {
    u8 x, y;
    TPoint() : x(0), y(0) {}
    TPoint(u8 xx, u8 yy) : x(xx), y(yy) {}
};

struct TKeyEvent{
    u8 keycode;
    u8 shift;
    u8 charcode;
};

struct TMouseEvent{
    u8 x, y;
    u8 buttons;
    u8 ctrlkeys;
    u8 event;
};


struct TMsgEvent{    
    enum {getfocus = 0, releasefocus};
    u32 data;
    u8 msg;
};

struct TEvent{
    enum {focused = 0, broadcast, upward} type;
    enum { nothing = 0, ekey, emouse, emsg } what;
    union {
        TKeyEvent key;
        TMouseEvent mouse;
        TMsgEvent msg;
    };
    void Consume() { what = nothing; }
    bool isKey() { return what == ekey; }
};

struct TObject;
typedef int(*do_something)(TObject *p);

#pragma pack(1) // affects derived classes also
struct TObject {
    TObject *next;
    TObject() : next(0) {}

    virtual ~TObject(){
        //delete all
        TObject *p = this->next;
        if (p)delete p;
        /*if(!p) return;
        TObject *pn = p->next;
        while(p){
        delete p;
        p = pn;
        pn = pn->next;
        }*/
    }

    TObject& Add(TObject &o){
        TObject *p = this;
        while (p->next) p = p->next;
        p->next = &o;
        return *this;
    }

    u8 GetNoItems(){
        u8 i = 0;
        TObject *p = this;
        while (p) {
            i++;
            p = p->next;
        }
        return i;
    }

	TObject* prev(TObject *first){
		TObject *p = first;
		while(p){
			if(p->next == this )  return p;
			p = p->next;
		}
		return 0;
	}

    TObject* GetAt(u8 i){
        TObject *p = this;
        while (p){
            if (i-- == 0) return p;
            p = p->next;
        }
        return this;
    }
	TObject* operator[](int n){
		return GetAt(n);
	}

    u8 GetIndexOf(TObject *first, TObject *item){
        TObject *p = first;
        u8 i = 0;
        while (p){
            if (p == item) return i;
            p = p->next;
            i++;
        }
        return 0xff;
    }

    void ForEach(do_something f){
        TObject *p = this;
        while (p){
            if ((*f)(p) == 0) break;
            p = p->next;
        }
    }   
};

inline TObject& operator + (TObject& s1, TObject& s2) { return s1.Add(s2); }
