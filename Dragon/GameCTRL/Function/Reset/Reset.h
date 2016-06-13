#pragma once
#include "function.h"
#include <list>
using namespace std;

class CReset :public CFunction
{
public:
	CReset(void);
	virtual ~CReset(void);
public:
	static list<int (*)[8]> List_Re;
	static void PushList(int (*Board_Re)[8]);
};

