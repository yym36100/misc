#include "system.h"
#include <stdlib.h>
#include <stdio.h>


#define LED	 *(volatile unsigned long int *)(LED_BASE | 0x80000000)
unsigned long int dat[1024];

void main(void)
{
 unsigned long int i;

 LED = 0;

 for(i=0;i<1024;i++){
	 dat[i]= i;
 }
 for(i=0;i<1024;i++){
	 if (dat[i]!= i)while(1);
 }

 while(1){
 for(i=0;i<1000000;i++);
 LED = 0;
 for(i=0;i<1000000;i++);
 LED = 1;
}

 while(1);

}
