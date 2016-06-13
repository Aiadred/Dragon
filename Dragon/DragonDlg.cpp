
// DragonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dragon.h"
#include "DragonDlg.h"
#include "afxdialogex.h"
#include "ShowInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern int iBoard[8][8];
extern int UP;
extern int iBL;//�������߾�
extern int iBT;//�����ϲ�߾�
extern int iBS;//������λ��λ
extern int iAIColor; //����������ɫ
extern int iGetChess; //����ʰȡ����
extern int iM_1,iN_1,iM_2,iN_2;  //ʰ�����������꣨�����±꣩
extern int iM,iN;
extern int turn; 
extern int UP_COUNT;
enum{AlphaBeta_TT,PVS_TT};
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnFhnvgtjVykvkv();
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
	
END_MESSAGE_MAP()


// CDragonDlg �Ի���



CDragonDlg::CDragonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDragonDlg::IDD, pParent)
{

	int (*p)[8];//���캯�������ʼ���̣��������ݼ�Move()
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	CReset::PushList(p);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CDragonDlg::~CDragonDlg()
{


}
void CDragonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, nCount_Hit_Show);
	DDX_Control(pDX, IDC_EDIT3, nCount_Push);
	DDX_Control(pDX, IDC_EDIT4, nCount_Eval);
	DDX_Control(pDX, IDC_EDIT5, nCount_Total);

	DDX_Control(pDX, IDC_EDIT1, ElementTimer);
	DDX_Control(pDX, IDC_EDIT6, TotalTimer);
	DDX_Control(pDX, IDC_EDIT7, WindowMin);
	DDX_Control(pDX, IDC_EDIT8, WindowMax);
	DDX_Control(pDX, IDC_EDIT9, nCount_Cut);
}

BEGIN_MESSAGE_MAP(CDragonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ALPHABETA_TT, &CDragonDlg::OnAlphabetaTt)
	ON_COMMAND(ID_PVS_TT, &CDragonDlg::OnPvsTt)
	ON_COMMAND(ID_DEPTHMENU_4, &CDragonDlg::OnDepthmenu4)
	ON_COMMAND(ID_DEPTHMENU_6, &CDragonDlg::OnDepthmenu6)
	ON_COMMAND(ID_DEPTHMENU_8, &CDragonDlg::OnDepthmenu8)
	ON_COMMAND(ID_DEPTHMENU_10, &CDragonDlg::OnDepthmenu10)
	ON_COMMAND(ID_DEPTHMENU_12, &CDragonDlg::OnDepthmenu12)
	ON_COMMAND(ID_DEPTHMENU_14, &CDragonDlg::OnDepthmenu14)
	ON_COMMAND(ID_FUNCTION_RESET, &CDragonDlg::OnFunctionReset)
END_MESSAGE_MAP()


// CDragonDlg ��Ϣ�������

BOOL CDragonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDragonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void DrawGo(CPaintDC* pDC)
{
	CBrush jBrush;
	jBrush.CreateSolidBrush(RGB(0,255,0));  //��
	pDC->SelectObject(&jBrush);
	pDC->Rectangle(iBL+9*iBS,iBT+iBS-25,iBL+10*iBS,iBT+8*iBS-25);
	pDC->SelectStockObject(BLACK_BRUSH);
	jBrush.DeleteObject();
	jBrush.CreateSolidBrush(RGB(0,0,255));  //��
	pDC->SelectObject(&jBrush);
	pDC->Rectangle(iBL+10*iBS,iBT+iBS-25,iBL+11*iBS,iBT+8*iBS-25);
	pDC->SelectStockObject(BLACK_BRUSH);
	jBrush.DeleteObject();
}
void DrawBoard(CPaintDC* pDC)
{
	int i,j;
	CBrush jBrush;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if((i+j)%2==0)//ǳ��ɫ��λ
				jBrush.CreateSolidBrush(RGB(120,120,120));
			else//���ɫ��λ
				jBrush.CreateSolidBrush(RGB(80,80,80));
			pDC->SelectObject(&jBrush);
			pDC->Rectangle(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
			pDC->SelectStockObject(BLACK_BRUSH);
			jBrush.DeleteObject();
		}
}
void DrawChess(CPaintDC* pDC)
{
	int i,j;
	CBrush jBrush;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if(iBoard[i][j]==-1)//����
			{
				jBrush.CreateSolidBrush(RGB(220,220,220));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==1)//����
			{
				jBrush.CreateSolidBrush(RGB(0,0,0));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==-2)//����
			{
				jBrush.CreateSolidBrush(RGB(220,220,220));
				pDC->SelectObject(&jBrush);
				pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==2)//����
			{
				jBrush.CreateSolidBrush(RGB(0,0,0));
				pDC->SelectObject(&jBrush);
				pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==5)//�յ�
			{
				jBrush.CreateSolidBrush(RGB(85,220,21));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS+12,iBL+i*iBS+12,iBT+(j+1)*iBS-10,iBL+(i+1)*iBS-12);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			
			if(iBoard[i][j]==-5)//����
			{
				jBrush.CreateSolidBrush(RGB(85,220,100));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(1==UP)
			{
				if(iBoard[i][j]==4)//����
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-4)//����
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==6)//����
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-6)//����
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
			}
			else
			{
				if(iBoard[i][j]==6)//����
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-6)//����
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==4)//����
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-4)//����
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
			}
		
		}
}
void CDragonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC pDC(this);
		DrawBoard(&pDC);
		DrawChess(&pDC);
		DrawGo(&pDC);
		CDialogEx::OnPaint();
	}
	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDragonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDragonDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CShowInfo::nCount_Cut=0;
	CShowInfo::nCount_Eval=0;
	CShowInfo::nCount_Hit=0;
	CShowInfo::nCount_Push=0;
	CShowInfo::nCount_EleTimer=0;
	CShowInfo::nCount_Total=0;
	CShowInfo::nCount_WinMax=0;
	CShowInfo::nCount_WinMin=0;
	CShowInfo::nCount_Cut=0;
	int iX,iY;
	iX= point.x;
	iY= point.y;
	
	if(m_nCGC.iInArea(iX,iY,iBL+9*iBS,iBT+iBS-25,iBL+10*iBS,iBT+8*iBS-25)) //����������壨���巶Χ��
	{
		m_nCGC.iMove();
		UP_COUNT=1;
	}
	if(m_nCGC.iInArea(iX,iY,iBL,iBT,iBL+iBS*8,iBT+iBS*8)) //���̷�Χ
	{
		m_nCGC.Move(iX,iY);
		UP_COUNT=1;
	}

	CShowInfo::ShowCountHit(&nCount_Hit_Show);
	CShowInfo::ShowCountTTPush(&nCount_Push);
	CShowInfo::ShowCountNodeEval(&nCount_Eval);
	CShowInfo::ShowCountNodeTotal(&nCount_Total);
	CShowInfo::ShowEleTimer(&ElementTimer);
	CShowInfo::ShowTotalTimer(&TotalTimer);
	CShowInfo::ShowCountWinMax(&WindowMax);
	CShowInfo::ShowCountWinMin(&WindowMin);
	CShowInfo::ShowCountNodeCut(&nCount_Cut);
	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}




void CDragonDlg::OnAlphabetaTt()
{
	
	CSelected::EngineChoose=AlphaBeta_TT;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnPvsTt()
{
	CSelected::EngineChoose=PVS_TT;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu4()
{
	CSelected::DepthChoose=4;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu6()
{
	CSelected::DepthChoose=6;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu8()
{
	CSelected::DepthChoose=8;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu10()
{
	CSelected::DepthChoose=10;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu12()
{
	CSelected::DepthChoose=12;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnDepthmenu14()
{
	CSelected::DepthChoose=14;
	// TODO: �ڴ���������������
}


void CDragonDlg::OnFunctionReset()
{
	if(CReset::List_Re.size()>1)
	{
		delete []CReset::List_Re.front();
		CReset::List_Re.pop_front();
		memcpy_s(iBoard,8*8*4,CReset::List_Re.front(),8*8*4);
	}
	else
		return;
	Invalidate();
	// TODO: �ڴ���������������
}
