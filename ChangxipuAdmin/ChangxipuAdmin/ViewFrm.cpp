// ViewFrm.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "ViewFrm.h"
#include "MainFrm.h"
#include "OrderItem.h"
#include "AddclothDlg.h"
#include "MySQLInterface.h"
#include "OrderListView.h"
#include "ServiceInfoGenDlg.h"
// CViewFrm


typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] = 
{
	{_T("衣服种类"),  170},
	{_T("衣服颜色"),  180},
	{_T("数量"),      110},
	{_T("备注"),      250},
} ;




IMPLEMENT_DYNCREATE(CViewFrm, CFormView)

CViewFrm::CViewFrm()
	: CFormView(CViewFrm::IDD)
	, m_DlgOrderInfo(_T(""))
{

	m_fontItem.CreateFont(   
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体"));

	m_iNumofCloth = 0;
	m_nTotalClothes = 0;
	
}

CViewFrm::~CViewFrm()
{
}

void CViewFrm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORDER_CLOTH_CFM_LIST, m_clothDetailList);
	DDX_Control(pDX, IDC_CB_TIMERANGE, m_timeRange);
	DDX_Text(pDX, IDC_EDIT_ORDER_INFO, m_DlgOrderInfo);
	DDX_Control(pDX, IDC_EDT_MESSAGE_LEFT, m_MessageLeftCtrl);
}

BEGIN_MESSAGE_MAP(CViewFrm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CViewFrm::OnBnClickedButton1)
	ON_MESSAGE(WM_ORDER_SHOW_CONFIRM, OnOrderShowConfirm)
	ON_MESSAGE(WM_ORDER_SMS_LEFT,OnShowSMSLeft)
	ON_BN_CLICKED(IDC_BTN_ADDCLOTH, &CViewFrm::OnBnClickedBtnAddcloth)
	ON_BN_CLICKED(IDC_BTN_DELCLOTH, &CViewFrm::OnBnClickedBtnDelcloth)
	ON_BN_CLICKED(IDC_BTN_UPDATETO_SQL, &CViewFrm::OnBnClickedBtnUpdatetoSql)
	ON_BN_CLICKED(IDC_BTN_SERVICE_INFO, &CViewFrm::OnBnClickedBtnServiceInfo)
END_MESSAGE_MAP()


// CViewFrm diagnostics

#ifdef _DEBUG
void CViewFrm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewFrm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewFrm message handlers

void CViewFrm::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
    UpdateData(FALSE);
    CString aa;
	int sel = m_timeRange.GetCurSel();
	aa.Format(_T("%d"),sel);
	//MessageBox(aa);
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	::SendMessage(pMain->m_hOrderListView,WM_ORDER_SHOW_CHANGE,0,sel);
	
}

void CViewFrm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_timeRange.InsertString( 0, _T("当日订单"));
	m_timeRange.InsertString( 1, _T("3天内订单"));
	m_timeRange.InsertString( 2, _T("7天内订单"));
	m_timeRange.InsertString( 3, _T("30天内订单"));
    m_timeRange.SetCurSel(0);
	// TODO: Add your specialized code here and/or call the base class

	m_clothDetailList.ModifyStyle(0, LVS_REPORT|LVS_SHOWSELALWAYS);
	m_clothDetailList.SetFont(&m_fontItem);
/*
	CImageList imgList;
	imgList.Create(1, 14, ILC_COLOR, 0, 0);

	list.SetImageList(&imgList, LVSIL_STATE);

	imgList.Detach();
*/

	for (int i=0; i<sizeof(s_reportItems)/sizeof(REPORT_ITEM); ++i)
	{
		m_clothDetailList.InsertColumn(i, s_reportItems[i].name, LVCFMT_LEFT, s_reportItems[i].width);
	}
	//this->m_curLine = 0;
	//ReDrawList();
	m_clothDetailList.SetExtendedStyle(m_clothDetailList.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL);  
	m_clothDetailList.SetRedraw(TRUE);
	m_clothDetailList.Invalidate();
	m_clothDetailList.UpdateWindow();
}




LRESULT CViewFrm::OnShowSMSLeft(WPARAM wparam, LPARAM lparam)
{


   CString smsLeft;
   smsLeft.Format(_T("%d"),(int)lparam);
   m_MessageLeftCtrl.SetWindowText(smsLeft);

   
   return 0L;


}

LRESULT CViewFrm::OnOrderShowConfirm(WPARAM wparam, LPARAM lparam)
{
	CString selstr;
	selstr.Format(_T("sel: %d"),(int)lparam);
	//MessageBox(_T("listView")+selstr);
	
    COrderItem *lpOrderItem = (COrderItem *)lparam;
	int i;
	for(i=m_clothDetailList.GetItemCount( );i>=-1;i--)
	{
		m_clothDetailList.DeleteItem(i);
	}
	m_iNumofCloth = 0;
	m_nTotalClothes = 0;
   if (lpOrderItem->orderID.Compare(_T("")))  //等于0是相等
   {
       GetDlgItem(IDC_CUR_ORDER)->SetWindowText(lpOrderItem->orderID+_T(" ")+ lpOrderItem->orderName);
	   GetDlgItem(IDC_CUR_ORDER)->SetWindowText(lpOrderItem->orderID);
	   m_OrderClothes.orderID = lpOrderItem->orderID;
	   m_OrderClothes.orderTel = lpOrderItem->orderTel;
	   if (MySQLInterface::instance()->isConnected())
	   {
		
		   CString sqlCstring = _T("select * from order_clothes_details where orderID = '")+lpOrderItem->orderID + _T("' and recordtype = 'primary' ");

		   //t	   wstring sqlstr = sqlCstring.GetBuffer();
		   string sqlstr = sqlCstring.GetBuffer();
		   sqlCstring.ReleaseBuffer();

		   string sql_s;

		   //t   WStringToString(sqlstr,sql_s);
		   MYSQL_RES *sql_res = NULL;

           int iFieldNum = 0;
		   //t       sql_res = MySQLInterface::instance()->DataQuery(sql_s,&iFieldNum);
		   sql_res = MySQLInterface::instance()->DataQuery(sqlstr,&iFieldNum);
		   if (sql_res==NULL)
		   {
			   return 0L;
		   }
		   int iRecordNum = mysql_num_rows(sql_res);
		   if(iRecordNum == 0)
		   {
			   MySQLInterface::instance()->FreeQueryResult(sql_res);
               return 0L;
		   }
		   MYSQL_ROW oneRow = MySQLInterface::instance()->Fetch_Query_Row(sql_res);
           //m_OrderClothes.orderID = oneRow[1];
		   //m_OrderClothes.orderID = lpOrderItem->orderID;
		   //m_OrderClothes.orderTel = oneRow[2];
		   //m_OrderClothes.orderTel = lpOrderItem->orderTel;
		   m_OrderClothes.confirmMessage = oneRow[4];
		   m_OrderClothes.receiveMessage = oneRow[5];
           m_OrderClothes.totalClothes = oneRow[6]; 
		   m_OrderClothes.otherInfos = oneRow[7]; 
           
		   m_DlgOrderInfo =  m_OrderClothes.otherInfos;
		   sqlCstring = _T("select * from order_clothes_details where orderID = '")+lpOrderItem->orderID + _T("' and recordtype = 'detail' ");
		   sqlstr = sqlCstring.GetBuffer();
		   sqlCstring.ReleaseBuffer();

		   MySQLInterface::instance()->FreeQueryResult(sql_res);

           
           sql_res = NULL;
		   iFieldNum = 0;
		   //t       sql_res = MySQLInterface::instance()->DataQuery(sql_s,&iFieldNum);
		   sql_res = MySQLInterface::instance()->DataQuery(sqlstr,&iFieldNum);
		   if (sql_res==NULL)
		   {
			   return 0L;
		   }
		   iRecordNum = mysql_num_rows(sql_res);
		   if(iRecordNum == 0)
		   {
			   MySQLInterface::instance()->FreeQueryResult(sql_res);
			   return 0L;
		   }
		  
		   for (i=0;i<iRecordNum;i++)
		   {

              OrderClothesDetail_Item oneItem;
              MYSQL_ROW oneDetailRow = MySQLInterface::instance()->Fetch_Query_Row(sql_res);
			  oneItem.clothes_type =  oneDetailRow[10];
			  oneItem.clothes_color = oneDetailRow[11];
			  oneItem.clothes_Num =   oneDetailRow[12];
			  oneItem.clothes_OtherInfo = oneDetailRow[13];

			   m_clothDetailList.InsertItem(i, oneItem.clothes_type);
			   m_clothDetailList.SetItemText(i, 1, oneItem.clothes_color);
			   m_clothDetailList.SetItemText(i, 2, oneItem.clothes_Num);
			   m_clothDetailList.SetItemText(i, 3, oneItem.clothes_OtherInfo);
               m_iNumofCloth++;
			   m_nTotalClothes+=atol(oneItem.clothes_Num);
		   }
		   MySQLInterface::instance()->FreeQueryResult(sql_res);
           UpdateData(FALSE);

	   }
   }

	return 0L;
}
void CViewFrm::OnBnClickedBtnAddcloth()
{
	// TODO: Add your control notification handler code here
	CAddclothDlg dlg;
	CString tempStr;

	if (IDOK == dlg.DoModal())
	{
		m_clothDetailList.SetRedraw(FALSE);
		m_iNumofCloth++;
		m_clothDetailList.InsertItem(m_iNumofCloth-1, dlg.m_type);		
		m_clothDetailList.SetItemText(m_iNumofCloth-1, 1, dlg.m_color);
		tempStr.Format(_T("%d"),dlg.m_iNumofclothes);
		m_clothDetailList.SetItemText(m_iNumofCloth-1, 2, tempStr);
		m_clothDetailList.SetItemText(m_iNumofCloth-1, 3, dlg.m_otherInfo);        
		m_clothDetailList.SetRedraw(TRUE);
		m_clothDetailList.Invalidate();
		m_clothDetailList.UpdateWindow();
		m_nTotalClothes += dlg.m_iNumofclothes;
	}
}

void CViewFrm::OnBnClickedBtnDelcloth()
{
	// TODO: Add your control notification handler code here
    int sel  =  -1;
	CString str;
	for(int i=0; i<m_clothDetailList.GetItemCount(); i++)
	{
		if( m_clothDetailList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			sel = i;
			break; 
		}
	}

	if (sel!=-1)
	{
		CString numOfClothesItem;
		numOfClothesItem = m_clothDetailList.GetItemText(sel,2);

		m_nTotalClothes -= atol(numOfClothesItem);
		m_clothDetailList.DeleteItem(sel);
		m_iNumofCloth--;

	}

}

void CViewFrm::OnBnClickedBtnUpdatetoSql()
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	COrderListView *lpListView = (COrderListView *)pMain->m_lpListView;

	if (lpListView->getCurrentListSelectedIndex()==-1)
	{
		MessageBox(_T("请在左侧选择一条订单"));
		return ;
	}

	CString curOrderID;
	UpdateData(TRUE);
    GetDlgItem(IDC_CUR_ORDER)->GetWindowText(curOrderID);
	if (0==curOrderID.Compare(_T("")))
	{
		return;
	}
	//“DELETE FROM `changxipu_db01`.`zkd_xiyi_order` WHERE `zkd_xiyi_order`.`no` = 206 AND `zkd_xiyi_order`.`ordernum` = \'15050400009-18217560851\'

	if (MySQLInterface::instance()->isConnected())
	{

	  CString sqlCstring = _T("DELETE FROM order_clothes_details WHERE orderID = '")+m_OrderClothes.orderID + _T("' ");

	  //t	   wstring sqlstr = sqlCstring.GetBuffer();
	  string sqlstr = sqlCstring.GetBuffer();
	  sqlCstring.ReleaseBuffer();

	  if (MySQLInterface::instance()->UpdateInsertData(sqlstr) == false)
	  {
		MessageBox(_T("更新数据库失败，请选择左侧一条订单再试一次"));
		return ;
	  }
	
	  
       sqlCstring = _T("INSERT INTO order_clothes_details (orderID, tel,recordtype,totalClothes,otherinfo,detailInfo_num) VALUES ");
	   CString sqlValue = _T("( '")+m_OrderClothes.orderID + _T("' , '")+m_OrderClothes.orderTel+_T("' , 'primary',");
       CString sqlValue2;
       //sqlValue2.Format(_T("%d,'%s',%d)"),m_nTotalClothes,m_OrderClothes.otherInfos,m_iNumofCloth);
	   sqlValue2.Format(_T("%d,'%s',%d)"),m_nTotalClothes,m_DlgOrderInfo,m_iNumofCloth);
       
	   sqlCstring = sqlCstring+sqlValue+sqlValue2;
	   sqlstr = sqlCstring.GetBuffer();
	   sqlCstring.ReleaseBuffer();

	   if (MySQLInterface::instance()->UpdateInsertData(sqlstr) == false)
	   {
		   MessageBox(_T("更新数据库失败，请选择左侧一条订单再试一次"));
		   return ;
	   }
	   CString ClothesItemType;
	   CString ClothesItemColor;
	   CString ClothesItemNum;
	   CString ClothesItemInfo;
	   for (int i =0;i<m_iNumofCloth;i++)
	   {
		   
		  // m_clothDetailList.GetItemText(i,2,ClothesItemContent);

		   sqlCstring = _T("INSERT INTO order_clothes_details (orderID, tel,recordtype,detail_index,detail_clothes_type,detail_clothes_color,detail_clothes_int,detail_other_info) VALUES ");
		   sqlValue = _T("( '")+m_OrderClothes.orderID + _T("' , '")+m_OrderClothes.orderTel+_T("' , 'detail',");


		   ClothesItemType = m_clothDetailList.GetItemText(i,0);
		   ClothesItemColor =  m_clothDetailList.GetItemText(i,1);
		   ClothesItemNum = m_clothDetailList.GetItemText(i,2);
		   ClothesItemInfo = m_clothDetailList.GetItemText(i,3);

		   sqlValue2.Format(_T("%d,'%s','%s',%d,'%s')"),i+1,ClothesItemType,ClothesItemColor,atol(ClothesItemNum),ClothesItemInfo);

		   sqlCstring = sqlCstring+sqlValue+sqlValue2;
		   sqlstr = sqlCstring.GetBuffer();
		   sqlCstring.ReleaseBuffer();

		   if (MySQLInterface::instance()->UpdateInsertData(sqlstr) == false)
		   {
			   MessageBox(_T("更新数据库失败，请选择左侧一条订单再试一次"));
			   return ;
		   }
	   }

	}
	else
	{
		MessageBox(_T("更新数据库失败，数据库未连接"));
		return ;
	}



}

void CViewFrm::OnBnClickedBtnServiceInfo()
{
	// TODO: Add your control notification handler code here
	CString orderId;
	 GetDlgItem(IDC_CUR_ORDER)->GetWindowText(orderId);
    CServiceInfoGenDlg dlg;
	dlg.m_serviceInfo = _T("客户您好，我们收到您的订单") + orderId + _T("有 ");

	CString ClothesItemType ;
	CString ClothesItemColor;
	CString ClothesItemNum ;
	CString ClothesItemInfo;

	for (int i=0;i<m_iNumofCloth;i++)
	{
		ClothesItemType = m_clothDetailList.GetItemText(i,0);
		ClothesItemColor =  m_clothDetailList.GetItemText(i,1);
		ClothesItemNum = m_clothDetailList.GetItemText(i,2);
		ClothesItemInfo = m_clothDetailList.GetItemText(i,3);

		dlg.m_serviceInfo += ClothesItemColor + ClothesItemType + ClothesItemNum + _T("件") + ClothesItemInfo + _T("; ");
	}

    dlg.m_serviceInfo += _T("请您确认，谢谢!");

	dlg.DoModal();

}
