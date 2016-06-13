#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer(void)
{
	QueryPerformanceCounter(&this->m_nBeginTime);
	QueryPerformanceFrequency(&this->m_nFrequency);
}


CTimer::~CTimer(void)
{
}
double  CTimer::CalculateTime()
{

	QueryPerformanceCounter(&this->m_nEndTime);
	return (double)((m_nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFrequency.QuadPart);
}