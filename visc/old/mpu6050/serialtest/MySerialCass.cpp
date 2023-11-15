#include <stdio.h>

#include "MySerialCass.h"

CMySerialCass::CMySerialCass(void)
{
}

CMySerialCass::~CMySerialCass(void)
{
}

int CMySerialCass::Open(void)
{
	char m_strPort[]="COM1";
	m_hCommPort = CreateFile(m_strPort,GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING,	0, NULL);
	if (m_hCommPort == INVALID_HANDLE_VALUE) return -3;

	DCB dcb;
	memset(&dcb,0,sizeof(dcb));
	dcb.DCBlength=sizeof(dcb);
	GetCommState(m_hCommPort,&dcb);
	if (!BuildCommDCB("baud=115200 parity=E data=8 stop=1",&dcb)) return -1;	

	// Common settings	
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDtrControl = FALSE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fNull = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;

	if (!SetCommState(m_hCommPort,&dcb)) return -2;	

	if (GetCommState(m_hCommPort,&dcb) == 0)
	{
		printf("Get configuration port has problem.");
		return FALSE;
	}

	// instance an object of COMMTIMEOUTS.
	COMMTIMEOUTS comTimeOut;                   
	// Specify time-out between charactor for receiving.
	comTimeOut.ReadIntervalTimeout = 1;
	// Specify value that is multiplied 
	// by the requested number of bytes to be read. 
	comTimeOut.ReadTotalTimeoutMultiplier = 1;
	// Specify value is added to the product of the 
	// ReadTotalTimeoutMultiplier member
	comTimeOut.ReadTotalTimeoutConstant = 1;
	// Specify value that is multiplied 
	// by the requested number of bytes to be sent. 
	comTimeOut.WriteTotalTimeoutMultiplier = 3;
	// Specify value is added to the product of the 
	// WriteTotalTimeoutMultiplier member
	comTimeOut.WriteTotalTimeoutConstant = 2;
	// set the time-out parameter into device control.
	SetCommTimeouts(m_hCommPort,&comTimeOut);

	return 0;
}

int CMySerialCass::Read(unsigned char* buffer, unsigned long *bytes_read)
{
	int res;
	res = ReadFile(m_hCommPort,buffer,*bytes_read,bytes_read,NULL);	 
	if(res!=0)
	{
		printf(".");
		for(int i=0;i<*bytes_read;i++)
		{
			if((i +28 )<=*bytes_read )
			{
				if( (buffer[i]=='M')&&(buffer[i+1]=='S')&&(buffer[i+2]=='G')&&(buffer[i+3]=='_') )
				{
					omsg.header[0] = buffer[i];
					omsg.header[1] = buffer[i+1];
					omsg.header[2] = buffer[i+2];
					omsg.header[3] = buffer[i+3];

					omsg.msg_count = buffer[i+4] | (buffer[i+5]<<8);

					omsg.gyro_data[0] = buffer[i+6] | (buffer[i+7]<<8);
					omsg.gyro_data[1] = buffer[i+8] | (buffer[i+9]<<8);
					omsg.gyro_data[2] = buffer[i+10] | (buffer[i+11]<<8);

					omsg.accel_data[0] = buffer[i+12] | (buffer[i+13]<<8);
					omsg.accel_data[1] = buffer[i+14] | (buffer[i+15]<<8);
					omsg.accel_data[2] = buffer[i+16] | (buffer[i+17]<<8);

					// pad 18 19
					omsg.temp_data = buffer[i+20] | (buffer[i+21]<<8) | (buffer[i+22]<<16) | (buffer[i+23]<<24);
					omsg.crc       = buffer[i+24] | (buffer[i+25]<<8) | (buffer[i+26]<<16) | (buffer[i+27]<<24);
					if(omsg.crc!=0x12345678)printf("c");

					return omsg.crc==0x12345678 ? 1 : -1;
				}
			}
			else
			{
				printf("H");
				return 0;
			}
		}
	}
	else
	{
		printf("read error\n");
	}
}

int CMySerialCass::Close(void)
{
	CloseHandle(m_hCommPort);
	return 0;
}

int CMySerialCass::Print(void)
{
	static char buff[5] = {0};
	memcpy(buff,omsg.header,4);
	printf("%3d. head = %s gx=%d gy=%d gz=%d ax=%d ay=%d az=%d t=%d.%d\n",
		omsg.msg_count,
		buff,
		omsg.gyro_data[0],omsg.gyro_data[1],omsg.gyro_data[2],
		omsg.accel_data[0],omsg.accel_data[1],omsg.accel_data[2],
		omsg.temp_data>>16,omsg.temp_data&0xffff
		);
	return 0;
}
