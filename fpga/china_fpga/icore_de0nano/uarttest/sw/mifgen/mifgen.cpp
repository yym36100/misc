#include <stdio.h>
#include <math.h>
#include <memory.h>

#define pi (3.1415926)

void print_content();

char text[64];

int main(int argc, char* argv[])
{
	FILE *f;
	f = fopen(argv[1],"rt");
	if(!f) return 0;
	memset(text,0,64);
	fread(text,64,1,f);
	fclose(f);
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

	for(int i=0;i<64;i++)
	{
		s =  ampl * sin(2*pi*freq*i/255.0);
		ss = (signed short)s;
		printf("%d : %2x;\n",i,(unsigned short)text[i]);
	}
}
