// opencv_winDoc.cpp : Copencv_winDoc Ŭ������ ����
//

#include "stdafx.h"
#include "opencv_win.h"

#include "opencv_winDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Copencv_winDoc

IMPLEMENT_DYNCREATE(Copencv_winDoc, CDocument)

BEGIN_MESSAGE_MAP(Copencv_winDoc, CDocument)
END_MESSAGE_MAP()


// Copencv_winDoc ����/�Ҹ�

Copencv_winDoc::Copencv_winDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

Copencv_winDoc::~Copencv_winDoc()
{
}

BOOL Copencv_winDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// Copencv_winDoc serialization

void Copencv_winDoc::Serialize(CArchive& ar)
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


// Copencv_winDoc ����

#ifdef _DEBUG
void Copencv_winDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Copencv_winDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Copencv_winDoc ���
