// sound3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "sound3.h"
#include "sound.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


class CWavesound : public CSound {

public:
	char *buffer;
	long buflen;
	char *playp;
	char *endp;

	virtual bool GetSignal(void) {
		bool res = true;
		if(playp<(endp-bufsize*2)){
			memcpy(dst,playp,bufsize*2);
			playp+=bufsize*2;
		} else {
			this->Stop();			
			res  = false;
		}
		return res;
	}
	void Init(void) {
		playp = 0;
		readFileData("e:\\visc\\ignite.wav");
		parseWav();		
		playp+=1024*18000;
		endp = buffer + buflen;
	}

	void readFileData(char *szFilename)
	{
		FILE *fp = fopen(szFilename, "rb");
		long len;		
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		buffer = (char*) calloc(1, len+1);
		fread(buffer, 1, len, fp);
		fclose(fp);
		buflen = len;		
	}

	void parseWav()
	{
		char *data = buffer;
		long *mPtr;
		long *tmpPtr;

		mPtr = (long*)data;

		if ( mPtr[0] == 0x46464952) //  little endian check for 'RIFF'
		{
			mPtr += 3;
			if (mPtr[0] == 0x20746D66)  // little endian for "fmt "
			{
				tmpPtr = mPtr;				
				tmpPtr += 6;
				mPtr = (long*)tmpPtr;
				if (mPtr[0] == 0x61746164)        // little endian for "data"
				{					
					playp = (char*)mPtr;					
				}
			}

		}		
	}
};

CWavesound *snd;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{	
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SOUND3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOUND3));

	snd = new CWavesound();
	snd->Init();
	snd->Open();
	snd->Play();
	/*Sleep(30000);
	snd->Stop();
	snd->Close();*/

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOUND3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SOUND3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
