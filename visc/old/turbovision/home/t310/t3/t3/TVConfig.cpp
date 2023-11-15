#include "stdint.h"

#include "TConsole.h"
#include "TWidget.h"
#include "TLineInput.h"
#include "TScroll.h"
#include "TFrame.h"
#include "TProgressBar.h"
#include "TStaticText.h"

TConsole *TWidget::con;
u8 TWidget::lx,TWidget::ly;
bool TWidget::showCursor = 0;
bool TWidget::gredraw = 0;
bool TWidget::fredraw = 0;
//bool TContainer::f = 0;

char TLineInput::tmptext[50];

char ctext::ttext[80 + 1];
char ctext::tattr[80 + 1];


const char *TScroll::art_set[] = {
	/* 0 */ sb_simple,
	/* 1 */ sb_simple1,
	/* 2 */ sb_simple2,
	/* 3 */ sb_classic1,
	/* 4 */ sb_classic1f,
	/* 5 */ sb_classic2,
	/* 6 */ sb_classic3,
	/* 7 */ sb_arrowy
};

const char *TFrame::art_set[] = {
	/* 0 */ funky,
	/* 1 */ funky2,
	/* 2 */ funky21,
	/* 3 */ funky22,
	/* 4 */ funky3,
	/* 5 */ basic,
	/* 6 */ simple,
	/* 7 */ doublel,
};

const char *TProgressBar::art_set[] = {
	/* 0 */ "\xdb\xb0""c",
	/* 1 */ "= r"
};
