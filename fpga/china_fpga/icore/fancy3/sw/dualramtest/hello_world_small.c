#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include <sys\alt_irq.h>
//#include "alt_legacy_irq.h"

int led_data[8] __attribute__ ((section (".ledram"))) = {0*65535/8.0,1*65535/8.0,0*65535/8.0,2*65535/8.0,3*65535/8.0,4*65535/8.0,5*65535/8.0,6*65535/8.0,7*65535/8.0};

volatile int counter = 0;
volatile int go = 0;
void timer_isr(void *context)
{
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE,0);//Clear TO(timeout) bit)
	counter ++;
	if(counter == 10)
	{
		go = 1;
		counter = 0;
	}
}

int main() {

	// init
	// extern int alt_irq_register (alt_u32 id, void*   context, alt_isr_func handler);
	//extern int alt_ic_isr_register(alt_u32 ic_id, alt_u32 irq, alt_isr_func isr, void *isr_context, void *flags);
	//alt_irq_register(TIMER_IRQ,0,timer_isr);
	printf("before isr enable\n");
	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID,TIMER_IRQ,timer_isr,0,0);
	alt_irq_cpu_enable_interrupts();
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE,(1<<2) | (1 << 1) | (1 << 0) );


	printf("Hello from Nios II!\n");
	int count = 0;
	int i = 0;
	while (1) {
		led_data[i] += 655;
		if(led_data[i]>65535) led_data[i]-=65535;
		i++;
		if(i==8) i = 0;
		go = 0; while(!go); go = 0;

		//printf("%d",count);
		count++;
	}
	return 0;
}
