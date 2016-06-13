#pragma once
#include "PublicDefine.h"
#include "Public.h"
#include "MakeMove.h"
class CMoveGenerator
{
public:
	CMoveGenerator();
	CMoveGenerator(int (*Input_Board)[8]);
	virtual ~CMoveGenerator();
	CMakeMove *pMM;
public:
	int MakePossibleChess(int nSide,int nPly);

	//���̸�������ֹ��Ⱦԭ����������
	int Board_MG[8][8];
	//�����������ӵĿ�������Ϣ
	CNodeChessInfo PossibleMove[20][100];
	static int nTypeToGo;
	Location Local_Current[12];
	
private:
	int Kill_Method;
	int Kill_Flag;
	int DepthMax[12];
protected:
	//PossibleMove���㺯��
	void FUNC_RESET(int nPly,int Position);
	bool MakePossibleKill(int x,int y,int nSide,int nCount,int Depth,int Direction_Form,int nPly);
	void MakePossibleMove(int x,int y,int nCount,int Value,int nPly);
	//��Ӳ�����Ϣ
	void Add_Poly(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nPly);
	//��������ɱ����е�����,�����Ժ�ɸѡ
	void Kill_Chain_Add(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nSpace_After,int x,int y,int nPly);
	//�������
	void Chain_Clear(void);
	//����ɱ�������е���Ϣ����ȡ��ɱ�������߷�
	bool AnalyzeKillInfo(int nCount,int (*Board_MG)[8],int nSide,int nPly);
	CNodeChessInfo *Head;
	CNodeChessInfo *Link;
	
};



