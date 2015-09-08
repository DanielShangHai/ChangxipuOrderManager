// ServiceInfoGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "ServiceInfoGenDlg.h"


// CServiceInfoGenDlg dialog

IMPLEMENT_DYNAMIC(CServiceInfoGenDlg, CDialog)

CServiceInfoGenDlg::CServiceInfoGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServiceInfoGenDlg::IDD, pParent)
	, m_serviceInfo(_T(""))
{

}

CServiceInfoGenDlg::~CServiceInfoGenDlg()
{
}

void CServiceInfoGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_serviceInfo);
}


BEGIN_MESSAGE_MAP(CServiceInfoGenDlg, CDialog)
END_MESSAGE_MAP()


// CServiceInfoGenDlg message handlers

BOOL CServiceInfoGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
