#include "stdafx.h"
#include "Reset.h"


CReset::CReset(void)
{
}


CReset::~CReset(void)
{
	list<int (*)[8]>::iterator ite=List_Re.begin();
	while(List_Re.empty()==false)
	{
		delete []List_Re.front();
		List_Re.pop_front();
	}

}
list<int (*)[8]> CReset::List_Re;

void CReset::PushList(int (*Board_Re)[8])
{
	List_Re.push_front(Board_Re);

}