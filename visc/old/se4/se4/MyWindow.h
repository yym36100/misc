#pragma once
#include "stdafx.h"

#include <Gdiplus.h>

using namespace Gdiplus;

#include "WinSurface.h"

// CMyWindow

class CMyWindow : public CWnd
{
	DECLARE_DYNAMIC(CMyWindow)

public:
	CMyWindow();

	CMyWindow(u16 w, u16 h)
	{
		width=w; height=h;

		CString strMyClass;
		strMyClass = AfxRegisterWndClass(
			CS_VREDRAW | CS_HREDRAW,
			::LoadCursor(NULL, IDC_ARROW),
			(HBRUSH) ::GetStockObject(WHITE_BRUSH),
			::LoadIcon(NULL, IDI_APPLICATION)); 
		CRect r = CRect(0,0,width,height);

		// adjusts window rect so the client area has the desired size
		CreateEx(0,strMyClass,L"Siege test",WS_CAPTION,r,NULL,0,0);
		CalcWindowRect(&r);
		MoveWindow(0, 0, r.Width(), r.Height());

		pSurface = new CWinSurface(w,h);


		r=CRect(0,0,width/2,height/2);
		HBRUSH hBR = GetSysColorBrush(COLOR_MENUBAR);
		FillRect(pSurface->m_iDC,&r,hBR);

		CDC *pDC = CDC::FromHandle(pSurface->m_iDC);
		pDC->SetTextColor(0xff);
		pDC->DrawText(L"window surface",&r,0);

		Graphics oGraph( pSurface->m_iDC );
		//oGraph.Clear( Color( 255, 0, 0, 0 ) );

		oGraph.SetTextRenderingHint( TextRenderingHintAntiAliasGridFit );
		oGraph.SetTextContrast( 0xffffffff );
		oGraph.SetCompositingMode( CompositingModeSourceOver );
		oGraph.SetCompositingQuality( CompositingQualityHighQuality );
		oGraph.SetPixelOffsetMode( PixelOffsetModeHighQuality );

		const FontFamily oFamily( L"Tahoma", NULL );
		Font oF600( &oFamily, 17.00, FontStyle::FontStyleRegular, Unit::UnitPixel );
			Color g_oTextColor( 255, 240, 55, 0 ); // Simply change Color to ( 254, 240, 0, 0 ) [to add slight transparency] and everything will work!

		SolidBrush oBrush( g_oTextColor ); 
		//oGraph.DrawString( L"Size 6.00", -1, &oF600, PointF(0, 0 ), &oBrush );
		//Bitmap bitmap(L"d:\\images.jpg");
		//Image image(L"d:\\temp\\1\\Background_HalfTubesDayviewStreet_Middle.png");
		//oGraph.DrawImage(&image,0,0,610,540);





		ShowWindow(1);

#define NL 3
		r.MoveToX(100);
		for(int i=0;i<NL;i++)
		{
			CWinSurface *pLayer = new CWinSurface(w,h);
			//pDC = CDC::FromHandle(pLayer->m_iDC);
			r.MoveToY(20*(i+1));
			pLayer->color=0xff000000;
			/*for(int y=0;y<20;y++)
				for(int x=0;x<100;x++)
					pLayer->SetPixel(x,20*(i+1)+y);*/
			/*pDC->SetTextColor(0xff);
			pDC->SetBkMode(TRANSPARENT);*/
			CString s;
			s.Format(L"layer %d",i);
			//pDC->DrawText(s,&r,0);
			//pLayers->AddNext(new CWinSurface(w,h));
			Graphics oGraph( pLayer->m_iDC );

			oGraph.SetTextRenderingHint( TextRenderingHintAntiAliasGridFit );
			oGraph.SetTextContrast( 0xffffffff );
			oGraph.SetCompositingMode( CompositingModeSourceOver );
			oGraph.SetCompositingQuality( CompositingQualityHighQuality );
			oGraph.SetPixelOffsetMode( PixelOffsetModeHighQuality );

			Color g_oTextColor( 0xff, 00, 0xff, 0 ); // Simply change Color to ( 254, 240, 0, 0 ) [to add slight transparency] and everything will work!
			SolidBrush oBrush( g_oTextColor ); 
			oGraph.DrawString( s, -1, &oF600, PointF(r.left, r.top ), &oBrush );

			switch (i)
			{
			case 0:
				{
				Image image(L"d:\\temp\\1\\Background_HalfTubesDayviewStreet_Middle.png ");
				oGraph.DrawImage(&image,0,0,610,540);
				}
				break;
			case 1:
				break;
			case 2:
				{
				Image image(L"d:\\temp\\1\\mymask.png ");
				oGraph.DrawImage(&image,0,0,610,540);			
				}
				break;
			case 3:
				{
					Image image(L"d:\\temp\\1\\MCLA_ChromeReflex_FT_L.png  ");
					oGraph.DrawImage(&image,0,0,130,249);		
				}
			case 4:
				{
					Image image(L"d:\\temp\\1\\MCLA_ChromeReflex_FT_L.png  ");
					oGraph.DrawImage(&image,130,130,130,249);		
				}
			case 5:
				{
					Image image(L"d:\\temp\\1\\MCLA_ChromeReflex_FT_L.png  ");
					oGraph.DrawImage(&image,450,20,130,249);		
				}
			case 6:
				{
					Image image(L"d:\\temp\\1\\MCLA_ChromeReflex_FT_L.png  ");
					oGraph.DrawImage(&image,300,220,130,249);		
				}
				break;
			}
			
			static u32 colors[]={0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,
			0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff,0xffff0000,0xff00ff00,0xff0000ff,0xff00ffff};
			pLayer->color=colors[i];
			for(int y=0;y<20;y++)
				for(int x=0;x<20;x++)
					pLayer->SetPixel(100+40*i+x,100+40*i+y);
			if(i==0)
				pLayers=pLayer;
			else
				pLayers->AddNext(pLayer);

		}
		CWinSurface *pLayer = pLayers;

		//blend all layers
		while(pLayer)
		{
			pLayer->blend(pSurface);
			pLayer=(CWinSurface*)pLayer->pNext;
		}
	}

	virtual ~CMyWindow();

	afx_msg void CMyWindow::OnPaint( )
	{
		PAINTSTRUCT ps;	
		CDC* pDC = BeginPaint(&ps);
		CRect r;
		BitBlt(pDC->m_hDC, 0, 0, pSurface->width,
			pSurface->height,
			pSurface->m_iDC, 0, 0, SRCCOPY); // copy hdc to their hdc
		EndPaint(&ps);
	}
	u16 width, height;
	CWinSurface *pSurface;

	CWinSurface *pLayers;

protected:
	DECLARE_MESSAGE_MAP()
};


