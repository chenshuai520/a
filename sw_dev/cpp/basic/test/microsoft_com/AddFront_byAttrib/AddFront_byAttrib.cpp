// AddFront_byAttrib.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "AddFront_byAttrib.h"
#include "MainFrm.h"

#include "AddFront_byAttribDoc.h"
#include "AddFront_byAttribView.h"
#include <initguid.h>
#include "AddFront_byAttrib_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddFront_byAttribApp


class CAddFront_byAttribModule :
	public CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_AddFront_byAttrib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ADDFRONT_BYATTRIB, "{C93009AF-C806-48AA-ABA6-482B54AFB610}");};

CAddFront_byAttribModule _AtlModule;

BEGIN_MESSAGE_MAP(CAddFront_byAttribApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAddFront_byAttribApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CAddFront_byAttribApp ����

CAddFront_byAttribApp::CAddFront_byAttribApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CAddFront_byAttribApp ��ü�Դϴ�.

CAddFront_byAttribApp theApp;
// �� �ĺ��ڴ� ���� ���α׷����� ��������� ������ ���� �������� �����Ǿ����ϴ�.
// Ư�� �ĺ��ڸ� ��ȣ�� ��� ������ �� �ֽ��ϴ�.

// {FEA675AE-146F-4506-B8D0-225C4D156A31}
static const CLSID clsid =
{ 0xFEA675AE, 0x146F, 0x4506, { 0xB8, 0xD0, 0x22, 0x5C, 0x4D, 0x15, 0x6A, 0x31 } };

const GUID CDECL BASED_CODE _tlid =
		{ 0x7FEA4B43, 0x31D4, 0x4501, { 0xA3, 0xA4, 0x1C, 0xB7, 0x60, 0xE4, 0x5, 0xD6 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CAddFront_byAttribApp �ʱ�ȭ

BOOL CAddFront_byAttribApp::InitInstance()
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
		RUNTIME_CLASS(CAddFront_byAttribDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CAddFront_byAttribView));
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
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// CoRegisterClassObject()�� ���� Ŭ���� ���͸��� ����մϴ�.
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)

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
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// ���� ���α׷��� ���� ���������� ���۵Ǿ��ų� �ٸ� ����ġ�� ���۵Ǿ����ϴ�(��: /Register
	// �Ǵ� /Regserver). typelibrary�� �����Ͽ� ������Ʈ�� �׸��� ������Ʈ�մϴ�.
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}

	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
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
void CAddFront_byAttribApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CAddFront_byAttribApp �޽��� ó����


BOOL CAddFront_byAttribApp::ExitInstance(void)
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	return CWinApp::ExitInstance();
}
