#pragma once


// NewStartPosition �Ի���

class NewStartPosition : public CDialog
{
	DECLARE_DYNAMIC(NewStartPosition)

public:
	NewStartPosition(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NewStartPosition();

	// �Ի�������
	enum { IDD = IDD_DIALOG_NEWSP };
	int		m_nX;
	int		m_nY;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
