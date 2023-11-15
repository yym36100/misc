#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>

#include "TConsole.h"
#include "TStaticText.h"
#include "TValue.h"
#include "TGroup.h"
#include "TSymbol.h"
#include "TFrame.h"
#include "TMultiLine.h"
#include "TEditBox.h"
#include "TScroll.h"
#include "TList.h"
#include "TContainer.h"
#include "TVisContainer.h"
#include "TLinearLayout.h"

#define helptext "But waht if the\ntext is too long\nalma\na\nfa\nalatt\nnyari\npiros\nalma"

TConsole *TWidget::con;
uint8_t TWidget::lx,TWidget::ly;

static uint32_t totalsize = 0;
static uint32_t dtotalsize = 0;
void* operator new  ( size_t count ){
	totalsize+=count;
	return malloc(count);
}

void operator delete(void * p)
{
	dtotalsize++;
  free(p);
}

int _tmain(int argc, _TCHAR* argv[])
{
	TConsole c(60, 25);
	TEvent e;

	TWidget::con = &c;

	TGroup *w;
	uint32_t data1 = 36;
	//uint32_t data2 = 100;
	//uint32_t data3 = 100;
	//uint32_t data4 = 100;
	//uint8_t idx = 0;
	uint8_t idx2 = 0;
	//uint8_t viscnt = 3;
	uint8_t menu = 0;

	char text[100];
	char edittext[100] = {0};
	
	w = new TGroup(
		*new TStaticText(1, 23, text)
		+*new TContainer(2,0,
			/**new TFrame(0,0,12+3,10,"Menu")
			+*/*new TList(1,2,12,8,&menu,
				*new TSymElem("Channel A")
				+*new TSymElem("Channel B")
				+*new TSymElem("Options")
				)
				+*new TVisContainer(&menu,
					*new TContainer (15,0,
						/**new TFrame(0,0,30,10," Channel A config")						
						+*/*new TLinearLayout(2,2,*new TStaticText(0,0,"Amplitude:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"mV"))						
						+*new TLinearLayout(2,4,*new TStaticText(0,0,"Frequency:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"Hz"))						
						+*new TLinearLayout(2,6,*new TStaticText(0,0,"Signal   :")+*new TSymbol(1,0,&idx2,
							*new TSymElem("sin") 
							+*new TSymElem("cos")
							+*new TSymElem("square") 
							+*new TSymElem("triangle"))
						)						
					)
					+*new TContainer (15,0,
						/**new TFrame(0,0,30,10," Channel B config")						
						+*/*new TLinearLayout(2,2,*new TStaticText(0,0,"Amplitude:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"mV"))						
						+*new TLinearLayout(2,4,*new TStaticText(0,0,"Frequency:")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"Hz"))						
						+*new TLinearLayout(2,6,*new TStaticText(0,0,"Signal   :")+*new TSymbol(1,0,&idx2,
							*new TSymElem("sin") 
							+*new TSymElem("cos")
							+*new TSymElem("square") 
							+*new TSymElem("triangle"))
						)
						+*new TLinearLayout(2,8,*new TStaticText(0,0,"Phase    :")+*new TValue(1,0,&data1)+*new TStaticText(1,0,"\xf8"))
					)
					+*new TContainer (15,0,
						*new TFrame(0,0,30,10,"Miscellanious")
						+*new TStaticText(2,2,"item 3")
					)
				)
			)			
		);

/*
	w = new TGroup(
		*new TStaticText(1, 23, text) 
		+*new TList(1,1,7,10,&idx2,
			*new TSymElem("First")
			+*new TSymElem("Masodik")
			+*new TSymElem("Dritte")			
			)
			+*new TFrame(0,0,8+2,10+2+1)
		+*new TValue(24,5,&data1)
		+*new TSymbol(24, 3, &idx, 
			*new TSymElem("sin") +
			*new TSymElem("cos") +
			*new TSymElem("square") +
			*new TSymElem("triangle"),
			's'
		)
		+*new TVisContainer(&idx2,
			*new TValue(16,18,&data3)
			+*new TContainer(
				*new TStaticText(1,20,"cont1_1")
				+*new TStaticText(1,21,"cont1_2")
				+*new TValue(1,22,&data2)
				+*new TValue(16,19,&data3)
			,0,0)		
			+*new TContainer(
				*new TStaticText(1,20,"cont2_1")
				+*new TStaticText(1,21,"cont2_2")
				+*new TValue(1,22,&data2)
				+*new TValue(16,22,&data3)
			,30,0)		
		)
						
		);
*/
	c.Clear();
	c.ShowCursor(false);

	sprintf(text,"TObject = %d TWidget = %d TValue = %d total = %d", sizeof(TObject),sizeof(TWidget),sizeof(TValue), totalsize);

	w->Run();

	return 0;
}

