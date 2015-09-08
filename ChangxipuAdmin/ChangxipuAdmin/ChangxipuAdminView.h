// ChangxipuAdminView.h : CChangxipuAdminView 类的接口
//


#pragma once


class CChangxipuAdminView : public CListView
{
protected: // 仅从序列化创建
	CChangxipuAdminView();
	DECLARE_DYNCREATE(CChangxipuAdminView)

private:
	CFont m_fontItem;


// 属性
public:
	CChangxipuAdminDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CChangxipuAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // ChangxipuAdminView.cpp 中的调试版本
inline CChangxipuAdminDoc* CChangxipuAdminView::GetDocument() const
   { return reinterpret_cast<CChangxipuAdminDoc*>(m_pDocument); }
#endif

