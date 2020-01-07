#pragma once


// NewStartPosition 对话框

class NewStartPosition : public CDialog
{
	DECLARE_DYNAMIC(NewStartPosition)

public:
	NewStartPosition(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NewStartPosition();

	// 对话框数据
	enum { IDD = IDD_DIALOG_NEWSP };
	int		m_nX;
	int		m_nY;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
