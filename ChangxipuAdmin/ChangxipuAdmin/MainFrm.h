// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include "OrderListView.h"



#define WM_ORDER_SHOW_CONFIRM            (WM_USER + 3)  // 
#define WM_ORDER_SHOW_CHANGE             (WM_USER + 7)  // 
#define WM_ORDER_SMS_LEFT                (WM_USER + 9)  // 





class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CSplitterWnd m_wndSplitter;
public:
	HWND m_hOrderListView;
	HWND m_hCtrlView;
	COrderListView *m_lpListView;

// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


