// AddFrontDoc.cpp : CAddFrontDoc Ŭ������ ����
//

#include "stdafx.h"
#include "AddFront.h"

#include "AddFrontDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddFrontDoc

IMPLEMENT_DYNCREATE(CAddFrontDoc, CDocument)

BEGIN_MESSAGE_MAP(CAddFrontDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAddFrontDoc, CDocument)
END_DISPATCH_MAP()

// ����: IID_IAddFront�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�. 
//  �� IID�� .IDL ������ dispinterface�� ÷�ε� GUID�� ��ġ�ؾ� �մϴ�.

// {75575FAA-B604-48F5-A0DD-5F0674D05352}
static const IID IID_IAddFront =
{ 0x75575FAA, 0xB604, 0x48F5, { 0xA0, 0xDD, 0x5F, 0x6, 0x74, 0xD0, 0x53, 0x52 } };

BEGIN_INTERFACE_MAP(CAddFrontDoc, CDocument)
	INTERFACE_PART(CAddFrontDoc, IID_IAddFront, Dispatch)
END_INTERFACE_MAP()


// CAddFrontDoc ����/�Ҹ�

CAddFrontDoc::CAddFrontDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

	EnableAutomation();

	AfxOleLockApp();
}

CAddFrontDoc::~CAddFrontDoc()
{
	AfxOleUnlockApp();
}

BOOL CAddFrontDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CAddFrontDoc serialization

void CAddFrontDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CAddFrontDoc ����

#ifdef _DEBUG
void CAddFrontDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAddFrontDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAddFrontDoc ���
