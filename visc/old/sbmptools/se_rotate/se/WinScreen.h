#pragma once
#include "Screen.h"
//#include "SiegeWnd.h"

class CSiegeWnd;

namespace siege{
	class CWinScreen : public CScreen
	{
	public:
		BITMAPINFO m_bi24BitInfo; // We set this up to grab what we want
		HDC m_iDC;

		CSiegeWnd *pMyWnd;
		char mode;
		uint16 pattern;
		//BITMAPINFO*
		void DrawFloat(i16 x1,i16 y1,i16 x2,i16 y2)const;
		void DrawDDA(i16 x1,i16 y1,i16 x2,i16 y2)const;
		void DrawBressenham(i16 x1,i16 y1,i16 x2,i16 y2)const;
		void DrawBressenham2(i16 x1,i16 y1,i16 x2,i16 y2)const;

		void DrawCircle1(i16 x,i16 y,i16 r)const;
		void DrawCircle2(i16 x,i16 y,i16 r)const;
		void DrawCircle3(i16 x,i16 y,i16 r)const;
		void DrawCircle4(i16 x,i16 y,i16 r)const;
		void DrawCircle5(i16 x,i16 y,i16 r)const;
		void DrawCircle6(i16 x,i16 y,i16 r)const;
		void DrawCircle7(i16 x,i16 y,i16 r)const;


		void PolyFill1(i16 *x,i16 *y, i16 n)const;
		void PolyFill2(float *x,float *y, i16 n)const;



		CWinScreen(void);
		virtual void SetPixel(int16 x, int16 y)const;
		virtual i16 GetPixel(i16 x, i16 y)const;
		virtual void vDrawLine(i16 x1,i16 y1,i16 x2,i16 y2)const;
		virtual void FillRect(int16 x, int16 y, uint16 w, uint16 h)const;
		virtual void FlodFill(i16 x, i16 y,i16 c)const;


		explicit CWinScreen::CWinScreen(uint16 width, uint16 height);
		virtual ~CWinScreen(void);
		virtual void blit();

	};

}
