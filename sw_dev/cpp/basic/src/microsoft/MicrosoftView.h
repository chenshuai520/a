// MicrosoftView.h : CMicrosoftView Ŭ������ �������̽�
//


#pragma once


class CMicrosoftView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMicrosoftView();
	DECLARE_DYNCREATE(CMicrosoftView)

// Ư���Դϴ�.
public:
	CMicrosoftDoc* GetDocument() const;

// �۾��Դϴ�.
public:

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
	virtual ~CMicrosoftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSoundSndplaysound();
public:
	afx_msg void OnSoundPlaysound();
};

#ifndef _DEBUG  // MicrosoftView.cpp�� ����� ����
inline CMicrosoftDoc* CMicrosoftView::GetDocument() const
   { return reinterpret_cast<CMicrosoftDoc*>(m_pDocument); }
#endif

