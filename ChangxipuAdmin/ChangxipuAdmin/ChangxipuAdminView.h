// ChangxipuAdminView.h : CChangxipuAdminView ��Ľӿ�
//


#pragma once


class CChangxipuAdminView : public CListView
{
protected: // �������л�����
	CChangxipuAdminView();
	DECLARE_DYNCREATE(CChangxipuAdminView)

private:
	CFont m_fontItem;


// ����
public:
	CChangxipuAdminDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CChangxipuAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // ChangxipuAdminView.cpp �еĵ��԰汾
inline CChangxipuAdminDoc* CChangxipuAdminView::GetDocument() const
   { return reinterpret_cast<CChangxipuAdminDoc*>(m_pDocument); }
#endif

