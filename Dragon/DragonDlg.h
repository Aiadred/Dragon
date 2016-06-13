
// DragonDlg.h : 头文件
//

#pragma once

#include "GameCTRL.h"
#include "afxwin.h"
#include "afxmenubutton.h"
// CDragonDlg 对话框
class CDragonDlg : public CDialogEx
{
	
// 构造
public:
	CDragonDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CDragonDlg();
// 对话框数据
	enum { IDD = IDD_DRAGON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAlphabetaTt();
public:
	
	CGameCTRL m_nCGC;

	CEdit m_Timer;
	CEdit nCount_Hit_Show;
	CEdit nCount_Push;
	CEdit nCount_Eval;
	CEdit nCount_Total;
	CEdit nCount_Cut;
	CEdit ElementTimer;
	CEdit TotalTimer;
	CEdit WindowMin;
	CEdit WindowMax;
	afx_msg void OnPvsTt();
	afx_msg void OnDepthmenu4();
	afx_msg void OnDepthmenu6();
	afx_msg void OnDepthmenu8();
	afx_msg void OnDepthmenu10();
	afx_msg void OnDepthmenu12();
	afx_msg void OnDepthmenu14();
	afx_msg void OnFunctionReset();
	
	
	
	
};
