// se4.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cse4App:
// See se4.cpp for the implementation of this class
//

class Cse4App : public CWinApp
{
public:
	Cse4App();
	~Cse4App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cse4App theApp;