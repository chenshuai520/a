// AddFront_byAttribDoc.h : CAddFront_byAttribDoc Ŭ������ �������̽�
//


#pragma once


class CAddFront_byAttribDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAddFront_byAttribDoc();
	DECLARE_DYNCREATE(CAddFront_byAttribDoc)

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
	virtual ~CAddFront_byAttribDoc();
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


