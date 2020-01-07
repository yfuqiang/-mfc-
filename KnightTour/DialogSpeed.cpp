// DialogSpeed.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KnightTour.h"
#include "DialogSpeed.h"
#include "afxdialogex.h"


// DialogSpeed �Ի���

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
	nspeedindex = ssss;//���õ�����������nspeedindex
}


BEGIN_MESSAGE_MAP(DialogSpeed, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSpeed::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &DialogSpeed::OnEnChangeEdit1)

END_MESSAGE_MAP()


// DialogSpeed ��Ϣ�������


void DialogSpeed::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//nspeedindex = m_combox_speed.GetCurSel();
	nspeedindex = ssss;
	CDialogEx::OnOK();
}


void DialogSpeed::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void DialogSpeed::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
