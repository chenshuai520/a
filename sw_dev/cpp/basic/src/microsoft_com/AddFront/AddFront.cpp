// AddFront.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "AddFront.h"
#include "MainFrm.h"

#include "AddFrontDoc.h"
#include "AddFrontView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddFrontApp

BEGIN_MESSAGE_MAP(CAddFrontApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAddFrontApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CAddFrontApp ����

CAddFrontApp::CAddFrontApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CAddFrontApp ��ü�Դϴ�.

CAddFrontApp theApp;
// �� �ĺ��ڴ� ���� ���α׷����� ��������� ������ ���� �������� �����Ǿ����ϴ�.
// Ư�� �ĺ��ڸ� ��ȣ�� ��� ������ �� �ֽ��ϴ�.
CComModule _Module;

// {37C4A7D6-592D-4B68-84AF-3EFDC0EE6460}
static const CLSID clsid =
{ 0x37C4A7D6, 0x592D, 0x4B68, { 0x84, 0xAF, 0x3E, 0xFD, 0xC0, 0xEE, 0x64, 0x60 } };

const GUID CDECL BASED_CODE _tlid =
		{ 0xFE19AE74, 0xD570, 0x4700, { 0xB9, 0xB6, 0xC2, 0x82, 0x49, 0xFC, 0x29, 0x55 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CAddFrontApp �ʱ�ȭ

BOOL CAddFrontApp::InitInstance()
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
	_Module.Init(NULL, NULL);
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
		RUNTIME_CLASS(CAddFrontDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CAddFrontView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// COleTemplateServer�� ���� ���ø��� �����մϴ�.
	//  COleTemplateServer�� OLE �����̳ʸ� ��û�ϴ� ��� ���� ���ø���
	//  ������ ������ ����Ͽ� �� ������
	//  ����ϴ�.
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// ����: SDI ���� ���α׷��� ����ٿ� /Embedding �Ǵ� /Automation��
		//   ���� ��쿡�� ���� ��ü�� ����մϴ�.



	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���� ���α׷��� /Embedding �Ǵ� /Automation ����ġ�� ���۵Ǿ����ϴ�.
	// ���� ���α׷��� �ڵ�ȭ ������ �����մϴ�.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ��� OLE ���� ���͸��� ���� ������ ����մϴ�. �̷��� �ϸ�
		//  OLE ���̺귯���� �ٸ� ���� ���α׷����� ��ü�� ���� �� �ֽ��ϴ�.
		COleTemplateServer::RegisterAll();

		// �� â�� ǥ������ �ʽ��ϴ�.
		return TRUE;
	}
	// ���� ���α׷��� /Unregserver �Ǵ� /Unregister ����ġ�� ���۵Ǿ����ϴ�. 
	// typelibrary�� ��� ����մϴ�. �ٸ� ��� ��Ҵ� ProcessShellCommand()���� �߻��մϴ�.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// ���� ���α׷��� ���� ���������� ���۵Ǿ��ų� �ٸ� ����ġ�� ���۵Ǿ����ϴ�(��: /Register
	// �Ǵ� /Regserver). typelibrary�� �����Ͽ� ������Ʈ�� �׸��� ������Ʈ�մϴ�.
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}

	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	//_Module.Term();

	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	return TRUE;
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
void CAddFrontApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CAddFrontApp �޽��� ó����


int CAddFrontApp::ExitInstance()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	_Module.Term();

	return CWinApp::ExitInstance();
}
