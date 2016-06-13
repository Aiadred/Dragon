#include "stdafx.h"
#include "ShowInfo.h"
int CShowInfo::nCount_Hit=0;
double CShowInfo::nCount_EleTimer=0;
double CShowInfo::nCount_TotalTimer=0;
int CShowInfo::nCount_Push=0;
int CShowInfo::nCount_Cut=0;
int CShowInfo::nCount_Eval=0;
int CShowInfo::nCount_Total=0;
int CShowInfo::nCount_WinMax=0;
int CShowInfo::nCount_WinMin=0;
void CShowInfo::ShowTotalTimer(CEdit *InputType)
{
	CString str;
	nCount_TotalTimer+=nCount_EleTimer;
	str.Format(L"%lf",nCount_TotalTimer/1000);
	InputType->SetWindowTextW(str);
}
void CShowInfo::ShowEleTimer(CEdit *InputType)
{
	CString str;
	str.Format(L"%lf",nCount_EleTimer/1000);
	InputType->SetWindowTextW(str);
}
void CShowInfo::ShowCountHit(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_Hit);
	InputType->SetWindowTextW(str);


}
void CShowInfo::ShowCountTTPush(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_Push);
	InputType->SetWindowTextW(str);

}
void CShowInfo::ShowCountNodeCut(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_Cut);
	InputType->SetWindowTextW(str);
}
void CShowInfo::ShowCountNodeEval(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_Eval);
	InputType->SetWindowTextW(str);

}
void CShowInfo::ShowCountNodeTotal(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_Total);
	InputType->SetWindowTextW(str);

}
void CShowInfo::ShowCountWinMax(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_WinMax);
	InputType->SetWindowTextW(str);

}
void CShowInfo::ShowCountWinMin(CEdit *InputType)
{
	CString str;
	str.Format(L"%d",nCount_WinMin);
	InputType->SetWindowTextW(str);
}