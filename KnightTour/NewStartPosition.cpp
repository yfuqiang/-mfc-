// NewStartPosition.cpp : 实现文件
//

#include "stdafx.h"
#include "KnightTour.h"
#include "NewStartPosition.h"
#include "afxdialogex.h"


// NewStartPosition 对话框

IMPLEMENT_DYNAMIC(NewStartPosition, CDialog)

NewStartPosition::NewStartPosition(CWnd* pParent /*=NULL*/)
: CDialog(NewStartPosition::IDD, pParent)
{
	m_nX = 0;
	m_nY = 0;

}

NewStartPosition::~NewStartPosition()
{
}

void NewStartPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewStartPosition)
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDV_MinMaxInt(pDX, m_nX, 1, 8);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	DDV_MinMaxInt(pDX, m_nY, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NewStartPosition, CDialog)
END_MESSAGE_MAP()


// NewStartPosition 消息处理程序