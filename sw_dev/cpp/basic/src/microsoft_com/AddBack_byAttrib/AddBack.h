// AddBack.h : CAddBack�� �����Դϴ�.

#pragma once
#include "resource.h"       // �� ��ȣ�Դϴ�.



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "���� ������ COM ��ü�� ��ü DCOM ������ �������� �ʴ� Windows Mobile �÷����� ���� Windows CE �÷������� ����� �������� �ʽ��ϴ�. ATL�� ���� ������ COM ��ü�� ������ �����ϰ� ���� ������ COM ��ü ������ ����� �� �ֵ��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA�� �����Ͻʽÿ�. rgs ������ ������ ���� DCOM Windows CE�� �ƴ� �÷������� �����Ǵ� ������ ������ ���̹Ƿ� 'Free'�� �����Ǿ� �ֽ��ϴ�."
#endif


// IAddBack
[
	object,
	uuid("493B7227-97B4-426D-9F47-B121E0DA6D3B"),
	dual,	helpstring("IAddBack Interface"),
	pointer_default(unique)
]
__interface IAddBack : IDispatch
{
	[propget, id(1), helpstring("�Ӽ� AddEnd")] HRESULT AddEnd([out, retval] SHORT* pVal);
	[propput, id(1), helpstring("�Ӽ� AddEnd")] HRESULT AddEnd([in] SHORT newVal);
	[propget, id(2), helpstring("�Ӽ� Sum")] HRESULT Sum([out, retval] SHORT* pVal);
	[id(3), helpstring("�޼��� Add")] HRESULT Add(void);
	[id(4), helpstring("�޼��� AddTen")] HRESULT AddTen(void);
	[id(5), helpstring("�޼��� Clear")] HRESULT Clear(void);
};


// _IAddBackEvents
[
	dispinterface,
	uuid("CB43E856-D48D-4688-92EC-060F5C2EDDCC"),
	helpstring("_IAddBackEvents Interface")
]
__interface _IAddBackEvents
{
	[id(1), helpstring("ChangedAddEnd �̺�Ʈ")] HRESULT ChangedAddEnd([in] SHORT newVal);
	[id(2), helpstring("ChangedSum �̺�Ʈ")] HRESULT ChangedSum([in] SHORT newVal);
};


// CAddBack

[
	coclass,
	default(IAddBack, _IAddBackEvents),
	threading("apartment"),
	event_source("com"),
	vi_progid("AddBack_byAttrib.AddBack"),
	progid("AddBack_byAttrib.AddBack.1"),
	version(1.0),
	uuid("A6F1D48F-0B55-43CF-8390-516AB184160D"),
	helpstring("AddBack Class")
]
class ATL_NO_VTABLE CAddBack :
	public IAddBack
{
public:
	CAddBack()
	{
		sum_ = 0;
		addEnd_ = 10;
	}

	__event __interface _IAddBackEvents;


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
	SHORT sum_;
	SHORT addEnd_;
};

