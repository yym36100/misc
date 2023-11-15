#pragma once

namespace siege{
	class CDebugMsg
	{
	public:
		CDebugMsg(void);
		virtual ~CDebugMsg(void);

		virtual void Msg(wchar_t *msg) =0;
	};
}