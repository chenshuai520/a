// AddFront.h : AddFront ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CAddFrontApp:
// �� Ŭ������ ������ ���ؼ��� AddFront.cpp�� �����Ͻʽÿ�.
//

class CAddFrontApp : public CWinApp
{
public:
	CAddFrontApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	COleTemplateServer m_server;
		// ���� ����⿡ ���� ���� ��ü�Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CAddFrontApp theApp;