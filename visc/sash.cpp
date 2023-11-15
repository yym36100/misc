// sash.cpp : Defines the entry point for the console application.
//

// this works with cmder
// https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html

#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	printf("\033[40m");
	printf("Hello\n");
	
	// some fg/bg colors
	printf("\033[40m A \033[41m B \033[42m C \033[43m D \033[0m\n");

	// print on the same line
	for (int i = 0; i < 20; i++){		
		printf("\33[1000D %d %% ", i);		
	}

	//various colors
	for (int i = 0; i < 256; i++){
		//sys.stdout.write(u"\u001b[38;5;" + code + "m " + code.ljust(4))
		printf("\33[38;5;%dm%02x ", i,i);
	}

	//various bg colors
	for (int i = 0; i < 256; i++){		
		printf("\33[48;5;%dm%02x ", i, i);
	}

	// print u"\u001b[0m" reset and new line
	printf("\033[40m");
	printf("\33[48;5;0m");
	//printf("\33[0m \n");
	printf("\njust plain text\n");


	//print u"\u001b[1m BOLD \u001b[0m\u001b[4m Underline \u001b[0m\u001b[7m Reversed \u001b[0m"
	printf("\33[1m BOLD \33[0m\33[4m Underline \33[0m\33[7m Reversed \33[0m");

	printf("\033[40m");
	printf("\nProgress bar\n");
	for (int i = 0; i <= 50; i++){
		//back to the beginning of the line

		//bar 1
		printf("\033[100D");
		printf("[");
		//print '#'
		for (int j = 0; j < i; j++)printf("#");
		for (int j = 0; j < 50-i; j++)printf("-");
		//print ' ' 
		printf(" %02d%%]",i*2);

		//bar 2
		printf("\n\033[100D");
		printf("[");
		//print '#'
		for (int j = 0; j < i; j++)printf("#");
		for (int j = 0; j < 50 - i; j++)printf("-");
		//print ' ' 
		printf(" %02d%%]", i * 2);

		// move up
		printf("\33[1A");

		//sys.stdout.write(u"\u001b[" + str(count) + "A") # Move up
		Sleep(50);
	}
	// move down
	printf("\33[1B");
	
	return 0;
}

