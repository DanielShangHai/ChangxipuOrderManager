#pragma once


// CAddclothDlg dialog

class CAddclothDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddclothDlg)

public:
	CAddclothDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddclothDlg();

// Dialog Data
	enum { IDD = IDD_DLG_ADD_CLOTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_otherInfo;
	int m_iNumofclothes;
	CString m_color;
	CString m_type;
	afx_msg void OnBnClickedOk();
};
