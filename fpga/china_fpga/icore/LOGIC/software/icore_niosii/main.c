#include "system.h"
#include <stdlib.h>
#include <stdio.h>


#define LED	 *(volatile unsigned long int *)(PIO_LED_BASE | 0x80000000)
unsigned long int dat[1024*1024];

void main(void)
{
 unsigned long int i;

 LED = 0;

 for(i=0;i<1024*1024;i++){
	 dat[i]= i;
 }
 for(i=0;i<1024*1024;i++){
	 if (dat[i]!= i){
		while(1){
			for(i=0;i<200000;i++);
		  LED = 0;
		  for(i=0;i<200000;i++);
		  LED = 1;
		}
	 }
 }

 while(1){
 for(i=0;i<10000000;i++);
 LED = 1;
 for(i=0;i<300000;i++);
 LED = 0;
}


}
