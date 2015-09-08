// ChangxipuAdminView.cpp : CChangxipuAdminView 类的实现
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"

#include "ChangxipuAdminDoc.h"
#include "ChangxipuAdminView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] = 
{
	{_T("下单时间"),             100},
	{_T("订单编号"),           100},
	{_T("客户姓名"), 110},
	{_T("客户电话"), 110},
	{_T("地址"),   150},
	{_T("小袋"),             50},
	{_T("大袋"),             50},
	{_T("取衣时间"),             50},
	{_T("订单类型"),             50},
	{_T("已付金额"),             50},
	{_T("优惠"),             50},
} ;





// CChangxipuAdminView

IMPLEMENT_DYNCREATE(CChangxipuAdminView, CView)

BEGIN_MESSAGE_MAP(CChangxipuAdminView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CChangxipuAdminView 构造/析构

CChangxipuAdminView::CChangxipuAdminView()
{
	// TODO: 在此处添加构造代码
	m_fontItem.CreateFont(   
		20,                        // nHeight
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


}

CChangxipuAdminView::~CChangxipuAdminView()
{
}

BOOL CChangxipuAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChangxipuAdminView 绘制

void CChangxipuAdminView::OnDraw(CDC* /*pDC*/)
{
	CChangxipuAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CChangxipuAdminView 打印

BOOL CChangxipuAdminView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChangxipuAdminView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChangxipuAdminView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CChangxipuAdminView 诊断

#ifdef _DEBUG
void CChangxipuAdminView::AssertValid() const
{
	CView::AssertValid();
}

void CChangxipuAdminView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChangxipuAdminDoc* CChangxipuAdminView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChangxipuAdminDoc)));
	return (CChangxipuAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CChangxipuAdminView 消息处理程序

void CChangxipuAdminView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


}
