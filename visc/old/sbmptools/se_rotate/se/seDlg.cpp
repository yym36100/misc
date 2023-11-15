// seDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cdef.h"

#include "se.h"
#include "seDlg.h"
#include "WinScreen.h"
#include "WinDbg.h"


#include "siegecfg.h"

#include "MsgPump.h"
#include "RectWidget.h"
#include "SBWidget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
LARGE_INTEGER lInt;
double ticksPerSecInv;

int variant=0;

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


// CseDlg dialog


afx_msg void CseDlg::OnClose( )
{
	if(pScreen) 
	{
		delete pScreen;
		siege_dbg(L"pScreen deleted\n");

		siege::MsgPump *pump =siege::MsgPump::getinstance();
		pump->deinit();
	}
	siege::CDebugMsg *pDbgMsg = CWinDbg::getInstance();
	((CWinDbg*)pDbgMsg)->deinit();


	CDialog::OnClose();
}

CseDlg::CseDlg(CWnd* pParent /*=NULL*/)
: CDialog(CseDlg::IDD, pParent)
, variant(0)
{
	autoinit = false;
	pScreen = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	QueryPerformanceFrequency(&lInt);
	ticksPerSecInv = 1.0/(double)lInt.QuadPart;
}

void CseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VAR, variant);
}

BEGIN_MESSAGE_MAP(CseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Init, &CseDlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_Deinit, &CseDlg::OnBnClickedDeinit)
	ON_EN_CHANGE(IDC_EDIT_VAR, &CseDlg::OnEnChangeEditVar)
END_MESSAGE_MAP()


// CseDlg message handlers

BOOL CseDlg::OnInitDialog()
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
	UpdateData(false);
	if(autoinit)
	{
		pScreen = new siege::CWinScreen(screen_w,screen_h);
		siege_dbg(L"pScreen allocated successfully\n");

		pScreen->SetPixel(10,10);
		pScreen->blit();
		SetTimer(0,10,NULL);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CseDlg::OnPaint()
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
HCURSOR CseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void processevent(siege::CSObject &r)
{
	siege::MsgPump *p = siege::MsgPump::getinstance();
	siege::CWidget *w = (siege::CWidget *)&r;
	w->HandleEvent((siege::CSEvent &)p->pEvent->GetFirst());
}

void drawwidget(siege::CSObject &r)
{
	siege::CWidget *w = (siege::CWidget *)&r;
	
	if(w->Draw())
	{
		siege::CScreen::instance->redraw=true;
	}
}

void CseDlg::OnTimer(UINT_PTR nIDEvent)
{
	//pScreen->SetPixel(rand()%200,rand()%200);
	//#define ww 20
	//
	//	pScreen->color=0;
	//	pScreen->FillRect(0,0,pScreen->width,pScreen->height);
	//	//pScreen->color=rand();
	//	for(int i=0;i<50;i++)
	//	{
	//		pScreen->color=rand();
	//		pScreen->FillRect(rand()%(pScreen->width -ww),rand()%(pScreen->height -ww),ww,ww );
	//	}

	siege::MsgPump *p = siege::MsgPump::getinstance();
	if(1||p->IsEvent())
	//		if(p->IsEvent())
	{

		//p->pChild->foreach(processevent);
		//siege::CSObject *o=&p->pEvent->RemoveFirst();
		//delete o;// don't forget this
		//o=NULL;

		//p->pChild->foreach(drawwidget);
		//pScreen->vDrawLine(10,10,10,400);
		//pScreen->vDrawLine(10,10,400,10);
		pScreen->color=0;
		((siege::CWinScreen*)pScreen)->pattern=0xffff;
		//pScreen->FillRect(0,0,400,400);
		((siege::CWinScreen*)pScreen)->mode=2;
	//	((siege::CWinScreen*)pScreen)->pattern=0xEEEE;
		siege::CWinScreen *ws= (siege::CWinScreen*)pScreen;
		static int state =1;

#define N	(6)

		pScreen->color=0xffff;
		
		LARGE_INTEGER lInt1, lInt2;
		double t1;
		QueryPerformanceCounter(&lInt1);

		static short c=0;
		static float ax[N];
		static float ay[N];
		static float ix[N],iy[N],s[N];

		switch(state)
			{
			case 0:
				{
				for(int i=0;i<N;i++)
					{
					pScreen->color=c++;
					unsigned int x1 = rand()%400;
					unsigned int y1 =  rand()%400;
					ax[i]=x1;
					ay[i]=y1;
					ix[i]=1;
					iy[i]=1;
					s[i]=0.2+(rand()%21)/5.0;
					/*unsigned int x2 =  rand()%400;
					unsigned int y2 =  rand()%400;*/

					//pScreen->vDrawLine(x1,y1,x2,y2);
					/*void DrawFloat(i16 x1,i16 y1,i16 x2,i16 y2)const;
					void DrawDDA(i16 x1,i16 y1,i16 x2,i16 y2)const;
					void DrawBressenham(i16 x1,i16 y1,i16 x2,i16 y2)const;
					void DrawBressenham2(i16 x1,i16 y1,i16 x2,i16 y2)const;*/
					/*switch(variant)
					{
					case 0: 
					case 1:ws->DrawFloat(x1,y1,x2,y2);break;
					case 2:ws->DrawDDA(x1,y1,x2,y2);break;
					case 3:ws->DrawBressenham(x1,y1,x2,y2);break;
					case 4:ws->DrawBressenham2(x1,y1,x2,y2);break;
					}*/
					/*	switch(variant)
					{
					case 0:
					case 1:ws->DrawCircle1(200,200,rand()%200);break;
					case 2:ws->DrawCircle2(200,200,rand()%200);break;
					case 3:ws->DrawCircle3(200,200,rand()%200);break;
					case 4:ws->DrawCircle4(200,200,rand()%200);break;
					case 5:ws->DrawCircle5(200,200,rand()%200);break;
					case 6:ws->DrawCircle6(200,200,rand()%200);break;
					case 7:ws->DrawCircle7(200,200,rand()%200);break;
					}*/
					//ws->DrawCircle1(200,200,rand()%200);

					}
				state=1;
				break;				
				}
			case 1:
				{
//#define s	5.0
				
			/*	for(int i=0;i<N;i++)
					{
					ax[i]+=ix[i] * s[i];
					ay[i]+=iy[i] * s[i];
					if(ax[i]<=s[i]||ax[i]>=(400-s[i]))ix[i]=-ix[i];
					if(ay[i]<=s[i]||ay[i]>=(400-s[i]))iy[i]=-iy[i];
					}
				ws->PolyFill2(ax,ay,N);*/
				break;
				}
			}
	
		siege::MsgPump *p = siege::MsgPump::getinstance();
		((siege::SBWidget*)p->pChild->f)->redraw = true;
		((siege::SBWidget*)p->pChild->f)->angle+=1.0;

		((siege::SBWidget*)p->pChild->f)->Draw();
		
		QueryPerformanceCounter(&lInt2);
		t1 = (lInt2.QuadPart - lInt1.QuadPart)*ticksPerSecInv;
		wchar_t buffer[130];
		swprintf(buffer,L"time=%f fps = %f\n",t1*1000.0,1.0/t1);
		siege_dbg(buffer);
		//pScreen->FlodFill(0,0,pScreen->GetPixel(0,0));
		pScreen->redraw=true;
		pScreen->blit();
	}


}


void CseDlg::OnBnClickedInit()
{
	// TODO: Add your control notification handler code here
	if(!pScreen)
	{
		pScreen = new siege::CWinScreen(screen_w,screen_h);
		siege_dbg(L"pScreen allocated\n");

		pScreen->SetPixel(10,10);
		//	pScreen->blit();

		siege::MsgPump *p = siege::MsgPump::getinstance();
		//for(int i=0;i<100;i++)
			//p->AddChild(*new siege::CRectWidget((rand()%(screen_w-20)),(rand()%(screen_h-20)),rand()));
			//p->AddChild(*new siege::SBWidget(10,10,40,40,(u8*)"d:\\work\\rot\\t1.raw"));
		//siege::SBWidget *w =new siege::SBWidget(10,10,120,120,(u8*)"d:\\work\\rot\\t2.raw");
		//p->AddChild(*new siege::SBWidget(10,10,8,4,(u8*)"d:\\work\\rot\\t4.raw"));
		//siege::SBWidget *w = new siege::SBWidget(10,10,256,256,(u8*)"d:\\work\\rot\\t3.raw");
		siege::SBWidget *w = new siege::SBWidget(10,10,565,753,(u8*)"d:\\work\\rot\\eri.raw");
		w->angle = 0.0;
			p->AddChild(*w);
			//p->AddChild(*new siege::SBWidget(10,10,2,2,(u8*)"d:\\p4.raw"));

		p->pChild->foreach(drawwidget);
		pScreen->blit();

		SetTimer(0,0,NULL);
	}
	else
	{
		AfxMessageBox(L"Already inited");
	}
}

void CseDlg::OnBnClickedDeinit()
{
	// TODO: Add your control notification handler code here
	if(pScreen)
	{
		KillTimer(0);
		delete pScreen;
		pScreen = NULL;
		siege_dbg(L"pScreen deleted\n");

		siege::MsgPump *pump =siege::MsgPump::getinstance();
		pump->deinit();
		siege_dbg(L"msgpump deleted\n");


		//siege::CDebugMsg *pDbgMsg = CWinDbg::getInstance();
		//((CWinDbg*)pDbgMsg)->deinit();

	}
	else
	{
		AfxMessageBox(L"Nothing to deinit");
	}
}

void CseDlg::OnEnChangeEditVar()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(true);
}
