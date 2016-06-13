#pragma once
#include "Public.h"
#include "MoveGenerator.h"

#include "Evalute.h"

#include "Trans_Table.h"
class CSearchEngine
{
public:
	CSearchEngine(void);
	virtual ~CSearchEngine(void);
	///////////////��������ӿ�/////////////////////////////////
	virtual void SearchAGoodMove(int (*iBoard)[8])=0;//��������ǰ��õ����巽��
	///////////////��������ӿ�/////////////////////////////////
	void SetSearchDepth(int nPly);//��ʼ���������
	void SetEvalutor(CEvalute *pEVA_Input);//��ʼ��Evalutor
	void SetMoveGenerator(CMoveGenerator *pMG_Input);//��ʼ��MoveGenerator
	////////ATTENTION!!!��δ����//////////
	int IsGameOver(int Depth);//�ж��Ƿ�GameOver
	int Board_Copy[8][8];
protected:
	//;//���������������ӣ����б�����������巽��
	CMoveGenerator *pMG;//MoveGeneratorָ�����ڵ���MoveGenerator
	CEvalute *pEVA;
	int MaxSearchPly;//�����������
	int Value_Buff[20][100];//10��//����ɱ�������ӵļ�ֵ�����ڻ�ԭ������
	CTrans_Table m_nTT;
	CNodeChessInfo *BestChess;
	static bool Flag;
};

