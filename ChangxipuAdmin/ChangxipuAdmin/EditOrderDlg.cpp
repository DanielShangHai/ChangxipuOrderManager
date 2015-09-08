// EditOrderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "EditOrderDlg.h"


// CEditOrderDlg dialog

IMPLEMENT_DYNAMIC(CEditOrderDlg, CDialog)

CEditOrderDlg::CEditOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditOrderDlg::IDD, pParent)
	, m_payedMoney(0)
	, m_discount(0)
	, m_StatusChecked(FALSE)
	, m_TypeChecked(FALSE)
	, m_discountChecked(FALSE)
	, m_PayedChecked(FALSE)
{

   m_iOrderStatus = 1;
   m_iOrderType = 0;
   m_discount = 0.0;
   m_payedMoney = 0.0;
   m_iEditType = 0;// single order edit;
}

CEditOrderDlg::~CEditOrderDlg()
{
}

void CEditOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_PAYED, m_payedMoney);
	DDX_Text(pDX, IDC_EDT_DISCOUNT, m_discount);
	DDX_Control(pDX, IDC_CB_ORDERSTATUS, m_DlgOrderStatus);
	DDX_Control(pDX, IDC_CB_ORDERTYPE, m_DlgOrderType);
	DDX_Check(pDX, IDC_CHECK_STATUS, m_StatusChecked);
	DDX_Check(pDX, IDC_CHECK_TYPE, m_TypeChecked);
	DDX_Check(pDX, IDC_CHECK_DISCOUNT, m_discountChecked);
	DDX_Check(pDX, IDC_CHECK_PAYEDMONEY, m_PayedChecked);
}


BEGIN_MESSAGE_MAP(CEditOrderDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_STATUS, &CEditOrderDlg::OnBnClickedCheckStatus)
	ON_BN_CLICKED(IDC_CHECK_TYPE, &CEditOrderDlg::OnBnClickedCheckType)
	ON_BN_CLICKED(IDC_CHECK_DISCOUNT, &CEditOrderDlg::OnBnClickedCheckDiscount)
	ON_BN_CLICKED(IDC_CHECK_PAYEDMONEY, &CEditOrderDlg::OnBnClickedCheckPayedmoney)
END_MESSAGE_MAP()


// CEditOrderDlg message handlers

BOOL CEditOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

 //  if ( 0 == m_iEditType )  //single order edit
   {
	   // TODO:  Add extra initialization here
	   m_DlgOrderStatus.InsertString(0,_T("0-失效"));
	   m_DlgOrderStatus.InsertString(1,_T("1-待审核"));
	   m_DlgOrderStatus.InsertString(2,_T("2-已审核"));
	   m_DlgOrderStatus.InsertString(3,_T("3-已分配收衣员"));
	   m_DlgOrderStatus.InsertString(4,_T("4-已确认衣物数量种类"));
	   m_DlgOrderStatus.InsertString(5,_T("5-洗衣中"));
	   m_DlgOrderStatus.InsertString(6,_T("6-已完成"));
	   m_DlgOrderStatus.InsertString(7,_T("7-已删除"));

	   m_DlgOrderStatus.SetCurSel(m_iOrderStatus);

	   m_DlgOrderType.InsertString(0,_T("正常"));
	   m_DlgOrderType.InsertString(1,_T("免单"));
	   m_DlgOrderType.InsertString(2,_T("优惠"));

	   m_DlgOrderType.SetCurSel(m_iOrderType);

	   m_StatusChecked = TRUE;
	   m_PayedChecked = TRUE;
       m_DlgOrderStatus.EnableWindow(TRUE);       
	   GetDlgItem(IDC_EDT_PAYED)->EnableWindow(TRUE);

       m_DlgOrderType.EnableWindow(FALSE);
       GetDlgItem(IDC_EDT_DISCOUNT)->EnableWindow(FALSE);
	   m_TypeChecked = FALSE;
	   m_discountChecked = FALSE;
   }
   /*
   else
   {
	   m_DlgOrderStatus.InsertString(0,_T("0-失效"));
	   m_DlgOrderStatus.InsertString(1,_T("1-待审核"));
	   m_DlgOrderStatus.InsertString(2,_T("2-已审核"));
	   m_DlgOrderStatus.InsertString(3,_T("3-已分配收衣员"));
	   m_DlgOrderStatus.InsertString(4,_T("4-已确认衣物数量种类"));
	   m_DlgOrderStatus.InsertString(5,_T("5-洗衣中"));
	   m_DlgOrderStatus.InsertString(6,_T("6-已完成"));
	   m_DlgOrderStatus.InsertString(6,_T("7-已删除"));

	   m_DlgOrderStatus.SetCurSel(m_iOrderStatus);

	   m_DlgOrderType.InsertString(0,_T("正常"));
	   m_DlgOrderType.InsertString(1,_T("免单"));
	   m_DlgOrderType.InsertString(2,_T("优惠"));

	   m_DlgOrderType.SetCurSel(m_iOrderType);

	   m_StatusChecked = TRUE;
	   m_PayedChecked = TRUE;
	   m_DlgOrderStatus.EnableWindow(TRUE);       
	   GetDlgItem(IDC_EDT_PAYED)->EnableWindow(TRUE);

	   m_DlgOrderType.EnableWindow(FALSE);
	   GetDlgItem(IDC_EDT_DISCOUNT)->EnableWindow(FALSE);
	   m_TypeChecked = FALSE;
	   m_discountChecked = FALSE;


   }
*/

    GetDlgItem(IDC_STATIC_ORDERID)->SetWindowText(m_OrderID);
     
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditOrderDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    //UpdateData(FALSE);

	m_iOrderStatus = m_DlgOrderStatus.GetCurSel();
	m_iOrderType = m_DlgOrderType.GetCurSel();

	UpdateData(TRUE);
	CDialog::OnOK();
}

void CEditOrderDlg::OnBnClickedCheckStatus()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString str;
	//str.Format(_T("%d"),m_StatusChecked);
	//MessageBox(str);

    if (!m_StatusChecked)
    {
		m_DlgOrderStatus.EnableWindow(FALSE);
    }
	else
	{
        m_DlgOrderStatus.EnableWindow(TRUE);
	}

}

void CEditOrderDlg::OnBnClickedCheckType()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString str;
	//str.Format(_T("%d"),m_TypeChecked);
	//MessageBox(str);

	if (!m_TypeChecked)
	{
		m_DlgOrderType.EnableWindow(FALSE);
	}
	else
	{
		m_DlgOrderType.EnableWindow(TRUE);
	}
}

void CEditOrderDlg::OnBnClickedCheckDiscount()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString str;
	//str.Format(_T("%d"),m_discountChecked);
	//MessageBox(str);

	if (!m_discountChecked)
	{
		GetDlgItem(IDC_EDT_DISCOUNT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDT_DISCOUNT)->EnableWindow(TRUE);
	}
}

void CEditOrderDlg::OnBnClickedCheckPayedmoney()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString str;
	//str.Format(_T("%d"),m_PayedChecked);
	//MessageBox(str);

	if (!m_PayedChecked)
	{
		GetDlgItem(IDC_EDT_PAYED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDT_PAYED)->EnableWindow(TRUE);
	}
}
