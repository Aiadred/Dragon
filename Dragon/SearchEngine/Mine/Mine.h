#pragma once
#include "FactoryObj.h"
class CMine:public CSearchEngine
{
public:
	CMine(void);
	virtual ~CMine(void);
public:
	void SetSearchDepth(int InputSearchDepth);

	
};

