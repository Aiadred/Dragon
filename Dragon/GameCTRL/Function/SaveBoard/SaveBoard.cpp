#include "stdafx.h"
#include "SaveBoard.h"
#include "Reset.h"

CSaveBoard::CSaveBoard(void)
{
	
}


CSaveBoard::~CSaveBoard(void)
{
}
ofstream CSaveBoard::output_file("HistoricalBoard.dat");
bool CSaveBoard::SaveBoard()
{
	if(!output_file)
	{
		cerr<<"open error!"<<endl;
        exit(1);  
		return false;
	}
	if(CReset::List_Re.size()>1)
	{
		list<int (*)[8]>::iterator ite=CReset::List_Re.begin();
		int BoardCopy[64];		
		ite++;
		memcpy_s(BoardCopy,8*8*4,(*ite),8*8*4);
		for(int i=0;i<64;i++)
		{
			int k=0;
			char Char_Buff[3];
			_itoa_s(*(BoardCopy+i),Char_Buff,3,10);
			while(*(Char_Buff+k)!='\0')
			{
				output_file.put(*(Char_Buff+k));
				k++;
			}output_file<<"   ";
			if((i+1)%8==0)
				output_file<<endl;
		}
		output_file<<endl;		
	}
	return true;
}