// ChangxipuAdminDoc.cpp : CChangxipuAdminDoc ���ʵ��
//

#include "stdafx.h"
#include "ChangxipuAdmin.h"

#include "ChangxipuAdminDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChangxipuAdminDoc

IMPLEMENT_DYNCREATE(CChangxipuAdminDoc, CDocument)

BEGIN_MESSAGE_MAP(CChangxipuAdminDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CChangxipuAdminDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CChangxipuAdminDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CChangxipuAdminDoc ����/����

CChangxipuAdminDoc::CChangxipuAdminDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CChangxipuAdminDoc::~CChangxipuAdminDoc()
{
}

BOOL CChangxipuAdminDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CChangxipuAdminDoc ���л�

void CChangxipuAdminDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CChangxipuAdminDoc ���

#ifdef _DEBUG
void CChangxipuAdminDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChangxipuAdminDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CChangxipuAdminDoc ����
