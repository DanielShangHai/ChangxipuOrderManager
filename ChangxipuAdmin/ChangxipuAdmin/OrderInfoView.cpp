// OrderInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"
#include "OrderInfoView.h"
#include "utf82unicode.h"



// COrderInfoView

IMPLEMENT_DYNCREATE(COrderInfoView, CView)

COrderInfoView::COrderInfoView()
{

}

COrderInfoView::~COrderInfoView()
{
}

BEGIN_MESSAGE_MAP(COrderInfoView, CView)
END_MESSAGE_MAP()


// COrderInfoView drawing

void COrderInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// COrderInfoView diagnostics

#ifdef _DEBUG
void COrderInfoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderInfoView message handlers
