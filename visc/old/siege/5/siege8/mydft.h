#include "stdafx.h"
#include <math.h>

template<class T, int SIZE = 10>
class arr{
public:
	T val[SIZE];
	T& operator[](int i)	{ return val[i]; }
	unsigned int bitrev(unsigned int n, unsigned int bits=10)
	{
		unsigned int nrev, N;
		unsigned int count;  
		N = 1<<bits;

		count = bits-1;   // initialize the count variable
		nrev = n;
		for(n>>=1; n; n>>=1)
		{
			nrev <<= 1;
			nrev |= n & 1;
			count--;
		}

		nrev <<= count;
		nrev &= N - 1;

		return nrev;
	}
	void bitrev(void)
	{
		T t;
		int b;
		for( int i=0;i<SIZE/2;i++)
		{
			t = val[i];
			b = bitrev(i);
			val[i] = val[b];
			val[b] = t;
		}
	}
};


template<class T>
class cmp{
public:
	T re,im;
	static int add,mul;
	cmp(void):re(0),im(0){}

	cmp operator+(cmp& i)
	{
		cmp res;	
		res.re = this->re + i.re;
		res.im = this->im + i.im;
		add++;
		return res;
	}
	cmp operator-(cmp& i)
	{
		cmp res;
		res.re = this->re - i.re;
		res.im = this->im - i.im;
		add++;
		return res;
	}

	cmp operator*(cmp& i)
	{
		cmp res;		
		res.re = this->re*i.re - this->im*i.im;
		res.im = this->im*i.re + this->re*i.im;
		mul++;
		return res;
	}
	cmp operator/(T i)
	{
		cmp res;		
		res.re = this->re/i;
		res.im = this->im/i;
		return res;
	}

};

int cmp<float>::add = 0;
int cmp<float>::mul = 0;

template<class T>
cmp<T> w(int i,int j,int s)
{
	cmp<T> res;
	res.re = (T)cos(2.0*3.14159265*i*j/(T)s);
	res.im = -(T)sin(2.0*3.14159265*i*j/(T)s);
	return res;
}

template<class T, int SIZE>
arr<cmp<T>,SIZE> powphase(arr<cmp<T>,SIZE> &in)
{
	arr<cmp<T>,SIZE> res;
	cmp<T> tmp,t2;
	for( int i = 0;i<SIZE;i++)
	{
		t2 = in[i];
		tmp.re = sqrt(t2.re * t2.re + t2.im * t2.im);
		tmp.im = 90.0f+(T)atan2(t2.im,t2.re)*360.0f/(2.0f*3.14159265f);
		res[i] = tmp;
	}	
	return res;

}

template<class T, int SIZE>
arr<cmp<T>,SIZE> gensin(T a=100, T f=6, T ph=12.34567890123, T of=0)
{
	arr<cmp<T>,SIZE> res;
	cmp<T> tmp;
	for( int i = 0;i<SIZE;i++)
	{
		tmp.re = a * (T)sin(2.0*3.14159265*f*i/(T)SIZE+ph*2*3.14159265/360.0)+of;
		tmp.im = 0;
		res[i] = tmp;
	}	
	return res;

}
template<class T, int SIZE>
void dft1(arr<cmp<T>,SIZE> &in,arr<cmp<T>,SIZE> &out)
{
	cmp<T> sum;
	for( int i=0;i<SIZE;i++)
	{
		sum = cmp<T>();
		printf("\n");
		for( int j=0;j<SIZE;j++)
		{
			printf(".");
			sum = sum + in[j]*w<T>(i,j,SIZE);
		}
		printf("S=");
		out[i] = sum/(T)SIZE;
	}
}

template<class T, int SIZE>
void fft2(arr<cmp<T>,SIZE> &io, int start, int size,int it=1)
{
	cmp<T> t;
	//printf("\nFFT start = %d size = %d it = %d ------------------------\n",start,size,it);
	for(int j=start;j<size/2+start;j++)
	{
		t = io[j];
		io[j] = t+io[j+size/2];
		io[j+size/2] = (t - io[j+size/2])*w<T>((j-start)*it,1,SIZE);
		printf("_");
	}
	if(size>2)
	{
		fft2<T>(io,start,size/2,it*2);
		fft2<T>(io,start+size/2,size/2,it*2);
	}
}
//#define SIZE	(16)
/*
int _tmain(int argc, _TCHAR* argv[])
{
printf("\nvariable defines\n");
arr<cmp<float>,SIZE> in,out,powph;

printf("\nsig gen\n");
in = gensin<float,SIZE>();

cmp<float>::add = 0;
cmp<float>::mul = 0;
printf("\ndft calculation\n");
dft1<float,SIZE>(in,out);

printf("\npow phase calculation\n");
powph = powphase<float,SIZE>(out);

printf("\n add = %d mul = %d\n",cmp<float>::add, cmp<float>::mul);
return 0;
}
*/
