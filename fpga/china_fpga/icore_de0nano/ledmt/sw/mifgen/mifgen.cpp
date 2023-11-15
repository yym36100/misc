#include <stdio.h>
#include <math.h>

void print_content();

int main(int argc, char* argv[])
{
	// print header
	printf(
		" -- mifgen generated file \n\n"
		"WIDTH=12;\n"
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
	double s;
	double si;
	signed short ss;

#define max_val	(0x0fff)
	// cie 1931 lum adjust
	for(int i=0;i<256;i++)
	{
		si = i*100.0/255.0;
		if(si<=8)
		{
			s = si / 902.3;
		}
		else
		{
			s = pow((si+16)/116.0,3);
		}
		//ss = (unsigned short)(max_val*s);
		ss = ((int)(i/8));
		printf("%d : %4d;\n",i,(unsigned short)ss);
	}
}
