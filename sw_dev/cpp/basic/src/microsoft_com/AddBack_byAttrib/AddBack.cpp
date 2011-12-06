// AddBack.cpp : CAddBack�� �����Դϴ�.

#include "stdafx.h"
#include "AddBack.h"


// CAddBack


STDMETHODIMP CAddBack::get_AddEnd(SHORT* pVal)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	*pVal = addEnd_;

	return S_OK;
}

STDMETHODIMP CAddBack::put_AddEnd(SHORT newVal)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	addEnd_ = newVal;
	__raise ChangedAddEnd(addEnd_);

	return S_OK;
}

STDMETHODIMP CAddBack::get_Sum(SHORT* pVal)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	*pVal = sum_;

	return S_OK;
}

STDMETHODIMP CAddBack::Add(void)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	sum_ += addEnd_;
	__raise ChangedSum(sum_);

	return S_OK;
}

STDMETHODIMP CAddBack::AddTen(void)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	sum_ += 10;
	__raise ChangedSum(sum_);

	return S_OK;
}

STDMETHODIMP CAddBack::Clear(void)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	sum_ = 0;
	__raise ChangedSum(sum_);

	return S_OK;
}
