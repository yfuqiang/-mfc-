#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KnightTour.h"
#endif

#include "KnightTourDoc.h"
#include "KnightTourView.h"
#include "NewStartPosition.h"
#include "DialogSpeed.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKnightTourView

CKnightTourView* g_view = NULL;

IMPLEMENT_DYNCREATE(CKnightTourView, CView)

BEGIN_MESSAGE_MAP(CKnightTourView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_MENU_NEWSTARTPOS, &CKnightTourView::OnMenuNewstartpos)//ID_MENU_SPEED
	ON_COMMAND(ID_MENU_SPEED, &CKnightTourView::OnMenuSpeed)//
	ON_COMMAND(ID_MENU_END, &CKnightTourView::OnMenuEnd)
	ON_COMMAND(ID_MENU_START, &CKnightTourView::OnMenuStart)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


int Forward[8][2] = { { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 },{ -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 } };//将骑士的可能遍历方向存入数组

// CKnightTourView 构造/析构

CKnightTourView::CKnightTourView()
{
	g_view = this;
	// TODO:  在此处添加构造代码
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
			Qipan[i][j] = 0; //初始化
	count = 0;
	width = 40;
	nR = 5;      //棋子半径
	Step = 0;
	m_x = 1;
	m_y = 1;
	ntimerms = 200;//初始速度
	for (int i = 0; i<64; i++)   
	{
		i_x[i] = 0;
		i_y[i] = 0;
	}
	KnightTour_Visit();

}

CKnightTourView::~CKnightTourView()
{
}

BOOL CKnightTourView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 500;
	cs.cy = 500;


	return CView::PreCreateWindow(cs);
}

// CKnightTourView 绘制

void CKnightTourView::OnDraw(CDC* pDC)
{
	CKnightTourDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	for (int i = 1; i <= 9; i++)
	{
		pDC->MoveTo(width, width*i);
		pDC->LineTo(width * 9, width*i);
	}
	for (int j = 1; j <= 9; j++)
	{
		pDC->MoveTo(width*j, width);
		pDC->LineTo(width*j, width * 9);
	}

	CString S, T, T_x, T_y,TT1, TT2,T_a;
	for (int i = 0; i<Step; i++)
	{
		if (Qipan[i_x[i] - 1][i_y[i] - 1] != 0)
		{
			CBrush brush;
			brush.CreateSolidBrush(RGB(0, 255, 0));//绿色表示遍历完
			pDC->SelectObject(&brush);
			pDC->Rectangle(width*i_x[i], width*i_y[i],
				width*(i_x[i] + 1), width*(i_y[i] + 1));
		}
	}
	//画棋子
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(m_x*width + nR, m_y*width + nR,
		(m_x + 1)*width - nR, (m_y + 1)*width - nR);
	
	pDC->TextOut( width *16, 2 * width-10 , _T("注意 请先设置速度！！！"));
	T_x.Format(_T("此 时 的 X 轴 坐 标 : %d"), m_x);
	pDC->TextOut(width * 11, width * 3, T_x);
	T_y.Format(_T("此 时 的 Y 轴 坐 标 : %d"), m_y);
	pDC->TextOut(width * 11, width * 4, T_y);
	T.Format(_T("总 步 数 为: %d"), count);
	pDC->TextOut(width * 11, width * 5, T);
	/*	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(150,255,150));
	pDC->SelectObject( &pen );*/
	pDC->TextOut(m_x * width + 12, m_y * width + 12, _T("骑"));
	pDC->TextOut(11 * width, 6 * width + 12, _T("各 步 是 ："));
	pDC->TextOut(11 * width - 10, 7 * width, _T("x"));
	pDC->TextOut(11 * width - 10, 8 * width - 10, _T("y"));
	if (count == 64)
	{
		for (int i = 0;i < 64;i++)
		{
			TT1.Format(_T("%d"), i_x[i]);
			pDC->TextOut(11 * width + i * 10, 7 * width, TT1);
			TT2.Format(_T("%d"), i_y[i]);
			pDC->TextOut(11 * width + i * 10, 8 * width - 10, TT2);
		}
	}
}


// CKnightTourView 打印

BOOL CKnightTourView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKnightTourView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CKnightTourView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CKnightTourView 诊断

#ifdef _DEBUG
void CKnightTourView::AssertValid() const
{
	CView::AssertValid();
}

void CKnightTourView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKnightTourDoc* CKnightTourView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKnightTourDoc)));
	return (CKnightTourDoc*)m_pDocument;
}
#endif //_DEBUG


// CKnightTourView 消息处理程序


void CKnightTourView::OnMenuNewstartpos()//设置起始位置
{
	// TODO:  在此添加命令处理程序代码
	
	count = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
			Qipan[i][j] = 0;
	for (int i = 0; i<64; i++)
	{
		i_x[i] = 0;
		i_y[i] = 0;
	}
	Step = 0;

	NewStartPosition dlgST;
	dlgST.m_nX = m_x;
	dlgST.m_nY = m_y;

	if (dlgST.DoModal() == IDOK)
	{
		m_x = dlgST.m_nX;//坐标赋值
		m_y = dlgST.m_nY;
	}
	KnightTour_Visit();
	Invalidate();
}

void CKnightTourView::OnMenuSpeed()//遍历速度控制
{
	int nspa[4] = {2000, 1000, 500, 100};
	KillTimer(1);
	DialogSpeed speed;
	if (speed.DoModal() == IDOK) {
		ntimerms = nspa[speed.nspeedindex];
	}
	else {
		ntimerms = 2000;
	}
	
}


void CKnightTourView::OnMenuEnd()
{
	// TODO:  在此添加命令处理程序代码
	KillTimer(1);
}


void CKnightTourView::OnMenuStart()
{
	// TODO:  在此添加命令处理程序代码
#if 0

	count = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
			Qipan[i][j] = 0;
	for (int i = 0; i<64; i++)
	{
		i_x[i] = 0;
		i_y[i] = 0;
	}
	Step = 0;

#endif
	this->SetTimer(1, ntimerms, NULL);    //设置定时器
	//KnightTour_Visit();
}
void CKnightTourView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}

void CKnightTourView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (count >= 64)
	{
		KillTimer(1);
		return;
	}
	KnightTour_Move(i_x[Step], i_y[Step]);
	Step++;
	CView::OnTimer(nIDEvent);
}
void CKnightTourView::KnightTour_Move(int a, int b)
{
	count++;//棋子移动
	m_x = a;
	m_y = b;
	Invalidate();
}

void CKnightTourView::KnightTour_Visit()
{
	int i, j, start, step = 0, order;
	start = 0;    //从0号着法开始顺序检查
	do
	{
#if 1
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++)
				Qipan[i][j] = 0;        //棋盘清零
		for (i = 0; i<64; i++)
		{
			i_x[i] = 0;
			i_y[i] = 0;
		}
#endif
		Qipan[m_x - 1][m_y - 1] = 1;//已经过
		i = m_x - 1;
		j = m_y - 1;
		i_x[step] = m_x;
		i_y[step] = m_y;
		for (step = 2; step <= 64; step++)
		{
			order = Select_NextExit(i, j, start);
			if (order == -1)
				break;                   
			i = i + Forward[order][0];   //前进
			j = j + Forward[order][1];
			Step++;
			i_x[Step] = i + 1;
			i_y[Step] = j + 1;
			Qipan[i][j] = 1;    //标记已走过
		}
		if (step > 64)
			break;        
		start++;        //序号增1
	} while (step <= 64);
	Step = 0;
}

int CKnightTourView::Select_NextExit(int i, int j, int start)
{
	int   min_nexit, nexit, temp, a[8], b[8], k, result;
	nexit = Exit_Number(i, j, start, a);    //确定出口个数
	if (nexit == 0)
		return(-1);     
	for (min_nexit = 9, k = 0; k < nexit; k++)   //逐一考察各个出口
	{
		temp = Exit_Number(i + Forward[a[k]][0], j + Forward[a[k]][1], start, b);//start用以对出口数相同的进行顺序排列
		if (temp < min_nexit)
		{
			min_nexit = temp;
			result = a[k];
		}
	}
	return result;//返回最小的
}

int CKnightTourView::Exit_Number(int i, int j, int start, int array[])//求取出口总数
{
	int a, b, k, count;
	for (count = k = 0; k < 8; k++)
	{
		a = i + Forward[(start + k) % 8][0];
		b = j + Forward[(start + k) % 8][1];
		if ((a >= 0 && a < 8) && (b >= 0 && b < 8) && Qipan[a][b] == 0)//如果在棋盘范围内就进入数组
			array[count++] = (start + k) % 8;
	}
	return count;        
}

