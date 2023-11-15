// se4Dlg.h : header file
//

#pragma once
#include "MyWindow.h"

// Cse4Dlg dialog
class Cse4Dlg : public CDialog
{
// Construction
public:
	Cse4Dlg(CWnd* pParent = NULL);	// standard constructor

	CMyWindow *pWindow;

// Dialog Data
	enum { IDD = IDD_SE4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInit();
};
