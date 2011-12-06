// opencv_winView.cpp : Copencv_winView Ŭ������ ����
//

#include "stdafx.h"
#include "opencv_win.h"

#include "opencv_winDoc.h"
#include "opencv_winView.h"

#include <opencv/highgui.h>
//#include <opencv/cvcam.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Copencv_winView

IMPLEMENT_DYNCREATE(Copencv_winView, CView)

BEGIN_MESSAGE_MAP(Copencv_winView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPENCVCAM_STARTCAM, &Copencv_winView::OnOpencvcamStartcam)
	ON_COMMAND(ID_OPENCVCAM_STOPCAM, &Copencv_winView::OnOpencvcamStopcam)
END_MESSAGE_MAP()

// Copencv_winView ����/�Ҹ�

Copencv_winView::Copencv_winView()
: visionSensor_(320, 240)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Copencv_winView::~Copencv_winView()
{
}

BOOL Copencv_winView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Copencv_winView �׸���

void Copencv_winView::OnDraw(CDC* /*pDC*/)
{
	Copencv_winDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// Copencv_winView �μ�

BOOL Copencv_winView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Copencv_winView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Copencv_winView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// Copencv_winView ����

#ifdef _DEBUG
void Copencv_winView::AssertValid() const
{
	CView::AssertValid();
}

void Copencv_winView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Copencv_winDoc* Copencv_winView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Copencv_winDoc)));
	return (Copencv_winDoc*)m_pDocument;
}
#endif //_DEBUG


// Copencv_winView �޽��� ó����

void Copencv_winView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void Copencv_winView::OnOpencvcamStartcam()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!visionSensor_.isInitialized())
	{
		const int camCount = cvcamGetCamerasCount();
		if (0 == camCount)
		{
			AfxMessageBox(_T("available camera not found"), MB_OK | MB_ICONSTOP);
			return;
		}
		const int camId = 0;
/*
		int* selectedCamIndexes;
		const int selectedCamCount = cvcamSelectCamera(&selectedCamIndexes);
		if (0 == selectedCamCount)
		{
			AfxMessageBox(_T("any cam failed to be connected"), MB_OK | MB_ICONSTOP);
			return;
		}
		const int camId = selectedCamIndexes[0];
*/
		visionSensor_.setSensorId(camId);
		visionSensor_.setWindowHandle((void*)&m_hWnd);

		visionSensor_.initSystem();
	}

	visionSensor_.startCapturing();
}

void Copencv_winView::OnOpencvcamStopcam()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	visionSensor_.stopCapturing();
	visionSensor_.reset();
}
