// AddFront_byAttribView.h : CAddFront_byAttribView Ŭ������ �������̽�
//


#pragma once
#include "EventHandler.h"

class CAddFront_byAttribView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CAddFront_byAttribView();
	DECLARE_DYNCREATE(CAddFront_byAttribView)

public:
	enum{ IDD = IDD_ADDFRONT_BYATTRIB_FORM };

// Ư���Դϴ�.
public:
	CAddFront_byAttribDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CAddFront_byAttribView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonAddTen();
	afx_msg void OnBnClickedButtonClear();

private:
	int m_iSum;
	int m_iAddEnd;
	IAddBackPtr addBackPtr_;
	CComObject<CEventHandler>* handlerPtr_;
	DWORD cookie_;
public:
	virtual BOOL DestroyWindow();
};

#ifndef _DEBUG  // AddFront_byAttribView.cpp�� ����� ����
inline CAddFront_byAttribDoc* CAddFront_byAttribView::GetDocument() const
   { return reinterpret_cast<CAddFront_byAttribDoc*>(m_pDocument); }
#endif

