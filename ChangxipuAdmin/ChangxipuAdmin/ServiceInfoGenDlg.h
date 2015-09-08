#pragma once


// CServiceInfoGenDlg dialog

class CServiceInfoGenDlg : public CDialog
{
	DECLARE_DYNAMIC(CServiceInfoGenDlg)

public:
	CServiceInfoGenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CServiceInfoGenDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SERVICE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_serviceInfo;
	virtual BOOL OnInitDialog();
};
