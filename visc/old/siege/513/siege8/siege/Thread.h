#pragma once
#include <windows.h>
namespace siege{

	class CThread
	{
	public:		
		static DWORD WINAPI static_run(void *Param);

		DWORD  id;
		HANDLE h;
		int go;
		int end;
		int runs;

		LARGE_INTEGER freq, start,stop;
		long long delta;
		double dur, min, max, avg, sum;

		CThread():go(0),end(0) 
		{			
			h=CreateThread(0,30*1024*1024,static_run,this,CREATE_SUSPENDED,&id);				
			QueryPerformanceFrequency(&freq);
			runs=0;
			min = 10000;
			max = 0;
			avg = 0;
			sum = 0;
		}
		void Suspend(void){	SuspendThread(h);}
		void Start(void){ResumeThread(h);}
		void Resume(void){ResumeThread(h);}
		void MStart(void)
		{			
			QueryPerformanceCounter(&start);
		}
		void MStop(void)
		{
			QueryPerformanceCounter(&stop);
			delta = stop.QuadPart - start.QuadPart;
			dur = 100*delta/(double)freq.QuadPart;
			sum+=dur;

			if(dur<min) min = dur;
			if(dur>max) max = dur;
			avg = sum/(double)runs;


		}


		~CThread(void){}
		virtual DWORD WINAPI Run(void) = 0;
	};

}; // siege
