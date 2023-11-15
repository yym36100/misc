#pragma once


namespace siege{
	class CSObject
	{
	public:
		CSObject(void);
		virtual ~CSObject(void);

		CSObject *p,*n;
	};
}