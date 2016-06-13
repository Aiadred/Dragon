#pragma once

#include "FactoryObj.h"
//Ö÷Òª±ßÀýËÑË÷ÒýÇæ PVS
class CPVS:public CSearchEngine
{

DECLEAR(CPVS)
public:
	CPVS(void);
	virtual ~CPVS(void);
	virtual void SearchAGoodMove(int (*iBoard)[8]);
protected:
	int PVS(int Depth,int Alpha,int Beta);
};

