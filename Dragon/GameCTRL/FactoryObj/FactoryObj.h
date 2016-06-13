#pragma once

#include <list>
#include "SearchEngine.h"

#define DECLEAR(INPUTCLASS)		\
	public:\
	static ObjNode INPUTCLASS##_Node;\
	static CSearchEngine *CreateObj();

#define IMPLEMENT(INPUTCLASS,Num)	\
	ObjNode INPUTCLASS::INPUTCLASS##_Node={&INPUTCLASS::CreateObj,Num,NULL};\
	CSearchEngine *INPUTCLASS::CreateObj()\
	{\
		return new INPUTCLASS;\
	}\
	ReChain INPUTCLASS##_Add(&INPUTCLASS::INPUTCLASS##_Node);

typedef struct NODE
{
	CSearchEngine *(*FuncObj)();
	int Num;
	struct NODE *pNext;
}ObjNode;




class CFactoryObj
{
public:
	/*static list<ObjNode *> m_pListObj;*/
	static CSearchEngine *SearchObj(int Num_Selected);
	static ObjNode* Head;
public:
	CFactoryObj(void);
	~CFactoryObj(void);

};

class ReChain
{
public:
	ReChain(ObjNode *InputNode)
	{
		InputNode->pNext=CFactoryObj::Head;
		CFactoryObj::Head=InputNode;

	}
	
};

