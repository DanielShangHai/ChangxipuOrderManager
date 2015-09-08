#pragma once
#include "afxcmn.h"
#include "OrderClothes.h"


// CViewFrm form view

class CViewFrm : public CFormView
{
	DECLARE_DYNCREATE(CViewFrm)

protected:
	CViewFrm();           // protected constructor used by dynamic creation
	virtual ~CViewFrm();

private:
	CFont m_fontItem;
	int m_iNumofCloth;
	int m_nTotalClothes;
    OrderClothes m_OrderClothes;


public:
	enum { IDD = IDD_CTRLDETAILINFO };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
    CString m_DlgOrderInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg LRESULT OnOrderShowConfirm(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnShowSMSLeft(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_clothDetailList;
	CEdit m_MessageLeftCtrl;
	CComboBox m_timeRange;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnAddcloth();
	afx_msg void OnBnClickedBtnDelcloth();
	afx_msg void OnBnClickedBtnUpdatetoSql();
	afx_msg void OnBnClickedBtnServiceInfo();
};


