// AddFront_byAttrib.h : AddFront_byAttrib ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "AddFront_byAttrib_i.h"


// CAddFront_byAttribApp:
// �� Ŭ������ ������ ���ؼ��� AddFront_byAttrib.cpp�� �����Ͻʽÿ�.
//

class CAddFront_byAttribApp : public CWinApp
{
public:
	CAddFront_byAttribApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	COleTemplateServer m_server;
		// ���� ����⿡ ���� ���� ��ü�Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	BOOL ExitInstance(void);
};

extern CAddFront_byAttribApp theApp;