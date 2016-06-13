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

	//棋盘副本，防止污染原有棋盘数据
	int Board_MG[8][8];
	//保存所有棋子的可行性信息
	CNodeChessInfo PossibleMove[20][100];
	static int nTypeToGo;
	Location Local_Current[12];
	
private:
	int Kill_Method;
	int Kill_Flag;
	int DepthMax[12];
protected:
	//PossibleMove置零函数
	void FUNC_RESET(int nPly,int Position);
	bool MakePossibleKill(int x,int y,int nSide,int nCount,int Depth,int Direction_Form,int nPly);
	void MakePossibleMove(int x,int y,int nCount,int Value,int nPly);
	//添加布局信息
	void Add_Poly(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nPly);
	//保存所有杀棋队列的链表,便于以后筛选
	void Kill_Chain_Add(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nSpace_After,int x,int y,int nPly);
	//清空链表
	void Chain_Clear(void);
	//解析杀棋链表中的信息，提取出杀得最多的走法
	bool AnalyzeKillInfo(int nCount,int (*Board_MG)[8],int nSide,int nPly);
	CNodeChessInfo *Head;
	CNodeChessInfo *Link;
	
};



