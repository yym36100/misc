/*------------------------------------------------------
   FILE NAME   : dso_menu.c
   DESCRIPTION :
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/


//-----------------Include files-------------------------//
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\include\dac.h"
#include "..\include\usart.h"
#include "..\include\adc.h"
#include "..\include\hardware.h"
#include "..\include\systick.h"
#include "..\include\fsmc.h"
#include "..\include\evtft.h"
#include "..\include\pwm.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\spi.h"
#include "..\include\flash.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\event.h"
#include "..\include\tab.h"
#include "..\include\button.h"
#include "..\include\diagram.h"
#include "..\include\infomation.h"
#include "..\include\fpga.h"
#include "..\include\main.h"
#include "..\include\dso.h"
#include "..\include\dso_frame.h"
#include "..\include\dso_set.h"
#include "..\include\dso_menu.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


//---------------- Function Prototype -------------------//


static int menu_base(void);
static int menu_trigger(void);
static int menu_measure(void);
int menu_about(void);


//---------------- Variable -----------------------------//

static int main_menu = 0;

char * menu_dso_sum[3][2][5] = {
	{
		{ "耦合方式", "电平增加", "电平减小", "电平归零", "  关  于" },
		{ " Coupling", "Level Raise", " Level Fall", " Level Zero", " About..." },
	}, {
		{ " 上升沿", " 下降沿", "电平增加", "电平减小", "电平归零" },
		{ " Posedge", " Negedge", "Level raise", " Level fall", " Level zero" },
	}, {
		{ " 频  率", " 峰峰值", " 有效值", " 平均值", "清除全部" },
		{ " Frequency", " Vpk-pk", "  Vrms", "  Varg", " Clear All" },
	}
};


MEASURE_BUFFER_T measure_buffer[4];

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
int dso_menu(void)
{
	int flag = 1;
	char * menu_dso[2][5] = {
		{ " 基 本\n 功 能", " 触 发\n 菜 单", " 测 量\n 菜 单", NULL, NULL },
		{ " Base\n Menu", " Trigger\n Menu", "Measure\n Menu", NULL, NULL }
	};
	int(*menu_func[3]) () = {
		menu_base,
		menu_trigger,
		menu_measure
	};



	if (event) {
		if (event == KEY_ESC) return 1;

		if (event == KEY_M1) {
			main_menu = 0;
			last = 0;
		}
		if (event == KEY_M2) {
			main_menu = 1;
			last = 1;
			dso.about_flag = 0;
		}
		if (event == KEY_M3) {
			main_menu = 2;
			dso.about_flag = 0;
		}
		if (event == KEY_RIGHT) {
			dso.x_scale--;
			if (dso.x_scale < 0) dso.x_scale = 0;

			dso_set.xscale();
			flag = 1;
		}
		if (event == KEY_LEFT) {
			dso.x_scale++;
			if (dso.x_scale > 13) dso.x_scale = 14;

			dso_set.xscale();
			flag = 1;
		}
		if (event == KEY_UP) {
			dso.y_scale--;
			if (dso.y_scale < 0) dso.y_scale = 0;
			dso_set.yscale();
			flag = 1;
		}
		if (event == KEY_DOWN) {
			dso.y_scale++;
			if (dso.y_scale > 8) dso.y_scale = 8;
			dso_set.yscale();
			flag = 1;
		}

		menu_func[main_menu]();         //exec
		///
		event = 0;

		if (flag) {
			lcd.write_a();
			button.drawl(menu_dso[sys.language], main_menu);
			button.drawb(menu_dso_sum[main_menu][sys.language], 6);
			lcd.write_b();
			button.drawl(menu_dso[sys.language], main_menu);
			button.drawb(menu_dso_sum[main_menu][sys.language], 6);

			fpga_ctl.b.ctl16 = 1;
			fpga_ctl.b.ctl22 = 1;

			fpga.ctl();

			fpga_ctl.b.ctl16 = 0;
			fpga_ctl.b.ctl22 = 0;

			fpga.ctl();
		}
	}

	return 0;
}

/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
menu_base(void)
{
	if (event == KEY_F1) {
		dso.coupling++;
		if (dso.coupling > 2) dso.coupling = 0;
		dso_set.coupling();
	}
	if (event == KEY_F2) {
		dso.offset += 0.05;
		if (dso.offset > 1) dso.offset = 1;
		dso_set.offset();
	}
	if (event == KEY_F3) {
		dso.offset -= 0.05;
		if (dso.offset < -1) dso.offset = -1;
		dso_set.offset();
	}
	if (event == KEY_F4) {
		dso.offset = 0;
		dso_set.offset();
	}
	if (event == KEY_F5) {
		dso.about_flag = !dso.about_flag;
	}

	return 0;
}
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
menu_trigger(void)
{
	if (event == KEY_F1) dso.trigger_type = 0;
	if (event == KEY_F2) dso.trigger_type = 1;
	if (event == KEY_F3) {
		dso.trigger_level += 0.02;
		if (dso.trigger_level > 1) dso.trigger_level = 1;
	}
	if (event == KEY_F4) {
		dso.trigger_level -= 0.02;
		if (dso.trigger_level < 0) dso.trigger_level = 0;
	}
	if (event == KEY_F5) {
		dso.trigger_level = 0.5;
	}
	dso_set.trigger_level();

	fpga_ctl.b.ctl24 = dso.trigger_type;
	fpga.ctl();

	return 0;
}
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
menu_measure(void)
{
	int i;

	if (event == KEY_F1) {
		if (dso.measure_number == 4)
			for (i = 0; i < dso.measure_number; i++) measure_buffer[i].type = measure_buffer[i + 1].type;

		dso.measure_number++;

		if (dso.measure_number > 4) dso.measure_number = 4;

		measure_buffer[dso.measure_number - 1].type = MEASURE_FREQUENCY;
	}
	if (event == KEY_F2) {
		if (dso.measure_number == 4)
			for (i = 0; i < dso.measure_number; i++) measure_buffer[i].type = measure_buffer[i + 1].type;

		dso.measure_number++;

		if (dso.measure_number > 4) dso.measure_number = 4;

		measure_buffer[dso.measure_number - 1].type = MEASURE_VPP;
	}
	if (event == KEY_F3) {
		if (dso.measure_number == 4)
			for (i = 0; i < dso.measure_number; i++) measure_buffer[i].type = measure_buffer[i + 1].type;

		dso.measure_number++;

		if (dso.measure_number > 4) dso.measure_number = 4;

		measure_buffer[dso.measure_number - 1].type = MEASURE_VRMS;
	}
	if (event == KEY_F4) {
		if (dso.measure_number == 4)
			for (i = 0; i < dso.measure_number; i++) measure_buffer[i].type = measure_buffer[i + 1].type;

		dso.measure_number++;

		if (dso.measure_number > 4) dso.measure_number = 4;

		measure_buffer[dso.measure_number - 1].type = MEASURE_VAVG;
	}
	if (event == KEY_F5) {
		dso.measure_number = 0;
	}






	return 0;
}
