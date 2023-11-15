#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"

int main() {
	printf("Hello from Nios II!\n");
	int count = 0;
	int delay;
	while (1) {
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, count );
		delay = 0;
		while (delay < 2000000) {
			delay++;
		}
		printf("%d",count);
		count++;
	}
	return 0;
}
