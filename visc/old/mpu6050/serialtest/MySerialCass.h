#pragma once

#include <windows.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

typedef signed short int16_t;
typedef signed long int32_t;

typedef struct t_uartmsg{
	uint8_t header[4];
	uint16_t msg_count;
	int16_t gyro_data[3];
	int16_t accel_data[3];
    uint32_t temp_data;
	uint32_t crc;
}t_uartmsg;

class CMySerialCass
{
public:
	HANDLE m_hCommPort;
	t_uartmsg omsg;

	CMySerialCass(void);
	~CMySerialCass(void);
	int Open(void);
	int Read(unsigned char* buffer, unsigned long *bytes_read);
	int Close(void);
	int Print(void);
};
