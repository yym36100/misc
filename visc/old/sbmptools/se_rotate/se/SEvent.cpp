#include "StdAfx.h"
#include "SEvent.h"

#include "siegecfg.h"

namespace siege{
	/*CSEvent::CSEvent(void)
	{
	}*/

	CSEvent::~CSEvent(void)
	{
		siege_dbg(L"Event deleted\n");
	}
}