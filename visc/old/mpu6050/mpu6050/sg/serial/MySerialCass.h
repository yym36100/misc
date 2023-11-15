#pragma once

#include <windows.h>

namespace sg{
	namespace com{

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

		struct t_stats{
			uint32_t readfile, bytesread,notenoughdata,crc;
		};

		class CMySerialCass
		{
		public:
			CRITICAL_SECTION cs;
			HANDLE threadHandle;
			HANDLE m_hCommPort;
			t_uartmsg omsg;

			t_stats mystats;
			

			t_uartmsg omsg_e;
			bool newdata;
			bool go;

			static DWORD WINAPI static_run(void *Param);
			virtual DWORD WINAPI Run(void);

			CMySerialCass(void);
			~CMySerialCass(void);
			int Open(void);
			int Read(unsigned char* buffer, unsigned long *bytes_read);
			int Close(void);
			int Print(void);

			int StartReceiveThread(void);
			int StopReceiveThread(void);			

			int GetData(t_uartmsg* data);
		};

	};
};