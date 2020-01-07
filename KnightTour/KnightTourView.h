
// KnightTourView.h : CKnightTourView ��Ľӿ�
//

#pragma once


class CKnightTourView : public CView
{
protected: // �������л�����
	CKnightTourView();
	DECLARE_DYNCREATE(CKnightTourView)
	int Qipan[8][8];   //��������
	int count;       //����������  
	int width;       //���ӿ��
	int nR;     //���Ӱ뾶
	int Step;        //���ڼ�¼
	int m_x;      //��ǰX��λ��
	int m_y;      //��ǰY��λ��
	int i_y[64];  //�����ʿ���ߵ�˳��
	int i_x[64];
	int ntimerms;//�ٶ�

// ����
public:
	CKnightTourDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
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

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // KnightTourView.cpp �еĵ��԰汾
inline CKnightTourDoc* CKnightTourView::GetDocument() const
   { return reinterpret_cast<CKnightTourDoc*>(m_pDocument); }
#endif

