
// KnightTourDoc.cpp : CKnightTourDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
// CKnightTourDoc 构造/析构

CKnightTourDoc::CKnightTourDoc()
{
	// TODO:  在此添加一次性构造代码

}

CKnightTourDoc::~CKnightTourDoc()
{
}

BOOL CKnightTourDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CKnightTourDoc 序列化

void CKnightTourDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		cout << "saving ..." << endl;
		if (g_view) {
			ar << g_view->Step << g_view->count
			   << g_view->width << g_view->nR
			   << g_view->m_x << g_view->m_y;//存入中间数据
			for (int i = 0; i < 64; i++) {
				ar << g_view->i_x[i] << g_view->i_y[i];
			}
			for (int a1 = 0; a1 < 8; a1++)
			{
				for (int a2 = 0; a2 < 8; a2++)
				{
					ar << g_view->Qipan[a1][a2];//存入棋盘当前状态
				}
			}
		}
		
	}
	else
	{
		// TODO:  在此添加加载代码
		cout << "loading ..." << endl;
		if (g_view) {
			ar >> g_view->Step >> g_view->count
			   >> g_view->width >> g_view->nR
				>> g_view->m_x >> g_view->m_y;//读入中间数据
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

// 缩略图的支持
void CKnightTourDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CKnightTourDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CKnightTourDoc 诊断

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


// CKnightTourDoc 命令
