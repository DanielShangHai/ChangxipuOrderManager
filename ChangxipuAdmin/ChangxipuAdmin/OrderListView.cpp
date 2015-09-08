// OrderListView.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "OrderListView.h"
#include "MySQLInterface.h"
#include "MainFrm.h"
#include <string>
#include "OrderInfo.h"
#include "EditOrderDlg.h"

using namespace std;


#define ID_TIMER_REFRESH_ORDER   0x1003 //滚动定时器，用于 按住+或-，数值一直增加或减少，直到松开按键
#define TIME_INTERVAL     60000 //定时时间为15秒


int DaysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};



typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] = 
{
	{_T("下单时间"),             170},
	{_T("订单编号"),           180},
	{_T("客户姓名"), 110},
	{_T("客户电话"), 110},
	{_T("地址"),   190},
	{_T("小袋"),             80},
	{_T("大袋"),             80},
	{_T("取衣时间"),             100},
	{_T("订单类型"),             100},
	{_T("已付金额"),             100},
	{_T("优惠"),             100},
	{_T("订单状态"),             100},
	{_T("微信号"),             100},
} ;





// COrderListView

IMPLEMENT_DYNCREATE(COrderListView, CListView)

COrderListView::COrderListView()
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
    m_iRecordNum = 0;
	m_OrderListQueryStr = _T("select * from zkd_xiyi_order where ");
    m_OrderListQueryStrEnd = _T(" ORDER BY ordertime DESC ");

    m_listCurSel = -1;



}

COrderListView::~COrderListView()
{
}

BEGIN_MESSAGE_MAP(COrderListView, CListView)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(NM_RCLICK, &COrderListView::OnNMRclick)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ORDER, &COrderListView::OnUpdateEditOrder)
	ON_COMMAND(ID_EDIT_ORDER, &COrderListView::OnEditOrder)
	ON_COMMAND(ID_MENU_EDIT_ORDER, &COrderListView::OnMenuEditOrder)
	ON_COMMAND(ID_MENU_CPY_ORDERINFO, &COrderListView::OnMenuCpyOrderinfo)
	ON_MESSAGE(WM_ORDER_SHOW_CHANGE, OnOrderShowChange)
	ON_NOTIFY_REFLECT(NM_CLICK, &COrderListView::OnNMClick)
	ON_COMMAND(ID_MENU_CPY_CELL, &COrderListView::OnMenuCpyCell)
END_MESSAGE_MAP()


// COrderListView diagnostics

#ifdef _DEBUG
void COrderListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderListView message handlers

void COrderListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class

	// TODO: Add your specialized code here and/or call the base class
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;

	CListCtrl& list = GetListCtrl();

	//list.ModifyStyle(0, LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
    
	list.ModifyStyle(0, LVS_REPORT|LVS_SHOWSELALWAYS);
	list.SetFont(&m_fontItem);

	
	//ListView_SetExtendedListViewStyle(m_list, 
	//	LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

	CImageList imgList;
	imgList.Create(1, 14, ILC_COLOR, 0, 0);

	list.SetImageList(&imgList, LVSIL_STATE);

	imgList.Detach();

	for (int i=0; i<sizeof(s_reportItems)/sizeof(REPORT_ITEM); ++i)
	{
		list.InsertColumn(i, s_reportItems[i].name, LVCFMT_LEFT, s_reportItems[i].width);
	}
	//this->m_curLine = 0;
	//ReDrawList();


    list.InsertItem(1, _T("aaa"));
	list.InsertItem(2, _T("bbb"));
	list.InsertItem(3, _T("ccc"));
	  //list.SetExtendedStyle(list.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	list.SetExtendedStyle(list.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);  
	ReDrawList();
	list.SetRedraw(TRUE);
	list.Invalidate();
	list.UpdateWindow();





	SYSTEMTIME sTime;
	GetLocalTime(&sTime);   
	struct tm tm1;  
	time_t time1;  

	tm1.tm_year = sTime.wYear - 1900;
	tm1.tm_mon = sTime.wMonth-1;
	tm1.tm_mday = sTime.wDay;
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;

	time1 = mktime(&tm1);
	unsigned long aa =  (unsigned long)time1;
	CString timeStone;
	timeStone.Format(_T(" %d "),(unsigned long)time1);
	m_OrderListConditionStr = _T(" ordertime >= ") + timeStone;
    
	pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	pMain->m_lpListView = this;



	SetTimer(TIME_INTERVAL,TIME_INTERVAL,NULL);
	// TODO: Add your specialized code here and/or call the base class
}

void COrderListView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
    switch(nIDEvent)
	{
	case ID_TIMER_REFRESH_ORDER:
		ReDrawList();
		//MessageBox(_T("hahahtimer"));
		break;
	default:
		break;
	}
	CListView::OnTimer(nIDEvent);
}



BOOL WStringToString(const std::wstring &wstr,std::string &str)
{    
	int nLen = (int)wstr.length();    
	str.resize(nLen,' ');
	int nResult = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wstr.c_str(),nLen,(LPSTR)str.c_str(),nLen,NULL,NULL);
	if (nResult == 0)
	{
		return FALSE;
	}
	return TRUE;
}


void COrderListView::ReDrawList()
{
   CListCtrl& list = GetListCtrl();
   list.SetRedraw(FALSE);
   
   SYSTEMTIME sTime;
   GetLocalTime(&sTime);   
   struct tm tm1;  
   time_t time1;  
   tm1.tm_year = sTime.wYear - 1900;
   tm1.tm_mon = sTime.wMonth-1;
   tm1.tm_mday = sTime.wDay;
   tm1.tm_hour = 0;
   tm1.tm_min = 0;
   tm1.tm_sec = 0;

   time1 = mktime(&tm1);  
   unsigned long aa =  (unsigned long)time1;

   CString timeStone;
   timeStone.Format(_T(" %d "),(unsigned long)time1);


   int iFieldNum = 0;
   MYSQL_RES *sql_res;
   int i;
   for(i=list.GetItemCount( );i>=-1;i--)
   {
	   list.DeleteItem(i);
   }
   m_iRecordNum = 0;
   m_selectedOrder.clear();
   m_listCurSel = -1;

   if (MySQLInterface::instance()->isConnected())
   {
	   //CString sqlCstring = _T("select * from zkd_xiyi_order where ordertime >=");
       //sqlCstring+=timeStone;
       //sqlCstring += _T("ORDER BY ordertime DESC");
	   
      CString sqlCstring = m_OrderListQueryStr + m_OrderListConditionStr + m_OrderListQueryStrEnd;

//t	   wstring sqlstr = sqlCstring.GetBuffer();
	   string sqlstr = sqlCstring.GetBuffer();
	   sqlCstring.ReleaseBuffer();

       string sql_s;

    //t   WStringToString(sqlstr,sql_s);
	   sql_res = NULL;


//t       sql_res = MySQLInterface::instance()->DataQuery(sql_s,&iFieldNum);
	   sql_res = MySQLInterface::instance()->DataQuery(sqlstr,&iFieldNum);
	   if (sql_res==NULL)
	   {
		    list.SetRedraw(true);
			list.Invalidate();
			list.UpdateWindow();
		   return;
	   }
	   int iRecordNum = mysql_num_rows(sql_res);
	   m_iRecordNum = iRecordNum;
       for (i=0;i<iRecordNum;i++)
       {

		   OrderInfo oneOrder;
		   MYSQL_ROW oneRow = MySQLInterface::instance()->Fetch_Query_Row(sql_res);
           oneOrder.FillDataFromSQLRow(oneRow,iFieldNum);

		   time_t the_time;
		   the_time = oneOrder.getOrderTime();
		   struct tm tm1;  
		   tm1 = *localtime(&the_time);  

		   CString localOrderTime;  

		   localOrderTime.Format(_T("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d"),
			   tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday,  
			   tm1.tm_hour, tm1.tm_min,tm1.tm_sec);


		   list.InsertItem(i, localOrderTime);
           list.SetItemText(i, 1, oneOrder.m_orderID);
		   list.SetItemText(i, 2, oneOrder.m_name);
		   list.SetItemText(i, 3, oneOrder.m_tel);
		   list.SetItemText(i, 4, oneOrder.m_address);
		   list.SetItemText(i, 5, oneOrder.m_smallbag);
		   list.SetItemText(i, 6, oneOrder.m_bigBag);
		   list.SetItemText(i, 7, oneOrder.m_getClothtime);
		   list.SetItemText(i, 8, oneOrder.m_OrderType);
		   list.SetItemText(i, 9, oneOrder.m_PayMoney);
		   list.SetItemText(i, 10, oneOrder.m_discount);
		   list.SetItemText(i, 11, oneOrder.m_orderStatus);
     
       }
	   


	   CString sqlMessage = _T("SELECT * from zkd_xiyi_sms ORDER BY time DESC limit 1");

	   //t	   wstring sqlstr = sqlCstring.GetBuffer();
	   string sqlMessagestr = sqlMessage.GetBuffer();
	   sqlMessage.ReleaseBuffer();

	   //t string sql_s;

	   //t   WStringToString(sqlstr,sql_s);
	   sql_res = NULL;

	   //t       sql_res = MySQLInterface::instance()->DataQuery(sql_s,&iFieldNum);
	   sql_res = MySQLInterface::instance()->DataQuery(sqlMessagestr,&iFieldNum);
	   if (sql_res==NULL)
	   {
		  ;
	   }
	   else
	   {
		   MYSQL_ROW oneSMSRow = MySQLInterface::instance()->Fetch_Query_Row(sql_res);
           CString leftsms = oneSMSRow[6];
		   CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
		   ::SendMessage(pMain->m_hCtrlView,WM_ORDER_SMS_LEFT,0,(LPARAM)atol(leftsms));
		   MySQLInterface::instance()->FreeQueryResult(sql_res);
           
	   }
	   

	  



   }
    list.SetRedraw(true);
	list.Invalidate();
	list.UpdateWindow();

}
void COrderListView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		CString strtemp;
		strtemp.Format(_T("单击的是第%d行第%d列"),
			pNMListView->iItem, pNMListView->iSubItem);
		//AfxMessageBox(strtemp);
	}
    //if (pNMListView->iItem<m_iRecordNum)
	if (pNMListView->iItem!=-1)
    {
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_POP_EDIT ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
    }

	


	*pResult = 0;
}

void COrderListView::OnUpdateEditOrder(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CListCtrl& list = GetListCtrl();
	int num = 0;
	CString str;
	for(int i=0; i<list.GetItemCount(); i++)
	{
		//if( list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || list.GetCheck(i))
		if( list.GetCheck(i))
		{
           num++;
		}
	}
	if (num>0)
	{
		pCmdUI->Enable(TRUE);
	}
    else
	{
		pCmdUI->Enable(FALSE);
	}
	
}

void COrderListView::OnEditOrder() ////主菜单上的批量
{
	// TODO: Add your command handler code here
    CString sqlstr,sqlstr1,sqlstr2;
	string sql_string;
    KillTimer(ID_TIMER_REFRESH_ORDER);
    CEditOrderDlg dlg;
    ListIDOrderMap::iterator iter = m_selectedOrder.begin();
    dlg.m_OrderID = iter->second.orderID;
	if (m_selectedOrder.size()==1)
	{        
		dlg.m_payedMoney  = (*iter).second.orderPayed;
		dlg.m_discount = (*iter).second.orderDiscount;

        CString orderStatus = (*iter).second.orderStatus;
        if (0==orderStatus.Compare(_T("0-失效")))
        {
			dlg.m_iOrderStatus = 0;
        }
        else if (0==orderStatus.Compare(_T("1-待审核")))
        {
			dlg.m_iOrderStatus = 1;
        }
		else if (0==orderStatus.Compare(_T("2-已审核")))
		{
			dlg.m_iOrderStatus = 2;
		}
		else if (0==orderStatus.Compare(_T("3-已分配收衣员")))
		{
			dlg.m_iOrderStatus = 3;
		}
		else if (0==orderStatus.Compare(_T("4-已确认衣物数量种类")))
		{
			dlg.m_iOrderStatus = 4;
		}
		else if (0==orderStatus.Compare(_T("5-洗衣中")))
		{
			dlg.m_iOrderStatus = 5;
		}
		else if (0==orderStatus.Compare(_T("6-已完成")))
		{
			dlg.m_iOrderStatus = 6;
		}
		else if (0==orderStatus.Compare(_T("7-已删除")))
		{
			dlg.m_iOrderStatus = 7;
		}
		else
		{
            dlg.m_iOrderStatus = 0;
		}
		
		CString orderType = (*iter).second.orderType;
		if (0==orderType.Compare(_T("正常")))
		{
			dlg.m_iOrderType = 0;
		}
		else if (0==orderType.Compare(_T("免单")))
		{
			dlg.m_iOrderType = 1;
		}
		else if (0==orderType.Compare(_T("优惠")))
		{
			dlg.m_iOrderType = 2;
		}
		else
		{
			dlg.m_iOrderType = 0;
		}
	}
	else
	{
		CString compStr;
		compStr.Format(_T("等%d条记录"),m_selectedOrder.size());
       dlg.m_OrderID += compStr;
	}
	if (dlg.DoModal()==IDOK)
	{
		CString orderStatus;
		CString orderType;
		CString payedMoney;
		CString discount;

		//int nIndex = dlg.m_DlgOrderStatus.GetCurSel();
		//dlg.m_DlgOrderStatus.GetLBText( nIndex, orderStatus);

		//nIndex = dlg.m_DlgOrderType.GetCurSel();
		//dlg.m_DlgOrderType.GetLBText( nIndex, orderType);

		int nIndex = dlg.m_iOrderType;
		switch(nIndex)
		{
		  case 0:
		    orderType = _T("正常");
            break;
		  case 1:
		    orderType = _T("免单");
		    break;
		  case 2:
			orderType = _T("优惠");
		    break;
		  default:
		    orderType = _T("正常");
			break;
		}

		nIndex = dlg.m_iOrderStatus;
		switch(nIndex)
		{
		case 0:
			orderStatus = _T("0-失效");
			break;
		case 1:
			orderStatus = _T("1-待审核");
			break;
		case 2:
			orderStatus = _T("2-已审核");
			break;
		case 3:
			orderStatus = _T("3-已分配收衣员");
			break;
		case 4:
			orderStatus = _T("4-已确认衣物数量种类");
			break;
		case 5:
			orderStatus = _T("5-洗衣中");
			break;
		case 6:
			orderStatus = _T("6-已完成");
			break;
		case 7:
			orderStatus = _T("7-已删除");
			break;
		default:
			orderStatus = _T("1-待审核");
			break;
		}
       
        int ChangeCount = 0;
		
		sqlstr = _T("update zkd_xiyi_order set ");
        if (dlg.m_TypeChecked)
        {
			ChangeCount++;
			sqlstr += _T(" OrderType = '") + orderType + _T("' ,");
        }
		if (dlg.m_discountChecked)
		{
			ChangeCount++;
			sqlstr1.Format(_T(" discount = %.2f ,"),dlg.m_discount );
			sqlstr+=sqlstr1;
		}
        if (dlg.m_PayedChecked)
        {
			ChangeCount++;
			sqlstr1.Format(_T(" PayedMoney = %.2f ,"),dlg.m_payedMoney );
			sqlstr+=sqlstr1;
        }
		if (dlg.m_StatusChecked)
		{
			ChangeCount++;
			sqlstr += _T(" status = '") + orderStatus + _T("' ,");
		}

        sqlstr += _T(" big = big + 0 ");

        if (ChangeCount>0)
        {
			sqlstr += _T("where ");

			ListIDOrderMap::iterator iter = m_selectedOrder.begin(),
				iter_end = m_selectedOrder.end();
			while(iter != iter_end)
			{
				if (iter==m_selectedOrder.begin())
				{
					sqlstr += _T(" ordernum = '")+iter->second.orderID+_T("' ");
				}
				else
				{
			        sqlstr += _T("or ordernum = '")+iter->second.orderID+_T("' ");
				}      
				iter++;
			}

            sql_string = sqlstr.GetBuffer();
			sqlstr.ReleaseBuffer();
			bool ret = MySQLInterface::instance()->UpdateInsertData(sql_string);
           
			if ((ret==TRUE)&&(dlg.m_StatusChecked))
			{

				if (0 == orderStatus.Compare(_T("6-已完成")))
				{
					ListIDOrderMap::iterator iter = m_selectedOrder.begin(),
						iter_end = m_selectedOrder.end();

                    sqlstr = _T("update zkd_xiyi_user set ");
                    int changeUserCount = 0;
					sqlstr1 = " ";
					while(iter != iter_end)
					{
						if (iter->second.orderStatus.Compare(_T("6-已完成"))!=0)  //原先为 未完成状态
						{
						   changeUserCount++;
						   if (iter==m_selectedOrder.begin())
						   {
                             sqlstr1+=_T(" tel = '") + iter->second.orderTel + _T("' ");
						   }
                           else
						   {
                             sqlstr1+=_T(" or tel = '") + iter->second.orderTel + _T("' ");
						   }

						}			
						iter++;
					}

					if (changeUserCount>0)
					{
                       sqlstr += _T("CompleteOrder_count = CompleteOrder_count + 1 where ") + sqlstr1;
					   sql_string = sqlstr.GetBuffer();
					   sqlstr.ReleaseBuffer();
					   MySQLInterface::instance()->UpdateInsertData(sql_string);					   
					}

				}
				else
				{
					ListIDOrderMap::iterator iter = m_selectedOrder.begin(),
						iter_end = m_selectedOrder.end();

					sqlstr = _T("update zkd_xiyi_user set ");
					int changeUserCount = 0;
					sqlstr1 = " ";
					while(iter != iter_end)
					{
						if (iter->second.orderStatus.Compare(_T("6-已完成"))==0)  //原先为 完成状态
						{
							changeUserCount++;
							if (iter==m_selectedOrder.begin())
							{
								sqlstr1+=_T(" tel = '") + iter->second.orderTel + _T("' ");
							}
							else
							{
								sqlstr1+=_T(" or tel = '") + iter->second.orderTel + _T("' ");
							}

						}			
						iter++;
					}

					if (changeUserCount>0)
					{
						sqlstr += _T("CompleteOrder_count = CompleteOrder_count - 1 where ") + sqlstr1;
						sql_string = sqlstr.GetBuffer();
						sqlstr.ReleaseBuffer();
						MySQLInterface::instance()->UpdateInsertData(sql_string);					   
					}
				}				

			}

			 ReDrawList();

        }


	}
	SetTimer(ID_TIMER_REFRESH_ORDER,TIME_INTERVAL,NULL);
}

void COrderListView::OnMenuEditOrder()///右键弹出菜单
{
	// TODO: Add your command handler code here
	KillTimer(ID_TIMER_REFRESH_ORDER);
	CEditOrderDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		CString orderStatus;
		CString orderType;
		CString payedMoney;
		CString discount;
		dlg.m_DlgOrderStatus.GetWindowText(orderStatus);
		dlg.m_DlgOrderType.GetWindowText(orderType);
		payedMoney.Format(_T("%.2f"),dlg.m_payedMoney);
		discount.Format(_T("%.2f"),dlg.m_discount);
	}
	SetTimer(ID_TIMER_REFRESH_ORDER,TIME_INTERVAL,NULL);
}

void COrderListView::OnMenuCpyOrderinfo()
{
	// TODO: Add your command handler code here

	CString source = m_CurSelOrderString;
	if( OpenClipboard() )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();


	//	wstring sqlstr = source.GetBuffer();
	//	source.ReleaseBuffer();
	//	string sql_s;
	//	WStringToString(sqlstr,sql_s);

	//	clipbuffer = GlobalAlloc(GMEM_DDESHARE, sql_s.length()+1);
	    clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);

		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);  
		SetClipboardData(CF_OEMTEXT,clipbuffer);
		//SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
/*
	//文本内容保存在source变量中
	if( OpenClipboard() )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		

		wstring sqlstr = source.GetBuffer();
		string sqlMessagestr = sqlMessage.GetBuffer();
		sqlMessage.ReleaseBuffer();

		//t string sql_s;

		//t   WStringToString(sqlstr,sql_s);
        
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);

		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
*/

	
	//下面的代码呈现了怎能从剪贴板上获得文本内容：
    /*
	char * buffer = NULL;
	//打开剪贴板
	CString fromClipboard;
	if ( OpenClipboard() )
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);
		fromClipboard = buffer;
		GlobalUnlock(hData);
		CloseClipboard();
	}
	*/
}



LRESULT COrderListView::OnOrderShowChange(WPARAM wparam, LPARAM lparam)
{
	CString selstr;
	selstr.Format(_T("sel: %d"),(int)lparam);
    //MessageBox(_T("listView")+selstr);


	SYSTEMTIME sTime;
	GetLocalTime(&sTime);   
	struct tm tm1;  
	time_t time1;  
	
	tm1.tm_year = sTime.wYear - 1900;
	tm1.tm_mon = sTime.wMonth-1;
	tm1.tm_mday = sTime.wDay;
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;
	


   int sel = (int)lparam;
   int daysBefore = 0;
   switch(sel)
   {
     case 0:
	   daysBefore = 0;
	   break;
	 case 1:
	   daysBefore = 3;
	   break;
	 case 2:
	   daysBefore = 7;
	   break;
	 case 3:
	   daysBefore = 30;
	   break;
	 default:
	   daysBefore = 0;
	   break;
   }

   int delta = 0;
   if (sTime.wDay>daysBefore)
   {
     tm1.tm_mday-=daysBefore;
   }
   else
   { 
      delta = daysBefore - tm1.tm_mday;
	  do
	  {
		 
		 if (tm1.tm_mon<1)
		 {
			 tm1.tm_mon = 11;
			 tm1.tm_year--;
		 }
		 else
		 {
             tm1.tm_mon--;
		 }
		 int dayM = DaysInMonth[tm1.tm_mon];
		 if (dayM>delta)
		 {
			 tm1.tm_mday = dayM - delta;
			 delta = -1;
		 }
		 else
		 {
            delta = delta - dayM;
		 }	  
	  }while(delta>=0);
     
   }
	time1 = mktime(&tm1);
	unsigned long aa =  (unsigned long)time1;
	CString timeStone;
	timeStone.Format(_T(" %d "),(unsigned long)time1);
	m_OrderListConditionStr = _T("ordertime >= ") + timeStone;
    
	ReDrawList();

	return 0;
}
void COrderListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CListCtrl& list = GetListCtrl();

	CString checkedStr;	

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	

	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

	list.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	UINT nFlag;
	int nItem = list.HitTest(point, &nFlag);
	//判断是否点在checkbox上
	if(nFlag == LVHT_ONITEMSTATEICON)
	{
		//AfxMessageBox(_T("点在listctrl的checkbox上"));

		if(pNMListView->iItem != -1)
		{
			if (list.GetCheck(pNMListView->iItem))
			{
				//checkedStr.Format(_T("Line Checked: %d"),1);	///original is checked , then is uncheck		
                m_selectedOrder.erase(pNMListView->iItem);
			}
			else
			{
				//checkedStr.Format(_T("Line Checked: %d"),0);		
				COrderItem it;
				it.iIndex = pNMListView->iItem;
				it.orderTel = list.GetItemText(pNMListView->iItem,3);
				it.orderID = list.GetItemText(pNMListView->iItem,1);
				it.orderStatus = list.GetItemText(pNMListView->iItem,11);
                it.orderType = list.GetItemText(pNMListView->iItem,8);
				it.orderName = list.GetItemText(pNMListView->iItem,2);
				CString floatCstr;
				floatCstr = list.GetItemText(pNMListView->iItem,9);
				it.orderPayed = atof(floatCstr);
                floatCstr = list.GetItemText(pNMListView->iItem,10);
                it.orderDiscount = atof(floatCstr);
                CString IntCstr;
                IntCstr = list.GetItemText(pNMListView->iItem,5);
                it.orderSmall = atol(IntCstr);
				IntCstr = list.GetItemText(pNMListView->iItem,6);
				it.orderBig = atol(IntCstr);

				m_selectedOrder.insert(	make_pair(pNMListView->iItem,it));

			}
			//MessageBox(checkedStr);
		}

	} 

    checkedStr.Format(_T("total select %d"),m_selectedOrder.size());
    //MessageBox(checkedStr);

    if(pNMListView->iItem != -1)
    {
	    m_curActiveOrder.iIndex = pNMListView->iItem;
		m_curActiveOrder.orderTel = list.GetItemText(pNMListView->iItem,3);
		CString nameStr;
		nameStr = list.GetItemText(pNMListView->iItem,2);
		m_curActiveOrder.orderName = nameStr;
		m_curActiveOrder.orderID = list.GetItemText(pNMListView->iItem,1);
		m_curActiveOrder.orderStatus = list.GetItemText(pNMListView->iItem,11);
		m_curActiveOrder.orderType = list.GetItemText(pNMListView->iItem,8);
		CString floatCstr;
		floatCstr = list.GetItemText(pNMListView->iItem,9);
		m_curActiveOrder.orderPayed = atof(floatCstr);
		floatCstr = list.GetItemText(pNMListView->iItem,10);
		m_curActiveOrder.orderDiscount = atof(floatCstr);
		CString IntCstr;
		IntCstr = list.GetItemText(pNMListView->iItem,5);
		m_curActiveOrder.orderSmall = atol(IntCstr);
		IntCstr = list.GetItemText(pNMListView->iItem,6);
		m_curActiveOrder.orderBig = atol(IntCstr);
       
		CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
		::SendMessage(pMain->m_hCtrlView,WM_ORDER_SHOW_CONFIRM,0,(LPARAM)&m_curActiveOrder);
		m_listCurSel = pNMListView->iItem;


		 
        m_CurSelOrderString = _T("");
	    for(int j=0;j<12;j++)
		{
            m_CurSelOrderString += list.GetItemText(pNMListView->iItem,j) + _T("  ");
		}
		m_CurSelOrderCellString = list.GetItemText(pNMListView->iItem,pNMListView->iSubItem) + _T("  ");


    }

	*pResult = 0;

}

void COrderListView::OnMenuCpyCell()
{
	// TODO: Add your command handler code here
	CString source = m_CurSelOrderCellString;

	//文本内容保存在source变量中
	if( OpenClipboard() )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
}


int COrderListView::getCurrentListSelectedIndex()
{
  return m_listCurSel;
}