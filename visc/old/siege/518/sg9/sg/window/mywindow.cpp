#include "mywindow.h"

namespace sg {
	void CFFTSound::UpdateGraph(void){
		double *s;
		static double max=0;
		static double max2=0;
		static double max3=0;
		char *pp = playp;
		wg::CGraphWidget *wg;
		wg = (wg::CGraphWidget*)w->w;
		s = wg->sig;

		static double st1[1024];
		for(int i=0;i<wg->siglen;i++){
			st1[i] = pp[0] + (pp[1]<<8);
			max = max<st1[i]?st1[i]:max;		
			pp+=4;
		}
		//scale down
		for(int i=0;i<wg->siglen;i++){
			st1[i] *= (wg->grect.h/2)/max;
			if(st1[i]>(wg->grect.h/2))
				st1[i] = (wg->grect.h/2);
			if(st1[i]<-(wg->grect.h/2))
				st1[i] = -(wg->grect.h/2);
			s[i] = st1[i];
		}

		//fft part
#define sss	(1024)
		short fr[sss*1];
		short fi[sss*1];
		int scale;
		double *s2;
		static double stemp[1024];

		for(u16 i=0;i<sss*1;i++)
		{				
			fr[i] = (short)s[i] * 327.65;
			fi[i] = 0;				
		}		

		int fix_fft(short fr[], short fi[], short m, short inverse);
		scale = fix_fft(fr,fi,10,0);

		wg = (wg::CGraphWidget*)w->w2;
		s2 = wg->sig;

		for(u16 i=0;i<sss/2;i++)
		{
			fr[i]<<=scale;
			fi[i]<<=scale;
			stemp[i]= sqrt((float)(fr[i]*fr[i]+fi[i]*fi[i]));
			if(stemp[i]<0)
			{
				stemp[i] = 0;
			}
			//s2[i] = log(s2[i]);
			max2 = max2<stemp[i]?stemp[i]:max2;
		}	
		//scale down
		for(int i=0;i<sss/2;i++){
			stemp[i] *= (wg->grect.h/2)/max2;
			//s2[i]=s2[i];
		}
		//log scale
		for(int i=0;i<sss/2;i++){
			stemp[i] = log10(stemp[i]+1);
			max3 = max3<stemp[i]?stemp[i]:max3;
		}
		//scale down
		for(int i=0;i<sss/2;i++){
			stemp[i] *= (wg->grect.h/2)/max3;
			if(stemp[i]<0)
			{
				stemp[i] = 0;
			}
			if(stemp[i]>(wg->grect.h/2))
			{
				stemp[i] = (wg->grect.h/2);
			}
			//s2[i]=s2[i];
			s2[i] = stemp[i] ;
		}

		InvalidateRect(w->hWnd,0,0);
	}
};