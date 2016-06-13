#include "stdafx.h"
#include "PVS.h"
#include "ShowInfo.h"
//��bug���������³���ʱ�����ϵ��ӳԵ�



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
	//22��24���ɵ���λ�ã���Ϊ24��ִ�е�����22��Board_Copy
	CMoveGenerator pMG_Input(Board_Copy);
	CEvalute pEVA_Input;
	SetMoveGenerator(&pMG_Input);
	SetEvalutor(&pEVA_Input);

	m_nTT.CaculateInitHashKey(Board_Copy);



	PVS(0,Alpha,Beta);

	pMG->pMM->MakeMove(*BestChess,pMG->Board_MG);

	memcpy_s(Board_Copy,8*8*4,pMG->Board_MG,8*8*4);

	//1.ͳ�Ƶ�ǰ�ҷ�����������
	//2.�����������ӵ�Alpha-Beta��֦�㷨�г��������ӵ���ѷ���(��ֵ)
	//3.��ѡ���Ź�ֵ������
	//4.����
}
////////////////Method 1//////////////
//int CPVS::PVS(int nPly,int Alpha,int Beta)
//{
//	int Value=0;
//	int nTypeRoute=0;
//	int Best=0;
//	int i;
//	if(nPly%2!=0&&nPly!=0)
//		Turn = ENEMY;	//������������2��ż�����������ض��ǶԷ�����
//	else
//		Turn = MINE;	//����Ϊ�ҷ�����
//	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
//		return i;
//	if(nPly==MaxSearchPly)
//	{
//		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//���ع�ֵ
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
		Turn = ENEMY;	//������������2��ż�����������ض��ǶԷ�����
	else
		Turn = MINE;	//����Ϊ�ҷ�����
	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
		return i;

	Value=m_nTT.SearchHashKey(Alpha,Beta,nPly,Turn);
	if(Value!=8459439)		//�û���ֱ�����У�����ֵ
	{
		CShowInfo ::nCount_Hit++;
		return Value;
	}

	if(nPly==MaxSearchPly)
	{
		Value=pEVA->Evalute(pMG->Board_MG,Turn);
		m_nTT.PushNodeIntoHash(exact,Value,nPly,Turn);
		return	Value;	//���ع�ֵ
	}
 	nTypeRoute=pMG->MakePossibleChess(Turn,nPly);	
	if(nTypeRoute==1&&nPly==0&&Flag==false)//���ֻ��һ���߷�(ɱ��)�����迼������
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
			if((Value>Alpha)&&(Value<Beta))//֤�����и��õ�PV�ڵ㣬�ղŵļ�֤�Ǵ����
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
		if(Value>=Beta)//�õ��½ڵ�
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
		if(Value>Alpha)//�õ�PV�ڵ�
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
//		Turn = ENEMY;	//������������2��ż�����������ض��ǶԷ�����
//	else
//		Turn = MINE;	//����Ϊ�ҷ�����
//	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
//		return i;
//	if(nPly==MaxSearchPly)
//	{
//		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//���ع�ֵ
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