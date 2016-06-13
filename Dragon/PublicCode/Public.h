#pragma once
#include "PublicDefine.h"

#include <list>
using namespace std;
//坐标结构体
typedef struct LOCATION
{
	int x;
	int y;
}Location;

//用于存储一个棋的所有信息
class CNodeChessInfo
{
public:
	CNodeChessInfo(void);
	//CNodeChessInfo(const CNodeChessInfo &Copy);
	virtual ~CNodeChessInfo(void);
public:
	Location Location_Current;//当前位置
	int nSide_;//势力范围
	int DirectionToMove[12];//最大12深度，每一深度对应一次走棋方向
	int Depth;//记录递归的层数，通过层数可以得出杀子的数量
	int nCount;//第n个棋子，遍历顺序为左上到右下
	int nSpace_Before[12];
	int nSpace_After[12];
	int nPly;
	CNodeChessInfo *pNext;
};


