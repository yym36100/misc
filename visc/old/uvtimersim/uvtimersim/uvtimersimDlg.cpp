// uvtimersimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uvtimersim.h"
#include "uvtimersimDlg.h"

extern "C" 
{
#include "picwrap.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

CListBox *mDbgmsgp;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CuvtimersimDlg dialog




CuvtimersimDlg::CuvtimersimDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CuvtimersimDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CuvtimersimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISP, mDisp);
	DDX_Control(pDX, IDC_BUTTON1, b1);
	DDX_Control(pDX, IDC_BUTTON2, b2);
	DDX_Control(pDX, IDC_LIST1, mDbgmsg);
}

BEGIN_MESSAGE_MAP(CuvtimersimDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CuvtimersimDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CuvtimersimDlg::OnBnClickedButton2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CuvtimersimDlg message handlers

BOOL CuvtimersimDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	mDbgmsgp = &mDbgmsg;


	CFont *m_Font1 = new CFont;
	//m_Font1->CreatePointFont(230, L"NI7seg");
	m_Font1->CreatePointFont(260, L"Digital-7 Mono");
	//m_Font1->CreatePointFont(260, L"semmi");
	mDisp.SetFont(m_Font1);
	
	mDbgmsg.AddString(L"Started");


	CSHDL_vInitReset();	
	this->SetTimer(2000,25,NULL);

	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CuvtimersimDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CuvtimersimDlg::OnTimer(UINT_PTR p)
{
	buttonstate[0] = (b1.GetState()&BST_PUSHED)!=0;
	buttonstate[1] = (b2.GetState()&BST_PUSHED)!=0;
	CAM_v25Active();

	CString s;
	s = dispbuffer;
	mDisp.SetWindowText(s);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CuvtimersimDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CuvtimersimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CuvtimersimDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}

void CuvtimersimDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}

 void DBG_vMessage(char *t)
 {
	 CString s;
	 int i;
	 s = t;
	mDbgmsgp->AddString(s);	
	i = mDbgmsgp->GetCount();
	mDbgmsgp->SetCurSel(i-1);
	
 }