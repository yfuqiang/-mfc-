
// KnightTourView.h : CKnightTourView 类的接口
//

#pragma once


class CKnightTourView : public CView
{
protected: // 仅从序列化创建
	CKnightTourView();
	DECLARE_DYNCREATE(CKnightTourView)
	int Qipan[8][8];   //定义棋盘
	int count;       //步数计数器  
	int width;       //格子宽度
	int nR;     //棋子半径
	int Step;        //用于记录
	int m_x;      //当前X轴位置
	int m_y;      //当前Y轴位置
	int i_y[64];  //存放骑士所走的顺序
	int i_x[64];
	int ntimerms;//速度

// 特性
public:
	CKnightTourDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	int Exit_Number(int  i, int j, int start, int array[]);
	int Select_NextExit(int i, int j, int start);
	void KnightTour_Visit();
	void KnightTour_Move(int a, int b);
	virtual ~CKnightTourView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuNewstartpos();
	afx_msg void OnMenuSpeed();
	afx_msg void OnMenuEnd();
	afx_msg void OnMenuStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
};

#ifndef _DEBUG  // KnightTourView.cpp 中的调试版本
inline CKnightTourDoc* CKnightTourView::GetDocument() const
   { return reinterpret_cast<CKnightTourDoc*>(m_pDocument); }
#endif

