// opencv_winDoc.h : Copencv_winDoc Ŭ������ �������̽�
//


#pragma once


class Copencv_winDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	Copencv_winDoc();
	DECLARE_DYNCREATE(Copencv_winDoc)

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
	virtual ~Copencv_winDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


