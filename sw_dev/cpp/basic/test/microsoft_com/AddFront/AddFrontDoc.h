// AddFrontDoc.h : CAddFrontDoc Ŭ������ �������̽�
//


#pragma once


class CAddFrontDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAddFrontDoc();
	DECLARE_DYNCREATE(CAddFrontDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CAddFrontDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

	// ������ OLE ����ġ �� �Լ�

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


