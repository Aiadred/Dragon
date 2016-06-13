#include "stdafx.h"
#include "MakeMove.h"
#include "PublicDefine.h"

CMakeMove::CMakeMove(void)
{
	memset(this->Board_MM,NULL,8*8*4);
	memset(this->Value_Buff,NULL,20*100*4);

}
CMakeMove::CMakeMove(int (*Board_Input)[8])
{
	memcpy_s(this->Board_MM,8*8*4,Board_Input,8*8*4);
	memset(this->Value_Buff,NULL,20*100*4);
}

CMakeMove::~CMakeMove(void)
{

}
//�߶�����
void CMakeMove::Move_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8])
{
	if(nSide==WHITE_SOLDIER||nSide==BLACK_SOLDIER)//����Ǳ�
	{
		switch (Direction)
		{
		case LEFT_UP:
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x-1][y-1]=nSide;
				x-=1;
				y-=1;
				break;
			}
		case RIGHT_UP:
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x-1][y+1]=nSide;	
				x-=1;
				y+=1;
				break;
			}
		case LEFT_DOWN:
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x+1][y-1]=nSide;
				x+=1;
				y-=1;
				break;
			}
		case RIGHT_DOWN:
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x+1][y+1]=nSide;
				x+=1;
				y+=1;
				break;
			}
		}
	}
}
//��ԭ�߶�����
void CMakeMove::Move_Re_Poly(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8])
{
	if(nSide==WHITE_SOLDIER||nSide==BLACK_SOLDIER)//����Ǳ�
	{
		switch (Direction)
		{
		case LEFT_UP://���������»�
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x+1][y+1]=nSide;
				x+=1;
				y+=1;
				break;
			}
		case RIGHT_UP://���������»�
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x+1][y-1]=nSide;	
				x+=1;
				y-=1;
				break;
			}
		case LEFT_DOWN://���������ϻ�
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x-1][y+1]=nSide;
				x-=1;
				y+=1;
				break;
			}
		case RIGHT_DOWN://���������ϻ�
			{
				Board_MM[x][y]=EMPTY;
				Board_MM[x-1][y-1]=nSide;
				x-=1;
				y-=1;
				break;
			}
		}
	}
}
//ɱ�岼��
int CMakeMove::Move_Kill(int Direction,int nSide,int &x,int &y,int (*Board_MM)[8])
{
	int Value;
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MM[x][y]=0;			
			Board_MM[x-2][y-2]=nSide;
			Value=Board_MM[x-1][y-1];
			Board_MM[x-1][y-1]=0;
			x-=2;
			y-=2;
			break;		
		}
	case RIGHT_UP:
		{
			Board_MM[x][y]=0;			
			Board_MM[x-2][y+2]=nSide;	
			Value=Board_MM[x-1][y+1];
			Board_MM[x-1][y+1]=0;
			x-=2;
			y+=2;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MM[x][y]=0;
			Board_MM[x+2][y-2]=nSide;
			Value=Board_MM[x+1][y-1];
			Board_MM[x+1][y-1]=0;
			x+=2;
			y-=2;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MM[x][y]=0;
			Board_MM[x+2][y+2]=nSide;
			Value=Board_MM[x+1][y+1];
			Board_MM[x+1][y+1]=0;
			x+=2;
			y+=2;
			break;
		}
	}	
	return Value;
}

//��ԭɱ�岼��
void CMakeMove::Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value,int (*Board_MM)[8])
{

	switch (Direction)
	{
	case LEFT_UP://���������»�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+1][y+1]=Value;
			Board_MM[x+2][y+2]=nSide;
			x+=2;
			y+=2;
			break;
		}
	case RIGHT_UP://���������»�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+1][y-1]=Value;
			Board_MM[x+2][y-2]=nSide;
			x+=2;
			y-=2;
			break;
		}
	case LEFT_DOWN://���������ϻ�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-1][y+1]=Value;
			Board_MM[x-2][y+2]=nSide;
			x-=2;
			y+=2;
			break;
		}
	case RIGHT_DOWN://���������ϻ�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-1][y-1]=Value;
			Board_MM[x-2][y-2]=nSide;
			x-=2;
			y-=2;
			break;
		}
	}
	
}
//�����߶�����
void CMakeMove::King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8])
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_Before][y-nSpace_Before]=nSide;
			x-=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case RIGHT_UP:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_Before][y+nSpace_Before]=nSide;
			x-=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_Before][y-nSpace_Before]=nSide;
			x+=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_Before][y+nSpace_Before]=nSide;
			x+=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	}

}
//�����߶����ֻ�ԭ
void CMakeMove::King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int (*Board_MM)[8])
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_Before][y+nSpace_Before]=nSide;
			x+=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case RIGHT_UP:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_Before][y-nSpace_Before]=nSide;
			x+=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_Before][y+nSpace_Before]=nSide;
			x-=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_Before][y-nSpace_Before]=nSide;
			x-=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	}

}
//����ɱ�岼�֣�����ɱ������ļ�ֵ
int CMakeMove::King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int (*Board_MM)[8])
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MM[x][y]=0;			
			Board_MM[x-nSpace_After-1-nSpace_Before][y-nSpace_After-1-nSpace_Before]=nSide;
			int Value=Board_MM[x-1-nSpace_Before][y-1-nSpace_Before];
			Board_MM[x-1-nSpace_Before][y-1-nSpace_Before]=0;
			x=x-nSpace_After-1-nSpace_Before;
			y=y-nSpace_After-1-nSpace_Before;
			return Value;		
		}
	case RIGHT_UP:
		{
			Board_MM[x][y]=0;			
			Board_MM[x-nSpace_After-1-nSpace_Before][y+nSpace_After+1+nSpace_Before]=nSide;	
			int Value=Board_MM[x-1-nSpace_Before][y+1+nSpace_Before];
			Board_MM[x-1-nSpace_Before][y+1+nSpace_Before]=0;
			x=x-nSpace_After-1-nSpace_Before;
			y=y+nSpace_After+1+nSpace_Before;
			return Value;	
		}
	case LEFT_DOWN:
		{
			Board_MM[x][y]=0;
			Board_MM[x+nSpace_After+1+nSpace_Before][y-nSpace_After-1-nSpace_Before]=nSide;
			int Value=Board_MM[x+1+nSpace_Before][y-1-nSpace_Before];
			Board_MM[x+1+nSpace_Before][y-1-nSpace_Before]=0;
			x=x+nSpace_After+1+nSpace_Before;
			y=y-nSpace_After-1-nSpace_Before;
			return Value;
		}
	case RIGHT_DOWN:
		{
			Board_MM[x][y]=0;
			Board_MM[x+nSpace_After+1+nSpace_Before][y+nSpace_After+1+nSpace_Before]=nSide;
			int Value=Board_MM[x+1+nSpace_Before][y+1+nSpace_Before];
			Board_MM[x+1+nSpace_Before][y+1+nSpace_Before]=0;
			x=x+nSpace_After+1+nSpace_Before;
			y=y+nSpace_After+1+nSpace_Before;
			return Value;
		}
	}
	return false;
}
//����ɱ�岼�ֻ�ԭ
void CMakeMove::King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value,int (*Board_MM)[8])
{
	switch (Direction)
	{
	case LEFT_UP://���������»�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_After][y+nSpace_After]=Value;
			Board_MM[x+1+nSpace_Before+nSpace_After][y+1+nSpace_Before+nSpace_After]=nSide;
			x=x+1+nSpace_Before+nSpace_After;
			y=y+1+nSpace_Before+nSpace_After;
			break;
		}
	case RIGHT_UP://���������»�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x+nSpace_After][y-nSpace_After]=Value;
			Board_MM[x+1+nSpace_Before+nSpace_After][y-1-nSpace_Before-nSpace_After]=nSide;
			x=x+1+nSpace_Before+nSpace_After;
			y=y-1-nSpace_Before-nSpace_After;
			break;
		}
	case LEFT_DOWN://���������ϻ�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_After][y+nSpace_After]=Value;
			Board_MM[x-1-nSpace_Before-nSpace_After][y+1+nSpace_Before+nSpace_After]=nSide;
			x=x-1-nSpace_Before-nSpace_After;
			y=y+1+nSpace_Before+nSpace_After;
			break;
		}
	case RIGHT_DOWN://���������ϻ�
		{
			Board_MM[x][y]=EMPTY;
			Board_MM[x-nSpace_After][y-nSpace_After]=Value;
			Board_MM[x-1-nSpace_Before-nSpace_After][y-1-nSpace_Before-nSpace_After]=nSide;
			x=x-1-nSpace_Before-nSpace_After;
			y=y-1-nSpace_Before-nSpace_After;
			break;
		}
	}

}
//ͳ�����ķ���������Ŀո�����
int CMakeMove::BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y)
{
	int nCount=0;
	switch(Direction)
	{
	case 1://�������������
		{
			while((x>0&&y>0)&&Board[--x][--y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	case 2://�������������
		{
			while((x>0&&y<7)&&Board[--x][++y]==EMPTY)
			{
				nCount++;
			}
			return nCount;

		}
	case -1://�������������
		{
			while((x<7&&y<7)&&Board[++x][++y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	case -2://�������������
		{
			while((x<7&&y>0)&&Board[++x][--y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	}
	return false;
}
//ͳ�ƹµ����Ӻ󷽵Ŀո�������Ҳ�����λ��
int CMakeMove::AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y)
{
	int nCount=0;
	int nSide=Board[x][y];
	int Enemy=(nSide<0?BLACK_SOLDIER:WHITE_SOLDIER);
	switch(Direction)
	{
	case 1://�������������
		{
			while((x>0&&y>0)&&Board[--x][--y]==EMPTY);
			if((x>=0&&y>=0)&&(Board[x][y]==Enemy||Board[x][y]==Enemy*2))
			{

				while((x!=0&&y!=0)&&(Board[--x][--y]==EMPTY))
				{
					
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}
	case 2://�������������
		{
			while((x>0&&y<7)&&Board[--x][++y]==EMPTY);
			if((x>0&&y<7)&&(Board[x][y]==Enemy||Board[x][y]==Enemy*2))
			{
				while((x!=0&&y!=7)&&(Board[--x][++y]==EMPTY))
				{				
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}
	case -1://�������������
		{
			while((x<7&&y<7)&&Board[++x][++y]==EMPTY);
			if((x<7&&y<7)&&(Board[x][y]==Enemy||Board[x][y]==Enemy*2))
			{
				while((x!=7&&y!=7)&&(Board[++x][++y]==EMPTY))
				{				
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;

			}
			return nCount;
		}
	case -2://�������������
		{
			while((x<7&&y>0)&&Board[++x][--y]==EMPTY);
			
			if((x<7&&y>0)&&(Board[x][y]==Enemy||Board[x][y]==Enemy*2))
			{
				while((x!=7&&y!=0)&&(Board[++x][--y]==EMPTY))
				{
					
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}

	}
	return false; 
}

//��������֮�������
void CMakeMove::MakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8])
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//�ж������߻��Ǳ���
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
		{
			this->Move_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Board_Input);
			
		}else
		{
			for(int i=0;i<Chess.Depth;i++)
			{
				Value_Buff[Chess.nPly][i]=Move_Kill(Chess.DirectionToMove[i],Chess.nSide_,(Chess.Location_Current.x),(Chess.Location_Current.y),Board_Input);
			}
		}
		
	}
	else if(Chess.nSide_==BLACK_KING||Chess.nSide_==WHITE_KING)
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
		{
			this->King_Move_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[0],Board_Input);
			
		}else
		{
			for(int i=0;i<Chess.Depth;i++)
			{
				Value_Buff[Chess.nPly][i]=King_Kill_Poly(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[i],Chess.nSpace_After[i],Board_Input);
			}
		}
	}
	for(int i=0;i<8;i++)
	{
		if(Board_Input[7][i]==-1)
		{
			Board_Input[7][i]=-2;
		}	
		else if(Board_Input[0][i]==1)
		{
			Board_Input[0][i]=2;

		}
	}
}
//��ԭ����������
void CMakeMove::ResetMakeMove(CNodeChessInfo &Chess,int (*Board_Input)[8])
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//�ж������߻��Ǳ���
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
		{
			Move_Re_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Board_Input);
			
		}else
		{
			int i=Chess.Depth-1;
			for(i;i>=0;i--)
			{
				Move_Re_Kill(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Value_Buff[Chess.nPly][i],Board_Input);
				
			}
		}
	}
	else if(Chess.nSide_==BLACK_KING||Chess.nSide_==WHITE_KING)
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
		{
			King_Move_Re_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[0],Board_Input);
			
		}else
		{
			int i=Chess.Depth-1;
			for(i;i>=0;i--)
			{
				King_Kill_Re_Poly(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[i],Chess.nSpace_After[i],Value_Buff[Chess.nPly][i],Board_Input);
			}
		}
	}
}