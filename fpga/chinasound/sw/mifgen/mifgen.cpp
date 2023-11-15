#include <stdio.h>
#include <math.h>

#define pi (3.1415926)

void print_content();

int main(int argc, char* argv[])
{
	// print header
	printf(
		" -- mifgen generated file \n\n"
		"WIDTH=16;\n"
		"DEPTH=256;\n"
		"\n"
		"ADDRESS_RADIX=UNS;\n"
		"DATA_RADIX=HEX;\n"
		"\n"
		"CONTENT BEGIN\n");

	// print content
	print_content();
	//print footer
	printf(
		"END;\n");
	return 0;
}

void print_content()
{
	const double ampl = 32767;
	const double freq = 1;

	double s;
	signed short ss;

	for(int i=0;i<256;i++)
	{
		s =  ampl * sin(2*pi*freq*i/255.0);
		ss = (signed short)s;
		printf("%d : %4x;\n",i,(unsigned short)ss);
	}
}
