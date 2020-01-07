#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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


int Forward[8][2] = { { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 },{ -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 } };//����ʿ�Ŀ��ܱ��������������

// CKnightTourView ����/����

CKnightTourView::CKnightTourView()
{
	g_view = this;
	// TODO:  �ڴ˴���ӹ������
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
			Qipan[i][j] = 0; //��ʼ��
	count = 0;
	width = 40;
	nR = 5;      //���Ӱ뾶
	Step = 0;
	m_x = 1;
	m_y = 1;
	ntimerms = 200;//��ʼ�ٶ�
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = 500;
	cs.cy = 500;


	return CView::PreCreateWindow(cs);
}

// CKnightTourView ����

void CKnightTourView::OnDraw(CDC* pDC)
{
	CKnightTourDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

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
			brush.CreateSolidBrush(RGB(0, 255, 0));//��ɫ��ʾ������
			pDC->SelectObject(&brush);
			pDC->Rectangle(width*i_x[i], width*i_y[i],
				width*(i_x[i] + 1), width*(i_y[i] + 1));
		}
	}
	//������
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(m_x*width + nR, m_y*width + nR,
		(m_x + 1)*width - nR, (m_y + 1)*width - nR);
	
	pDC->TextOut( width *16, 2 * width-10 , _T("ע�� ���������ٶȣ�����"));
	T_x.Format(_T("�� ʱ �� X �� �� �� : %d"), m_x);
	pDC->TextOut(width * 11, width * 3, T_x);
	T_y.Format(_T("�� ʱ �� Y �� �� �� : %d"), m_y);
	pDC->TextOut(width * 11, width * 4, T_y);
	T.Format(_T("�� �� �� Ϊ: %d"), count);
	pDC->TextOut(width * 11, width * 5, T);
	/*	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(150,255,150));
	pDC->SelectObject( &pen );*/
	pDC->TextOut(m_x * width + 12, m_y * width + 12, _T("��"));
	pDC->TextOut(11 * width, 6 * width + 12, _T("�� �� �� ��"));
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


// CKnightTourView ��ӡ

BOOL CKnightTourView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKnightTourView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CKnightTourView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CKnightTourView ���

#ifdef _DEBUG
void CKnightTourView::AssertValid() const
{
	CView::AssertValid();
}

void CKnightTourView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKnightTourDoc* CKnightTourView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKnightTourDoc)));
	return (CKnightTourDoc*)m_pDocument;
}
#endif //_DEBUG


// CKnightTourView ��Ϣ�������


void CKnightTourView::OnMenuNewstartpos()//������ʼλ��
{
	// TODO:  �ڴ���������������
	
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
		m_x = dlgST.m_nX;//���긳ֵ
		m_y = dlgST.m_nY;
	}
	KnightTour_Visit();
	Invalidate();
}

void CKnightTourView::OnMenuSpeed()//�����ٶȿ���
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
	// TODO:  �ڴ���������������
	KillTimer(1);
}


void CKnightTourView::OnMenuStart()
{
	// TODO:  �ڴ���������������
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
	this->SetTimer(1, ntimerms, NULL);    //���ö�ʱ��
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
	count++;//�����ƶ�
	m_x = a;
	m_y = b;
	Invalidate();
}

void CKnightTourView::KnightTour_Visit()
{
	int i, j, start, step = 0, order;
	start = 0;    //��0���ŷ���ʼ˳����
	do
	{
#if 1
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++)
				Qipan[i][j] = 0;        //��������
		for (i = 0; i<64; i++)
		{
			i_x[i] = 0;
			i_y[i] = 0;
		}
#endif
		Qipan[m_x - 1][m_y - 1] = 1;//�Ѿ���
		i = m_x - 1;
		j = m_y - 1;
		i_x[step] = m_x;
		i_y[step] = m_y;
		for (step = 2; step <= 64; step++)
		{
			order = Select_NextExit(i, j, start);
			if (order == -1)
				break;                   
			i = i + Forward[order][0];   //ǰ��
			j = j + Forward[order][1];
			Step++;
			i_x[Step] = i + 1;
			i_y[Step] = j + 1;
			Qipan[i][j] = 1;    //������߹�
		}
		if (step > 64)
			break;        
		start++;        //�����1
	} while (step <= 64);
	Step = 0;
}

int CKnightTourView::Select_NextExit(int i, int j, int start)
{
	int   min_nexit, nexit, temp, a[8], b[8], k, result;
	nexit = Exit_Number(i, j, start, a);    //ȷ�����ڸ���
	if (nexit == 0)
		return(-1);     
	for (min_nexit = 9, k = 0; k < nexit; k++)   //��һ�����������
	{
		temp = Exit_Number(i + Forward[a[k]][0], j + Forward[a[k]][1], start, b);//start���ԶԳ�������ͬ�Ľ���˳������
		if (temp < min_nexit)
		{
			min_nexit = temp;
			result = a[k];
		}
	}
	return result;//������С��
}

int CKnightTourView::Exit_Number(int i, int j, int start, int array[])//��ȡ��������
{
	int a, b, k, count;
	for (count = k = 0; k < 8; k++)
	{
		a = i + Forward[(start + k) % 8][0];
		b = j + Forward[(start + k) % 8][1];
		if ((a >= 0 && a < 8) && (b >= 0 && b < 8) && Qipan[a][b] == 0)//��������̷�Χ�ھͽ�������
			array[count++] = (start + k) % 8;
	}
	return count;        
}

