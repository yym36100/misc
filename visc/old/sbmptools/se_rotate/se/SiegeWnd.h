#pragma once
#include "WinScreen.h"

// CSiegeWnd
class siege::CScreen;

class CSiegeWnd : public CWnd
{
	DECLARE_DYNAMIC(CSiegeWnd)
public:

	siege::CWinScreen *pMyDlg;

	CSiegeWnd();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC*pDC);
	virtual ~CSiegeWnd();

	afx_msg void OnLButtonDown(
		UINT nFlags,
		CPoint point );
	afx_msg void OnLButtonUp(
		UINT nFlags,
		CPoint point 
		);
	afx_msg void OnMouseMove(
		UINT nFlags,
		CPoint point 
		);




protected:
	DECLARE_MESSAGE_MAP()
};


