// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "OrderListView.h"



#define WM_ORDER_SHOW_CONFIRM            (WM_USER + 3)  // 
#define WM_ORDER_SHOW_CHANGE             (WM_USER + 7)  // 
#define WM_ORDER_SMS_LEFT                (WM_USER + 9)  // 





class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
protected:
	CSplitterWnd m_wndSplitter;
public:
	HWND m_hOrderListView;
	HWND m_hCtrlView;
	COrderListView *m_lpListView;

// 操作
public:

// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


