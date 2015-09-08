#pragma once


// CEditOrderDlg dialog

class CEditOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditOrderDlg)

public:
	CEditOrderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditOrderDlg();

// Dialog Data
	enum { IDD = IDD_DLG_BAT_EDITORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_payedMoney;
	float m_discount;
	int m_iOrderStatus;
    int m_iOrderType;
	CComboBox m_DlgOrderStatus;
	CComboBox m_DlgOrderType;
    CString m_OrderID;
	int m_iEditType;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	BOOL m_StatusChecked;
	BOOL m_TypeChecked;
	BOOL m_discountChecked;
	BOOL m_PayedChecked;
	afx_msg void OnBnClickedCheckStatus();
	afx_msg void OnBnClickedCheckType();
	afx_msg void OnBnClickedCheckDiscount();
	afx_msg void OnBnClickedCheckPayedmoney();
};
