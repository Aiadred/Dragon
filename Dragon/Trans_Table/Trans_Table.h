#pragma once
#include <hash_map>
#include "Public.h"
#include "MakeMove.h"
using namespace std;
//关于置换表：			1.使用数据结构为hash—map，记录信息分别为1.当前棋盘的key值 2.层次 3.alpha，beta 4.Evalute
//						2.靠近根节点的值总是精确于靠近叶节点的值，可以直接调用map中的值避免重复搜索
//						3.不必要在每次搜索时清空hashmap，上次的搜索结果同样可以应用到下次
//							p.s.可以用多个hashmap记录不同层次的值，用相同的层次来查找
//						4.hash-map越大散列程度越好，但是会有饱和点
//						
//				pro		1.是否将子叶节点存入hash_map,子节点加入hashmap无疑会节省估值花费的时间
//						2.关于冲突问题，有待商榷
//
//
enum entry_type{exact,lower_bound,upper_bound};
typedef struct HASHITEM
{
	LONGLONG Checksum;
	entry_type	Data_type;
	short nPly;
	int Eval;
}HashItem;

class CTrans_Table
{
public:
	CTrans_Table(void);
	virtual ~CTrans_Table(void);
public:
	//根据棋盘计算key值
	void CaculateInitHashKey(int (*Board_Input)[8]);
	//根据走法产生新的key值
	void MakeMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn);
	//撤销走法产生新的key值
	void ResetMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn,int (*ValueBuff)[100]);
	//查询hash_map当前节点数据
	int SearchHashKey(int Alpha,int Beta,int nPly,int Turn);
	//将当前节点值压入Hash_map
	void PushNodeIntoHash(entry_type entry_type,int Evalute,short nPly,int Turn);
	//初始化随机数组创建Hash_map
	void SrandBulidHash();

	int ChessChoose(int nTypeChess);
public:
	UINT m_nHashKey_32[4][8][8];
	LONGLONG m_nHashKey_64[4][8][8];
	HashItem *m_pTT[2];
	UINT m_HashKey_32;
	LONGLONG m_HashKey_64;
};

