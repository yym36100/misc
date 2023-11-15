#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>

#include "tv.h"

u32 totalsize = 0, dtotalsize = 0;

void* operator new(size_t count){
    totalsize += count;
    u16 sz = count;
    char* p = (char*)malloc(count + 4);
    p[0] = sz & 0xff; p[1] = sz >> 8;
    return p + 4;
}

void operator delete(void * p) {
    char *c = (char*)p;
    u16 sz = c[-4] | (c[-3] << 8);
    dtotalsize += sz;
    free((char*)p - 4);
}

u32 data1 = 36;
u32 data2 = 100;
u32 data3 = 42;

char sizetext[100];
char mousetext[100];


//u32 data3 = 100;
u32 data4 = 100;
u8 idx = 0;
u8 idx2 = 0;
u8 viscnt = 3;
u8 menu = 0;
u8 progbar;

	char text[100] = "hello";
	char text2[100] = "second";
	char text3[100] = "harom";
	char edittext[100] = {0};
	//char sizetext[100];
	char lineinp[50] = "default";



#define helptext "Change selection with the +/- keys\n"\
	"Move focus with the TAB key\n\n"\
	"Configure Channel A parameters here"\
	"Line 1\n"\
	"Line 2\n"\
	"Line 3\n"\
	"So a for a bear and a rabbit enter a bar, and the fox says ring ting ting ding ding yaa chaa chaa yuk yuk yuk\n"\
	"Last line\n"


struct Tm1 : public TContainer {
	Tm1(u8 x, u8 y) : TContainer(x,y) {};
	void build(){
		if(first) return;
		first = new TContainer (0,0,
					*new TContainer(15,0,
						*new TWindow(0,0,30,10," Channel A config")
						+*new TVertLayout(2,2,
							*new TLinearLayout(0,0,*new TSCTExt(0,0,"A~m~plitude:")+*new TValue(1,0,&data1,'m')+*new TStaticText(1,0,"mV"))						
							+*new TLinearLayout(0,0,*new TSCTExt(0,0,"~F~requency:")+*new TValue(1,0,&data2,'f')+*new TStaticText(1,0,"Hz"))						
							+*new TLinearLayout(0,0,*new TSCTExt(0,0,"~S~ignal   :")+*new TSymbol(1,0,&idx2,
								*new TSymElem("sin") 
								+*new TSymElem("cos")
								+*new TSymElem("square") 
								+*new TSymElem("triangle"),'s')
							)
						)
					)
					+*new TContainer(0,10,
						*new TWindow(0,0,45,10,"~H~elp")
						+*new TMultiLine(1,1,42,4,helptext,0x12,'h')
						+*new TProgressBar(1,6,&progbar,30,1)
						+*new TScroll(1,7,&data1,0,7)
						+*new TProgressBar(1,8,&progbar,30)
					)
			);
	}	
};

struct Tm2 : public TContainer {
	Tm2(u8 x, u8 y) : TContainer(x,y) {};
	void build(){
		if(first) return;
		first = new TContainer (15,0,
		*new TWindow(0,0,30,10," Channel B config")						
		+*new TLinearLayout(2,2,*new TStaticText(0,0,"Amplitude:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"mV"))						
		+*new TLinearLayout(2,4,*new TStaticText(0,0,"Frequency:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"Hz"))						
		+*new TLinearLayout(2,6,*new TStaticText(0,0,"Signal   :")+*new TSymbol(1,0,&idx2,
		*new TSymElem("sin") 
		+*new TSymElem("cos")
		+*new TSymElem("square") 
		+*new TSymElem("triangle"))
		)
		+*new TLinearLayout(2,8,*new TStaticText(0,0,"Phase    :")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"\xf8"))
		);
	}
};

struct Tm3 : public TContainer {
	Tm3(u8 x, u8 y) : TContainer(x,y) {};
	void build(){
		if(first) return;
		first = new TContainer (15,0,
		*new TWindow(0,0,30,10,"Miscellanious")
		+*new TLinearLayout(2,2,*new TStaticText(0,0,"Resolution:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"bit"))
		+*new TLinearLayout(2,4,*new TStaticText(0,0,"Out. buff.:")+*new TSymbol(1,0,&idx2,
		*new TSymElem("On") 
		+*new TSymElem("Off")
		)
		)
		);
	}	
};

struct Tm4 : public TContainer {
	Tm4(u8 x, u8 y) : TContainer(x,y) {};
	void build(){
		if(first) return;
		first = new TContainer (15,0,
		*new TWindow(0,0,30,20,"About",7,0x02)
		+*new TBackground(1,1,28,18,"sado ",8)
		+*new TStaticText(2,2,"myTV demonstrator",0x02)
		+*new TStaticText(2,4,"sado TECH 2017",0x02)

		+*new TStaticText(2,6, "           _____ _____ ",0,10)
		+*new TStaticText(2,7, " _____ _ _|_   _|  |  |",0,10)
		+*new TStaticText(2,8, "|     | | | | | |  |  |",0,10)
		+*new TStaticText(2,9, "|_|_|_|_  | |_|  \\___/ ",0,10)
		+*new TStaticText(2,10,"      |___|            ",0,10)
		+*new TLineInput(2,14,lineinp)
		);
	}	
};

struct Tm5 : public TContainer {
	Tm5(u8 x, u8 y) : TContainer(x,y) {};
	void build(){
		if(first) return;
		first = new TContainer (15,0,*new TStaticText(2,2,"empty",0x02));
	}	
};

int _tmain(int argc, _TCHAR* argv[])
{
    TConsole *c = new TConsole(60, 25);
    TWidget::con = c;

    TGroup *w;

   	Tm1 *m1 = new Tm1(0,0);
	Tm2 *m2 = new Tm2(0,0);
	Tm3 *m3 = new Tm3(0,0);
	Tm4 *m4 = new Tm4(0,0);
	Tm5 *m5 = new Tm5(0,0);
		
	w = new TGroup(
			*new TBackground(0,0,60,25)
			+*new TStaticText(1, 23, sizetext, TWidget::always_redraw)
			+*new TContainer(6,2,
				*new TWindow(0,0,12+3,10,"Me~n~u")
				+*new TList(1,2,12,8,&menu, *new TSymElem("Channel A")+*new TSymElem("Channel B")+*new TSymElem("Options")+*new TSymElem("About")+*new TSymElem("Nothing"),'n')
				+*new TVisContainer(&menu,*m1+*m2+*m3+*m4+*m5)
			)
		);

    c->Clear(); c->ShowCursor(false);

    while (w->Run()){

        sprintf(sizetext, "Heap used by widgets %d %s", totalsize - dtotalsize, mousetext);

        w->gredraw = 1;
        w->DrawUpdate();
        Sleep(20);
    }
    delete c; delete w;

    printf("total used : %d total freed : %d", totalsize, dtotalsize);
    //getch();
    return 0;
}
