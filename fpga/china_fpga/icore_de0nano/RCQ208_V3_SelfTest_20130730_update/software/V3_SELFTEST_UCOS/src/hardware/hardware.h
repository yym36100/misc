#ifndef HARDWARE_H_
#define HARDWARE_H_

/*#define TEMP_DATA_BASE  0x040020A0
#define PS2_DATA_BASE   0x040020B0
#define UART_DATA_BASE  0x040020C0
#define RTC_DATAR_BASE  0x040020D0
#define IR_DATAR_BASE   0x040020E0
#define ADC_DATA_BASE   0x04002130*/

#define READ_TEMP_DATA  IORD_ALTERA_AVALON_PIO_DATA(TEMP_DATA_BASE)
#define READ_PS2_DATA   IORD_ALTERA_AVALON_PIO_DATA(PS2_DATA_REC_BASE)
#define READ_UART_DATA  IORD_ALTERA_AVALON_PIO_DATA(UART_RX_DATA_BASE)
#define READ_RTC_DATA   IORD_ALTERA_AVALON_PIO_DATA(RTC_DATA_BASE)
#define READ_IR_DATA    IORD_ALTERA_AVALON_PIO_DATA(IR_DATA_BASE)
#define READ_ADC_DATA    IORD_ALTERA_AVALON_PIO_DATA(ADC_DATA_BASE)




extern void hardware_test (void);

#endif