#pragma once
#include "afxwin.h"


// DialogSpeed �Ի���

class DialogSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSpeed)

public:
	DialogSpeed(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSpeed();

	int nspeedindex;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPEED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox_speed;
	afx_msg void OnBnClickedOk();
	int ssss;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck1();
};
