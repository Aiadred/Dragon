#include "stdafx.h"
#include "SearchEngine.h"
//�������⣺
//1.MoveGenerator��SearchEngine���ν�����
//2.����Board_Copy�ĸ�ֵ����
//3.MakeMove��ResetMakeMove��Ǳ������
//4.����������������ʱ����ܷ����ϴ����ߵ���ʼ��
//
bool CSearchEngine::Flag=false;
CSearchEngine::CSearchEngine(void)
{
	pMG=NULL;//MoveGeneratorָ�����ڵ���MoveGenerator
	pEVA=NULL;
	MaxSearchPly=0;//�����������

	memset(Value_Buff,0,10*12*4);//////////////////////ATTENTION!!!!
	BestChess=NULL;
}


CSearchEngine::~CSearchEngine(void)
{
	
	pMG=NULL;//MoveGeneratorָ�����ڵ���MoveGenerator
	pEVA=NULL;
	BestChess=NULL;
}
//��ʼ���������
void CSearchEngine::SetSearchDepth(int nPly)
{
	MaxSearchPly=nPly;
}
//��ʼ��Evalutor
void CSearchEngine::SetEvalutor(CEvalute *pEVA_Input)
{

	pEVA=pEVA_Input;

}
//��ʼ��MoveGenerator
void CSearchEngine::SetMoveGenerator(CMoveGenerator *pMG_Input)
{
	pMG=pMG_Input;

}
//��δ�����ã��������λ
//�ж��Ƿ�GameOver
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
