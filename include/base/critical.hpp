#ifndef __CRITICAL_HPP__
#define __CRITICAL_HPP__

#include <Windows.h>

namespace CCTool{

class Critical
{
public:
	Critical()
	{
		InitializeCriticalSection(&g_cs);
	}
	~Critical(){}
	void lock()
	{
		EnterCriticalSection(&g_cs);
	}

	void unlock()
	{
		LeaveCriticalSection(&g_cs);
	}
protected:
private:
	CRITICAL_SECTION g_cs;
};

}

#endif