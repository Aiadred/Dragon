#include "stdafx.h"
#include "AlphaBeta.h"
#include "ShowInfo.h"
//���⣺1.Ϊ�ε�����Ϊ�������ǻ᷸ɵ��
//		2.�����������̫ǿ��������
//		3.�߷��������������Ŀǰ����ֻ��һ���߷�ʱ���迼���������߷�
//		4.��ֵ�д�����
//		5.��������ĸ����Լ�����ȵ��㷨


IMPLEMENT(CAlphaBeta,0)

CAlphaBeta::CAlphaBeta(void)
{



}
CAlphaBeta::~CAlphaBeta(void)
{


}

void CAlphaBeta::SearchAGoodMove(int (*iBoard)[8])
{

	int Alpha=-10300;
	int Beta=-10280;
	memcpy_s(Board_Copy,8*8*4,iBoard,8*8*4);
	//22��24���ɵ���λ�ã���Ϊ24��ִ�е�����22��Board_Copy
	CMoveGenerator pMG_Input(Board_Copy);
	CEvalute pEVA_Input;
	SetMoveGenerator(&pMG_Input);
	SetEvalutor(&pEVA_Input);

	m_nTT.CaculateInitHashKey(Board_Copy);
	
	AlphaBeta(0,Alpha,Beta);
	pMG->pMM->MakeMove(*BestChess,pMG->Board_MG);

	memcpy_s(Board_Copy,8*8*4,pMG->Board_MG,8*8*4);

	//1.ͳ�Ƶ�ǰ�ҷ�����������
	//2.�����������ӵ�Alpha-Beta��֦�㷨�г��������ӵ���ѷ���(��ֵ)
	//3.��ѡ���Ź�ֵ������
	//4.����
}


int CAlphaBeta::AlphaBeta(int nPly,int Alpha,int Beta)
{
	CShowInfo::nCount_Total++;

	int Turn=0;
	int Value=0;
	int i=0;
	int nTypeRoute=0;
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
	int TypeCount=0;
	int eval_is_exact=0;
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
	else 
	{
		for(int TypeCount=0;TypeCount<nTypeRoute;TypeCount++)
		{
			m_nTT.MakeMoveHashKey(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG,Turn);
			pMG->pMM->MakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);
			int Turn_Copy=Turn;
			Value=-AlphaBeta(nPly+1,-Beta,-Alpha);

			m_nTT.ResetMoveHashKey(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG,Turn,pMG->pMM->Value_Buff);
			pMG->pMM->ResetMakeMove(pMG->PossibleMove[nPly][TypeCount],pMG->Board_MG);
			if(Value>=Alpha)
			{
				eval_is_exact=1;
				if(nPly==0)
				{
					BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
				}
				Alpha=Value;
			}
			if(Alpha>=Beta)
			{
				CShowInfo::nCount_Cut++;
				m_nTT.PushNodeIntoHash(lower_bound,Value,nPly,Turn);
				if(nPly==0)
				{
					CShowInfo::nCount_WinMin= Alpha;
					CShowInfo::nCount_WinMax= Beta;
				}
				return Alpha;
			}
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