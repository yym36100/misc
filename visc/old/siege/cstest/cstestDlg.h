// cstestDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"


// CcstestDlg dialog
class CcstestDlg : public CDialog
{
// Construction
public:
	CcstestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSTEST_DIALOG };

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit m_address;
	CEdit m_text;
	CListBox m_list;

	CMySocket *socket;
	afx_msg void OnBnClickedButton1();
};
