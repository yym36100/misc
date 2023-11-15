// SiegeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "se.h"
#include "SiegeWnd.h"
#include "siegecfg.h"

#include "MsgPump.h"
#include "SEvent.h"

// CSiegeWnd

IMPLEMENT_DYNAMIC(CSiegeWnd, CWnd)

CSiegeWnd::CSiegeWnd()
{
}

CSiegeWnd::~CSiegeWnd()
{
}


afx_msg void CSiegeWnd::OnPaint( )
{
	siege_dbg(L"screen blit\n");
	PAINTSTRUCT ps;	
	CDC* pDC = BeginPaint(&ps);
	BitBlt(pDC->m_hDC, 0, 0, pMyDlg->m_bi24BitInfo.bmiHeader.biWidth,
		-pMyDlg->m_bi24BitInfo.bmiHeader.biHeight,
		pMyDlg->m_iDC, 0, 0, SRCCOPY); // copy hdc to their hdc
	EndPaint(&ps);
}
afx_msg BOOL CSiegeWnd::OnEraseBkgnd(CDC*pDC)
{
	return 0;
}

afx_msg void CSiegeWnd::OnLButtonDown(
						   UINT nFlags,
						   CPoint point )
{
	siege::CSEvent *ev=new siege::CSEvent(point.x,point.y,true);
	siege_event(*ev);
}

afx_msg void CSiegeWnd::OnLButtonUp(
						 UINT nFlags,
						 CPoint point 
						 )
{
}

afx_msg void CSiegeWnd::OnMouseMove(
						 UINT nFlags,
						 CPoint point 
						 )
{
	siege::CSEvent *ev=new siege::CSEvent(point.x,point.y,true);
	siege_event(*ev);
}

BEGIN_MESSAGE_MAP(CSiegeWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CSiegeWnd message handlers


