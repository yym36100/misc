#include "StdAfx.h"
#include "siegecfg.h"

#include "WinScreen.h"
#include "SiegeWnd.h"

#include "math.h"



namespace siege{
	CWinScreen::CWinScreen(void)
	{
	}

	CWinScreen::CWinScreen(uint16 w, uint16 h)
		:mode(1),pattern(0xffff)
	{
		//this creates a 16bit surface
		pMyWnd = new CSiegeWnd();
		siege_dbg(L"pMyWnd allocated\n");

		width = w;
		height = h;
		CString strMyClass;
		strMyClass = AfxRegisterWndClass(
			CS_VREDRAW | CS_HREDRAW,
			::LoadCursor(NULL, IDC_ARROW),
			(HBRUSH) ::GetStockObject(WHITE_BRUSH),
			::LoadIcon(NULL, IDI_APPLICATION)); 

		RECT r = {0,0,width,height};

		// adjusts window rect so the client area has the desired size
		::AdjustWindowRectEx(&r,WS_CAPTION,FALSE,0); 
		CRect rr = r;
		rr.MoveToXY(100,100);
		m_bi24BitInfo.bmiHeader.biBitCount = 32; // rgb 8 bytes for each component(3)
		m_bi24BitInfo.bmiHeader.biCompression = BI_RGB;// rgb = 3 components
		m_bi24BitInfo.bmiHeader.biPlanes = 1;
		m_bi24BitInfo.bmiHeader.biSize = sizeof(m_bi24BitInfo.bmiHeader); // size of this struct
		m_bi24BitInfo.bmiHeader.biWidth = w; // width of window
		m_bi24BitInfo.bmiHeader.biHeight = -h; // height of window

		pBuffer = new uint8[m_bi24BitInfo.bmiHeader.biWidth * -m_bi24BitInfo.bmiHeader.biHeight * 4]; // create enough room. all pixels * each color component
		memset(pBuffer,0,m_bi24BitInfo.bmiHeader.biWidth * -m_bi24BitInfo.bmiHeader.biHeight * 4);
		siege_dbg(L"pBuffer allocated\n");


		m_iDC = CreateCompatibleDC(0); // create dc to store the image
		HBITMAP iBitmap = CreateDIBSection(m_iDC, &m_bi24BitInfo, DIB_RGB_COLORS, 0, 0, 0); // create a dib section for the dc
		SelectObject(m_iDC, iBitmap); // assign the dib section to the dc

		pMyWnd->pMyDlg = this;

		pMyWnd->CreateEx(0,strMyClass,L"Siege test",WS_CAPTION,rr,NULL,0,0);
		pMyWnd->ShowWindow(1);
		//SetDIBitsToDevice(m_iDC,
		//	0, 0, m_bi24BitInfo.bmiHeader.biWidth, -m_bi24BitInfo.bmiHeader.biHeight,
		//	0, 0, 0, -m_bi24BitInfo.bmiHeader.biHeight, pBuffer, &m_bi24BitInfo, DIB_RGB_COLORS); // set the new dibs to the dc
		//pMyWnd->Invalidate(false);
		blit();
		instance = this;
	}

	CWinScreen::~CWinScreen(void)
	{
		delete pMyWnd;
		siege_dbg(L"pMyWnd deleted\n");
		delete[] pBuffer;
		siege_dbg(L"pBuffer deleted\n");
	}

	void CWinScreen::SetPixel(int16 x, int16 y)const
	{
		if(x<width&&y<height)
			{
				uint32 * p = (uint32*)pBuffer;
				p+=(y*width+x);
				*p=color;
			}	
	}
	i16 CWinScreen::GetPixel(i16 x, i16 y)const
	{
		uint16 * p = (uint16*)pBuffer;
		p+=(y*width+x);
		return *p;
	}
	void CWinScreen::vDrawLine(i16 x1,i16 y1,i16 x2,i16 y2)const
	{
		if(x1==x2)
		{
			for(int i=y1;i<y2;i++)
			{
				SetPixel(x1,i);
			}
		}
		else if(y1==y2)
		{
			for(int i=x1;i<x2;i++)
			{
				SetPixel(i,y1);
			}
		}
		else
		{
			switch(mode)
			{
			case 0:
				{
					DrawFloat(x1,y1,x2,y2);
					break;
				}
			case 1:
				{
					DrawDDA(x1,y1,x2,y2);
					break;
				}
			case 2:
				{
					DrawBressenham(x1,y1,x2,y2);
					break;
				}
				case 3:
					{
					DrawBressenham2(x1,y1,x2,y2);
					break;
				}
			}
		}
	}
	void CWinScreen::DrawFloat(i16 x1,i16 y1,i16 x2,i16 y2)const
	{
		float dx=x2-x1;
		float dy=y2-y1;
		float m=dy/dx;
		float b=y1-m*x1;
		if(abs(m)<1)
		{
			for(i16 x=x1;x<x2;x++)
			{
				float y = m*x+b;
				SetPixel(x,y);
			}
		}
		else
		{
			for(i16 y=y1;y<y2;y++)
			{
				//float y = m*x+b;
				float x = (y-b)/m;
				SetPixel(x,y);
			}
		}
	}
	void CWinScreen::DrawDDA(i16 x1,i16 y1,i16 x2,i16 y2)const
	{
		float dx=x2-x1;
		float dy=y2-y1;
		float m=dy/dx;
		float r=abs(m);
		if((r<1 && x1>x2)||(r>1 && y1>y2))
		{
			float t;
			t=x1;x1=x2;x2=t;
			t=y1;y1=y2;y2=t;
		}
		if(r<1)
		{
			//x++
			float y = y1;
			for(int x=x1;x<x2;x++)
			{
				SetPixel(x,y);
				y+=m;
			}
		}
		else
		{
			//y++
			float x=x1;
			m=1/m;
			for(int y=y1;y<y2;y++)
			{
				SetPixel(x,y);
				x+=m;
			}
		}
	}

#define MYABS(x) x<0?-x:x;
	void CWinScreen::DrawBressenham(i16 x1,i16 y1,i16 x2,i16 y2)const
	{
		i16 dx=(x2-x1);
		i16 dy=(y2-y1);

		i16 sx,sy;
		if(dx<0) sx=-1;else sx=1;
		if(dy<0) sy=-1;else sy=1;

		dx=MYABS(dx);
		dy=MYABS(dy);
		if(dx>dy)
		{
			i16 e=dy-dx>>1;
			for(;x1!=x2;)
			{
				SetPixel(x1,y1);
				if(e>0)
				{
					e-=dx;y1+=sy;
				}
				x1+=sx;
				e+=dy;
			}
		}
		else
		{
			i16 e=dx-dy>>1;
			for(;y1!=y2;)
			{
				SetPixel(x1,y1);
				if(e>0)
				{
					e-=dy;x1+=sx;
				}
				y1+=sy;
				e+=dx;
			}
		}
		
	}

void CWinScreen::DrawBressenham2(i16 x1,i16 y1,i16 x2,i16 y2)const
	{
		uint16 * p = (uint16*)pBuffer;
		/*	p+=(y*width+x);
			*p=color;*/
		i16 dx=(x2-x1);
		i16 dy=(y2-y1);

		i16 sx,sy;
		
		int sa;
		if(dx<0) sx=-1;else sx=1;
		if(dy<0) {sy=-1;sa = -width;}else {sy=1;sa = width;}
		

		p+=(y1*width+x1);

		dx=MYABS(dx);
		dy=MYABS(dy);
		if(dx>dy)
		{
			i16 e=dy-dx>>1;
			
			for(;x1!=x2;)
			{
				//SetPixel(x1,y1);
				*p=color;
				if(e>0)
				{
					e-=dx;y1+=sy;
					p+=sa;
				}
				x1+=sx;
				p+=sx;
				e+=dy;
			}
		}
		else
		{
			i16 e=dx-dy>>1;
			for(;y1!=y2;)
			{
				//SetPixel(x1,y1);
				*p=color;
				if(e>0)
				{
					e-=dy;x1+=sx;p+=sx;
				}
				y1+=sy;p+=sa;
				e+=dx;
			}
		}
		
	}

void CWinScreen::DrawCircle1(i16 x,i16 y,i16 r)const
{
	//X=XC+RCOS(T)
	//Y=YC+RSIN(T)
	float tpi = 2*3.14159265358;
	i16 xx,yy;
	for(float i=0;i<tpi;i+=1.0/r)
	{
		xx = r*cos(i);
		yy = r*sin(i);
		SetPixel(x+xx,y+yy);
	}
}

void CWinScreen::DrawCircle2(i16 x,i16 y,i16 r)const
{
	//X=XC+RCOS(T)
	//Y=YC+RSIN(T)
	float tpi = 3.14159265358/2;
	i16 xx,yy;
	for(float i=0;i<tpi;i+=1.0/r)
	{
		xx = r*cos(i);
		yy = r*sin(i);
		SetPixel(x+xx,y+yy);
		SetPixel(x-xx,y+yy);
		SetPixel(x+xx,y-yy);
		SetPixel(x-xx,y-yy);
	}
}

void CWinScreen::DrawCircle3(i16 x,i16 y,i16 r)const
{
	float tpi = 2*3.14159265358;
	float dx,dy=0,c,s,t=r;
	c=cos(1.0/r);
	s=sin(1.0/r);
	for(float i=0;i<tpi;i+=1.0/r)
	{
		dx=t*c-dy*s;
		dy=t*s+dy*c;
		t=dx;
		SetPixel(x+dx,y+dy);
	}
}

void CWinScreen::DrawCircle4(i16 x,i16 y,i16 r)const
{
	float tpi = 3.14159265358/2;
	float dx,dy=0,c,s,t=r;
	c=cos(1.0/r);
	s=sin(1.0/r);
	for(float i=0;i<tpi;i+=1.0/r)
	{
		dx=t*c-dy*s;
		dy=t*s+dy*c;
		t=dx;
		SetPixel(x+dx,y+dy);
		SetPixel(x-dx,y+dy);
		SetPixel(x+dx,y-dy);
		SetPixel(x-dx,y-dy);
	}
}

void CWinScreen::DrawCircle5(i16 x,i16 y,i16 r)const
{
	float tpi = 3.14159265358/4;
	float dx,dy=0,c,s,t=r;
	c=cos(1.0/r);
	s=sin(1.0/r);
	for(float i=0;i<tpi;i+=1.0/r)
	{
		dx=t*c-dy*s;
		dy=t*s+dy*c;
		t=dx;
		SetPixel(x+dx,y+dy);
		SetPixel(x-dx,y+dy);
		SetPixel(x+dx,y-dy);
		SetPixel(x-dx,y-dy);

		SetPixel(x+dy,y+dx);
		SetPixel(x-dy,y+dx);
		SetPixel(x+dy,y-dx);
		SetPixel(x-dy,y-dx);
	}
}

//by the book bresenham
void CWinScreen::DrawCircle6(i16 x,i16 y,i16 r)const
{
	i16 xx,yy,t;
	t=3-2*r;
	for(xx=0,yy=r;xx<yy;xx++)
	{
		if(t<0)
		{
			t+=6+4*xx;
		}
		else
		{
			t+=10+4*(xx-yy);
			yy--;
		}

		SetPixel(x+xx,y+yy);
		SetPixel(x-xx,y+yy);
		SetPixel(x+xx,y-yy);
		SetPixel(x-xx,y-yy);

		SetPixel(x+yy,y+xx);
		SetPixel(x-yy,y+xx);
		SetPixel(x+yy,y-xx);
		SetPixel(x-yy,y-xx);

	}
}
//wiki bressenham circle ??
void CWinScreen::DrawCircle7(i16 x,i16 y,i16 r)const
{
	i16 xx,yy,t;
	t=1-r;
	for(xx=0,yy=r;xx<yy;xx++)
	{
		if(t<0)
		{
			t+=1+xx<<1;
		}
		else
		{
			yy--;
			t+=1-(yy-xx)<<1;
		}

		SetPixel(x+xx,y+yy);
		SetPixel(x-xx,y+yy);
		SetPixel(x+xx,y-yy);
		SetPixel(x-xx,y-yy);

		SetPixel(x+yy,y+xx);
		SetPixel(x-yy,y+xx);
		SetPixel(x+yy,y-xx);
		SetPixel(x-yy,y-xx);
	}
}
//	void GRLP_vLine(uint8 x1, uint8 y1, uint8 x2, uint8 y2)
//{
//	short d,ax,ay,sx,sy,dx,dy;
//	dx=x2-x1; ax=abs(dx)<<1; if(dx<0)sx=-1;else sx=1;
//	dy=y2-y1; ay=abs(dy)<<1; if(dy<0)sy=-1;else sy=1;
//	
//	GRLP_vSetPixel(x1,y1);
//	
// 	if(ax>ay)
//	 	{
//	 		d=ay-(ax>>1);
//		 	while (x1!=x2)
//			 	{
//			 	if(d>=0){y1+=sy;d-=ax;}
//			 	x1+=sx;d+=ay;
//			 	GRLP_vSetPixel(x1,y1);
//			 	}
//		}
//		else
//		{
//			d=ax-(ay>>1);
//			while(y1!=y2)
//				{
//				if(d>=0){x1+=sx;d-=ay;} 
//				y1+=sy;d+=ax;GRLP_vSetPixel(x1,y1);
//				}
//		}		
//}

	void CWinScreen::FillRect(int16 x, int16 y, uint16 w, uint16 h)const
	{
		for(uint16 i=0;i<h;i++)
			for(uint16 j=0;j<w;j++)
				SetPixel(x+j,y+i);
	}
	void CWinScreen::FlodFill(i16 x, i16 y,i16 c)const
	{
		if(x<width &&y<height&&c!=color)
		{
			if(GetPixel(x,y)== c)
			{
				SetPixel(x,y);
				FlodFill(x-1,y,c);
				FlodFill(x+1,y,c);
				FlodFill(x,y-1,c);
				FlodFill(x,y+1,c);
			}
		}
	}

	void CWinScreen::PolyFill1(i16 *x,i16 *y, i16 n)const
		{
		for(int i=0;i<n-1;i++)
			{
			DrawBressenham2(*x,*y,*(x+1),*(y+1));
			x++;y++;
			}
		}

#define MAX_POLY_CORNERS (5000)
#define IMAGE_TOP	(0)
#define IMAGE_BOT	(400)
#define IMAGE_RIGHT	(400)
#define	IMAGE_LEFT	(0)

	void CWinScreen::PolyFill2(float *polyX,float *polyY, i16 polyCorners)const
		{
		static float nodeX[MAX_POLY_CORNERS];
		int  nodes, pixelX, pixelY, i, j, swap ;

		//  Loop through the rows of the image.
		for (pixelY=IMAGE_TOP; pixelY<IMAGE_BOT; pixelY++) {

			//  Build a list of nodes.
			nodes=0; j=polyCorners-1;
			for (i=0; i<polyCorners; i++) {
				if (polyY[i]<(double) pixelY && polyY[j]>=(double) pixelY
					||  polyY[j]<(double) pixelY && polyY[i]>=(double) pixelY) {
						nodeX[nodes++]=(int) (polyX[i]+(pixelY-polyY[i])/(polyY[j]-polyY[i])
							*(polyX[j]-polyX[i])); }
				j=i; }

			//  Sort the nodes, via a simple “Bubble” sort.
			i=0;
			while (i<nodes-1) {
				if (nodeX[i]>nodeX[i+1]) {
					swap=nodeX[i]; nodeX[i]=nodeX[i+1]; nodeX[i+1]=swap; if (i) i--; }
				else {
					i++; }}

			//  Fill the pixels between node pairs.
			for (i=0; i<nodes; i+=2) {
				if   (nodeX[i  ]>=IMAGE_RIGHT) break;
				if   (nodeX[i+1]> IMAGE_LEFT ) {
					if (nodeX[i  ]< IMAGE_LEFT ) nodeX[i  ]=IMAGE_LEFT ;
					if (nodeX[i+1]> IMAGE_RIGHT) nodeX[i+1]=IMAGE_RIGHT;
					for (j=nodeX[i]; j<nodeX[i+1]; j++) SetPixel(j,pixelY); }}}
		}	

	void CWinScreen::blit()
	{
		//this blit is 16bit
		if(redraw)
		{
			redraw=false;
			siege_dbg(L"surface blit\n");
			SetDIBitsToDevice(m_iDC,
				0, 0, m_bi24BitInfo.bmiHeader.biWidth, -m_bi24BitInfo.bmiHeader.biHeight,
				0, 0, 0, -m_bi24BitInfo.bmiHeader.biHeight, pBuffer, &m_bi24BitInfo, DIB_RGB_COLORS); // set the new dibs to the dc
			pMyWnd->Invalidate(false);
		}
	}

}
