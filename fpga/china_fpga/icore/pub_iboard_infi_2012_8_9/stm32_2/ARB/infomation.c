/*------------------------------------------------------
   FILE NAME   : infomation.c
   DESCRIPTION : frame
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\infomation.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\main.h"
#include "..\include\config.h"
#include "..\include\waveform.h"
#include "..\include\arb.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//---------------- Function Prototype -------------------//
static int show_function(int, COLOR_T);
static int initialize(void);

//---------------- Variable -----------------------------//
INFOMATION_T infomation = {
	.initialize = initialize,
	.show_function = show_function
};

const char * wave_list[2][15] = {
	{
		"正弦波",
		"方波",
		"三角波",
		"锯齿波",
		"负锯齿",
		"抽样函数",
		"噪声",
		"升指数",
		"降指数",
		"正全波整流",
		"负全波整流",
		"正半波整流",
		"负半波整流",
		"高斯函数",
		"直流"
	}, {
		"Sine",
		"Square",
		"Triangle",
		"RAMP",
		"N-RAMP",
		"SINC",
		"Noise",
		"EXPR",
		"EXPF",
		"FULL_SIN_P",
		"FULL_SIN_N",
		"HALF_SIN_P",
		"HALF_SIN_N",
		"GAUSSIAN",
		"DC"
	}
};

//-----------------Function------------------------------//

static int initialize(void)
{
	BOX_T b;

	b.startx = 7;
	b.starty = 60;
	b.endx = 177;
	b.endy = 176;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK; //make_rgb565(166,189,160);
	gui.box(&b);

	return 0;
}
/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
int get_freq_range(double freq)
{
	if (freq < 0.001) return RANGE_uHz;
	else if (freq < 1.0) return RANGE_mHz;
	else if (freq < 1000.0) return RANGE_Hz;
	else if (freq < 1000000.0) return RANGE_kHz;
	else return RANGE_MHz;
}
/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int freq_to_string(char *buf, double freq)
{
	switch (get_freq_range(freq)) {
	case RANGE_uHz:
		sprintf(buf, "%.0f uHz", freq * 1000000);
		break;
	case RANGE_mHz:
		sprintf(buf, "%.3f mHz", freq * 1000);
		break;
	case RANGE_Hz:
		sprintf(buf, "%.4f Hz", freq);
		break;
	case RANGE_kHz:
		sprintf(buf, "%.3f kHz", freq / 1000.0);
		break;
	case RANGE_MHz:
		sprintf(buf, "%.4f MHz", freq / 1000000.0);
		break;
	}

	return 0;
}

/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
void fill_space(STRING_T * s)
{
	while (s->x < 170) font.printf(s, " ");
	font.printf(s, "\n");
	s->x = 12;
}

/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
show_function(int active, COLOR_T c)
{
	STRING_T s;
	char buf[20];


	font._default.single_byte = &fixedsys;


	s.x = 12;
	s.y = 65;
	s.space.line = 5;
	s.space.word = 0;
	s.color = (active == 0 ? c : COLOR_LIME);
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	//info waveform
	font.printf(&s, "%s%s", sys.language == LANGUAGE_EN ? "WAVE: " : "波形：", wave_list[sys.language][ag.waveform]);

	fill_space(&s);

	//info frequency
	s.color = (active == 1 ? c : COLOR_LIME);
	freq_to_string(buf, ag.frequency);
	font.printf(&s, "%s%s", sys.language == LANGUAGE_EN ? "FREQ: " : "频率：", buf);

	fill_space(&s);

	s.color = (active == 2 ? c : COLOR_LIME);

	//info amplitude
	if (ag.amplitude < 1.0) font.printf(&s, "%s%.0f mVpp", sys.language == LANGUAGE_EN ? "AMP: " : "幅度：", ag.amplitude * 1000);
	else font.printf(&s, "%s%.3f Vpp", sys.language == LANGUAGE_EN ? "AMP: " : "幅度：", ag.amplitude);

	fill_space(&s);

	s.color = (active == 3 ? c : COLOR_LIME);

	//info offset
	font.printf(&s, "%s%.3f Vdc", sys.language == LANGUAGE_EN ? "Offset:" : "直流偏置：", ag.offset);

	fill_space(&s);

	s.color = (active == 4 ? c : COLOR_LIME);

	//info duty_cycle
	if (ag.waveform == SQUA) font.printf(&s, "%s%.1f %%", sys.language == LANGUAGE_EN ? "Duty Cycle:" : "占空比：", ag.duty_cycle);
	else if (ag.waveform == TRI) font.printf(&s, "%s%.1f %%", sys.language == LANGUAGE_EN ? "Symmetry:" : "对称度：", ag.symmetry);

	fill_space(&s);


	return 0;
}

