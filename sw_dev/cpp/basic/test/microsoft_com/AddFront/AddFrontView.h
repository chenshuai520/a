// AddFrontView.h : CAddFrontView Ŭ������ �������̽�
//


#pragma once
#include "afxwin.h"
#include "EventHandler.h"

class CAddFrontView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CAddFrontView();
	DECLARE_DYNCREATE(CAddFrontView)

public:
	enum{ IDD = IDD_ADDFRONT_FORM };

// Ư���Դϴ�.
public:
	CAddFrontDoc* GetDocument() const;

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
	virtual ~CAddFrontView();
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

#ifndef _DEBUG  // AddFrontView.cpp�� ����� ����
inline CAddFrontDoc* CAddFrontView::GetDocument() const
   { return reinterpret_cast<CAddFrontDoc*>(m_pDocument); }
#endif

