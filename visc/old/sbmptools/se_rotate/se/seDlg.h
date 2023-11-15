// seDlg.h : header file
#include "WinScreen.h"


#pragma once


// CseDlg dialog
class CseDlg : public CDialog
{
	// Construction
public:
	bool autoinit;
	CseDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_SE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HICON m_hIcon;

	void OnTimer(UINT_PTR nIDEvent);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose( );
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	siege::CScreen *pScreen;
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedDeinit();
	int variant;
	afx_msg void OnEnChangeEditVar();
};
