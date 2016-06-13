#include "stdafx.h"
#include "FactoryObj.h"
using namespace std;
CFactoryObj::CFactoryObj(void)
{
}


CFactoryObj::~CFactoryObj(void)
{
}
//list<ObjNode *> CFactoryObj::m_pListObj;
ObjNode* CFactoryObj::Head=NULL;
CSearchEngine *CFactoryObj::SearchObj(int Num_Selected)
{
	while(Head!=NULL)
	{
		if(Head->Num==Num_Selected)
			return CFactoryObj::Head->FuncObj();
		Head=Head->pNext;
	}
}
