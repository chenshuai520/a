// AddFront_byAttribDoc.cpp : CAddFront_byAttribDoc Ŭ������ ����
//

#include "stdafx.h"
#include "AddFront_byAttrib.h"

#include "AddFront_byAttribDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddFront_byAttribDoc

IMPLEMENT_DYNCREATE(CAddFront_byAttribDoc, CDocument)

BEGIN_MESSAGE_MAP(CAddFront_byAttribDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAddFront_byAttribDoc, CDocument)
END_DISPATCH_MAP()

// ����: IID_IAddFront_byAttrib�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�. 
//  �� IID�� .IDL ������ dispinterface�� ÷�ε� GUID�� ��ġ�ؾ� �մϴ�.

// {A855185B-71B9-4228-87A8-90AC95A08C8F}
static const IID IID_IAddFront_byAttrib =
{ 0xA855185B, 0x71B9, 0x4228, { 0x87, 0xA8, 0x90, 0xAC, 0x95, 0xA0, 0x8C, 0x8F } };

BEGIN_INTERFACE_MAP(CAddFront_byAttribDoc, CDocument)
	INTERFACE_PART(CAddFront_byAttribDoc, IID_IAddFront_byAttrib, Dispatch)
END_INTERFACE_MAP()


// CAddFront_byAttribDoc ����/�Ҹ�

CAddFront_byAttribDoc::CAddFront_byAttribDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

	EnableAutomation();

	AfxOleLockApp();
}

CAddFront_byAttribDoc::~CAddFront_byAttribDoc()
{
	AfxOleUnlockApp();
}

BOOL CAddFront_byAttribDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CAddFront_byAttribDoc serialization

void CAddFront_byAttribDoc::Serialize(CArchive& ar)
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


// CAddFront_byAttribDoc ����

#ifdef _DEBUG
void CAddFront_byAttribDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAddFront_byAttribDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAddFront_byAttribDoc ���
