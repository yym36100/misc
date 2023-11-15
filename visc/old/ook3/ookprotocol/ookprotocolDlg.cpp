// ookprotocolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ookprotocol.h"
#include "ookprotocolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C"
{
#include ".\src\ookproto.h"
#include ".\src\subbitdec.h"
	u8 ook_prbs7();
	void sbd_decode(u16 time);
}

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


// CookprotocolDlg dialog




CookprotocolDlg::CookprotocolDlg(CWnd* pParent /*=NULL*/)
: CDialog(CookprotocolDlg::IDD, pParent)
, m_radio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CookprotocolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mInputText);
	DDX_Control(pDX, IDC_EDIT3, m_a_Data);
	DDX_Control(pDX, IDC_EDIT2, m_p_Data);
	DDX_Control(pDX, IDC_EDIT4, m_c_Data);
	DDX_Control(pDX, IDC_EDIT5, m_h_Data);
	//DDX_Control(pDX, IDC_EDIT6, m_b_Data);

	DDX_Control(pDX, IDC_EDIT7, m_a_Len);
	DDX_Control(pDX, IDC_EDIT8, m_p_Len);
	DDX_Control(pDX, IDC_EDIT9, m_c_Len);
	DDX_Control(pDX, IDC_EDIT10, m_h_Len);
	//DDX_Control(pDX, IDC_EDIT11, m_b_Len);

	DDX_Control(pDX, IDC_EDIT12, m_b_DC);



	DDX_Control(pDX, IDC_EDIT13, m_dh_Data);
	DDX_Control(pDX, IDC_EDIT15, m_dc_Data);
	DDX_Control(pDX, IDC_EDIT14, m_dp_Data);
	DDX_Control(pDX, IDC_EDIT16, m_da_Data);

	DDX_Control(pDX, IDC_EDIT17, m_dh_Msg);
	DDX_Control(pDX, IDC_EDIT18, m_dc_Msg);
	DDX_Control(pDX, IDC_EDIT19, m_dp_Msg);
	DDX_Control(pDX, IDC_EDIT20, m_da_Msg);


	DDX_Control(pDX, IDC_CHECK1, m_wrongcrc);
	DDX_Control(pDX, IDC_CHECK2, m_seedfreeze);
	DDX_Control(pDX, IDC_CHECK3, m_keyfreeze);
	DDX_Control(pDX, IDC_EDIT21, m_nrbiterrors);
	DDX_Control(pDX, IDC_EDIT22, m_statistics);
	DDX_Control(pDX, IDC_STATIC_DRAW, m_drawarea);

	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_EDIT23, m_errorbits);//todo
	DDX_Control(pDX, IDC_EDIT24, m_channelnoise);
	DDX_Control(pDX, IDC_EDIT25, m_bittolerance);
	DDX_Control(pDX, IDC_EDIT11, m_r_nrrestart);
	DDX_Control(pDX, IDC_EDIT26, m_r_nrerrors);
}

BEGIN_MESSAGE_MAP(CookprotocolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &CookprotocolDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CookprotocolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CookprotocolDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CookprotocolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CookprotocolDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT21, &CookprotocolDlg::OnEnChangeEdit21)
	ON_BN_CLICKED(IDC_BUTTON4, &CookprotocolDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDrawArea, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CookprotocolDlg message handlers

BOOL CookprotocolDlg::OnInitDialog()
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
	OnBnClickedButton4();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CookprotocolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CookprotocolDlg::OnPaint()
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
HCURSOR CookprotocolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CookprotocolDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString str;
	char buffer[2500];
	char *pb = buffer;
	mInputText.GetWindowText(str);

	UpdateData();


	// 1. application
	int len = str.GetLength();
	signed int dcbal = 0;
	static double dcbalavg = 0;
	static int nrmes = 1;
	u8 res;
	int nrerrors;

	u8 statlen;
	u8 *statptr;
		

	m_p_Data.SetWindowText(str);
	sprintf(buffer,"%d",len);
	m_a_Len.SetWindowText(buffer);


	if(m_radio==3)
	{
	statlen = len;
	statptr = (u8*)a_buffer;
	}


	for(u8 i = 0;i<len;i++)
	{
		pb+= sprintf(pb,"%02x ",str.GetAt(i));
	}
	m_a_Data.SetWindowText(buffer);

	ook_a_SendData((char*)(LPCTSTR)str,len);


	ook__p_MakeCont(a_buffer,len);

	if (m_wrongcrc.GetState()&BST_CHECKED)
	{
		//alter crc value
		p_buffer[len+2] =0x55;
	}

	if ((m_seedfreeze.GetState()&BST_CHECKED)==0)
		seed++;

	if ((m_keyfreeze.GetState()&BST_CHECKED)==0)	
		rrr = rand();

	ook__c_EncrypData(p_buffer,len+3);

	

	ook__h_EncodeData(c_buffer,len+3+2);
	

	
	//ook__b_SerializeData(h_buffer,(len+3+2)*2);

	// 2. presentation
	if(m_radio==2)
	{
	statlen = len+3;
	statptr = (u8*)p_buffer;
	}

	pb = buffer;
	for(u8 i = 0;i<len+3;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(p_buffer[i]));
	}
	m_p_Data.SetWindowText(buffer);

	sprintf(buffer,"%d",len+3);
	m_p_Len.SetWindowText(buffer);

	// 3. crypt
	if(m_radio==1)
	{
	statlen = len+3+2;
	statptr = (u8*)c_buffer;
	}
	pb = buffer;
	for(u8 i = 0;i<len+3+2;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(c_buffer[i]));
	}
	m_c_Data.SetWindowText(buffer);

	//sprintf(buffer,"%d",len+3+2);
	//m_c_Len.SetWindowText(buffer);

	pb = buffer;
	pb+= sprintf(pb,"s=%02x k=%02x l=%d",seed,key,len+3+2);
	m_c_Len.SetWindowText(buffer);

	// 4. hamming coding
	/*srand(h_buffer[0]);
	for(u16 i=1;i<(len+3+2)*2;i++)
	{
		h_buffer[i]+=rand()%256;
	}*/

	if(m_radio==0)
	{
	statlen = (len+3+2)*2;
	statptr = (u8*)h_buffer;
	}

	pb = buffer;
	for(u8 i = 0;i<(len+3+2)*2;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(h_buffer[i]));
	}
	m_h_Data.SetWindowText(buffer);

	sprintf(buffer,"%d",(len+3+2)*2);
	m_h_Len.SetWindowText(buffer);

	// add bit error on the hamming coding
	m_nrbiterrors.GetWindowText(str);
	nrerrors = _ttoi(str);

	buffer[0]=0;
	pb = buffer;
	for(u8 k=0;k<nrerrors;k++)
	{
		u16 bbitpos = rand()% ((len+3+2)*2*8);
		u8 bytepos = bbitpos/8;
		u8 bitpos = bbitpos%8;

		h_buffer[bytepos] = h_buffer[bytepos] ^(1<<bitpos);

		pb+= sprintf(pb,"%02x ",(u8)bbitpos);
	}

	/*pb = buffer;
	pb+= sprintf(pb,"len = %d ",(u8)rxlen);*/
	m_errorbits.SetWindowText(buffer);

	ook__b_SerializeData(h_buffer,(len+3+2)*2);

	

	// 5. Sub bit coding
	/*statlen = (len+3+2)*2*3+2;
	statptr = (u8*)b_buffer;*/
	if(m_radio==4)
	{
	statlen = (len+3+2)*2*3+2;
	statptr = (u8*)b_buffer;
	}

	pb = buffer;
	for(u8 i = 0;i<(len+3+2)*2*3+2;i++)
	{
		for(u8 b=0;b<8;b++)
		{
			if((b_buffer[i]&(1<<(7-b)))!=0)
			{
				//	pb+= sprintf(pb,"1");
				dcbal++;
			}
			else
			{
				//	pb+= sprintf(pb,"0");
				dcbal--;
			}

		}

		pb+= sprintf(pb,"%02x ",(u8)(b_buffer[i]));
		if(((i+1)%25)==0)
		{
			pb+= sprintf(pb,"\r\n");
		}
	}
//	m_b_Data.SetWindowText(buffer);



	/*static double dcbalavg = 0;
	static int nrmes = 1;*/
	dcbalavg= (dcbalavg+dcbal)/(double)nrmes;
	nrmes++;

	sprintf(buffer,"%d",(len+3+2)*2*3+2);
//	m_b_Len.SetWindowText(buffer);
	sprintf(buffer,"%f",dcbalavg);
	m_b_DC.SetWindowText(buffer);

	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------
	/// ok now try to decode it

	//change encode and decode stuff here
	// dont use bit buffer, use hamming buffer and encode data 
	memset(&sbd_state,0,sizeof(sbd_state));

	{
		u16 chnoise,bittol;
		m_channelnoise.GetWindowText(str);
		chnoise = _ttoi(str);
		m_bittolerance.GetWindowText(str);
		bittol = _ttoi(str);

#define noise_amp (10)
		u16 t;
		for(u16 i=0;i<chnoise;i++)
		{
			sbd_decode(rand()%3000);
		}

		sbd_decode(2000);
		bittol+=1;
		for(u8 i=0;i<(len+3+2)*2;i++)
		{
			for(u8 j=0;j<8;j++)
			{
				if(h_buffer[i]&(1<<(7-j)))
					t = 1000;
				else
					t = 500;
	
				t+=rand()%bittol-bittol/2;
				sbd_decode(t);
			}
		}
	}
	
	// fill decoding statistics
	sprintf(buffer,"%d",sbd_state.nr_errors);
	m_r_nrerrors.SetWindowText(buffer);

	sprintf(buffer,"%d",sbd_state.nr_restarts);
	m_r_nrrestart.SetWindowText(buffer);


	//rec hamming
	memcpy(rh_buffer,sbd_state.recbuffer,(len+3+2)*2);
	rxlen = (len+3+2)*2;



	//bit
	//memset(rb_buffer,0,b_size);
	//memcpy(rb_buffer,b_buffer,(len+3+2)*2*3+2);
	//ook__rb_BitDecode();

	pb = buffer;
	for(u8 i = 0;i<(len+3+2)*2;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(rh_buffer[i]));
	}
	m_dh_Data.SetWindowText(buffer);

	pb = buffer;
	pb+= sprintf(pb,"len = %d ",(u8)rxlen);
	m_dh_Msg.SetWindowText(buffer);


	 ook_dec_b1error =0;
 ook_dec_b2error =0;
 
	//---------------
	/*srand(rh_buffer[0]);
	for(u16 i=1;i<(len+3+2)*2;i++)
	{
		rh_buffer[i]-=rand()%256;
	}*/
	ook__rh_HammingDecode();
	pb = buffer;
	for(u8 i = 0;i<len+3+2;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(rc_buffer[i]));
	}
	m_dc_Data.SetWindowText(buffer);

	pb = buffer;
	pb+= sprintf(pb,"len = %d b1e=%d b2e=%d",(u8)rxlen*2,ook_dec_b1error,ook_dec_b2error);
	m_dh_Msg.SetWindowText(buffer);

	//------------
	res = ook__rc_Decrypt();
	pb = buffer;
	for(u8 i = 0;i<len+3;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(rp_buffer[i]));
	}
	m_dp_Data.SetWindowText(buffer);
	
	pb = buffer;
	pb+= sprintf(pb,"s=%02x k=%02x lockout=%d",dec_seed,dec_key,res);
	m_dc_Msg.SetWindowText(buffer);





	///-
	res = ook_a_GetData();
	pb = buffer;
	for(u8 i = 0;i<len;i++)
	{
		pb+= sprintf(pb,"%02x ",(u8)(ra_buffer[i]));
	}
	m_da_Data.SetWindowText(buffer);

	pb = buffer;
	pb+= sprintf(pb,"crc valid = %d ",1-(u8)res);
	m_dp_Msg.SetWindowText(buffer);


	//calculate statistics
	{
		pb = buffer;
		u16 i;
		u8 j;



		for(i=0;i<statlen;i++)
		{
			j = statptr[i];
			//j = ook_prbs7();
			if(stats[j]<255)
				stats[j]++;			
		}
		for(i=0;i<256;i++)
		{
			pb+= sprintf(pb,"%2d ",stats[i]);
			if(((i+1)%32)==0)
			{
				pb+= sprintf(pb,"\r\n");
			}
		}
		m_statistics.SetWindowText(buffer);
		m_statistics.UpdateWindow();

		memcpy(m_drawarea.stat,stats,256);
		m_drawarea.Invalidate(0);
		
	}





}

void CookprotocolDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	OnEnChangeEdit1();
}

void CookprotocolDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	OnEnChangeEdit1();
}

void CookprotocolDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString str;
	char a;
	mInputText.GetWindowText(str);
	a = str.GetAt(str.GetLength()-1);
	str.SetAt(str.GetLength()-1,a+1);
	mInputText.SetWindowText(str);


	OnEnChangeEdit1();
}

void CookprotocolDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString str;
	char a;
	mInputText.GetWindowText(str);
	a = str.GetAt(str.GetLength()-1);
	str.SetAt(str.GetLength()-1,a-1);
	mInputText.SetWindowText(str);
	OnEnChangeEdit1();
}

void CookprotocolDlg::OnEnChangeEdit21()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
//	OnEnChangeEdit1();

}

void CookprotocolDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	u16 i;
	for(i=0;i<256;i++)
	{
		stats[i]=0;			
	}		
	OnEnChangeEdit1();
}
