#include "StdAfx.h"
#include "SContainer.h"
#include "MsgPump.h"

namespace siege{
	MsgPump MsgPump::instance;


	void MsgPump::init()
	{
		pEvent = new CSContainer;
		pChild = new CSContainer;
	}

	void MsgPump::deinit()
	{
		inited=false;
		delete pEvent;
		delete pChild;
		pEvent = NULL;
	}

}