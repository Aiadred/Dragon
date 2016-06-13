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
		//单兵价
#define SOLDIER_VAL_0								650000									//普通炮灰的价值
#define SOLDIER_VAL_1								500000									//普通炮灰的价值
#define SOLDIER_VAL_2								480000									//普通炮灰的价值
#define SOLDIER_VAL_3								340000									//普通炮灰的价值
#define SOLDIER_VAL_4								340000								//普通炮灰的价值
#define SOLDIER_VAL_5								460000									//普通炮灰的价值
#define SOLDIER_VAL_6								700000									//普通炮灰的价值
		//王棋价值
#define KING_VAL									2000000									//王的价值
///////灵活性价值/////////////
#define FLEXIBLE_KING_MOVE_VAL						75									//王的灵活性的价值
#define FLEXIBLE_KING_KILL_VAL						125									//王的灵活性的价值(可以杀人)
#define FLEXIBLE_SOLDIER_MOVE_VAL					50								//兵的灵活性的价值
#define FLEXIBLE_SOLDIER_KILL_VAL					65									//兵的灵活性的价值(可以杀人)
///////安全态价值/////////////
#define SAFETY_KING_VAL								100									//王的安全态价值
#define SAFETY_SOLDIER_BOARD_VAL					75									//兵的安全态价值
#define SAFETY_SOLDIER_DEFENSE_VAL					65	
///////攻击态价值/////////////
#define ATTACK_KING_VAL								70
#define ATTACK_SOLDIER_VAL							50
///////防御态价值/////////////
#define DEFENCE_KING_VAL							40
#define DEFENCE_SOLDIER_VAL							60
		//前进方向为EMPTY或者为ENEMY都为进攻态,如果前进方向为边界则不为进攻态
#define ATTACK_VAL(nTypeToGo)						15*nTypeToGo						//处于进攻状态的棋子的价值
		//前进方向为MINE或者在最后一行为防御态
#define DEFENSE_VAL(nTypeToGo)						10*nTypeToGo						//处于防御状态的棋子的价值	
		//边界棋子或后方为我方棋子都为安全态
#define SAFE_VAL									20									//处于安全状态的棋子的价值


		//孤立的王灵活性极强
#define KING_ALONE_VAL(nTypeToGo)					20*nTypeToGo						//孤立的棋子的价值


//ABOUT POLYANALYZE

#define LMRPOLY_VAL									000
	
///////关于纵队/////////////		
	///////白棋/////////////
		///////右下方向/////////////
#define CWR_30_63			000
#define CWR_21_65			000
#define CWR_12_56			000
#define CWR_14_36			000
		///////左下方向/////////////
#define CWL_47_65			000
#define CWL_27_63			000
#define CWL_16_61			000
#define CWL_14_41			000
	///////白棋/////////////
		///////左下方向/////////////
#define CBL_12_30			000
#define	CBL_14_50			000
#define CBL_16_52			000
#define CBL_27_54			000
		///////右下方向/////////////
#define CBR_30_52			000
#define CBR_10_54			000
#define CBR_12_56			000
#define CBR_14_47			000

///////关于中心区域子力/////////////
#define CENTRE_WHITE_VALUE	000
#define CENTRE_BLACK_VALUE	000

///////关于正三角型/////////////
#define TRIANGLE_VALUE		000
///////关于单排占领型/////////////
#define ROWOCCUPY_VALUE		000
///////关于压制阵型/////////////
#define	REPRESS_VALUE		000
