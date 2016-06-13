#include "stdafx.h"
#include "PVS.h"
#include "ShowInfo.h"
//有bug，在王右下吃子时把左上的子吃掉



IMPLEMENT(CPVS,1)

CPVS::CPVS(void)
{
}


CPVS::~CPVS(void)
{
}

void CPVS::SearchAGoodMove(int (*iBoard)[8])
{
	int nCount=0;
	int Alpha=-20000000;
	int Beta=20000000;
	memcpy_s(Board_Copy,8*8*4,iBoard,8*8*4);
	//22与24不可调换位置，因为24的执行调用了22的Board_Copy
	CMoveGenerator pMG_Input(Board_Copy);
	CEvalute pEVA_Input;
	SetMoveGenerator(&pMG_Input);
	SetEvalutor(&pEVA_Input);

	m_nTT.CaculateInitHashKey(Board_Copy);



	PVS(0,Alpha,Beta);

	pMG->pMM->MakeMove(*BestChess,pMG->Board_MG);

	memcpy_s(Board_Copy,8*8*4,pMG->Board_MG,8*8*4);

	//1.统计当前我方势力棋子数
	//2.遍历所有棋子的Alpha-Beta剪枝算法列出所有棋子的最佳方案(估值)
	//3.挑选最优估值的棋子
	//4.行棋
}
////////////////Method 1//////////////
//int CPVS::PVS(int nPly,int Alpha,int Beta)
//{
//	int Value=0;
//	int nTypeRoute=0;
//	int Best=0;
//	int i;
//	if(nPly%2!=0&&nPly!=0)
//		Turn = ENEMY;	//如果进入层数是2的偶数倍，则最后必定是对方走棋
//	else
//		Turn = MINE;	//否则为我方走棋
//	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
//		return i;
//	if(nPly==MaxSearchPly)
//	{
//		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//返回估值
//	}
// 	nTypeRoute=pMG->MakePossibleChess(Turn,nPly);	
//	pMG->pMM->MakeMove(pMG->PossibleMove[nPly][0],pMG->Board_MG);	
//	Best=-PVS(nPly+1,-Beta,-Alpha);
//	pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][0],pMG->Board_MG);
//	if(nPly==0)
//		BestChess=&(pMG->PossibleMove[nPly][0]);
//	for(int TypeCount=1;TypeCount<nTypeRoute;TypeCount++)
//	{
//		pMG->pMM->MakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);		
//		Value=-PVS(nPly+1,-Alpha-1,-Alpha);
//		if(Value>Alpha&&Value<Beta)
//		{
//			Value=-PVS(nPly+1,-Beta,-Alpha);
//			if(nPly==0)
//			{
//				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
//			}
//		}
//		pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);
//		if(Value>=Best)
//		{
//			Best=Value;
//			if(nPly==0)
//				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
//			if(Value>=Alpha)
//			{
//				Alpha=Value;
//			}
//			if(Value>=Beta)
//			{
//				break;
//			}
//		}
//	}
//
//	return Best;
//}
////////////////Method 2//////////////
int CPVS::PVS(int nPly,int Alpha,int Beta)
{
	CShowInfo::nCount_Total++;
	int Turn=0;
	int Value=0;
	int nTypeRoute=0;
	int i;
	bool FoundPV=false;
	if(nPly%2!=0&&nPly!=0)
		Turn = ENEMY;	//如果进入层数是2的偶数倍，则最后必定是对方走棋
	else
		Turn = MINE;	//否则为我方走棋
	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
		return i;

	Value=m_nTT.SearchHashKey(Alpha,Beta,nPly,Turn);
	if(Value!=8459439)		//置换表直接命中，返回值
	{
		CShowInfo ::nCount_Hit++;
		return Value;
	}

	if(nPly==MaxSearchPly)
	{
		Value=pEVA->Evalute(pMG->Board_MG,Turn);
		m_nTT.PushNodeIntoHash(exact,Value,nPly,Turn);
		return	Value;	//返回估值
	}
 	nTypeRoute=pMG->MakePossibleChess(Turn,nPly);	
	if(nTypeRoute==1&&nPly==0&&Flag==false)//如果只有一种走法(杀棋)则无需考虑其他
	{
		m_nTT.MakeMoveHashKey(pMG->PossibleMove[0][0],pMG->Board_MG,Turn);
		pMG->pMM->MakeMove(pMG->PossibleMove[0][0],pMG->Board_MG);

		Value=pEVA->Evalute(pMG->Board_MG,Turn);

		m_nTT.ResetMoveHashKey(pMG->PossibleMove[0][0],pMG->Board_MG,Turn,pMG->pMM->Value_Buff);
		pMG->pMM->ResetMakeMove(pMG->PossibleMove[0][0],pMG->Board_MG);

		m_nTT.PushNodeIntoHash(exact,Value,nPly,Turn);
		BestChess=&(pMG->PossibleMove[0][0]);
		Flag=true;
		return Alpha;
	}
	int eval_is_exact=0;
	for(int TypeCount=0;TypeCount<nTypeRoute;TypeCount++)
	{
		m_nTT.MakeMoveHashKey(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG,Turn);
		pMG->pMM->MakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);			
		if(FoundPV)
		{
			Value=-PVS(nPly+1,-Alpha-1,-Alpha);
			if((Value>Alpha)&&(Value<Beta))//证明还有更好的PV节点，刚才的假证是错误的
			{
				Value=-PVS(nPly+1,-Beta,-Alpha);
			}
			/*if(nPly==0)
			{
				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
			}*/
		}
		else
			Value=-PVS(nPly+1,-Beta,-Alpha);
		m_nTT.ResetMoveHashKey(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG,Turn,pMG->pMM->Value_Buff);
		pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);
		if(Value>=Beta)//得到β节点
		{
			CShowInfo::nCount_Cut++;
			m_nTT.PushNodeIntoHash(lower_bound,Value,nPly,Turn);
			if(nPly==0)
			{
				CShowInfo::nCount_WinMin= Alpha;
				CShowInfo::nCount_WinMax= Beta;
				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
			}
			return Value;
		}
		if(Value>Alpha)//得到PV节点
		{
			eval_is_exact=1;
			if(nPly==0)
				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
			Alpha=Value;
			FoundPV=true;
		}		
	}
	
	if(eval_is_exact)
		m_nTT.PushNodeIntoHash(exact,Alpha,nPly,Turn);
	else
		m_nTT.PushNodeIntoHash(upper_bound,Alpha,nPly,Turn);
	if(nPly==0)
	{
		CShowInfo::nCount_WinMin= Alpha;
		CShowInfo::nCount_WinMax= Beta;
	}
	return Alpha;
}
////////////////Method 3//////////////
//int CPVS::PVS(int nPly,int Alpha,int Beta)
//{
//	int Value=0;
//	int nTypeRoute=0;
//	int Best=0;
//	int i;
//	if(nPly%2!=0&&nPly!=0)
//		Turn = ENEMY;	//如果进入层数是2的偶数倍，则最后必定是对方走棋
//	else
//		Turn = MINE;	//否则为我方走棋
//	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
//		return i;
//	if(nPly==MaxSearchPly)
//	{
//		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//返回估值
//	}
// 	nTypeRoute=pMG->MakePossibleChess(Turn,nPly);	
//	pMG->pMM->MakeMove(pMG->PossibleMove[nPly][0],pMG->Board_MG);	
//	Best=-PVS(nPly+1,-Beta,-Alpha);
//	pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][0],pMG->Board_MG);
//	if(nPly==0)
//		BestChess=&(pMG->PossibleMove[nPly][0]);
//	for(int TypeCount=1;TypeCount<nTypeRoute;TypeCount++)
//	{
//		if(Best<Beta)
//		{
//			if(Best>Alpha)
//				Alpha=Best;
//			pMG->pMM->MakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);		
//			Value=-PVS(nPly+1,-Alpha-1,-Alpha);
//			if(Value>Alpha&&Value<Beta)
//			{
//				Best=-PVS(nPly+1,-Beta,-Value);
//				if(nPly==0)
//				{
//					BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
//				}
//			}
//			else if(Value>Best)
//			{
//				Best=Value;
//				if(nPly==0)
//				{
//					BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
//				}
//			}
//			pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);
//		}
//	}
//
//	return Best;
//}