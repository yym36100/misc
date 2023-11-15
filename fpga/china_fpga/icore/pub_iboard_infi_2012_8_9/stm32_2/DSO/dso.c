/*------------------------------------------------------
   FILE NAME   : main.c
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
#include "..\include\evtft.h"
#include "..\include\adc.h"
#include "..\include\hardware.h"

#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\systick.h"

#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\event.h"

#include "..\include\button.h"

#include "..\include\fpga.h"
#include "..\include\main.h"
#include "..\include\dso.h"
#include "..\include\dso_frame.h"
#include "..\include\dso_set.h"
#include "..\include\dso_menu.h"
#include "..\include\pwm.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>


static int dso_main(void);
//-------------------------------------------------------//

unsigned char dbuffer[10][512];

int read_buffer[512];

#define MEAN    1

#define DSO_TY  200 + 34 - 24
#define DSO_BY  34 - 24

#define DSO_LX  12
#define DSO_RX  412

#define DSO_LINE 1


DSO_T dso = {
	.x_scale = 6,
	.y_scale = 3,
	.coupling = COUPLING_DC,
	.trigger_type = 0,
	.trigger_level = .5, //0~1
	.offset = 0., //-1 ~ 1
	.measure_number = 0,
	.about_flag = 0,
	.main = dso_main
};

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
static int
measure(void)
{
	int sum;
	float ftemp, temp;
	int max, min;
	int i;
	const float weight[] = {
		20, 8, 4, 2, 0.8, 0.4, 0.2, 0.08, 0.04
	};


	max = read_buffer[0];
	min = read_buffer[0];
	ftemp = 0;
	sum = 0;

	for (i = 0; i < 512; i++) {
		if (read_buffer[i] > max) max = read_buffer[i];
		if (read_buffer[i] < min) min = read_buffer[i];

		temp = read_buffer[i] - 128;
		sum += (128 - read_buffer[i]);

		temp /= 128;
		temp *= temp;
		ftemp += temp;
	}
	dso.vpp = max - min;
	dso.vpp *= weight[dso.y_scale];
	dso.vpp *= 2;
	dso.vpp /= 256;

	ftemp /= 512;
	ftemp = sqrt(ftemp);

	dso.vrms = ftemp * weight[dso.y_scale];

	dso.vavg = sum;

	dso.vavg /= 512;
	dso.vavg *= 2;
	dso.vavg /= 256;

	dso.vavg *= weight[dso.y_scale];

	//MFREQ

	if ((FPGA_WR2) & 0X4000) {
		temp = FPGA_WR3;
		temp *= 65536;
		temp += FPGA_WR4;

		temp = 100000000. / temp;
		dso.frequency = temp;
	}
	fpga_ctl.b.ctl25 = 1;
	fpga.ctl();

	fpga_ctl.b.ctl25 = 0;
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
initialize(void)
{
	DSO_ACDC_OUTPUT;
	DSO_ATT_OUTPUT;

	dso_set.trigger_level();
	dso_set.xscale();
	dso_set.yscale();
	dso_set.offset();

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
int dso_main(void)
{
	int i, j, m, n;
	unsigned short int a;

	initialize();

	//clear lcd
	lcd.write_a();
	lcd.cls(COLOR_WINDOW_BACKGROUND);


	lcd.write_b();

	lcd.cls(COLOR_WINDOW_BACKGROUND);

	event = KEY_M1;


	fpga_ctl.b.ctl16 = 1;
	fpga_ctl.b.ctl17 = 0;

	fpga.ctl();

	fpga_ctl.b.ctl16 = 0;

	fpga.ctl();

	while (1) {
 star:   usb_command.capture_handle();

		if (dso_menu()) return 0;

		for (i = 0; i < sizeof(read_buffer) / 4; i++) read_buffer[i] = 0;

//		for(n=0;n<MEAN;n++){
		//reset

		for (i = 0; i < 40000; i++) if (event) goto star;
		while (!((FPGA_WR2) & 0X8000)) if (event) goto star;
		if (FPGA_WR2 & 0X2000) dso.trigged = 1;
		else dso.trigged = 0;

		fpga_ctl.b.ctl17 = 1;

		fpga.ctl();

		for (i = 0; i < 512; i++) {
			a = FPGA_CTL0;
			//		read_buffer[i] = a >>8;
			read_buffer[i] = a & 0xff;
		}
		if (j % 10 == 0) measure();
		//	}
		for (i = 0; i < 512; i++) {
			read_buffer[i] *= 25;
			read_buffer[i] /= 32;
			read_buffer[i] /= MEAN;
		}
		if (dso.coupling == COUPLING_GND) for (i = 0; i < 420; i++) dbuffer[0][i] = 100 + dso.offset * -100;
		else
			for (i = 0; i < 420; i++) {
				dbuffer[0][i] = read_buffer[i];
			}



		fpga_ctl.b.ctl16 = 1;
		fpga_ctl.b.ctl17 = 0;

		fpga.ctl();

		fpga_ctl.b.ctl16 = 0;

		fpga.ctl();


		//sel
		if (j % 2) {
			lcd_ctl.b.disp_buf = 1;
			lcd_ctl.b.write_buf = 0;
			lcd_ctl.b.csrmode = 0;
			LCD_CTL = lcd_ctl.w;
		}else {
			lcd_ctl.b.disp_buf = 0;
			lcd_ctl.b.write_buf = 1;
			lcd_ctl.b.csrmode = 0;
			LCD_CTL = lcd_ctl.w;
		}


		dso_frame.grid();

		for (n = 0; n >= 0; n--) {
			gui.set_cursor(DSO_LX, dbuffer[n][0] + 34 - 24);

			for (i = 0; i < (DSO_RX - DSO_LX); i++) {
				for (m = 0; m < DSO_LINE; m++) gui.line_to(i + DSO_LX, dbuffer[n][i] + m + 34 - 24, COLOR_LIME);
			}
		}
		dso_frame.main();

		//



		// for(n=1;n>0;n--)for(i=0;i<512;i++)dbuffer[n][i]=dbuffer[n-1][i];

		j++;

		if (j % 2) {
			lcd_ctl.b.disp_buf = 1;
			lcd_ctl.b.write_buf = 0;
			lcd_ctl.b.csrmode = 0;
			LCD_CTL = lcd_ctl.w;
		}else {
			lcd_ctl.b.disp_buf = 0;
			lcd_ctl.b.write_buf = 1;
			lcd_ctl.b.csrmode = 0;
			LCD_CTL = lcd_ctl.w;
		}
		if (j % 2) LED_ON;
		else LED_OFF;


		if (first_run == 1) {
			for (j = 0; j < 100000; j++) ;
			for (i = 0; i <= 100; i++) {
				pwm.initialize(i);
				for (j = 0; j < 20000; j++) ;
				first_run = 0;
			}
		}
	}
}
