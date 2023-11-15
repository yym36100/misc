// se4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "se4.h"
#include "se4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

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


// Cse4Dlg dialog




Cse4Dlg::Cse4Dlg(CWnd* pParent /*=NULL*/)
: CDialog(Cse4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cse4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cse4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_INIT, &Cse4Dlg::OnBnClickedButtonInit)
END_MESSAGE_MAP()


// Cse4Dlg message handlers

BOOL Cse4Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cse4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cse4Dlg::OnPaint()
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
HCURSOR Cse4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD ThreadProc (LPVOID lpdwThreadParam );
void Cse4Dlg::OnBnClickedButtonInit()
{
	// TODO: Add your control notification handler code here
	//pWindow = new CMyWindow(430,430);
	pWindow = new CMyWindow(610,540);
	//pWindow = new CMyWindow(1024,740);
	//SetTimer(1000,1,NULL);

	DWORD dwThreadId;
	HANDLE h;
	if ((h=CreateThread(NULL, //Choose default security
		0, //Default stack size
		(LPTHREAD_START_ROUTINE)&ThreadProc,
		//Routine to execute
		(LPVOID) this, //Thread parameter
		0, //Immediately run the thread
		&dwThreadId //Thread Id
		)) == NULL)
	{
		SetThreadPriority(h,THREAD_PRIORITY_HIGHEST);
	}
}
afx_msg void Cse4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CWinSurface *p = (CWinSurface *)pWindow->pLayers->pNext;
	CWinSurface *pLayer = (CWinSurface *)pWindow->pLayers;

	Graphics oGraph( p->m_iDC );
	oGraph.Clear( Color( 0, 0,0,0 ) );
	static int i=0;
	Image image(L"d:\\temp\\1\\MCLA_CursorBar.png ");
	oGraph.DrawImage(&image,(610-506)/2,80+i%300,506,58);
	i+=1;

	while(pLayer)
	{
		pLayer->blend(pWindow->pSurface);
		pLayer=(CWinSurface*)pLayer->pNext;
	}
	pWindow->Invalidate(false);
}

DWORD ThreadProc (LPVOID lpdwThreadParam )
{
	Image image(L"d:\\temp\\1\\MCLA_CursorBar.png ");
	Cse4Dlg *pDlg = (Cse4Dlg *)lpdwThreadParam;
	CWinSurface *p = (CWinSurface *)pDlg->pWindow->pLayers->pNext;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	static LARGE_INTEGER time1,time2,time3;
	static double deltaT,deltaT2;
	static CString s1,s2;

	const FontFamily oFamily( L"Tahoma", NULL );
	Font oF600( &oFamily, 17.00, FontStyle::FontStyleRegular, Unit::UnitPixel );
	Color g_oTextColor( 255, 255,255,255 ); // Simply change Color to ( 254, 240, 0, 0 ) [to add slight transparency] and everything will work!

	SolidBrush oBrush( g_oTextColor ); 
	//oGraph.DrawString( L"Size 6.00", -1, &oF600, PointF(0, 0 ), &oBrush );

	while(1)
	{
		//	Sleep(1000/90);
		QueryPerformanceCounter(&time2);
		deltaT = ((time2.QuadPart - time1.QuadPart) *1000 )/ freq.QuadPart;
		time1 = time2;


		CWinSurface *pLayer = (CWinSurface *)pDlg->pWindow->pLayers;

		Graphics oGraph( p->m_iDC );
		oGraph.Clear( Color( 0, 0,0,0 ) );
		static int i=0;

		oGraph.DrawImage(&image,(610-506)/2,80+i%300,506,58);
		s1.Format(L"fps %f",1000.0/deltaT);

		s2.Format(L"1 max fps %f",1000.0/deltaT2);

		oGraph.SetTextRenderingHint( TextRenderingHintAntiAliasGridFit );
		oGraph.SetTextContrast( 0xffffffff );
		oGraph.SetCompositingMode( CompositingModeSourceOver );
		oGraph.SetCompositingQuality( CompositingQualityHighQuality );
		oGraph.SetPixelOffsetMode( PixelOffsetModeHighQuality );
		oGraph.DrawString( s1, -1, &oF600, PointF(0, 0 ), &oBrush );
		oGraph.DrawString( s2, -1, &oF600, PointF(0, 40 ), &oBrush );
		i+=4;

		while(pLayer)
		{
			pLayer->blend(pDlg->pWindow->pSurface);
			pLayer=(CWinSurface*)pLayer->pNext;
		}

		//now insted of inavlidate just draw directly to the dc
		//pDlg->pWindow->Invalidate(false); this is slow because of the wmpaint processing, just draw directly
		{
			CClientDC dc(pDlg->pWindow);

			CClientDC *pDC = &dc;
			CRect r;
			BitBlt(pDC->m_hDC, 0, 0, pDlg->pWindow->pSurface->width,
				pDlg->pWindow->pSurface->height,
				pDlg->pWindow->pSurface->m_iDC, 0, 0, SRCCOPY); // copy hdc to their hdc
		}
		QueryPerformanceCounter(&time3);
		deltaT2 = ((time3.QuadPart - time2.QuadPart) *1000 )/ freq.QuadPart;

	}
	return 1;
}