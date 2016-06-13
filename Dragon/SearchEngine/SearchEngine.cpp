#include "stdafx.h"
#include "SearchEngine.h"
//存在问题：
//1.MoveGenerator与SearchEngine的衔接问题
//2.关于Board_Copy的赋值紊乱
//3.MakeMove与ResetMakeMove有潜在问题
//4.关于如何在深层搜索时，规避返回上次行走的起始点
//
bool CSearchEngine::Flag=false;
CSearchEngine::CSearchEngine(void)
{
	pMG=NULL;//MoveGenerator指针用于调用MoveGenerator
	pEVA=NULL;
	MaxSearchPly=0;//最大的搜索深度

	memset(Value_Buff,0,10*12*4);//////////////////////ATTENTION!!!!
	BestChess=NULL;
}


CSearchEngine::~CSearchEngine(void)
{
	
	pMG=NULL;//MoveGenerator指针用于调用MoveGenerator
	pEVA=NULL;
	BestChess=NULL;
}
//初始化搜索深度
void CSearchEngine::SetSearchDepth(int nPly)
{
	MaxSearchPly=nPly;
}
//初始化Evalutor
void CSearchEngine::SetEvalutor(CEvalute *pEVA_Input)
{

	pEVA=pEVA_Input;

}
//初始化MoveGenerator
void CSearchEngine::SetMoveGenerator(CMoveGenerator *pMG_Input)
{
	pMG=pMG_Input;

}
//尚未被调用，或许存在位
//判断是否GameOver
int CSearchEngine::IsGameOver(int Depth)
{
	int i;	int j;
	bool Black_Live=false;	
	bool White_Live=false;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(Board_Copy[i][j]==BLACK_SOLDIER||Board_Copy[i][j]==BLACK_KING)
			{
				Black_Live=true;
			}
			else if(Board_Copy[i][j]==WHITE_SOLDIER||Board_Copy[i][j]==WHITE_KING)
			{
				White_Live=true;
			}
			else if(Black_Live==true&&White_Live==true)
				goto GO_TO_FLAG;

		}
	}
	GO_TO_FLAG :;
	i=(MaxSearchPly-Depth+1)%2;
	if(Black_Live==false)
	{
		if(i)
			return 199990+Depth;
		else
			return -199990-Depth;
	}
	else if(White_Live==false)
	{
		if(i)
			return -199990-Depth;
		else
			return 199990+Depth;
	}
}
