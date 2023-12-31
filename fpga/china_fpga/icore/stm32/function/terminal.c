#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "..\include\terminal.h"
#include "..\include\hardware.h"
#include "..\include\usart.h"


#define FSIZE   *((volatile unsigned short*)(0X1FFFF7E0))
#define SHELL_VER       "5.a.d"


int initialize(void);
int command_interpreter(void);

void func_null(void);
void func_clear(void);
void func_help(void);
void func_cpuinfo(void);
void func_read(void);
void func_reset(void);
void func_uid(void);


COMMAND_T cmd_uid = {
	.command = "uid",
	.function = func_uid,
	.next = NULL
};
COMMAND_T cmd_reset = {
	.command = "reset",
	.function = func_reset,
	.next = &cmd_uid
};
COMMAND_T cmd_read = {
	.command = "read",
	.function = func_read,
	.next = &cmd_reset
};
COMMAND_T cmd_cpuinfo = {
	.command = "cpuinfo",
	.function = func_cpuinfo,
	.next = &cmd_read
};
COMMAND_T cmd_help = {
	.command = "help",
	.function = func_help,
	.next = &cmd_cpuinfo
};

COMMAND_T cmd_clear = {
	.command = "clear",
	.function = func_clear,
	.next = &cmd_help
};

COMMAND_T cmd_null = {
	.command = "\r",
	.function = func_null,
	.next = &cmd_clear
};

static char buffer[BUFFER_SIZE];


TERMINAL_T terminal = {
	.initialize = initialize,
	.ci = command_interpreter
};

__asm void system_reset(void)
{
	MOV R0, # 1
	MSR FAULTMASK, R0
	LDR R0, = 0xE000ED0C
	LDR R1, = 0x05FA0004
	STR R1, [R0]

deadloop
	B deadloop
}


static int initialize(void) {
	usart1.printf("\x0c\r\n\r\n");
	usart1.printf("-------------------------------------\r\n");
	usart1.printf("       \033[1;31;40miShell for iBoard / iCore");
	usart1.printf("\r\n\r\n       V %s,%s\r\n", SHELL_VER, __DATE__);
	usart1.printf("-------------------------------------\r\n");
	usart1.printf("\r\n\r\n");
	usart1.printf("\033[1;34;40mroot@iCore#\033[0;37;40m");

	return 0;
}

int command_interpreter(void) {
	int i = 0;

	COMMAND_T * cp;

	if (usart1.receive_ok_flag) {
		usart1.receive_ok_flag = 0;
		memset(buffer, 0, BUFFER_SIZE);
		memcpy(buffer, usart1.receive_buffer, strlen(usart1.receive_buffer));
		memset(usart1.receive_buffer, 0, BUFFER_SIZE);

		for (i = 0; i < BUFFER_SIZE; i++) buffer[i] = tolower(buffer[i]);

		cp = &cmd_null;

		while (cp != NULL) {
			if (memcmp(buffer, cp->command, strlen(cp->command)) == 0) {
				cp->function();
				goto next;
			}
			cp = cp->next;
		}
		buffer[strlen(buffer) - 1] = 0;     //remove \r

		usart1.printf("\r\n\033[1;31;40m\"%s\" is not a command!\033[0;37;40m\r\n", buffer);
 next:   usart1.printf("\033[1;34;40mroot@iCore#\033[0;37;40m");
	}

	return 0;
}

void func_null(void) {
	usart1.printf("\r\n");
}

void func_clear(void){
	usart1.printf("\x0c");
}

void func_help(void) {
	static const char help[] = {
		"\r\n"
		"-clear: clear screen.\r\n"
		"-help: help.\r\n"
	};

	usart1.printf(help);
}

void func_cpuinfo(void) {
	usart1.printf("\r\n\r\n");
	usart1.printf("Implementer code: %s\r\n", SCB->CPUID.B.IMPLEMENTER == 0x41 ? "arm" : NULL);
	usart1.printf("Variant number: r%d\r\n", SCB->CPUID.B.VARIANT);
	usart1.printf("Part number: %s\r\n", SCB->CPUID.B.PARTNO == 0XC23 ? "Cortex-M3" : NULL);
	usart1.printf("Revision number: p%d\r\n", SCB->CPUID.B.REVISION);
	usart1.printf("Flash SIZE:%dkB\r\n\r\n", FSIZE);
}

void func_read(void) {
	char *s;
	unsigned long int temp = 0, tempb = 0;

	s = strchr(buffer, ' ');

	while (*s++ == ' ' && *s != '\0') ;
	s--;
	sscanf(s, "%x", &temp);

	tempb = (*((volatile unsigned long*)temp));

	usart1.printf("\r\n0x%08X:%08X\r\n", temp, tempb);
}

void func_reset(void) {
	system_reset();
}

void func_uid(void) {
	usart1.printf("\r\nUID is 0x%x%x%x", U_ID0, U_ID1, U_ID2);
}
