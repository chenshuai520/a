// MicrosoftView.cpp : CMicrosoftView Ŭ������ ����
//

#include "stdafx.h"
#include "Microsoft.h"

#include "MicrosoftDoc.h"
#include "MicrosoftView.h"

#include <mmsystem.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicrosoftView

IMPLEMENT_DYNCREATE(CMicrosoftView, CView)

BEGIN_MESSAGE_MAP(CMicrosoftView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SOUND_SNDPLAYSOUND, &CMicrosoftView::OnSoundSndplaysound)
	ON_COMMAND(ID_SOUND_PLAYSOUND, &CMicrosoftView::OnSoundPlaysound)
END_MESSAGE_MAP()

// CMicrosoftView ����/�Ҹ�

CMicrosoftView::CMicrosoftView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMicrosoftView::~CMicrosoftView()
{
}

BOOL CMicrosoftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMicrosoftView �׸���

void CMicrosoftView::OnDraw(CDC* /*pDC*/)
{
	CMicrosoftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMicrosoftView �μ�

BOOL CMicrosoftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMicrosoftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMicrosoftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMicrosoftView ����

#ifdef _DEBUG
void CMicrosoftView::AssertValid() const
{
	CView::AssertValid();
}

void CMicrosoftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMicrosoftDoc* CMicrosoftView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMicrosoftDoc)));
	return (CMicrosoftDoc*)m_pDocument;
}
#endif //_DEBUG


// CMicrosoftView �޽��� ó����

void CMicrosoftView::OnSoundSndplaysound()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//sndPlaySound(_T(".\\data\\sound\\wmpaud1.wav"), SND_ASYNC);
	sndPlaySound(_T(".\\data\\sound\\oasis.wav"), SND_ASYNC);
	Sleep(1000);
	sndPlaySound(_T(".\\data\\sound\\wmpaud6.wav"), SND_ASYNC);
}

void CMicrosoftView::OnSoundPlaysound()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	PlaySound(_T(".\\data\\sound\\oasis.wav"), NULL, SND_FILENAME);
	Sleep(1000);
	PlaySound(_T(".\\data\\sound\\wmpaud6.wav"), NULL, SND_FILENAME);
}
