
// KnightTour.h : KnightTour Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKnightTourApp:
// �йش����ʵ�֣������ KnightTour.cpp
//

class CKnightTourApp : public CWinApp
{
public:
	CKnightTourApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKnightTourApp theApp;
