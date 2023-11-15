
#include <stdio.h>
#include "MySerialCass.h"

CMySerialCass oSerial;

int main(int argc, char* argv[])
{
	unsigned char buff[100]={0};
	int res;
	unsigned long size=100;
	
	res = oSerial.Open();
	printf("open = %d\n",res);
	for(int i=0;i<200;i++)
	{
		size = 100;
		res = oSerial.Read(buff,&size);
		//printf("res = %d size = %d read = %s \n",res,size,buff);
		//oSerial.Print();
	}

	printf("close\n",res);
	oSerial.Close();
	return 0;
}

