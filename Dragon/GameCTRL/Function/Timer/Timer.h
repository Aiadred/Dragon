#pragma once
#include "function.h"
class CTimer :
	public CFunction
{
public:
	CTimer(void);
	virtual ~CTimer(void);
public:
	double  CalculateTime();
private:
	LARGE_INTEGER m_nFrequency;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
};

