// mycomplex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include <complex>

template <typename q>
class myarray{
public:
	q a[10];
	q& operator[] (const q i)
	{
		return this->a[i];
	}
	int getsize(void)
	{
		return sizeof(*this);
	}
};

class mycomplex{
public:
	double re, im;
	static short nradd,nrmul;

	mycomplex(double r=0,double i=0):re(r),im(i){}

	mycomplex operator *(mycomplex &a)
	{
		mycomplex res;
		nrmul++;
		res.re = this->re * a.re - this->im * a.im;
		res.im = this->im * a.re + this->re * a.im;
		return res;
	}

	mycomplex operator +(mycomplex &a)
	{
		mycomplex res;
		nradd++;

		res.re = this->re + a.re;
		res.im = this->im + a.im;
		return res;
	}
	void print(void)
	{
		printf("%2.0f %+2.0fi\n",this->re, this->im);
	}
	void print_stat(void)
	{
		printf("nr add = %d , nr mul = %d\n",nradd,nrmul);
	}
};

short mycomplex::nradd = 0;
short mycomplex::nrmul = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	int ss;
	myarray<int> ma;
	mycomplex a(1.0,2.0),b(3.0,4.0),c;
	std::complex<double> cc;
	c = a+b;
	c = c*b;
	ss = ma.getsize();

	ma[1]=1;

	a.print();
	b.print();
	c.print();
	a.print_stat();
	return 0;
}

