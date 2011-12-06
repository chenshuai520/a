// opencv_winView.h : Copencv_winView Ŭ������ �������̽�
//


#pragma once

#include "OpenCvVisionSensor.h"

class Copencv_winView : public CView
{
protected: // serialization������ ��������ϴ�.
	Copencv_winView();
	DECLARE_DYNCREATE(Copencv_winView)

// Ư���Դϴ�.
public:
	Copencv_winDoc* GetDocument() const;

// �۾��Դϴ�.
public:

private:
	OpenCvVisionSensor visionSensor_;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~Copencv_winView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpencvcamStartcam();
	afx_msg void OnOpencvcamStopcam();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // opencv_winView.cpp�� ����� ����
inline Copencv_winDoc* Copencv_winView::GetDocument() const
   { return reinterpret_cast<Copencv_winDoc*>(m_pDocument); }
#endif

