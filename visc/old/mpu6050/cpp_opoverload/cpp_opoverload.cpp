// cpp_opoverload.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class gpio{
public:
	int port, pin;
	gpio(int pport, int ppin): port(pport),pin(ppin){}
	gpio & operator=(int a)
	{
		if(a)printf("set\n");
		else printf("clear\n");
		return *this;
	}
};

int  & operator=(gpio a)
	{
		printf("get\n");
		return this->pin;
	}

int _tmain(int argc, _TCHAR* argv[])
{
	int c;
	gpio a(3,4);
	a= 1;
	a = 0;
	c = a;
	return 0;
}

