#include "stdafx.h"
#include "Public.h"
#include <iostream>



//���ӽڵ��ʼ��
CNodeChessInfo::CNodeChessInfo(void)
{
	this->Location_Current.x=0;//��ǰλ��
	this->Location_Current.y=0;//��ǰλ��
	this->Depth=0;
	this->nCount=0;
	this->nSide_=0;
	this->nPly=0;
	memset(DirectionToMove,0,12*4);
	memset(nSpace_Before,0,12*4);
	memset(nSpace_After,0,12*4);
	
	this->pNext=NULL;
}
CNodeChessInfo::~CNodeChessInfo(void)
{

	this->pNext=NULL;

}





