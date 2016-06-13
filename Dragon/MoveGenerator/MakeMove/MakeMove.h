#pragma once
#include "Public.h"
class CMakeMove
{
public:
	CMakeMove(int (*Board_Input)[8]);
	CMakeMove(void);
	~CMakeMove(void);
public:
	//走动布局
	void Move_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//还原走动布局
	void Move_Re_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//杀棋布局,返回杀掉的棋的价值
	int Move_Kill(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//还原杀棋布局
	void Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value,int (*Board_MM)[8]);
	//王的走动布局
	void King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8]);
	//王的走动布局还原
	void King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8]);
	//王的杀棋布局，返回杀掉的棋的价值
	int King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int (*Board_MM)[8]);
	//王的杀棋布局还原
	void King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value,int (*Board_MM)[8]);
	//产生行棋之后的棋盘,nTypeRoute第n种走法，只负责产生当前一种局面
	void MakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8]);
	//还原行棋后的棋盘,nTypeRoute第n种走法，只负责还原当前一种局面
	void ResetMakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8]);
	int BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//统计空格1，x，y是我方坐标
	int AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//统计空格2，x，y是敌方坐标
public:
	int Board_MM[8][8];
	int Value_Buff[20][100];//10层//储存杀死的棋子的价值，用于还原棋盘用
	Location Loc_Fence[32];
};

