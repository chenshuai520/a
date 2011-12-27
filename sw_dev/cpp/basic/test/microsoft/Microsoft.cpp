// Microsoft.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "Microsoft.h"
#include "MainFrm.h"

#include "MicrosoftDoc.h"
#include "MicrosoftView.h"

#include "ConsoleWindow.h"
#include <string>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicrosoftApp

BEGIN_MESSAGE_MAP(CMicrosoftApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMicrosoftApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMicrosoftApp ����

CMicrosoftApp::CMicrosoftApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CMicrosoftApp ��ü�Դϴ�.

CMicrosoftApp theApp;


// CMicrosoftApp �ʱ�ȭ

BOOL CMicrosoftApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.
	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMicrosoftDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CMicrosoftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.

	//------------------------------------------------------------------------------------
	// output debug
	OutputDebugString(_T(">>>>> initialize console window\n"));
	//------------------------------------------------------------------------------------
	// initialize console window
	ConsoleWindow::initialize();

	//------------------------------------------------------------------------------------
	// use console window
	if (ConsoleWindow::getInstance().isValid())
	{
		HANDLE stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		HANDLE stdInputHandle = GetStdHandle(STD_INPUT_HANDLE);
		if (INVALID_HANDLE_VALUE != stdOutputHandle && INVALID_HANDLE_VALUE != stdInputHandle)
		{
			//
			DWORD dwCharsWritten = 0;
			WriteConsole(stdOutputHandle, _T("enter some text ...\n"), 20, &dwCharsWritten, NULL);

			const DWORD dwCharsToRead = 1024;
			DWORD dwCharsRead = 0;
			TCHAR buf[dwCharsToRead] = { 0, };
			ReadConsole(stdInputHandle, buf, dwCharsToRead, &dwCharsRead, NULL);
			if (dwCharsRead)
				WriteConsole(stdOutputHandle, buf, dwCharsRead, &dwCharsWritten, NULL);
		}

		//
		std::cout << "enter some text ..." << std::endl;
		std::string str;
		std::getline(std::cin, str);
		if (!str.empty())
			std::cout << str << std::endl;
	}

	return TRUE;
}

int CMicrosoftApp::ExitInstance()
{
	//------------------------------------------------------------------------------------
	// output debug
	OutputDebugString(_T(">>>>> finalize console window\n"));
	//------------------------------------------------------------------------------------
	// finalize console window
	ConsoleWindow::finalize();

	return CWinApp::ExitInstance();
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CMicrosoftApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CMicrosoftApp �޽��� ó����
