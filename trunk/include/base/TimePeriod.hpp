#ifndef __TIME_PERIOD_HPP__
#define __TIME_PERIOD_HPP__

#include <Windows.h>
#include <assert.h>

namespace CCTool{

class TimePeriod
{
public:
	TimePeriod()
	{
		int b = QueryPerformanceFrequency(&Freq_);
		assert(b);
	}
	void setBegin()
	{
		QueryPerformanceCounter(&time_begin_); 
	}

	void setEnd()
	{
		QueryPerformanceCounter(&time_end_); 
	}

	int getTimePeriod()
	{
		int time=(((time_end_.QuadPart - time_begin_.QuadPart) * 1000)/Freq_.QuadPart);
		return time;
	}
	int getTimePeriodns()
	{
		int time=(((time_end_.QuadPart - time_begin_.QuadPart) * 1000)/(Freq_.QuadPart/1000));
		return time;
	}
protected:
private:
	LARGE_INTEGER time_begin_;
	LARGE_INTEGER time_end_;
	LARGE_INTEGER Freq_;

};

}
#endif