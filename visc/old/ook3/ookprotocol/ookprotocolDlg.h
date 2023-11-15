// ookprotocolDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include ".\src\cdef.h"

// CookprotocolDlg dialog

class CMyDrawArea : public CStatic
{

protected:
	DECLARE_MESSAGE_MAP()
public:
	u8 stat[256];
	u8 dbg;
	static const COLORREF bgcolor = RGB(66,99,145);
	static const COLORREF fgcolor = RGB(0,0,0);
	CMyDrawArea():CStatic()
	{
		//memset(stat,0,256);
		for(u16 i=0;i<256;i++)
		{
			stat[i]=i;
		}
	}
	afx_msg void OnPaint()
	{
		CRect r;
		this->GetWindowRect(r);
		CPaintDC dc(this);
		//dc.TextOut(0,0,"alma");
		CBrush b(bgcolor);
		CPen NewPen1(PS_SOLID,1,fgcolor);
		dc.SelectObject(NewPen1);
		dc.SelectObject(b);
		r.MoveToXY(0,0);
		dc.FillRect(r,&b);

		{
			u16 maxval = 0;
			//get max
			for(u16 i=0;i<256;i++)
			{
				maxval = maxval<stat[i]?stat[i]:maxval;
			}
			// draw stats
			dc.MoveTo(3,r.Height()-1);
			double ww = 3;
			double wi = (r.Width()-6)/256.0;
			for(u16 i=0;i<256;i++)
			{
			
				u8 h = r.Height()*stat[i]/(double)maxval;

				dc.LineTo(ww,r.Height()-h-1);
				ww+=wi;
				dc.MoveTo(ww,r.Height()-1);				
			}
		}

		/*dc.FillRect(r,&b);
		dc.MoveTo(0,0);
		dc.LineTo(10,10);
		dbg++;*/
	}
};

class CookprotocolDlg : public CDialog
{
	// Construction
public:
	CookprotocolDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_OOKPROTOCOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit mInputText;
	CEdit m_a_Data;
	CEdit m_p_Data;
	CEdit m_c_Data;
	CEdit m_h_Data;
	CEdit m_b_Data;

	CEdit m_a_Len;
	CEdit m_p_Len;
	CEdit m_c_Len;
	CEdit m_h_Len;
	CEdit m_b_Len;
	CEdit m_b_DC;


	CEdit m_dh_Data;
	CEdit m_dc_Data;
	CEdit m_dp_Data;
	CEdit m_da_Data;

	CEdit m_dh_Msg;
	CEdit m_dc_Msg;
	CEdit m_dp_Msg;
	CEdit m_da_Msg;


	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CButton m_wrongcrc;
	afx_msg void OnBnClickedCheck1();
	CButton m_seedfreeze;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton m_keyfreeze;
	CEdit m_nrbiterrors;
	afx_msg void OnEnChangeEdit21();
	CEdit m_statistics;
	afx_msg void OnBnClickedButton4();

	u8 stats[256];
	CMyDrawArea m_drawarea;
	int m_radio;
	CEdit m_errorbits;
	CEdit m_channelnoise;
	CEdit m_bittolerance;
	CEdit m_r_nrrestart;
	CEdit m_r_nrerrors;
};
