#pragma once
#include "Public.h"
class CMakeMove
{
public:
	CMakeMove(int (*Board_Input)[8]);
	CMakeMove(void);
	~CMakeMove(void);
public:
	//�߶�����
	void Move_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//��ԭ�߶�����
	void Move_Re_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//ɱ�岼��,����ɱ������ļ�ֵ
	int Move_Kill(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8]);
	//��ԭɱ�岼��
	void Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value,int (*Board_MM)[8]);
	//�����߶�����
	void King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8]);
	//�����߶����ֻ�ԭ
	void King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8]);
	//����ɱ�岼�֣�����ɱ������ļ�ֵ
	int King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int (*Board_MM)[8]);
	//����ɱ�岼�ֻ�ԭ
	void King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value,int (*Board_MM)[8]);
	//��������֮�������,nTypeRoute��n���߷���ֻ���������ǰһ�־���
	void MakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8]);
	//��ԭ����������,nTypeRoute��n���߷���ֻ����ԭ��ǰһ�־���
	void ResetMakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8]);
	int BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//ͳ�ƿո�1��x��y���ҷ�����
	int AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//ͳ�ƿո�2��x��y�ǵз�����
public:
	int Board_MM[8][8];
	int Value_Buff[20][100];//10��//����ɱ�������ӵļ�ֵ�����ڻ�ԭ������
	Location Loc_Fence[32];
};

