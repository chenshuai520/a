// opencv_win.h : opencv_win ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// Copencv_winApp:
// �� Ŭ������ ������ ���ؼ��� opencv_win.cpp�� �����Ͻʽÿ�.
//

class Copencv_winApp : public CWinApp
{
public:
	Copencv_winApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Copencv_winApp theApp;