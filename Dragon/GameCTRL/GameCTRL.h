#pragma once
#include "FactoryObj.h"
#include "AlphaBeta.h"
#include "PVS.h"
#include "Reset.h"
class CGameCTRL
{
public:
	CGameCTRL(void);
	~CGameCTRL(void);
public:
	CSearchEngine *Moving;
	int iInArea(int x,int y,int x1,int y1,int x2,int y2);
	void MoveJump_L(int i,int j); //向左下间隔跳
	void MoveJump_R(int i,int j); //向右下间隔跳
	void Move1_L(int i,int j)	;//向左下跳
	void Move1_R(int i,int j)	;//向右下跳
	void iMove();
	void Move(int iX,int iY);
};

class CSelected
{
public:

	static int EngineChoose;
	static int DepthChoose;
};
