// MicrosoftDoc.h : CMicrosoftDoc Ŭ������ �������̽�
//


#pragma once


class CMicrosoftDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMicrosoftDoc();
	DECLARE_DYNCREATE(CMicrosoftDoc)

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
	virtual ~CMicrosoftDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


