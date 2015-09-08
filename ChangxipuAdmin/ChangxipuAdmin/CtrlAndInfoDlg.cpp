// CtrlAndInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "CtrlAndInfoDlg.h"


// CCtrlAndInfoDlg dialog

IMPLEMENT_DYNAMIC(CCtrlAndInfoDlg, CDialog)

CCtrlAndInfoDlg::CCtrlAndInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtrlAndInfoDlg::IDD, pParent)
	, m_DlgOrderInfo(_T(""))
{

}

CCtrlAndInfoDlg::~CCtrlAndInfoDlg()
{
}

void CCtrlAndInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORDER_CLOTH_CFM_LIST, m_ConfirmClothList);
	DDX_Text(pDX, IDC_EDIT_ORDER_INFO, m_DlgOrderInfo);
	DDX_Control(pDX, IDC_EDT_MESSAGE_LEFT, m_MessageLeftCtrl);
}


BEGIN_MESSAGE_MAP(CCtrlAndInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CCtrlAndInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_ADDCLOTH, &CCtrlAndInfoDlg::OnBnClickedBtnAddcloth)
END_MESSAGE_MAP()


// CCtrlAndInfoDlg message handlers

void CCtrlAndInfoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("aaaa"));
}

void CCtrlAndInfoDlg::OnBnClickedBtnAddcloth()
{
	// TODO: Add your control notification handler code here

   

}
