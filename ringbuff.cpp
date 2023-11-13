// ringbuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;

class CRingBuff{
	enum {size=5};
	uint8_t items[size];
	uint16_t rp, wp;

public:
	CRingBuff(){}
	void Init(void){
		rp = 0;
		wp = 0;
	}
	bool isEmpty() {return rp==wp;}
	uint16_t getSize() {
		int16_t delta= wp-rp;
		if(delta==0)return 0;
		if(delta<0) delta += size;
		return delta;
	};
	bool isFull() {return getSize()==size-1;}

	void inc_wp(){wp++;if(wp==size) wp=0;}
	void inc_rp(){rp++;if(rp==size) rp=0;}

	void add(uint8_t d){
		if(isFull()) return;
		items[wp] = d;
		inc_wp();
	}
	uint8_t get(void){
		uint8_t res;
		if(isEmpty())return 0;
		res = items[rp];
		items[rp]=0;
		inc_rp();
		return res;
	}

	void print(){
		printf("size=%d e=%d f=%d rp=%d wp=%d [",getSize(),isEmpty(), isFull(),rp, wp);
		for(int i=0;i<size;i++){
			printf("%d ", items[i]);
		}
		printf("]\n");
	}
};

CRingBuff myRingBuff;
int _tmain(int argc, _TCHAR* argv[])
{
	myRingBuff.print();
	myRingBuff.add(1); myRingBuff.print();
	myRingBuff.add(2); myRingBuff.print();
	myRingBuff.add(3); myRingBuff.print();

	myRingBuff.add(4); myRingBuff.print();
	myRingBuff.add(5); myRingBuff.print();

	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();
	myRingBuff.add(6); myRingBuff.print();
	myRingBuff.add(7); myRingBuff.print();

	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();
	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();	

	myRingBuff.add(8); myRingBuff.print();
	myRingBuff.add(9); myRingBuff.print();


	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();
	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();	
	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();
	printf("get=%d. ",myRingBuff.get()); myRingBuff.print();	
	return 0;
}

