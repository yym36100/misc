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
	void bitrev(unsigned int sz=3)
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

int cmp<double>::add = 0;
int cmp<double>::mul = 0;

template<class T>
cmp<T> w(int i,int j,int s)
{
	cmp<T> res;
	res.re = (T)cos(2.0*3.14159265358979*i*j/(T)s);
	res.im = -(T)sin(2.0*3.14159265358979*i*j/(T)s);
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
		for( int j=0;j<SIZE;j++)
		{			
			sum = sum + in[j]*w<T>(i,j,SIZE);
		}		
		out[i] = sum;///(T)SIZE;
	}
}

template<class T, int SIZE>
void fft2(arr<cmp<T>,SIZE> &io, int start, int size,int it=1)
{
	cmp<T> t;	
	for(int j=start;j<size/2+start;j++)
	{
		t = io[j];
		io[j] = t+io[j+size/2];
		io[j+size/2] = (t - io[j+size/2])*w<T>((j-start)*it,1,SIZE);		
	}
	if(size>2)
	{
		fft2<T>(io,start,size/2,it*2);
		fft2<T>(io,start+size/2,size/2,it*2);
	}
}

template<class T, int SIZE>
void fft2_2(arr<cmp<T>,SIZE> &io, int start, int size)
{	
	cmp<T> t;
	int sz = size/2;
	int o = start + sz;
	int e = start;

	for(int j=0;j<sz;j++)
	{
		t = io[e];
		io[e] = t+io[o];
		io[o] = (t - io[o])*w<T>(j,1,size);		
		e++;o++;
	}
	if(size>2)
	{
		fft2_2<T>(io,start,sz);
		fft2_2<T>(io,start+sz,sz);
	}
}
///////////////// fast
extern double *sincos;
extern int *bitr;

inline unsigned int br(unsigned int n, unsigned int bits)
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
inline void bitrev(double *r, double *i,unsigned int sz, int size)
{
	double tr,ti;
	int b;
	for( int n=0;n<size/2;n++)
	{
		tr = r[n];
		ti = i[n];

		b = br(n,sz);
		if(n<b)
		{
			r[n] = r[b];
			i[n] = i[b];
			r[b] = tr;
			i[b] = ti;
		}
	}
}

inline void bitrev2(double *r, double *i,int size)
{
	double tr,ti;
	int b;
	for( int n=0;n<size/2;n++)
	{
		tr = r[n];
		ti = i[n];

		b = bitr[n];
		if(n<b)
		{
			r[n] = r[b];
			i[n] = i[b];
			r[b] = tr;
			i[b] = ti;
		}
	}
}


inline double wre(int i,int s)
{	
	return cos(2.0*3.14159265358979*i/s);	
}

inline double wim(int i,int s)
{	
	return -sin(2.0*3.14159265358979*i/s);
}



inline void sc_init(int size){
	static bool done = false;
	if(!done)
	{
		sincos = new double[size*2];
		for(int i=0;i<size;i++)
		{
			sincos[i*2+0] = wre(i,size);
			sincos[i*2+1] = wim(i,size);
		}
		done = true;
	}
}

inline void br_init(int size){
	static bool done = false;
	
	int i = size;
	int l=0;
	while (i >>= 1) { ++l; }

	if(!done)
	{		
		bitr = new int[size/2];
		for(int n=0;n<size/2;n++)
		{
			bitr[n] = br(n,l);
		}
		done = true;
	}
}


inline double wre2(int i,int s)
{	
	return sincos[i*s*2+0];
}

inline double wim2(int i,int s)
{	
	return sincos[i*s*2+1];
}

inline void fft2_2_fast(double *r,double *i, int start, int size,int it = 1)
{	
	double tr,ti, ar,ai;

	int sz = size/2;
	int o = start + sz;
	int e = start;
	sc_init(size);
	br_init(size);

	for(int j=0;j<sz;j++)
	{
		tr = r[e];
		ti = i[e];

		r[e] = tr+r[o];
		i[e] = ti+i[o];

		ar = (tr - r[o]);
		ai = (ti - i[o]);

		r[o] = ar * wre2(j,it) - ai*wim2(j,it);		
		i[o] = ai * wre2(j,it) + ar*wim2(j,it);	

		e++;o++;
	}
	if(size>2)
	{
		it<<=1;
		fft2_2_fast(r,i,start,sz,it);
		fft2_2_fast(r,i,start+sz,sz,it);
	}
}

inline void powphase(double *r, double *i, int size)
{	
	double tr,ti;
	for( int n = 0;n<size;n++)
	{
		tr = r[n];
		ti = i[n];
		r[n] = sqrt(tr*tr + ti*ti);
		i[n] = 90.0f+atan2(ti,tr)*360.0f/(2.0f*3.14159265f);		
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
}

template<class T, int SIZE>
void fft4(arr<cmp<T>,SIZE> &io, int e, int N)
{
	int o=0,Np;
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
