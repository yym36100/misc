#pragma once
#include "stdint.h"

struct TPoint {
    uint8_t x, y;
};

struct TEvent{
    uint8_t keycode;
    uint8_t shift;
    uint8_t charcode;
};

struct TObject;

typedef int (*do_something)(TObject *p); 

struct TObject {
    TObject *next;
    TObject() : next(0) {}
    ~TObject(){};

    void Add(TObject &o){
        TObject *p = this;
        while (p->next) p = p->next;
        p->next = &o;
    }

    uint8_t GetNoItems(){
        uint8_t i = 0;
        TObject *p = this;
        while (p) {
            i++;
            p = p->next;
        }
        return i;
    }

    TObject* GetAt(uint8_t i){
        TObject *p = this;
        while (p){
            if (i-- == 0) return p;
            p = p->next;
        }
        return this;
    }

	void ForEach( do_something f){
		 TObject *p = this;
        while (p){
            if((*f)(p) == 0) break;
            p = p->next;
        }
	}	
};

inline TObject& operator + (TObject& s1, TObject& s2){
    s1.Add(s2);
    return s1;
}