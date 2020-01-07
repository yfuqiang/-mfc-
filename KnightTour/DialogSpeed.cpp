// DialogSpeed.cpp : 实现文件
//

#include "stdafx.h"
#include "KnightTour.h"
#include "DialogSpeed.h"
#include "afxdialogex.h"


// DialogSpeed 对话框

IMPLEMENT_DYNAMIC(DialogSpeed, CDialogEx)

DialogSpeed::DialogSpeed(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SPEED, pParent)
	, ssss(0)
{
	nspeedindex = 0;
}

DialogSpeed::~DialogSpeed()
{
}

void DialogSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, ssss);
	DDV_MinMaxInt(pDX, ssss, 0, 3);
	nspeedindex = ssss;//将得到的数组送入nspeedindex
}


BEGIN_MESSAGE_MAP(DialogSpeed, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSpeed::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &DialogSpeed::OnEnChangeEdit1)

END_MESSAGE_MAP()


// DialogSpeed 消息处理程序


void DialogSpeed::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//nspeedindex = m_combox_speed.GetCurSel();
	nspeedindex = ssss;
	CDialogEx::OnOK();
}


void DialogSpeed::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void DialogSpeed::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}
