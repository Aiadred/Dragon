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
//                  佛祖保佑             永无BUG   
//          佛曰:    
//                  写字楼里写字间，写字间里程序员；    
//                  程序人员写程序，又拿程序换酒钱。    
//                  酒醒只在网上坐，酒醉还来网下眠；    
//                  酒醉酒醒日复日，网上网下年复年。    
//                  但愿老死电脑间，不愿鞠躬老板前；    
//                  奔驰宝马贵者趣，公交自行程序员。    
//                  别人笑我忒疯癫，我笑自己命太贱；    
//                  不见满街漂亮妹，哪个归得程序员？ 








int iBoard[8][8]={	{ 0,-1, 0,-1, 0,-1, 0,-1},
					{-1, 0,-1, 0,-1, 0,-1, 0},
					{ 0, -1, 0, -1, 0,-1, 0,-1},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 0, 1, 0, 1, 0, 1, 0},
					{ 0, 1, 0, 1, 0, 1, 0, 1},
					{ 1, 0, 1, 0, 1, 0, 1, 0}};
int UP=1;
int iBL=50;//棋盘左侧边距
int iBT=50;//棋盘上侧边距
int iBS=50;//棋盘棋位单位
int iAIColor=-1; //引擎棋子颜色
int iGetChess=0; //对手拾取棋子
int iM_1,iN_1,iM_2,iN_2;  //拾棋与落棋座标（数组下标）
int iM,iN;
int turn=1; 

int UP_COUNT=0;
int CSelected::EngineChoose=0;		//默认alpha_beta剪枝引擎
int CSelected::DepthChoose=10;		//默认10层深度
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

void CGameCTRL::MoveJump_L(int i,int j) //向左下间隔跳
{
	iBoard[i+2][j-2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j-1]=0;
}
void CGameCTRL::MoveJump_R(int i,int j) //向右下间隔跳
{
	iBoard[i+2][j+2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j+1]=0;
}
void CGameCTRL::Move1_L(int i,int j)	//向左下跳
{
	iBoard[i+1][j-1]=iBoard[i][j];
	iBoard[i][j]=0;
}
void CGameCTRL::Move1_R(int i,int j)	//向右下跳
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


	//Move中有介绍
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
		iM=(iY-iBT)/iBS;  //将座标转换成数组下标，iM为纵，iN为横
		iN=(iX-iBL)/iBS;
		iM_2=iM;
		iN_2=iN;
		
		
		if(iGetChess==0&&(iBoard[iM][iN]==BLACK_SOLDIER||iBoard[iM][iN]==BLACK_KING))  //拾棋
		{	
			
			memcpy_s(Board_King,8*8*4,iBoard,8*8*4);
			iM_1=iM;
			iN_1=iN;
			Value=iBoard[iM][iN];
			iBoard[iM][iN]=0;
			turn=0;
			iGetChess=1; 
		}
		else if(iM_2==iM_1&&iN_2==iN_1)  //原地
		{
			iBoard[iM][iN]=Value;
			iGetChess=0;	turn=1; 		
		} 
		else if(turn==0)//落棋
		{
			
			if(iBoard[iM][iN]==EMPTY&&Value==BLACK_SOLDIER)
			{
				if((iM_2==iM_1-2)&&(iN_2==iN_1-2)&&((iBoard[iM_1-1][iN_1-1]==-1)||(iBoard[iM_1-1][iN_1-1]==-2)))  //左上上
				{
					iBoard[iM_1-1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if((iM_2==iM_1-2)&&(iN_2==iN_1+2)&&((iBoard[iM_1-1][iN_1+1]==-1)||(iBoard[iM_1-1][iN_1+1]==-2)))  //右上上
				{
					iBoard[iM_1-1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if((iM_2==iM_1+2)&&(iN_2==iN_1-2)&&((iBoard[iM_1+1][iN_1-1]==-1)||(iBoard[iM_1+1][iN_1-1]==-2)))//左下下
				{
					iBoard[iM_1+1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if((iM_2==iM_1+2)&&(iN_2==iN_1+2)&&((iBoard[iM_1+1][iN_1+1]==-1)||(iBoard[iM_1+1][iN_1+1]==-2)))//右下下
				{
					iBoard[iM_1+1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if(iM_2==iM_1-1&&iN_2==iN_1-1&&iBoard[iM_1-1][iN_1-1]==0||iM_2==iM_1-1&&iN_2==iN_1+1&&iBoard[iM_1-1][iN_1+1]==0)  //左上或右上
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
			//落棋之后保存棋盘
			int (*p)[8];//这个是一个数组指针，是指针，只有4字节，指向8*8的内容，所以8*8自己申请
 			p = (int (*)[8])malloc(8*8*4);//申请空间
			memcpy_s(p,8*8*4,iBoard,8*8*4);
			CReset::PushList(p);//压入链表
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