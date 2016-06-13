#pragma once
#include "Public.h"
#include "MoveGenerator.h"
class CEvalute
{
public:
	CEvalute(void);
	~CEvalute(void);
public:
	int Evalute(int (*Board)[8],int Turn);
	int Board_Eva[8][8];
	int Turn;
	int WhiteChessPoly[32];
	int BlackChessPoly[32];
	void Statistics(int *WhiteChessPoly,int *BlackChessPoly);
public:
/////////////单元价值计数////////////
	int FlexibleCount();//灵活性
	int ValueCount();//价值计数
	int SafetyCount();//安全态计数
	int AttackCount();//攻击态计数
	int DefenseCount();//防御态计数
/////////////局势价值计数////////////
	int TriangleCount();
	int CentreCount();//中心区域子力
	int ColumnCount();//纵队计数，纵队有利于整体进攻
	int DefenseLineCount();
	int LMRPolyCount();
	int RowOccupy();
	int RepressCount();
};

