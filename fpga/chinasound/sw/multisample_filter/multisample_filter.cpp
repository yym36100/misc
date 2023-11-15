#include <stdio.h>
#include <math.h>

#define pi			(3.1415926)
#define NO_SAMPLES	(8)
#define ampl		(100)
#define freq		(1) 

double orig_data[NO_SAMPLES];
double hires_data[8*NO_SAMPLES];
double multisampled_data[8*NO_SAMPLES];
double step8x_data[8*NO_SAMPLES];

double filter_array[8] = {0.0};

void gen_orig_samples()
{
	double s;
	for(int i=0;i<NO_SAMPLES;i++)
	{
		s = ampl * sin(2*pi*freq*i/((double)NO_SAMPLES));
		orig_data[i] = s;
		for(int j=0;j<8;j++)
			step8x_data[i*8+j] = s;
	}
}

void gen_hires_samples()
{
	double s;
	for(int i=0;i<8*NO_SAMPLES;i++)
	{
		s = ampl * sin(2*pi*freq*i/((double)(8*NO_SAMPLES)));
		hires_data[i] = s;
	}
}

void print_samples(double *s, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%2.3f\n",s[i]);
	}
}

double x8_interpolate_filter(double in)
{
	static int i = 0;
	double acc = 0;
	filter_array[i] = in/8.0;
	if(++i == 8) i = 0;
	for( int j=0;j<8;j++)
	{
		acc += filter_array[j];
	}
	return acc;
}

void filter_samples()
{
	for(int i=0;i<8*NO_SAMPLES;i++)
	{
		multisampled_data[i] = x8_interpolate_filter(step8x_data[i]);
	}
}

int main(int argc, char* argv[])
{
	gen_orig_samples();
	gen_hires_samples();
	filter_samples();

	printf("step\n");
	print_samples(step8x_data,8*NO_SAMPLES);
	printf("hires\n");
	print_samples(hires_data,8*NO_SAMPLES);
	printf("filtered\n");
	print_samples(multisampled_data,8*NO_SAMPLES);

	return 0;
}

