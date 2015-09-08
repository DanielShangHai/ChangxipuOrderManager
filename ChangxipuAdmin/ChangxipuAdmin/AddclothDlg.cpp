// AddclothDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "AddclothDlg.h"


// CAddclothDlg dialog

IMPLEMENT_DYNAMIC(CAddclothDlg, CDialog)

CAddclothDlg::CAddclothDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddclothDlg::IDD, pParent)
	, m_otherInfo(_T(""))
	, m_iNumofclothes(0)
	, m_color(_T(""))
	, m_type(_T(""))
{

}

CAddclothDlg::~CAddclothDlg()
{
}

void CAddclothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OTHERINFO, m_otherInfo);
	DDX_Text(pDX, IDC_EDIT_NUM, m_iNumofclothes);
	DDX_Text(pDX, IDC_EDT_COLOR, m_color);
	DDX_Text(pDX, IDC_EDT_TYPE, m_type);
}


BEGIN_MESSAGE_MAP(CAddclothDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddclothDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddclothDlg message handlers

void CAddclothDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iNumofclothes<1)
	{
		MessageBox(_T("衣物数量必须大于0"));
		return;
	}
	OnOK();
}
