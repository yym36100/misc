// serialporttest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	// 1 open
	HANDLE hSerial;
	hSerial = CreateFile("COM3",                 // Replace with your serial port name (e.g., "COM1", "COM2")
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (hSerial == INVALID_HANDLE_VALUE) {
		// Handle error here
		printf("failed to open port\n");
		return 1;
	}

	//2 configure
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Handle error here
		return 2;
	}

	dcbSerialParams.BaudRate = 2000000;  // Change to your desired baud rate
	dcbSerialParams.ByteSize = 8;        // 8 data bits
	dcbSerialParams.StopBits = ONESTOPBIT; // 1 stop bit
	dcbSerialParams.Parity = EVENPARITY;     // No parity

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		// Handle error here
		return 3;
	}

	//3 read and write
	char buffer[256];
	DWORD bytesRead;
#if 0
	// Reading from the serial port
	if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
		// Process data in buffer
	}
#endif

	// Writing to the serial port
	char data[] = "Hello, Serial Port!";
	DWORD bytesWritten;

#define bigbuffsize (100*1024)
	char bigbuff[bigbuffsize];
	for(int i=0;i<bigbuffsize;i++){
		bigbuff[i]=i;
	}
	if (WriteFile(hSerial, bigbuff, bigbuffsize, &bytesWritten, NULL)) {
		// Data sent successfully
	}

	//4 close port
	CloseHandle(hSerial);

	return 0;
}

