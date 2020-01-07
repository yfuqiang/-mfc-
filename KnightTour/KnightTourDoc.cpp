
// KnightTourDoc.cpp : CKnightTourDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "KnightTour.h"
#endif

#include "KnightTourDoc.h"
#include "KnightTourView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKnightTourDoc
extern CKnightTourView* g_view;

IMPLEMENT_DYNCREATE(CKnightTourDoc, CDocument)

BEGIN_MESSAGE_MAP(CKnightTourDoc, CDocument)
END_MESSAGE_MAP()

using namespace std;
// CKnightTourDoc ����/����

CKnightTourDoc::CKnightTourDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CKnightTourDoc::~CKnightTourDoc()
{
}

BOOL CKnightTourDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CKnightTourDoc ���л�

void CKnightTourDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
		cout << "saving ..." << endl;
		if (g_view) {
			ar << g_view->Step << g_view->count
			   << g_view->width << g_view->nR
			   << g_view->m_x << g_view->m_y;//�����м�����
			for (int i = 0; i < 64; i++) {
				ar << g_view->i_x[i] << g_view->i_y[i];
			}
			for (int a1 = 0; a1 < 8; a1++)
			{
				for (int a2 = 0; a2 < 8; a2++)
				{
					ar << g_view->Qipan[a1][a2];//�������̵�ǰ״̬
				}
			}
		}
		
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
		cout << "loading ..." << endl;
		if (g_view) {
			ar >> g_view->Step >> g_view->count
			   >> g_view->width >> g_view->nR
				>> g_view->m_x >> g_view->m_y;//�����м�����
			for (int i = 0; i < 64; i++) {
				ar >> g_view->i_x[i] >> g_view->i_y[i];
			}
			for (int a1 = 0; a1 < 8; a1++)
			{
				for (int a2 = 0; a2 < 8; a2++)
				{
					ar >> g_view->Qipan[a1][a2];
				}
			}
			
		}
		
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CKnightTourDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CKnightTourDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CKnightTourDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKnightTourDoc ���

#ifdef _DEBUG
void CKnightTourDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKnightTourDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKnightTourDoc ����
