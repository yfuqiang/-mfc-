#pragma once
#include "afxwin.h"


// DialogSpeed 对话框

class DialogSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSpeed)

public:
	DialogSpeed(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogSpeed();

	int nspeedindex;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPEED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox_speed;
	afx_msg void OnBnClickedOk();
	int ssss;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck1();
};
