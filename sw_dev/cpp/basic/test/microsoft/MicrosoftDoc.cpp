// MicrosoftDoc.cpp : CMicrosoftDoc Ŭ������ ����
//

#include "stdafx.h"
#include "Microsoft.h"

#include "MicrosoftDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicrosoftDoc

IMPLEMENT_DYNCREATE(CMicrosoftDoc, CDocument)

BEGIN_MESSAGE_MAP(CMicrosoftDoc, CDocument)
END_MESSAGE_MAP()


// CMicrosoftDoc ����/�Ҹ�

CMicrosoftDoc::CMicrosoftDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMicrosoftDoc::~CMicrosoftDoc()
{
}

BOOL CMicrosoftDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMicrosoftDoc serialization

void CMicrosoftDoc::Serialize(CArchive& ar)
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


// CMicrosoftDoc ����

#ifdef _DEBUG
void CMicrosoftDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMicrosoftDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMicrosoftDoc ���
