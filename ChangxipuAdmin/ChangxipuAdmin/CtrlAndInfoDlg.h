#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCtrlAndInfoDlg dialog

class CCtrlAndInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CCtrlAndInfoDlg)

public:
	CCtrlAndInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCtrlAndInfoDlg();

// Dialog Data
	enum { IDD = IDD_CTRLDETAILINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ConfirmClothList;
	afx_msg void OnBnClickedBtnAddcloth();
	CString m_DlgOrderInfo;
	CEdit m_MessageLeftCtrl;
};
