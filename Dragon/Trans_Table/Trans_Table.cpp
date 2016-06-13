#include "stdafx.h"
#include "Trans_Table.h"
#include "ShowInfo.h"
#include <time.h>
LONGLONG rand64(void)
{
	return rand()^
		((LONGLONG)rand()<<15)^
		((LONGLONG)rand()<<30)^
		((LONGLONG)rand()<<45)^
		((LONGLONG)rand()<<60);
}
UINT rand32(void)
{
	return rand()^
		((UINT)rand()<<15)^
		((UINT)rand()<<30);
}
CTrans_Table::CTrans_Table(void)
{
	SrandBulidHash();
}


CTrans_Table::~CTrans_Table(void)
{
	delete this->m_pTT[0];
	delete this->m_pTT[1];
}
enum ChessType{White_Soldier,White_King,Black_Soldier,Black_King};
int CTrans_Table::ChessChoose(int nTypeChess)
{
	//为了匹配相应的数组下标，故将棋子种类转换
	switch (nTypeChess)
	{
	case WHITE_SOLDIER:
		return White_Soldier;			////-1->0
	case WHITE_KING:
		return White_King;				////-2->1
	case BLACK_SOLDIER:
		return Black_Soldier;			////1 ->2
	case BLACK_KING:
		return Black_King;				////2 ->3		
	}
}
//根据棋盘计算key值
void CTrans_Table::CaculateInitHashKey(int (*Board_Input)[8])
{
	int i,j,nChessType;
	m_HashKey_32=0;
	m_HashKey_64=0;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			nChessType=Board_Input[i][j];
			if(nChessType==WHITE_SOLDIER||nChessType==WHITE_KING||nChessType==BLACK_SOLDIER||nChessType==BLACK_KING)
			{
				nChessType=ChessChoose(nChessType);
				m_HashKey_32=m_HashKey_32^m_nHashKey_32[nChessType][i][j];
				m_HashKey_64=m_HashKey_64^m_nHashKey_64[nChessType][i][j];

			}

		}
	}

}
//根据走法产生新的key值
void CTrans_Table::MakeMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn)
{
	int nToID,nFromID;
	int Board_Copy[8][8];
	int Board_Monitor[8][8];
	CMakeMove m_pMakeMove(Board_Input);
	int Current_Loc_x=Chess_Input.Location_Current.x;
	int Current_Loc_y=Chess_Input.Location_Current.y;
	memcpy_s(Board_Copy,8*8*4,Board_Input,8*8*4);
	nFromID=Chess_Input.nSide_;
	nFromID=ChessChoose(nFromID);
	m_pMakeMove.MakeMove(Chess_Input,Board_Input);
	memcpy_s(Board_Monitor,8*8*4,Board_Input,8*8*4);
	//去掉我方初始位置的棋子的key值
	m_HashKey_32=m_HashKey_32^m_nHashKey_32[nFromID][Current_Loc_x][Current_Loc_y];
	m_HashKey_64=m_HashKey_64^m_nHashKey_64[nFromID][Current_Loc_x][Current_Loc_y];


	for(int i=0,k=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			
			//加上我方最后位置的棋子的key值
			if((Board_Input[i][j]==Turn||Board_Input[i][j]==2*Turn)
				&&(Board_Copy[i][j]==EMPTY))
			{
				m_HashKey_32=m_HashKey_32^m_nHashKey_32[nFromID][i][j];
				m_HashKey_64=m_HashKey_64^m_nHashKey_64[nFromID][i][j];
			}
			//去掉吃掉的地方的棋子的key值,之比较地方棋子
			if((Board_Input[i][j]==EMPTY)&&
				(Board_Copy[i][j]==-Turn||Board_Copy[i][j]==-Turn*2))
			{
					nToID=Board_Copy[i][j];
					nToID=ChessChoose(nToID);
					m_HashKey_32=m_HashKey_32^m_nHashKey_32[nToID][i][j];
					m_HashKey_64=m_HashKey_64^m_nHashKey_64[nToID][i][j];
				
			}

		}

	}
	m_pMakeMove.ResetMakeMove(Chess_Input,Board_Input);
}
//撤销走法产生新的key值
void CTrans_Table::ResetMoveHashKey(CNodeChessInfo Chess_Input,int (*Board_Input)[8],int Turn,int (*ValueBuff)[100])
{
	int nToID,nFromID;
	int Board_Copy[8][8];
	int Board_Monitor[8][8];
	CMakeMove m_pMakeMove(Board_Input);

	int Current_Loc_x=Chess_Input.Location_Current.x;
	int Current_Loc_y=Chess_Input.Location_Current.y;
	memcpy_s(Board_Copy,8*8*4,Board_Input,8*8*4);
	
	nFromID=Chess_Input.nSide_;
	nFromID=ChessChoose(nFromID);
	memcpy(m_pMakeMove.Value_Buff,ValueBuff,20*100*4);

	m_pMakeMove.ResetMakeMove(Chess_Input,Board_Input);
	memcpy_s(Board_Monitor,8*8*4,Board_Input,8*8*4);
	//加上我方初始位置的棋子的key值
	m_HashKey_32=m_HashKey_32^m_nHashKey_32[nFromID][Current_Loc_x][Current_Loc_y];
	m_HashKey_64=m_HashKey_64^m_nHashKey_64[nFromID][Current_Loc_x][Current_Loc_y];


	for(int i=0,k=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			
			//去掉我方最后位置的棋子的key值
			if((Board_Input[i][j]==Turn||Board_Input[i][j]==Turn*2)
				&&(Board_Copy[i][j]==EMPTY))
			{

				m_HashKey_32=m_HashKey_32^m_nHashKey_32[nFromID][i][j];
				m_HashKey_64=m_HashKey_64^m_nHashKey_64[nFromID][i][j];

			}
			//去掉吃掉的地方的棋子的key值,之比较地方棋子
			if((Board_Copy[i][j]==EMPTY)&&
				(Board_Input[i][j]==-Turn||Board_Copy[i][j]==-Turn*2))
			{
				nToID=Board_Input[i][j];
				nToID=ChessChoose(nToID);
				m_HashKey_32=m_HashKey_32^m_nHashKey_32[nToID][i][j];
				m_HashKey_64=m_HashKey_64^m_nHashKey_64[nToID][i][j];
			
			}

		}

	}
	m_pMakeMove.MakeMove(Chess_Input,Board_Input);
	memcpy_s(Board_Monitor,8*8*4,Board_Input,8*8*4);
}
//查询hash_map当前节点数据
int CTrans_Table::SearchHashKey(int Alpha,int Beta,int nPly,int Turn)
{
	int x;
	Turn=(Turn<0==true)?0:1;
	HashItem *pHItem;
	x=m_HashKey_32 & 0xFFFFF;				///////////#########################################///////////////
	pHItem=&m_pTT[Turn][x];
	if(pHItem->nPly>=nPly&&pHItem->Checksum==m_HashKey_64)
	{
		switch(pHItem->Data_type)
		{
		case exact:
			return pHItem->Eval;
		case lower_bound:
			{
				if(pHItem->Eval>=Beta)
					return pHItem->Eval;
				else
					break;
			}
		case upper_bound:
			{
				if(pHItem->Eval<=Alpha)
					return pHItem->Eval;
				else
					break;
			}
		}
	}
	return 8459439;							///////////#########################################///////////////


}

//将当前节点值压入Hash_map
void CTrans_Table::PushNodeIntoHash(entry_type entry_type,int Evalute,short nPly,int Turn)
{
	int x;
	HashItem *pHItem;

	Turn=(Turn<0==true)?0:1;
	x=m_HashKey_32&0xFFFFF;					///////////#########################################///////////////
	pHItem=&m_pTT[Turn][x];
	pHItem->Checksum=m_HashKey_64;
	pHItem->Data_type=entry_type;
	pHItem->Eval=Evalute;
	pHItem->nPly=nPly;
	CShowInfo::nCount_Push++;
}
//初始化随机数组创建Hash_map
void CTrans_Table::SrandBulidHash()
{
	int nType,i,j;
	srand((unsigned int)time(NULL));
	for(nType=0;nType<4;nType++)
	{
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				m_nHashKey_32[nType][i][j]=rand32();
				m_nHashKey_64[nType][i][j]=rand64();
			}

		}
	}
	this->m_pTT[0]=new HashItem[1024*1024];
	this->m_pTT[1]=new HashItem[1024*1024];
}