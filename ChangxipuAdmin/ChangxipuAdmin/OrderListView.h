#pragma once

#include <map>
#include "OrderItem.h"


using namespace std;
// COrderListView view

class COrderListView : public CListView
{
	DECLARE_DYNCREATE(COrderListView)

protected:
	COrderListView();           // protected constructor used by dynamic creation
	virtual ~COrderListView();
public:
	COrderItem m_curActiveOrder;
	int m_listCurSel;
private:
	CFont m_fontItem;
	int   m_iRecordNum;
	CString m_OrderListQueryStr;
	CString m_OrderListQueryStrEnd;
    CString m_OrderListConditionStr;

    CString m_CurSelOrderString;
	CString m_CurSelOrderCellString;

	typedef map<int,COrderItem> ListIDOrderMap;
	ListIDOrderMap m_selectedOrder;
	
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg LRESULT OnOrderShowChange(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	int getCurrentListSelectedIndex();
	void ReDrawList();
	virtual void OnInitialUpdate();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateEditOrder(CCmdUI *pCmdUI);
	afx_msg void OnEditOrder();
	afx_msg void OnMenuEditOrder();
	afx_msg void OnMenuCpyOrderinfo();
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuCpyCell();
};


