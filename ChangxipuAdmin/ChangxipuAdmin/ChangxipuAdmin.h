// ChangxipuAdmin.h : ChangxipuAdmin Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChangxipuAdminApp:
// �йش����ʵ�֣������ ChangxipuAdmin.cpp
//

class CChangxipuAdminApp : public CWinApp
{
public:
	CChangxipuAdminApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChangxipuAdminApp theApp;