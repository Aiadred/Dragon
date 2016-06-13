#pragma once

class CShowInfo
{
public:
	CShowInfo(void)
	{
	}
	~CShowInfo(void)
	{
	}
	static int nCount_Hit;
	static double nCount_EleTimer;
	static double nCount_TotalTimer;
	static int nCount_Push;
	static int nCount_Cut;
	static int nCount_Eval;
	static int nCount_Total;
	static int nCount_WinMax;
	static int nCount_WinMin;
	
public:
	static void ShowEleTimer(CEdit *InputType);
	static void ShowTotalTimer(CEdit *InputType);
	static void ShowCountHit(CEdit *InputType);
	static void ShowCountTTPush(CEdit *InputType);
	static void ShowCountNodeCut(CEdit *InputType);
	static void ShowCountNodeEval(CEdit *InputType);
	static void ShowCountNodeTotal(CEdit *InputType);
	static void ShowCountWinMax(CEdit *InputType);
	static void ShowCountWinMin(CEdit *InputType);
};

