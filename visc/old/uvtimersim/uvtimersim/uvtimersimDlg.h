// uvtimersimDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CuvtimersimDlg dialog
class CuvtimersimDlg : public CDialog
{
// Construction
public:
	CuvtimersimDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVTIMERSIM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint(void);
	afx_msg void OnTimer(UINT_PTR p);
	
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CStatic mDisp;
	CButton b1;
	CButton b2;
	CListBox mDbgmsg;
};

extern CListBox *mDbgmsgp;
extern "C"
{
	 void DBG_vMessage(char *t);
}