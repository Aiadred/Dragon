#include "stdafx.h"
#include "GameCTRL.h"
#include "ShowInfo.h"
#include "Timer.h"
#include "SaveBoard.h"

//                            _ooOoo_    
//                           o8888888o    
//                           88" . "88    
//                           (| -_- |)    
//                            O\ = /O    
//                        ____/`---'\____    
//                      .   ' \\| |// `.    
//                       / \\||| : |||// \    
//                     / _||||| -:- |||||- \    
//                       | | \\\ - /// | |    
//                     | \_| ''\---/'' | |    
//                      \ .-\__ `-` ___/-. /    
//                   ___`. .' /--.--\ `. . __    
//                ."" '< `.___\_<|>_/___.' >'"".    
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |    
//                 \ \ `-. \_ __\ /__ _/ .-` / /    
//         ======`-.____`-.___\_____/___.-`____.-'======    
//                            `=---='      
//         .............................................    
//                  ���汣��             ����BUG   
//          ��Ի:    
//                  д��¥��д�ּ䣬д�ּ������Ա��    
//                  ������Աд�������ó��򻻾�Ǯ��    
//                  ����ֻ���������������������ߣ�    
//                  ��������ո��գ����������긴�ꡣ    
//                  ��Ը�������Լ䣬��Ը�Ϲ��ϰ�ǰ��    
//                  ���۱������Ȥ���������г���Ա��    
//                  ����Ц��߯��񲣬��Ц�Լ���̫����    
//                  ��������Ư���ã��ĸ���ó���Ա�� 








int iBoard[8][8]={	{ 0,-1, 0,-1, 0,-1, 0,-1},
					{-1, 0,-1, 0,-1, 0,-1, 0},
					{ 0, -1, 0, -1, 0,-1, 0,-1},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 0, 1, 0, 1, 0, 1, 0},
					{ 0, 1, 0, 1, 0, 1, 0, 1},
					{ 1, 0, 1, 0, 1, 0, 1, 0}};
int UP=1;
int iBL=50;//�������߾�
int iBT=50;//�����ϲ�߾�
int iBS=50;//������λ��λ
int iAIColor=-1; //����������ɫ
int iGetChess=0; //����ʰȡ����
int iM_1,iN_1,iM_2,iN_2;  //ʰ�����������꣨�����±꣩
int iM,iN;
int turn=1; 

int UP_COUNT=0;
int CSelected::EngineChoose=0;		//Ĭ��alpha_beta��֦����
int CSelected::DepthChoose=10;		//Ĭ��10�����
CGameCTRL::CGameCTRL(void)
{
	
	
}


CGameCTRL::~CGameCTRL(void)
{
	
}
int CGameCTRL::iInArea(int x,int y,int x1,int y1,int x2,int y2)
{
	if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
		return 1;
	else
		return 0;
}

void CGameCTRL::MoveJump_L(int i,int j) //�����¼����
{
	iBoard[i+2][j-2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j-1]=0;
}
void CGameCTRL::MoveJump_R(int i,int j) //�����¼����
{
	iBoard[i+2][j+2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j+1]=0;
}
void CGameCTRL::Move1_L(int i,int j)	//��������
{
	iBoard[i+1][j-1]=iBoard[i][j];
	iBoard[i][j]=0;
}
void CGameCTRL::Move1_R(int i,int j)	//��������
{
	iBoard[i+1][j+1]=iBoard[i][j];
	iBoard[i][j]=0;
}



	
void CGameCTRL::iMove()
{
	CTimer EleTime;
	
	
	Moving= CFactoryObj::SearchObj(CSelected::EngineChoose);
	Moving->SetSearchDepth(CSelected::DepthChoose);
	Moving->SearchAGoodMove(iBoard);
	memcpy_s(iBoard,8*8*4,Moving->Board_Copy,8*8*4);
	delete Moving;
	Moving=NULL;

	CShowInfo::nCount_EleTimer=EleTime.CalculateTime();


	//Move���н���
	int (*p)[8];
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	CReset::PushList(p);	
	CSaveBoard::SaveBoard();
}
void CGameCTRL::Move(int iX,int iY)
{
		static int Value;
		static int Board_King[8][8];
		iM=(iY-iBT)/iBS;  //������ת���������±꣬iMΪ�ݣ�iNΪ��
		iN=(iX-iBL)/iBS;
		iM_2=iM;
		iN_2=iN;
		
		
		if(iGetChess==0&&(iBoard[iM][iN]==BLACK_SOLDIER||iBoard[iM][iN]==BLACK_KING))  //ʰ��
		{	
			
			memcpy_s(Board_King,8*8*4,iBoard,8*8*4);
			iM_1=iM;
			iN_1=iN;
			Value=iBoard[iM][iN];
			iBoard[iM][iN]=0;
			turn=0;
			iGetChess=1; 
		}
		else if(iM_2==iM_1&&iN_2==iN_1)  //ԭ��
		{
			iBoard[iM][iN]=Value;
			iGetChess=0;	turn=1; 		
		} 
		else if(turn==0)//����
		{
			
			if(iBoard[iM][iN]==EMPTY&&Value==BLACK_SOLDIER)
			{
				if((iM_2==iM_1-2)&&(iN_2==iN_1-2)&&((iBoard[iM_1-1][iN_1-1]==-1)||(iBoard[iM_1-1][iN_1-1]==-2)))  //������
				{
					iBoard[iM_1-1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if((iM_2==iM_1-2)&&(iN_2==iN_1+2)&&((iBoard[iM_1-1][iN_1+1]==-1)||(iBoard[iM_1-1][iN_1+1]==-2)))  //������
				{
					iBoard[iM_1-1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if((iM_2==iM_1+2)&&(iN_2==iN_1-2)&&((iBoard[iM_1+1][iN_1-1]==-1)||(iBoard[iM_1+1][iN_1-1]==-2)))//������
				{
					iBoard[iM_1+1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if((iM_2==iM_1+2)&&(iN_2==iN_1+2)&&((iBoard[iM_1+1][iN_1+1]==-1)||(iBoard[iM_1+1][iN_1+1]==-2)))//������
				{
					iBoard[iM_1+1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if(iM_2==iM_1-1&&iN_2==iN_1-1&&iBoard[iM_1-1][iN_1-1]==0||iM_2==iM_1-1&&iN_2==iN_1+1&&iBoard[iM_1-1][iN_1+1]==0)  //���ϻ�����
				{
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();	
				}
				
			}
			if(iBoard[iM][iN]==EMPTY&&Value==BLACK_KING)
			{
				CMakeMove *pMM_iMove=new CMakeMove;
				int Flag=0;
				int nSpace_Before;
				int nSpace_After;
				int length=iM_2-iM_1>0?iM_2-iM_1:iM_1-iM_2;
				if((nSpace_After=pMM_iMove->AfterKingSpaceCount(Board_King,LEFT_UP,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,LEFT_UP,iM_1,iN_1);
					iM_1-=nSpace_Before;
					iN_1-=nSpace_Before;
					iBoard[iM_1-1][iN_1-1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=pMM_iMove->AfterKingSpaceCount(Board_King,RIGHT_UP,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,RIGHT_UP,iM_1,iN_1);
					iM_1-=nSpace_Before;
					iN_1+=nSpace_Before;
					iBoard[iM_1-1][iN_1+1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=pMM_iMove->AfterKingSpaceCount(Board_King,LEFT_DOWN,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,LEFT_DOWN,iM_1,iN_1);
					iM_1+=nSpace_Before;
					iN_1-=nSpace_Before;
					iBoard[iM_1+1][iN_1-1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=pMM_iMove->AfterKingSpaceCount(Board_King,RIGHT_DOWN,iM_1,iN_1))>0)
				{			
					Flag=1;
					nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,RIGHT_DOWN,iM_1,iN_1);
					iM_1+=nSpace_Before;
					iN_1+=nSpace_Before;
					iBoard[iM_1+1][iN_1+1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				if(Flag!=1)
				{
					if((nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,LEFT_UP,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,RIGHT_UP,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,LEFT_DOWN,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=pMM_iMove->BeforeKingSpaceCount(Board_King,RIGHT_DOWN,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
				}
			}
			///////
			////////
			//����֮�󱣴�����
			int (*p)[8];//�����һ������ָ�룬��ָ�룬ֻ��4�ֽڣ�ָ��8*8�����ݣ�����8*8�Լ�����
 			p = (int (*)[8])malloc(8*8*4);//����ռ�
			memcpy_s(p,8*8*4,iBoard,8*8*4);
			CReset::PushList(p);//ѹ������
			CSaveBoard::SaveBoard();
		}	
		
		for(int i=0;i<8;i++)
		{
			if(iBoard[0][i]==1)
			{
				iBoard[0][i]=2;
			}			
		}
}