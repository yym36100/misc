#ifndef KEY_CTL_H_
#define KEY_CTL_H_

/*
#define KEY_FOCUS_BASE      0x040020F0
#define LED_DATA_BASE       0x04002100
#define BUZZER_DATA_BASE    0x04002110
#define DAC_DATA_BASE       0x04002120*/

#define READ_KEY_FOCUS  IORD_ALTERA_AVALON_PIO_DATA(KEY_FOCUS_BASE)
#define READ_LED_DATA   IORD_ALTERA_AVALON_PIO_DATA(LED_DATA_BASE)
#define READ_BUZZER_DATA  IORD_ALTERA_AVALON_PIO_DATA(BUZZER_DATA_BASE)
#define READ_DAC_DATA   IORD_ALTERA_AVALON_PIO_DATA(DAC_DATA_BASE)

extern void key_ctl_test (void);

#endif
