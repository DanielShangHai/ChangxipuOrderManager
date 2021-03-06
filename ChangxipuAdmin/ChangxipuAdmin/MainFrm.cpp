// MainFrm.cpp : CMainFrame 类的实现
//



#include "stdafx.h"
#include "ChangxipuAdmin.h"

#include "MainFrm.h"
#include "OrderInfoView.h"
#include "OrderListView.h"
#include "ViewFrm.h"

#include <winsock.h>
#include "mysql.h"
#include "utf82unicode.h"
#include "MySQLInterface.h"

#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};








// 注释：多字节包括GBK和UTF-8  
int GBK2UTF8(char *szGbk,char *szUtf8,int Len)  
{  
	// 先将多字节GBK（CP_ACP或ANSI）转换成宽字符UTF-16  
	// 得到转换后，所需要的内存字符数  
	int n = MultiByteToWideChar(CP_ACP,0,szGbk,-1,NULL,0);  
	// 字符数乘以 sizeof(WCHAR) 得到字节数  
	WCHAR *str1 = new WCHAR[sizeof(WCHAR) * n];  
	// 转换  
	MultiByteToWideChar(CP_ACP,  // MultiByte的代码页Code Page  
		0,            //附加标志，与音标有关  
		szGbk,        // 输入的GBK字符串  
		-1,           // 输入字符串长度，-1表示由函数内部计算  
		str1,         // 输出  
		n             // 输出所需分配的内存  
		);  

	// 再将宽字符（UTF-16）转换多字节（UTF-8）  
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
	if (n > Len)  
	{  
		delete[]str1;  
		return -1;  
	}  
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, szUtf8, n, NULL, NULL);  
	delete[]str1;  
	str1 = NULL;  

	return 0;  
}  


//UTF-8 GBK  
int UTF82GBK(char *szUtf8,char *szGbk,int Len)  
{  
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);  
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR) * n];  
	memset(wszGBK, 0, sizeof(WCHAR) * n);  
	MultiByteToWideChar(CP_UTF8, 0,szUtf8,-1, wszGBK, n);  

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	if (n > Len)  
	{  
		delete[]wszGBK;  
		return -1;  
	}  

	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGbk, n, NULL, NULL);  

	delete[]wszGBK;  
	wszGBK = NULL;  

	return 0;  
}  




// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码

  const char user[] = "root";
  const char password[] = "";
  const char host[] = "localhost";
  const char schema[] = "ssq";

  unsigned int port = 3306;
  MYSQL mysql;
  MYSQL_RES *result;
  MYSQL_ROW sql_row;
  MYSQL_FIELD *field;
  unsigned char column[32][32];
  int res;


  long i=1257938819;
  time_t the_time = 1432564628;
  CString tempstr;
  
  tempstr.Format(_T("aaa%s"),ctime(&the_time));
  char utcTime[50];
  memset(utcTime,0,50);
  strcpy(utcTime,ctime(&the_time));
  int charlen = strlen(utcTime);
  int len = MultiByteToWideChar(CP_ACP, 0, utcTime, charlen, NULL, 0); //计算多字节字符的大小，按字符计算  
  wchar_t *pWChar = new wchar_t[len + 1]; //为宽字节字符数申请空间，  
  MultiByteToWideChar(CP_ACP, 0, utcTime, charlen, pWChar, len); //多字节编码转换成宽字节编码  
  pWChar[len] = '\0';  
  delete[] pWChar;  




  //将wchar_t数组转换为CString  
  CString str22;  
  str22+=utcTime;
  struct tm tm1;  
  tm1 = *localtime(&the_time);  
  CString str33;  
  
  str33.Format(_T("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d"),
	   tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday,  
	   tm1.tm_hour, tm1.tm_min,tm1.tm_sec);

  
//  MessageBox(str33);



  //struct tm tm1;  
  time_t time1;  
  tm1.tm_year = 2015;
  tm1.tm_mon = 6;
  tm1.tm_mday = 14;
  tm1.tm_hour = 0;
  tm1.tm_min = 0;
  tm1.tm_sec = 0;
  tm1.tm_year -= 1900;   
  time1 = mktime(&tm1);  
  unsigned long aa =  (unsigned long)time1;
  





  SYSTEMTIME sTime;
  GetLocalTime(&sTime);                                              
  CString strTime;
  strTime.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), 
	  sTime.wYear, 
	  sTime.wMonth,  
	  sTime.wDay,  
	  sTime.wHour,
	  sTime.wMinute,
	  sTime.wSecond);

  //MessageBox(strTime);

  MySQLInterface::instance()->initialize();
   MySQLInterface::instance()->connect();

   string insertSql = "INSERT INTO zkd_xiyi_user  (tel, name, adress, openid,MainAreaID, SubAreaID, DetailAddressID, AddressName, accountmoney) VALUES ('13795457236', '宋嫡儿', '水电路1013弄3号楼707室内', 'aaaa',1,1,1,'abb',54)";
 // MySQLInterface::instance()->UpdateInsertData(insertSql);
  //mysql_init(&mysql);

 // if (!mysql_real_connect(&mysql, host,user, NULL, "changxipu", 3306, NULL, 0)) {
//	  return ;
  //}

  //Select db
  //int selectResult =   mysql_select_db(&mysql,"changxipu");
  //if(!) {
  //	  return ;
  //}
  //mysql_query(&mysql, "SET NAMES GBK");
  //mysql_set_character_set(&mysql, "utf8");
  //Set character
  //if (!mysql_set_character_set(&mysql, "utf8")) {
	//  return ;
  //}

  //Query
  //if(mysql_query(&mysql,str)!=0) {
//	  return FALSE;
 // }
 // result = mysql_use_result(&mysql);


  //Free results
  //mysql_free_result(result);
/*
  ASSERT(mysql_query(&mysql, "SELECT * FROM zkd_xiyi_user") == 0);

  result = mysql_store_result(&mysql);
  MYSQL_ROW row;
  ULONG colLen = mysql_num_fields(result);
  CString datas = L"";
  char temp[256];
  int i = 0;
  CString localCstr;
  while(row = mysql_fetch_row(result)) // 遍历每行记录
  {
	  i++;
     for(ULONG i=0; i<colLen; i++) 
     {
       int len = strlen(row[i]);
	   size_t resultNum = 0;
	   localCstr ="";
	   if (row[i]!=NULL)
	   {
		  ;// localCstr+=QXUtf82Unicode(row[i],&resultNum);
		  //UTF82GBK(row[i],temp,200);
		  //localCstr+= temp;
		  //memset(temp,0,256);
		  localCstr+= row[i];
	   }
	   
       //datas += row[i] ? row[i] : "NULL";
       //datas += "\t";
     }
     datas += "\n\n";
  }


 int r =  mysql_query(&mysql,"INSERT INTO zkd_xiyi_user  (tel, name, adress, openid,MainAreaID, SubAreaID, DetailAddressID, AddressName, accountmoney) VALUES ('13795457236', '宋嫡儿', '水电路1013弄3号楼707室内', 'aaaa',1,1,1,'abb',54)");
  
  
  mysql_free_result(result);
  mysql_close(&mysql);

*/

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

    CRect rect;
    GetClientRect(&rect);
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(COrderListView), CSize(rect.Width()*0.85, rect.Height()), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CViewFrm),  CSize(rect.Width()*0.15, rect.Height()), pContext);

	this->m_hCtrlView  = m_wndSplitter.GetPane(0, 1)->m_hWnd;
	this->m_hOrderListView = m_wndSplitter.GetPane(0,0)->m_hWnd;



//    return CFrameWnd::OnCreateClient(lpcs, pContext);
//	return m_wndSplitter.Create(this,
//		2, 2,               // TODO: 调整行数和列数
//		CSize(10, 10),      // TODO: 调整最小窗格大小
//		pContext);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序



