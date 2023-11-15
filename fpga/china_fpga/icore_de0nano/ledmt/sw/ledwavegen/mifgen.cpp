#include <stdio.h>
#include <math.h>

void print_content();

int main(int argc, char* argv[])
{
	// print header
	printf(
		" -- mifgen generated file \n\n"
		"WIDTH=8;\n"
		"DEPTH=2048;\n"
		"\n"
		"ADDRESS_RADIX=UNS;\n"
		"DATA_RADIX=UNS;\n"
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

#define max_val	(0x0fff)

	for(int i=0;i<256;i++)
	{
		for(int j=0;j<8;j++)
		{
			//s = 255 * sin( 1 * 3.14159265 * 1 * i /256.0 + j * 3.14159265/8.0);
			s = (unsigned char)(i+j);
			printf("%d : %4d;\n",i*8+j,(unsigned char)s);
		}		
	}
}
