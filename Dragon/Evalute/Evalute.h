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
/////////////��Ԫ��ֵ����////////////
	int FlexibleCount();//�����
	int ValueCount();//��ֵ����
	int SafetyCount();//��ȫ̬����
	int AttackCount();//����̬����
	int DefenseCount();//����̬����
/////////////���Ƽ�ֵ����////////////
	int TriangleCount();
	int CentreCount();//������������
	int ColumnCount();//�ݶӼ������ݶ��������������
	int DefenseLineCount();
	int LMRPolyCount();
	int RowOccupy();
	int RepressCount();
};

