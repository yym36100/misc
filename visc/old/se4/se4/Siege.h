#pragma once

class CSiege
{
public:

	CSiege *pNext;

	CSiege(void):pNext(NULL){}
	virtual ~CSiege(void){}

	void AddNext(CSiege *pN)
	{
		CSiege *n=this;
		while(n->pNext)
			n=n->pNext;
		n->pNext = pN;
	}
};
