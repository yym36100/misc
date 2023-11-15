/*------------------------------------------------------
   FILE NAME   : dso_set.c
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

#include "..\include\button.h"

#include "..\include\fpga.h"
#include "..\include\main.h"
#include "..\include\dso.h"
#include "..\include\dso_frame.h"
#include "..\include\dso_set.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


//---------------- Function Prototype -------------------//

static int set_trigger_level(void);
static int set_xscale(void);
static int set_yscale(void);
static int set_coupling(void);
static int set_trigger_level(void);
static int set_offset(void);





//---------------- Variable -----------------------------//
DSO_SET_T dso_set = {
	.trigger_level = set_trigger_level,
	.xscale = set_xscale,
	.yscale = set_yscale,
	.coupling = set_coupling,
	.trigger_level = set_trigger_level,
	.offset = set_offset
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
set_trigger_level(void)
{
	dac.trig_dc = dso.trigger_level * VREF;

	dac.set();

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
set_coupling(void)
{
	if (dso.coupling == COUPLING_DC) {
		DSO_ACDC_OFF;
	}
	if (dso.coupling == COUPLING_AC) {
		DSO_ACDC_ON;
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
int set_vga(float vga)
{
	/*
	      dB = 40*Vdc + 10;

	      Vdc = (dB - 10)/40;

	      Vin = Vdc *(2.2 + 6.8) / 2.2

	 */
	vga -= 10.;
	vga /= 40.;
	vga *= 9.;
	vga /= 2.2;


	if (vga > 0) {
		dac.dso_vgap = vga;
		dac.dso_vgan = 0.;
	}else {
		dac.dso_vgap = 0.;
		dac.dso_vgan = -vga;
	}

	dac.set();

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
set_yscale(void)
{
	static float vga_weight[] = {
		-6.0206,
		1.9382,
		7.9588,
		-6.0206,
		1.9382,
		7.9588,
		13.9794,
		21.9382,
		27.9588
	};
	static int flag = 0;
	int i;
	set_vga(vga_weight[dso.y_scale]);

	if (dso.y_scale > 2) {
		DSO_ATT_ON;
		if (flag == 1) for (i = 0; i < 300000; i++) ;
		flag = 0;
	}else {
		DSO_ATT_OFF;
		if (flag == 0) for (i = 0; i < 300000; i++) ;
		flag = 1;
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
set_xscale(void)
{
	fpga_ctl.b.x_scale = dso.x_scale;
	fpga.ctl();

	return 0;
}
/*-------------------------------------------------------
   NAME       :
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
set_offset(void)
{
	dac.dso_offset = dso.offset + 1 + 0.03;

	if (dac.dso_offset < 0) dac.dso_offset = 0;
	if (dac.dso_offset > VREF) dac.dso_offset = VREF;

	dac.set();

	return 0;
}
