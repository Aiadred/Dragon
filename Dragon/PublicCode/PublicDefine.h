#pragma once
//About Chess Info
#define EMPTY 0
#define	MINE   -1
#define ENEMY 1
#define FENCE 3
#define BLACK_SOLDIER 1
#define BLACK_KING	2
#define WHITE_SOLDIER -1
#define WHITE_KING -2
#define LEFT_UP 1
#define RIGHT_UP 2
#define LEFT_DOWN -2
#define RIGHT_DOWN -1





//About Evalute Info
//ABOUT ELEMENTAL
		//������
#define SOLDIER_VAL_0								650000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_1								500000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_2								480000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_3								340000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_4								340000								//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_5								460000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_6								700000									//��ͨ�ڻҵļ�ֵ
		//�����ֵ
#define KING_VAL									2000000									//���ļ�ֵ
///////����Լ�ֵ/////////////
#define FLEXIBLE_KING_MOVE_VAL						75									//��������Եļ�ֵ
#define FLEXIBLE_KING_KILL_VAL						125									//��������Եļ�ֵ(����ɱ��)
#define FLEXIBLE_SOLDIER_MOVE_VAL					50								//��������Եļ�ֵ
#define FLEXIBLE_SOLDIER_KILL_VAL					65									//��������Եļ�ֵ(����ɱ��)
///////��ȫ̬��ֵ/////////////
#define SAFETY_KING_VAL								100									//���İ�ȫ̬��ֵ
#define SAFETY_SOLDIER_BOARD_VAL					75									//���İ�ȫ̬��ֵ
#define SAFETY_SOLDIER_DEFENSE_VAL					65	
///////����̬��ֵ/////////////
#define ATTACK_KING_VAL								70
#define ATTACK_SOLDIER_VAL							50
///////����̬��ֵ/////////////
#define DEFENCE_KING_VAL							40
#define DEFENCE_SOLDIER_VAL							60
		//ǰ������ΪEMPTY����ΪENEMY��Ϊ����̬,���ǰ������Ϊ�߽���Ϊ����̬
#define ATTACK_VAL(nTypeToGo)						15*nTypeToGo						//���ڽ���״̬�����ӵļ�ֵ
		//ǰ������ΪMINE���������һ��Ϊ����̬
#define DEFENSE_VAL(nTypeToGo)						10*nTypeToGo						//���ڷ���״̬�����ӵļ�ֵ	
		//�߽����ӻ��Ϊ�ҷ����Ӷ�Ϊ��ȫ̬
#define SAFE_VAL									20									//���ڰ�ȫ״̬�����ӵļ�ֵ


		//������������Լ�ǿ
#define KING_ALONE_VAL(nTypeToGo)					20*nTypeToGo						//���������ӵļ�ֵ


//ABOUT POLYANALYZE

#define LMRPOLY_VAL									000
	
///////�����ݶ�/////////////		
	///////����/////////////
		///////���·���/////////////
#define CWR_30_63			000
#define CWR_21_65			000
#define CWR_12_56			000
#define CWR_14_36			000
		///////���·���/////////////
#define CWL_47_65			000
#define CWL_27_63			000
#define CWL_16_61			000
#define CWL_14_41			000
	///////����/////////////
		///////���·���/////////////
#define CBL_12_30			000
#define	CBL_14_50			000
#define CBL_16_52			000
#define CBL_27_54			000
		///////���·���/////////////
#define CBR_30_52			000
#define CBR_10_54			000
#define CBR_12_56			000
#define CBR_14_47			000

///////����������������/////////////
#define CENTRE_WHITE_VALUE	000
#define CENTRE_BLACK_VALUE	000

///////������������/////////////
#define TRIANGLE_VALUE		000
///////���ڵ���ռ����/////////////
#define ROWOCCUPY_VALUE		000
///////����ѹ������/////////////
#define	REPRESS_VALUE		000
