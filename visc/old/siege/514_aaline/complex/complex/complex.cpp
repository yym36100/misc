#include "stdafx.h"
#include <math.h>

template<class T, int SIZE = 10>
class arr{
public:
	T val[SIZE];
	T& operator[](int i)	{ return val[i]; }
	unsigned int br(unsigned int n, unsigned int bits=5)
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
	void bitrev(unsigned int sz)
	{
		T t;
		int b;
		for( int i=0;i<SIZE/2;i++)
		{
			t = val[i];
			b = br(i,sz);
			if(i<b)
			{
			val[i] = val[b];
			val[b] = t;
			}
		}
	}

	void bit_reverse_reorder( int N)
{
    int bits, i, j, k;
    double tempr, tempi;
    
    for (i=0; i<MAXPOW; i++)
	if (pow_2[i]==N) bits=i;

    for (i=0; i<N; i++)
    {
	j=0;
	for (k=0; k<bits; k++)
	    if (i&pow_2[k]) j+=pow_2[bits-k-1];

	if (j>i)  /** Only make "up" swaps */
	{
	    tempr=W[i].r;
	    tempi=W[i].i;
	    W[i].r=W[j].r;
	    W[i].i=W[j].i;
	    W[j].r=tempr;
	    W[j].i=tempi;
	}
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
//		printf("+");
		res.re = this->re + i.re;
		res.im = this->im + i.im;
		add++;
		return res;
	}
	cmp operator-(cmp& i)
	{
		cmp res;
//		printf("-");
		res.re =  this->re - i.re;
		res.im =  this->im - i.im;
		add++;
		return res;
	}
	cmp operator*(cmp& i)
	{
		cmp res;
//		printf("*");
		res.re = this->re*i.re - this->im*i.im;
		res.im = this->im*i.re + this->re*i.im;
		mul++;
		return res;
	}
	cmp operator/(T i)
	{
		cmp res;
//		printf("/");
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
	printf("(W%2.1f )",16*i*j/(T)(s));
	res.re = (T)cos(2.0*3.14159265358*i*j/(T)s);
	res.im = -(T)sin(2.0*3.14159265358*i*j/(T)s);
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

		/*tmp.re = tmp.re < 0.001 ? 0: tmp.re;
		tmp.im = tmp.im < 0.001 ? 0: tmp.im;*/
		res[i] = tmp;
	}	
	return res;

}

template<class T, int SIZE>
arr<cmp<T>,SIZE> gensin(T a=10, T f=2, T ph=0, T of=0)
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
			//printf(".");
			sum = sum + in[j]*w<T>(i,j,SIZE);
		}
		printf("S=");
		/*sum.re = abs(sum.re) < 0.0001f ? 0: sum.re;
		sum.im = abs(sum.im) < 0.0001f ? 0: sum.im;*/
		out[i] = sum;///(T)SIZE;
	}
}

template<class T, int SIZE>
void fft1(arr<cmp<T>,SIZE> &in,arr<cmp<T>,SIZE> &out, int sz)
{
	if(sz == 2)
	{

	}
	arr<cmp<T>,SIZE/2> a,b;

	for( int i=0;i<sz/2;i++)
	{
		a[i] = in[i] + in[sz/2+i];
		b[i] = (in[i] - in[sz/2+i])*w<T>(i,1,SIZE);
	}
}

template<class T, int SIZE>
void fft2(arr<cmp<T>,SIZE> &io, int start, int size,int it=1)
{
	cmp<T> t;
	printf("\n--- FFT start = %d size = %d it = %d ------------------------\n",start,size,it);
	for(int j=start;j<size/2+start;j++)
	{
		t = io[j];
		io[j] = t+io[j+size/2];
		io[j+size/2] = (t - io[j+size/2])*w<T>((j-start)*it,1,SIZE);
		//printf("_");

	}
	if(size>2)
	{
		fft2<T>(io,start,size/2,it*2);
		fft2<T>(io,start+size/2,size/2,it*2);
	}
	else
	{
		int j =start;
		io[j].re = abs(io[j].re) < 0.0001f ? 0: io[j].re;
		io[j].im = abs(io[j].im) < 0.0001f ? 0: io[j].im;

		io[j+size/2].re = abs(io[j+size/2].re) < 0.001f ? 0: io[j+size/2].re;
		io[j+size/2].im = abs(io[j+size/2].im) < 0.001f ? 0: io[j+size/2].im;
	}
}

template<class T, int SIZE>
void fft3(arr<cmp<T>,SIZE> &io, int start, int size)
{
	cmp<T> t;
	int e,o=0;
	printf("\n--- FFT start = %d size = %d  ------------------------\n",start,size);
	size >>= 1;
	//for(int j=start;j<size+start;j++)
	e = start;
	o = start + size;
	for(int n=0;n<size;n++)
	{
		t = io[e];
		io[e] = (t + io[o]);
		io[o] = (t - io[o]) * w<T>(n,1,size*2);
		e++; o++;		
	}
	if(size>1)
	{
		fft3<T>(io,start,size);
		fft3<T>(io,start+size,size);
	}
	else
	{
		
		/*io[e].re = abs(io[e].re) < 0.0001f ? 0: io[e].re;
		io[e].im = abs(io[e].im) < 0.0001f ? 0: io[e].im;

		io[o].re = abs(io[o].re) < 0.001f ? 0: io[o].re;
		io[o].im = abs(io[o].im) < 0.001f ? 0: io[o].im;*/
	}
}


template<class T, int SIZE>
void fft4(arr<cmp<T>,SIZE> &io, int e, int N)
{
	int o=0,Np;
	printf("\n--- FFT start = %d size = %d  ------------------------\n",e,N);

	if(N==1)
	{
		;//do nothing
	}
	else
	{
		Np = N>>1;
		o = e + Np;
		for(int n=0;n<Np;n++)
		{
			cmp<T> t = io[e+n];
			io[e+n] = (t + io[o+n]);
			io[o+n] = (t - io[o+n]) * w<T>(n,1,N);		
		}
		fft4<T>(io,e,Np);
		fft4<T>(io,o,Np);
	}
}


#define SIZE	(16)
#define logsize	(4)
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
	fft4<float,SIZE>(in,0,SIZE);

	printf("\npow phase calculation\n");
	in.bitrev(logsize);
	powph = powphase<float,SIZE>(in);
	//powph = powphase<float,SIZE>(out);

	printf("\n add = %d mul = %d\n",cmp<float>::add, cmp<float>::mul);
	return 0;
}


