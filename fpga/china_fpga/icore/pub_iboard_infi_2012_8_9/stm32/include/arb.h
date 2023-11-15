//arb.h


#ifndef __arb_h__
#define __arb_h__


//-----------------Include files-------------------------//

//----------------- DEFINE ------------------------------//
typedef struct{
	int waveform;
	double frequency;
	double amplitude;
	double offset;
	double duty_cycle;
	double symmetry;
	int burst_state;
	int burst_number;
	double burst_cycle;
}AG_T;


typedef const struct{
	int (* main)(void);
	int (* initialize)(void);
}ARB_T;


extern ARB_T arb;
extern AG_T ag;
extern char * menu_main[2][5];

#endif //__arb_h__
