/*
 * FILE								: adc.h
 * DESCRIPTION				: This file is gmt7 nvic.
 * Author							: XiaomaGee@Gmail.com
 * Copyright					:
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 08/26/2012
 *
 * create.
 * -------------------
 */
//-----------------Define--------------------------------//
#ifndef __ADC_H__
#define __ADC_H__
//-----------------Include files-------------------------//
#define ADC_REF 2.483

//----------------- Typedef------------------------------//

typedef  struct {
	int (* initialize)(void);
	int (* read)(int);
	double value[5];
}SYS_ADC_T;

extern SYS_ADC_T adc;
#endif //__ADC_H__
