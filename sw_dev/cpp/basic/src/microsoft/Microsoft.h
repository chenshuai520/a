// Microsoft.h : Microsoft ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMicrosoftApp:
// �� Ŭ������ ������ ���ؼ��� Microsoft.cpp�� �����Ͻʽÿ�.
//

class CMicrosoftApp : public CWinApp
{
public:
	CMicrosoftApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMicrosoftApp theApp;