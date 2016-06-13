#pragma once
#include "PublicDefine.h"

#include <list>
using namespace std;
//����ṹ��
typedef struct LOCATION
{
	int x;
	int y;
}Location;

//���ڴ洢һ�����������Ϣ
class CNodeChessInfo
{
public:
	CNodeChessInfo(void);
	//CNodeChessInfo(const CNodeChessInfo &Copy);
	virtual ~CNodeChessInfo(void);
public:
	Location Location_Current;//��ǰλ��
	int nSide_;//������Χ
	int DirectionToMove[12];//���12��ȣ�ÿһ��ȶ�Ӧһ�����巽��
	int Depth;//��¼�ݹ�Ĳ�����ͨ���������Եó�ɱ�ӵ�����
	int nCount;//��n�����ӣ�����˳��Ϊ���ϵ�����
	int nSpace_Before[12];
	int nSpace_After[12];
	int nPly;
	CNodeChessInfo *pNext;
};


