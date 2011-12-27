// AddBack.h : CAddBack�� �����Դϴ�.

#pragma once
#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "AddBackServer.h"
#include "_IAddBackEvents_CP.h"
#include "IAddBackEvents_CP.H"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "���� ������ COM ��ü�� ��ü DCOM ������ �������� �ʴ� Windows Mobile �÷����� ���� Windows CE �÷������� ����� �������� �ʽ��ϴ�. ATL�� ���� ������ COM ��ü�� ������ �����ϰ� ���� ������ COM ��ü ������ ����� �� �ֵ��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA�� �����Ͻʽÿ�. rgs ������ ������ ���� DCOM Windows CE�� �ƴ� �÷������� �����Ǵ� ������ ������ ���̹Ƿ� 'Free'�� �����Ǿ� �ֽ��ϴ�."
#endif



// CAddBack

class ATL_NO_VTABLE CAddBack :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAddBack, &CLSID_AddBack>,
	public IConnectionPointContainerImpl<CAddBack>,
	public CProxy_IAddBackEvents<CAddBack>,
	public IDispatchImpl<IAddBack, &IID_IAddBack, &LIBID_AddBackServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public CProxyIAddBackEvents<CAddBack>
{
public:
	CAddBack()
	{
		sum_ = 0;
		addEnd_ = 10;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADDBACK)


BEGIN_COM_MAP(CAddBack)
	COM_INTERFACE_ENTRY(IAddBack)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAddBack)
	CONNECTION_POINT_ENTRY(__uuidof(IAddBackEvents))
	CONNECTION_POINT_ENTRY(__uuidof(_IAddBackEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_AddEnd)(SHORT* pVal);
	STDMETHOD(put_AddEnd)(SHORT newVal);
	STDMETHOD(get_Sum)(SHORT* pVal);
	STDMETHOD(Add)(void);
	STDMETHOD(AddTen)(void);
	STDMETHOD(Clear)(void);

private:
	void FireChangedAddEnd();
	void FireChangedSum();

private:
	SHORT sum_;
	SHORT addEnd_;
};

OBJECT_ENTRY_AUTO(__uuidof(AddBack), CAddBack)
