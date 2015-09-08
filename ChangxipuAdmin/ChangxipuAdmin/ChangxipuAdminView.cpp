// ChangxipuAdminView.cpp : CChangxipuAdminView ���ʵ��
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
	{_T("�µ�ʱ��"),             100},
	{_T("�������"),           100},
	{_T("�ͻ�����"), 110},
	{_T("�ͻ��绰"), 110},
	{_T("��ַ"),   150},
	{_T("С��"),             50},
	{_T("���"),             50},
	{_T("ȡ��ʱ��"),             50},
	{_T("��������"),             50},
	{_T("�Ѹ����"),             50},
	{_T("�Ż�"),             50},
} ;





// CChangxipuAdminView

IMPLEMENT_DYNCREATE(CChangxipuAdminView, CView)

BEGIN_MESSAGE_MAP(CChangxipuAdminView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CChangxipuAdminView ����/����

CChangxipuAdminView::CChangxipuAdminView()
{
	// TODO: �ڴ˴���ӹ������
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
		_T("����"));


}

CChangxipuAdminView::~CChangxipuAdminView()
{
}

BOOL CChangxipuAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChangxipuAdminView ����

void CChangxipuAdminView::OnDraw(CDC* /*pDC*/)
{
	CChangxipuAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CChangxipuAdminView ��ӡ

BOOL CChangxipuAdminView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChangxipuAdminView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChangxipuAdminView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CChangxipuAdminView ���

#ifdef _DEBUG
void CChangxipuAdminView::AssertValid() const
{
	CView::AssertValid();
}

void CChangxipuAdminView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChangxipuAdminDoc* CChangxipuAdminView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChangxipuAdminDoc)));
	return (CChangxipuAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CChangxipuAdminView ��Ϣ�������

void CChangxipuAdminView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


}
