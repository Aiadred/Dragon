#include "stdafx.h"
#include "Evalute.h"
#include "ShowInfo.h"

CEvalute::CEvalute(void)
{
	memset(Board_Eva,0,8*8*4);
	
}


CEvalute::~CEvalute(void)
{

}
int CEvalute::Evalute(int (*Board)[8],int Turn)
{
	int Total_Value=0;
	int Element_Value=0;
	int Poly_Value=0;
	this->Turn=Turn;
	memset(WhiteChessPoly,0,32*4);
	memset(BlackChessPoly,0,32*4);
	memcpy_s(Board_Eva,8*8*4,Board,8*8*4);
	Statistics(WhiteChessPoly,BlackChessPoly);
	Element_Value=ValueCount()+SafetyCount()+AttackCount()+DefenseCount();
	Poly_Value=LMRPolyCount()+ColumnCount()+CentreCount();
	Total_Value=Element_Value+Poly_Value;
	CShowInfo::nCount_Eval++;

	return Total_Value;
}
//
void CEvalute::Statistics(int *WhiteChessPoly,int *BlackChessPoly)
{
	//切记：白棋黑棋的数组都是从上向下开始计算的
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i%2==0)//偶数行
			{
				if(Board_Eva[i][j]==WHITE_SOLDIER)
					WhiteChessPoly[(j+1)/2+i*4-1]=WHITE_SOLDIER;
				if(Board_Eva[i][j]==BLACK_SOLDIER)
					BlackChessPoly[(j+1)/2+i*4-1]=BLACK_SOLDIER;
			}
			if(i%2!=0)
			{
				if(Board_Eva[i][j]==WHITE_SOLDIER)
					WhiteChessPoly[(j+2)/2+i*4-1]=WHITE_SOLDIER;
				if(Board_Eva[i][j]==BLACK_SOLDIER)
					BlackChessPoly[(j+2)/2+i*4-1]=BLACK_SOLDIER;
			}
		}
	}

}
//价值计数
int CEvalute::ValueCount()
{
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	int NumBlackSoldierLine[8];
	int NumBlackKingLine[8];
	int NumWhiteSoldierLine[8];
	int NumWhiteKingLine[8];
	int Value=0;
	memset(NumBlackSoldierLine,0,8*4);
	memset(NumBlackKingLine,0,8*4);
	memset(NumWhiteSoldierLine,0,8*4);
	memset(NumWhiteKingLine,0,8*4);
	//棋盘计数
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(Board_Eva[i][j]==WHITE_SOLDIER)
				++NumWhiteSoldierLine[i];
			else if(Board_Eva[i][j]==WHITE_KING)
				++NumWhiteKingLine[i];
			if(Board_Eva[i][j]==BLACK_SOLDIER)
				++NumBlackSoldierLine[i];
			else if(Board_Eva[i][j]==BLACK_KING)
				++NumBlackKingLine[i];
		}

	}
	//价值估算
	for(int i=0;i<8;i++)
	{
		switch(i)
		{
		case 0:
			TotalWhiteValue+=NumWhiteSoldierLine[0]*SOLDIER_VAL_0+NumWhiteKingLine[0]*KING_VAL;
			TotalBlackValue+=NumBlackKingLine[0]*KING_VAL;
			break;
		case 1:
			TotalWhiteValue+=NumWhiteSoldierLine[1]*SOLDIER_VAL_1+NumWhiteKingLine[1]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[1]*SOLDIER_VAL_6+NumBlackKingLine[1]*KING_VAL;
			break;
		case 2:
			TotalWhiteValue+=NumWhiteSoldierLine[2]*SOLDIER_VAL_2+NumWhiteKingLine[2]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[2]*SOLDIER_VAL_5+NumBlackKingLine[2]*KING_VAL;
			break;
		case 3:
			TotalWhiteValue+=NumWhiteSoldierLine[3]*SOLDIER_VAL_3+NumWhiteKingLine[3]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[3]*SOLDIER_VAL_4+NumBlackKingLine[3]*KING_VAL;
			break;
		case 4:
			TotalWhiteValue+=NumWhiteSoldierLine[4]*SOLDIER_VAL_4+NumWhiteKingLine[4]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[4]*SOLDIER_VAL_3+NumBlackKingLine[4]*KING_VAL;
			break;
		case 5:
			TotalWhiteValue+=NumWhiteSoldierLine[5]*SOLDIER_VAL_5+NumWhiteKingLine[5]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[5]*SOLDIER_VAL_2+NumBlackKingLine[5]*KING_VAL;
			break;
		case 6:
			TotalWhiteValue+=NumWhiteSoldierLine[6]*SOLDIER_VAL_6+NumWhiteKingLine[6]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[6]*SOLDIER_VAL_1+NumBlackKingLine[6]*KING_VAL;
			break;
		case 7:
			TotalWhiteValue+=NumWhiteKingLine[7]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[7]*SOLDIER_VAL_0+NumBlackKingLine[7]*KING_VAL;
			break;
		}
	}
	if(this->Turn==ENEMY)
		return Value=TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return Value=TotalWhiteValue-TotalBlackValue;
}
//安全态计数
int CEvalute::SafetyCount()
{
	int TotalBlackValue=0;
	int TotalWhiteValue=0;

	int NumDefenseBlack=0;
	int NumBoardBlack=0;
	int NumDefenseWhite=0;
	int NumBoardWhite=0;

	int NumBlackKing=0;
	int NumWhiteKing=0;
	/////边界安全态//////
	for(int j=0;j<8;j++)
	{
		if(Board_Eva[0][j]==WHITE_SOLDIER)
			++NumBoardWhite;
		if(Board_Eva[0][j]==WHITE_KING)
			++NumWhiteKing;
		if(Board_Eva[7][j]==WHITE_KING)
			++NumWhiteKing;

		if(Board_Eva[7][j]==BLACK_SOLDIER)
			++NumBoardBlack;
		if(Board_Eva[7][j]==BLACK_KING)
			++NumBlackKing;
		if(Board_Eva[0][j]==BLACK_KING)
			++NumBlackKing;
	}
	for(int i=0;i<8;i++)
	{
		if(Board_Eva[i][0]==WHITE_SOLDIER)
			++NumBoardWhite;
		else if((Board_Eva[i][0]==WHITE_KING)&&(i!=7))
			++NumWhiteKing;
		if(Board_Eva[i][7]==WHITE_SOLDIER&&(i!=0))
			++NumBoardWhite;
		else if((Board_Eva[i][7]==WHITE_KING)&&(i!=0))
			++NumWhiteKing;

		if(Board_Eva[i][7]==BLACK_SOLDIER)
			++NumBoardBlack;
		else if(Board_Eva[i][7]==BLACK_KING&&(i!=0))
			++NumBlackKing;
		if(Board_Eva[i][0]==BLACK_SOLDIER&&(i!=7))
			++NumBoardBlack;
		else if(Board_Eva[i][0]==BLACK_KING&&(i!=7))
			++NumBlackKing;
	}
	/////被防御安全态//////
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(((0<i&&i<7)&&(0<j&&j<7)))
			{
				if(Board_Eva[i][j]==WHITE_SOLDIER)
				{
					if(Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i+1][j-1]==WHITE_SOLDIER||Board_Eva[i+1][j-1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i+1][j+1]==WHITE_SOLDIER||Board_Eva[i+1][j+1]==WHITE_KING)
						++NumDefenseWhite;
				}
				if(Board_Eva[i][j]==BLACK_SOLDIER)
				{
					if(Board_Eva[i-1][j-1]==BLACK_SOLDIER||Board_Eva[i-1][j-1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i-1][j+1]==BLACK_SOLDIER||Board_Eva[i-1][j+1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING)
						++NumDefenseBlack;
				}		
			}
		}

	}
	TotalWhiteValue=NumWhiteKing*SAFETY_KING_VAL+NumBoardWhite*SAFETY_SOLDIER_BOARD_VAL+NumDefenseWhite*SAFETY_SOLDIER_DEFENSE_VAL;		
	TotalBlackValue=NumBlackKing*SAFETY_KING_VAL+NumBoardBlack*SAFETY_SOLDIER_BOARD_VAL+NumDefenseBlack*SAFETY_SOLDIER_DEFENSE_VAL;	
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
//攻击态计数
int CEvalute::AttackCount()
{
	//攻击态的标准：1.某方棋子的前进方向为EMPTY
	//				2.某方棋子的前进方向为为ENEMY(此情况不适用于ENEMY在边界,且我方后方必须有防御)
	//				3.后方棋子为ENEMY
	int NumBlack=0;
	int NumWhite=0;
	int NumBlackKing=0;
	int NumWhiteKing=0;
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(Board_Eva[i][j]==WHITE_SOLDIER)
			{
				//////白棋视角//////
				if((i!=7&&j!=0)&&Board_Eva[i+1][j-1]==EMPTY)
					++NumWhite;
				if(((i<6)&&(1<j)&&(j<6))
					&&((Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING))
					&&((Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_SOLDIER)))
				{
					++NumWhite;
				}
				if((i!=7&&j!=7)&&Board_Eva[i+1][j+1]==EMPTY)
					++NumWhite;
				if((i<6)&&((j>1)&&(j<6))
					&&((Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING))
					&&((Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_SOLDIER)))
				{
					++NumWhite;
				}
			}
			if(Board_Eva[i][j]==WHITE_KING)
			{
				Location Local_Current;
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=7&&Local_Current.y!=7)&&(Board_Eva[++Local_Current.x][++Local_Current.y]!=WHITE_SOLDIER||Board_Eva[++Local_Current.x][++Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while(Local_Current.x!=7&&Local_Current.y!=0&&(Board_Eva[++Local_Current.x][--Local_Current.y]!=WHITE_SOLDIER||Board_Eva[++Local_Current.x][--Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=7)&&(Board_Eva[--Local_Current.x][++Local_Current.y]!=WHITE_SOLDIER||Board_Eva[--Local_Current.x][++Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;						
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=0)&&(Board_Eva[--Local_Current.x][--Local_Current.y]!=WHITE_SOLDIER||Board_Eva[--Local_Current.x][--Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;				
				}
			}			
			//////黑棋视角//////
			if(Board_Eva[i][j]==BLACK_SOLDIER)
			{
				//////黑棋视角//////
				if((i!=0&&j!=0)&&Board_Eva[i-1][j-1]==EMPTY)
					++NumBlack;
				if(((i>1)&&(1<j)&&(j<6))
					&&((Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_KING))
					&&((Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING)))
				{
					++NumBlack;
				}
				if((i!=0&&j!=7)&&Board_Eva[i-1][j+1]==EMPTY)
					++NumBlack;
				if((i>1)&&((j>1)&&(j<6))
					&&((Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_KING))
					&&((Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING)))
				{
					++NumBlack;
				}
			}
			if(Board_Eva[i][j]==BLACK_KING)
			{
				Location Local_Current;
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=7&&Local_Current.y!=7)&&(Board_Eva[++Local_Current.x][++Local_Current.y]!=BLACK_SOLDIER||Board_Eva[++Local_Current.x][++Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while(Local_Current.x!=7&&Local_Current.y!=0&&(Board_Eva[++Local_Current.x][--Local_Current.y]!=BLACK_SOLDIER||Board_Eva[++Local_Current.x][--Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=7)&&(Board_Eva[--Local_Current.x][++Local_Current.y]!=BLACK_SOLDIER||Board_Eva[--Local_Current.x][++Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;						
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=0)&&(Board_Eva[--Local_Current.x][--Local_Current.y]!=BLACK_SOLDIER||Board_Eva[--Local_Current.x][--Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;				
				}

			}
			
		}
	}
	TotalWhiteValue=NumWhiteKing*ATTACK_KING_VAL+NumWhite*ATTACK_SOLDIER_VAL;
	TotalBlackValue=NumBlackKing*ATTACK_KING_VAL+NumBlack*ATTACK_SOLDIER_VAL;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
//防御态计数
int CEvalute::DefenseCount()
{
	//防御态基准： 当我方棋子前进方向为我方棋子时，此棋子为防御态，当然注意棋子范围
	int NumBlack=0;
	int NumWhite=0;
	int NumBlackKing=0;
	int NumWhiteKing=0;
	int TotalBlackValue=0;
	int TotalWhiteValue=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if((i<7)&&(j>0)&&(j<7)&&(Board_Eva[i][j]==WHITE_SOLDIER||Board_Eva[i][j]==WHITE_KING))
			{
				if(Board_Eva[i+1][j-1]==WHITE_SOLDIER||Board_Eva[i+1][j-1]==WHITE_KING)
					NumWhite++;
				if(Board_Eva[i+1][j+1]==WHITE_SOLDIER||Board_Eva[i+1][j+1]==WHITE_KING)
					NumWhite++;
			}

			if((i>0)&&(j>0)&&(j<7)&&Board_Eva[i][j]==BLACK_SOLDIER||Board_Eva[i][j]==BLACK_KING)
			{
				if(Board_Eva[i-1][j-1]==BLACK_SOLDIER||Board_Eva[i-1][j-1]==BLACK_KING)
					NumBlack++;
				if(Board_Eva[i-1][j+1]==BLACK_SOLDIER||Board_Eva[i-1][j+1]==BLACK_KING)
					NumBlack++;
			}
		}

	} 
	TotalBlackValue=NumBlackKing*DEFENCE_KING_VAL+NumBlack*DEFENCE_SOLDIER_VAL;
	TotalWhiteValue=NumWhiteKing*DEFENCE_KING_VAL+NumWhite*DEFENCE_SOLDIER_VAL;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
////*****************局势分析*****************////
int CEvalute::LMRPolyCount()
{
	//思路：计算整体某方势力的棋子分布，原则为整体前进，禁止出现某一侧空子情况
	int TotalBlackValue=0;
	int TotalWhiteValue=0;
	int TotalBlackCount=0;
	int TotalWhiteCount=0;
	int LBCount=0,MBCount=0,RBCount=0;
	int LWCount=0,MWCount=0,RWCount=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(j<=2)
			{
				if(LBCount<3&&(Board_Eva[i][j]==BLACK_SOLDIER||Board_Eva[i][j]==BLACK_KING))
				{
					LBCount++;
				}
				if(LWCount<2&&(Board_Eva[i][j]==WHITE_SOLDIER||Board_Eva[i][j]==WHITE_KING))
				{
					LWCount++;
				}
			}
			if(j>=3&&j<=4)
			{
				if(MBCount<2&&(Board_Eva[i][j]==BLACK_SOLDIER||Board_Eva[i][j]==BLACK_KING))
				{
					MBCount++;
				}
				if(MWCount<2&&(Board_Eva[i][j]==WHITE_SOLDIER||Board_Eva[i][j]==WHITE_KING))
				{
					MWCount++;
				}

			}
			if(j>=5)
			{
				if(RBCount<2&&(Board_Eva[i][j]==BLACK_SOLDIER||Board_Eva[i][j]==BLACK_KING))
				{
					MBCount++;
				}
				if(MWCount<3&&(Board_Eva[i][j]==WHITE_SOLDIER||Board_Eva[i][j]==WHITE_KING))
				{
					RWCount++;
				}
			}

		}
	}
	TotalBlackCount=LBCount+MBCount+RBCount;
	TotalWhiteCount=LWCount+MWCount+RWCount;
	TotalBlackValue=TotalBlackCount*LMRPOLY_VAL;
	TotalWhiteValue=TotalWhiteCount*LMRPOLY_VAL;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;

}
//纵队有利于整体进攻	整个棋盘从上(相对)向下遍历，根据队头找纵队，纵队个数其次，重要的是纵队的规模
//									
int CEvalute::ColumnCount()
{
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	int Board_Temp[8][8];
	
	memcpy_s(Board_Temp,8*8*4,Board_Eva,8*8*4);
	//About WhiteSoldier			Only the rough guess  
		//CWR_30_63
	int nCount=0;
	if((Board_Temp[3][6]==WHITE_SOLDIER&&Board_Temp[2][5]==WHITE_SOLDIER&&Board_Temp[1][4]==WHITE_SOLDIER)
		||(Board_Temp[2][5]==WHITE_SOLDIER&&Board_Temp[1][4]==WHITE_SOLDIER&&Board_Temp[0][3]==WHITE_SOLDIER))
		TotalWhiteValue+=CWR_30_63;
		//CWR_21_54
	if((Board_Temp[2][1]==WHITE_SOLDIER&&Board_Temp[3][2]==WHITE_SOLDIER&&Board_Temp[4][3]==WHITE_SOLDIER)
		||(Board_Temp[3][2]==WHITE_SOLDIER&&Board_Temp[4][3]==WHITE_SOLDIER&&Board_Temp[5][4]==WHITE_SOLDIER)
		||(Board_Temp[4][3]==WHITE_SOLDIER&&Board_Temp[5][4]==WHITE_SOLDIER&&Board_Temp[6][5]==WHITE_SOLDIER))
		TotalWhiteValue+=CWR_21_65;
		//CWR_12_56
	if((Board_Temp[1][2]==WHITE_SOLDIER&&Board_Temp[2][3]==WHITE_SOLDIER&&Board_Temp[3][4]==WHITE_SOLDIER)
		||(Board_Temp[2][3]==WHITE_SOLDIER&&Board_Temp[3][4]==WHITE_SOLDIER&&Board_Temp[4][5]==WHITE_SOLDIER)
		||(Board_Temp[3][4]==WHITE_SOLDIER&&Board_Temp[4][5]==WHITE_SOLDIER&&Board_Temp[5][6]==WHITE_SOLDIER))
		TotalWhiteValue+=CWR_12_56;
		//CWR_14_36
	if(Board_Temp[1][4]==WHITE_SOLDIER&&Board_Temp[2][5]==WHITE_SOLDIER&&Board_Temp[3][6]==WHITE_SOLDIER)	
		TotalWhiteValue+=CWR_14_36;
		//CWL_47_65
	if(Board_Temp[4][7]==WHITE_SOLDIER&&Board_Temp[5][6]==WHITE_SOLDIER&&Board_Temp[6][6]==WHITE_SOLDIER)	
		TotalWhiteValue+=CWL_47_65;
		//CWL_27_63
	if((Board_Temp[2][7]==WHITE_SOLDIER&&Board_Temp[3][6]==WHITE_SOLDIER&&Board_Temp[4][5]==WHITE_SOLDIER)
		||(Board_Temp[3][6]==WHITE_SOLDIER&&Board_Temp[4][5]==WHITE_SOLDIER&&Board_Temp[5][4]==WHITE_SOLDIER)
		||(Board_Temp[4][5]==WHITE_SOLDIER&&Board_Temp[5][4]==WHITE_SOLDIER&&Board_Temp[6][3]==WHITE_SOLDIER))
		TotalWhiteValue+=CWL_27_63;
		//CWL_16_61
	if((Board_Temp[1][6]==WHITE_SOLDIER&&Board_Temp[2][5]==WHITE_SOLDIER&&Board_Temp[3][4]==WHITE_SOLDIER)
		||(Board_Temp[2][5]==WHITE_SOLDIER&&Board_Temp[3][4]==WHITE_SOLDIER&&Board_Temp[4][3]==WHITE_SOLDIER)
		||(Board_Temp[3][4]==WHITE_SOLDIER&&Board_Temp[4][3]==WHITE_SOLDIER&&Board_Temp[5][2]==WHITE_SOLDIER)
		||(Board_Temp[4][3]==WHITE_SOLDIER&&Board_Temp[5][2]==WHITE_SOLDIER&&Board_Temp[6][1]==WHITE_SOLDIER))
		TotalWhiteValue+=CWL_16_61;
		//CWL_14_41
	if((Board_Temp[1][4]==WHITE_SOLDIER&&Board_Temp[2][3]==WHITE_SOLDIER&&Board_Temp[3][2]==WHITE_SOLDIER)
		||(Board_Temp[2][3]==WHITE_SOLDIER&&Board_Temp[3][2]==WHITE_SOLDIER&&Board_Temp[4][1]==WHITE_SOLDIER))
		TotalWhiteValue+=CWL_14_41;
	//About BlackSoldier			Only the rough guess
		//CBL_12_30
	if(Board_Temp[1][2]==BLACK_SOLDIER&&Board_Temp[2][1]==BLACK_SOLDIER&&Board_Temp[3][0]==BLACK_SOLDIER)
		TotalBlackValue+=CBL_12_30;
		//CBL_14_50
	if((Board_Temp[1][4]==BLACK_SOLDIER&&Board_Temp[2][3]==BLACK_SOLDIER&&Board_Temp[3][2]==BLACK_SOLDIER)
		||(Board_Temp[2][3]==BLACK_SOLDIER&&Board_Temp[3][2]==BLACK_SOLDIER&&Board_Temp[4][1]==BLACK_SOLDIER)
		||(Board_Temp[3][2]==BLACK_SOLDIER&&Board_Temp[4][1]==BLACK_SOLDIER&&Board_Temp[5][0]==BLACK_SOLDIER))
		TotalBlackValue+=CBL_14_50;
		//CBL_16_52
	if((Board_Temp[1][6]==BLACK_SOLDIER&&Board_Temp[2][5]==BLACK_SOLDIER&&Board_Temp[3][4]==BLACK_SOLDIER)
		||(Board_Temp[2][5]==BLACK_SOLDIER&&Board_Temp[3][4]==BLACK_SOLDIER&&Board_Temp[4][3]==BLACK_SOLDIER)
		||(Board_Temp[3][4]==BLACK_SOLDIER&&Board_Temp[4][3]==BLACK_SOLDIER&&Board_Temp[5][2]==BLACK_SOLDIER))
		TotalBlackValue+=CBL_16_52;
		//CBL_27_54
	if((Board_Temp[2][7]==BLACK_SOLDIER&&Board_Temp[3][6]==BLACK_SOLDIER&&Board_Temp[4][5]==BLACK_SOLDIER)
		||(Board_Temp[3][6]==BLACK_SOLDIER&&Board_Temp[4][5]==BLACK_SOLDIER&&Board_Temp[5][4]==BLACK_SOLDIER))
		TotalBlackValue+=CBL_27_54;
		//CBR_30_52
	if(Board_Temp[3][0]==BLACK_SOLDIER&&Board_Temp[4][1]==BLACK_SOLDIER&&Board_Temp[5][2]==BLACK_SOLDIER)
		TotalBlackValue+=CBR_30_52;
		//CBR_10_54
	if((Board_Temp[1][0]==BLACK_SOLDIER&&Board_Temp[2][1]==BLACK_SOLDIER&&Board_Temp[3][2]==BLACK_SOLDIER)
		||(Board_Temp[2][1]==BLACK_SOLDIER&&Board_Temp[3][2]==BLACK_SOLDIER&&Board_Temp[4][3]==BLACK_SOLDIER)
		||(Board_Temp[3][2]==BLACK_SOLDIER&&Board_Temp[4][3]==BLACK_SOLDIER&&Board_Temp[5][4]==BLACK_SOLDIER))
		TotalBlackValue+=CBR_10_54;
		//CBR_12_56
	if((Board_Temp[1][2]==BLACK_SOLDIER&&Board_Temp[2][3]==BLACK_SOLDIER&&Board_Temp[3][4]==BLACK_SOLDIER)
		||(Board_Temp[2][3]==BLACK_SOLDIER&&Board_Temp[3][4]==BLACK_SOLDIER&&Board_Temp[4][5]==BLACK_SOLDIER)
		||(Board_Temp[3][4]==BLACK_SOLDIER&&Board_Temp[4][5]==BLACK_SOLDIER&&Board_Temp[5][6]==BLACK_SOLDIER))
		TotalBlackValue+=CBR_12_56;
		//CBR_14_47
	if((Board_Temp[1][4]==BLACK_SOLDIER&&Board_Temp[2][5]==BLACK_SOLDIER&&Board_Temp[3][6]==BLACK_SOLDIER)
		||(Board_Temp[2][5]==BLACK_SOLDIER&&Board_Temp[3][6]==BLACK_SOLDIER&&Board_Temp[4][7]==BLACK_SOLDIER))
		TotalBlackValue+=CBR_14_47;
	
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
int CEvalute::CentreCount()
{
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	int TotalWhiteCount=0;
	int TotalBlackCount=0;
	for(int i=2,k=3,temp=k,Flag=1;i<=5;i++,temp--,k=temp)
	{
		int nCount=0;		
		while(true)
		{
			nCount++;
			if(k<8&&(Board_Eva[i][k]==WHITE_SOLDIER||Board_Eva[i][k]==WHITE_KING))
			{
				TotalWhiteCount++;
			
			}
			if(k<8&&(Board_Eva[i][k]==BLACK_SOLDIER||Board_Eva[i][k]==BLACK_KING))
			{
				TotalBlackCount++;
			}
			k+=2;
			if(i>3&&nCount==i)
			{		
				nCount=i-Flag;
				Flag++;			
				break;
			}
			else if(nCount==i)
			{
				k=temp;
				break;
			}
		}		
	}
	TotalWhiteValue=TotalWhiteCount*CENTRE_WHITE_VALUE;
	TotalBlackValue=TotalBlackCount*CENTRE_BLACK_VALUE;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}

int CEvalute::TriangleCount()
{
	int TotalBlackValue=0;
	int TotalWhiteValue=0;
	int TotalWhiteCount=0;
	int TotalBlackCount=0;
	for(int i=1;i<7;i++)								//统计三角形数量只有在扣除最外界才有意义
	{
		for(int j=1;j<7;j++)
		{
			if(Board_Eva[i][j]==WHITE_SOLDIER)			//从白棋方看起
			{
				if(Board_Eva[i-1][j-1]==WHITE_SOLDIER&&Board_Eva[i-1][j+1]==WHITE_SOLDIER)	
					TotalWhiteCount++;
			}
			if(Board_Eva[i][j]==BLACK_SOLDIER)
			{
				if(Board_Eva[i+1][j-1]==BLACK_SOLDIER&&Board_Eva[i+1][j+1]==BLACK_SOLDIER)
					TotalBlackCount++;
			}
		}
	}
	TotalWhiteValue=TotalWhiteCount*TRIANGLE_VALUE;
	TotalBlackValue=TotalBlackCount*TRIANGLE_VALUE;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
int CEvalute::RowOccupy()			//待定
{
	int TotalWhiteCount=0;
	int TotalBlackCount=0;
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	for(int i=1;i<7;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==2||i==4||i==6)
			{
				if(Board_Eva[i][1]==BLACK_SOLDIER&&Board_Eva[i][3]==WHITE_SOLDIER&&Board_Eva[i][5]==BLACK_SOLDIER)
				{
					TotalBlackCount++;
				}
				if(Board_Eva[i][3]==BLACK_SOLDIER&&Board_Eva[i][5]==WHITE_SOLDIER&&Board_Eva[i][7]==BLACK_SOLDIER)
				{
					TotalBlackCount++;
				}
				if(Board_Eva[i][1]==WHITE_SOLDIER&&Board_Eva[i][3]==BLACK_SOLDIER&&Board_Eva[i][5]==WHITE_SOLDIER)
				{
					TotalWhiteCount++;
				}
				if(Board_Eva[i][3]==WHITE_SOLDIER&&Board_Eva[i][5]==BLACK_SOLDIER&&Board_Eva[i][7]==WHITE_SOLDIER)
				{
					TotalWhiteCount++;
				}
			}
			if(i==3||i==5)
			{
				if(Board_Eva[i][0]==BLACK_SOLDIER&&Board_Eva[i][2]==WHITE_SOLDIER&&Board_Eva[i][4]==BLACK_SOLDIER)
				{
						TotalBlackCount++;
				}
				if(Board_Eva[i][2]==BLACK_SOLDIER&&Board_Eva[i][4]==WHITE_SOLDIER&&Board_Eva[i][6]==BLACK_SOLDIER)
				{
						TotalBlackCount++;
				}
				if(Board_Eva[i][0]==WHITE_SOLDIER&&Board_Eva[i][2]==BLACK_SOLDIER&&Board_Eva[i][4]==WHITE_SOLDIER)
				{
						TotalWhiteCount++;
				}
				if(Board_Eva[i][2]==WHITE_SOLDIER&&Board_Eva[i][4]==BLACK_SOLDIER&&Board_Eva[i][6]==WHITE_SOLDIER)
				{
						TotalWhiteCount++;
				}
			
			}
		}
	}
	TotalWhiteValue=TotalWhiteCount*TRIANGLE_VALUE;
	TotalBlackValue=TotalBlackCount*TRIANGLE_VALUE;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
int CEvalute::RepressCount()
{
	int TotalWhiteCount=0;
	int TotalBlackCount=0;
	int TotalWhiteValue=0;
	int TotalBlackValue=0;

	for(int i=0;i<32;i++)
	{
		if(WhiteChessPoly[i]==WHITE_SOLDIER)
		{
			switch(i)
			{
			case 0:				//右侧下方压制	偶数层	0
				if(Board_Eva[1][2]==EMPTY&&
					WhiteChessPoly[i+8]!=WHITE_SOLDIER&&
					BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			case 1:				//左侧下方压制	偶数层	0
			case 2:					
				if((WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 3:				//左侧下方压制	偶数层	0
				if(Board_Eva[1][6]==EMPTY&&
					WhiteChessPoly[i+7]!=WHITE_SOLDIER&&
					BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			case 4:				//右侧下方压制	奇数层	1
				if(Board_Eva[2][1]==EMPTY&&
					WhiteChessPoly[i+8]!=WHITE_SOLDIER&&
					BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			case 5:				//左侧下方压制	奇数层	1
			case 6:
				if((WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 7:				//左侧下方压制	奇数层	1
				if(Board_Eva[2][5]==EMPTY&&
					WhiteChessPoly[i+7]!=WHITE_SOLDIER&&
					BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			case 8:				//右侧上下压制	偶数层	2
				if((WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 16:
				if((WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER&&(BlackChessPoly[i-7]+BlackChessPoly[i-8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 9:				//四恻到处压制	偶数层	2
			case 10:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER
					||(WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 17:
			case 18:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-9]==BLACK_SOLDIER)
					||(WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER&&(BlackChessPoly[i-7]+BlackChessPoly[i-8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 11:			//左侧上下压制	偶数层	2
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+8]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 19:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-9]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+8]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 12:			//右侧上下压制	奇数层	3
			case 20:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-7]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 13:			//四恻到处压制	奇数层	3
			case 14:		
			case 21:
			case 22:
				if((WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-9]==BLACK_SOLDIER)
					||(WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER&&(BlackChessPoly[i-7]+BlackChessPoly[i-8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+7]+BlackChessPoly[i+8]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&WhiteChessPoly[i+9]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+9]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 15:			//左侧上下压制	奇数层	3
			case 23:
				if((WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-9]==BLACK_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&WhiteChessPoly[i+7]!=WHITE_SOLDIER&&(BlackChessPoly[i+8]+BlackChessPoly[i+7]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 24:			//右侧下方压制	偶数层	7
				if(Board_Eva[5][2]==EMPTY&&
					WhiteChessPoly[i-7]!=WHITE_SOLDIER&&
					BlackChessPoly[i-7]+BlackChessPoly[i-8]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			case 25:			//左右下方压制	偶数层	7
			case 26:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&WhiteChessPoly[i-9]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-9]==BLACK_SOLDIER)
					||(WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&WhiteChessPoly[i-7]!=WHITE_SOLDIER&&(BlackChessPoly[i-8]+BlackChessPoly[i-7]==BLACK_SOLDIER))
					TotalWhiteCount++;
				break;
			case 27:
				if(Board_Eva[5][6]==EMPTY&&
					WhiteChessPoly[i-9]!=WHITE_SOLDIER&&
					BlackChessPoly[i-9]+BlackChessPoly[i-8]==BLACK_SOLDIER)
					TotalWhiteCount++;
				break;
			}
		}
		if(BlackChessPoly[i]==BLACK_SOLDIER)
		{
			switch(i)
			{
			case 4:				//右侧下方压制	奇数层 1
				if(Board_Eva[2][1]==EMPTY&&
					BlackChessPoly[i+9]!=BLACK_SOLDIER&&
					WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			case 5:				//左侧下方压制	奇数层 1
			case 6:					
				if((WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER&&(WhiteChessPoly[i+7]+WhiteChessPoly[i+8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 7:				//左侧下方压制	奇数层 1
				if(Board_Eva[1][6]==EMPTY&&
					BlackChessPoly[i+7]!=BLACK_SOLDIER&&
					WhiteChessPoly[i+7]+WhiteChessPoly[i+8]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			case 8:				//右侧上下压制	偶数层 2
			case 16:
				if((WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 9:				//四恻到处压制	偶数层 2
			case 10:
			case 17:
			case 18:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER&&(WhiteChessPoly[i+7]+WhiteChessPoly[i+8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+5]==EMPTY&&BlackChessPoly[i+5]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 11:			//左侧上下压制	偶数层 2
			case 19:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER&&(WhiteChessPoly[i+7]+WhiteChessPoly[i+8]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 12:				//右侧上下压制	奇数层	3
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 20:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER)
					TotalBlackCount++;
				break;
			case 13:				//四恻上下压制	奇数层	3		
			case 14:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER&&(WhiteChessPoly[i+7]+WhiteChessPoly[i+8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+9]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 21:
			case 22:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER
					||(WhiteChessPoly[i+4]==EMPTY&&BlackChessPoly[i+4]==EMPTY)&&BlackChessPoly[i+9]!=BLACK_SOLDIER)
					TotalBlackCount++;
				break;
			case 15:				//左侧到处压制	奇数层	3
				if((WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER&&(WhiteChessPoly[i+8]+WhiteChessPoly[i+7]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 23:
				if((WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i+3]==EMPTY&&BlackChessPoly[i+3]==EMPTY)&&BlackChessPoly[i+7]!=BLACK_SOLDIER)
					TotalBlackCount++;
				break;
			case 24:
				if(Board_Eva[5][2]==EMPTY&&
					BlackChessPoly[i-7]!=BLACK_SOLDIER&&
					WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			case 25:
			case 26:
				if((WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					||(WhiteChessPoly[i-3]==EMPTY&&BlackChessPoly[i-3]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 27:			//左侧上下压制	偶数层	2
				if(Board_Eva[5][6]==EMPTY&&
					BlackChessPoly[i-9]!=BLACK_SOLDIER&&
					WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			case 28:
				if(Board_Eva[6][1]==EMPTY&&
					BlackChessPoly[i-7]!=BLACK_SOLDIER&&
					WhiteChessPoly[i-7]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			case 29:			//右侧上下压制	奇数层	3
			case 30:
				if((WhiteChessPoly[i-5]==EMPTY&&BlackChessPoly[i-5]==EMPTY)&&BlackChessPoly[i-9]!=BLACK_SOLDIER&&(WhiteChessPoly[i-8]+WhiteChessPoly[i-9]==WHITE_SOLDIER)
					||(WhiteChessPoly[i-4]==EMPTY&&BlackChessPoly[i-4]==EMPTY)&&BlackChessPoly[i-7]!=BLACK_SOLDIER&&(WhiteChessPoly[i-8]+WhiteChessPoly[i-7]==WHITE_SOLDIER))
					TotalBlackCount++;
				break;
			case 31:			//四恻到处压制	奇数层	3
				if(Board_Eva[6][5]==EMPTY&&
					BlackChessPoly[i-9]!=BLACK_SOLDIER&&
					WhiteChessPoly[i-9]+WhiteChessPoly[i-8]==WHITE_SOLDIER)
					TotalBlackCount++;
				break;
			}

		}
	}
	TotalWhiteValue = TotalWhiteCount*REPRESS_VALUE;
	TotalBlackValue = TotalBlackCount*REPRESS_VALUE;
	if(this->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(this->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}