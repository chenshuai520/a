// AddFront_byAttribView.cpp : CAddFront_byAttribView Ŭ������ ����
//

#include "stdafx.h"
#include "AddFront_byAttrib.h"

#include "AddFront_byAttribDoc.h"
#include "AddFront_byAttribView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddFront_byAttribView

IMPLEMENT_DYNCREATE(CAddFront_byAttribView, CFormView)

BEGIN_MESSAGE_MAP(CAddFront_byAttribView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddFront_byAttribView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TEN, &CAddFront_byAttribView::OnBnClickedButtonAddTen)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CAddFront_byAttribView::OnBnClickedButtonClear)
END_MESSAGE_MAP()

// CAddFront_byAttribView ����/�Ҹ�

CAddFront_byAttribView::CAddFront_byAttribView()
	: CFormView(CAddFront_byAttribView::IDD)
	, m_iSum(0)
	, m_iAddEnd(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CAddFront_byAttribView::~CAddFront_byAttribView()
{
}

void CAddFront_byAttribView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUM, m_iSum);
	DDX_Text(pDX, IDC_EDIT_ADD_END, m_iAddEnd);
}

BOOL CAddFront_byAttribView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CAddFront_byAttribView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

#if defined(__USE_ADDBACK_DUAL) || defined(__USE_ADDBACK_DISPATCH)
	addBackPtr_ = IAddBackPtr(__uuidof(AddBack));
#elif defined(__USE_ADDBACK_BYATTRIB_DISPATCH)
	addBackPtr_ = IAddBackPtr(__uuidof(CAddBack));
#endif
	CComObject<CEventHandler>::CreateInstance(&handlerPtr_);

	if (!handlerPtr_->HookEvent(addBackPtr_))
	{
		MessageBox(_T("�̺�Ʈ�� ���� �� �����ϴ�."), _T("�̺�Ʈ ����"), MB_OK);
		return;
	}

	m_iAddEnd = addBackPtr_->AddEnd;
	m_iSum = addBackPtr_->Sum;
	UpdateData(FALSE);
}


// CAddFront_byAttribView ����

#ifdef _DEBUG
void CAddFront_byAttribView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAddFront_byAttribView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAddFront_byAttribDoc* CAddFront_byAttribView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAddFront_byAttribDoc)));
	return (CAddFront_byAttribDoc*)m_pDocument;
}
#endif //_DEBUG


// CAddFront_byAttribView �޽��� ó����

void CAddFront_byAttribView::OnBnClickedButtonAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	try
	{
		addBackPtr_->AddEnd = m_iAddEnd;
		addBackPtr_->Add();
		m_iSum = addBackPtr_->Sum;
	}
	catch(const _com_error &e)
	{
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		CString szMsg(_T("������ �߻��߽��ϴ�.!\n"));
		CString szTemp;

		szTemp.Format(_T("�����ڵ�: %081x\n"), e.Error());
		szMsg += szTemp;
		szTemp.Format(_T("��������: %s\n"), e.ErrorMessage());
		szMsg += szTemp;
		szTemp.Format(_T("�����ҽ�: %s\n"), bstrSource.length() ? (LPCTSTR)bstrSource : _T("����"));
		szMsg += szTemp;
		MessageBox(szMsg.GetBuffer(szMsg.GetLength()), _T("���� �߻�"));
	}

	UpdateData(FALSE);
}

void CAddFront_byAttribView::OnBnClickedButtonAddTen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	try
	{
		addBackPtr_->AddTen();
		m_iSum = addBackPtr_->Sum;
	}
	catch(const _com_error &e)
	{
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		CString szMsg(_T("������ �߻��߽��ϴ�.!\n"));
		CString szTemp;

		szTemp.Format(_T("�����ڵ�: %081x\n"), e.Error());
		szMsg += szTemp;
		szTemp.Format(_T("��������: %s\n"), e.ErrorMessage());
		szMsg += szTemp;
		szTemp.Format(_T("�����ҽ�: %s\n"), bstrSource.length() ? (LPCTSTR)bstrSource : _T("����"));
		szMsg += szTemp;
		MessageBox(szMsg.GetBuffer(szMsg.GetLength()), _T("���� �߻�"));
	}

	UpdateData(FALSE);
}

void CAddFront_byAttribView::OnBnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	try
	{
		addBackPtr_->Clear();
		m_iSum = addBackPtr_->Sum;
	}
	catch(const _com_error &e)
	{
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		CString szMsg(_T("������ �߻��߽��ϴ�.!\n"));
		CString szTemp;

		szTemp.Format(_T("�����ڵ�: %081x\n"), e.Error());
		szMsg += szTemp;
		szTemp.Format(_T("��������: %s\n"), e.ErrorMessage());
		szMsg += szTemp;
		szTemp.Format(_T("�����ҽ�: %s\n"), bstrSource.length() ? (LPCTSTR)bstrSource : _T("����"));
		szMsg += szTemp;
		MessageBox(szMsg.GetBuffer(szMsg.GetLength()), _T("���� �߻�"));
	}

	UpdateData(FALSE);
}

BOOL CAddFront_byAttribView::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
#if defined(__USE_ADDBACK_DUAL)
	//handlerPtr_->UnhookEvent(addBackPtr_);
	AtlUnadvise(addBackPtr_, __uuidof(IAddBackEvents), cookie_);
#elif defined(__USE_ADDBACK_DISPATCH) || defined(__USE_ADDBACK_BYATTRIB_DISPATCH)
	handlerPtr_->UnhookEvent(addBackPtr_);
#endif

	handlerPtr_ = 0;
	addBackPtr_ = 0;

	return CFormView::DestroyWindow();
}