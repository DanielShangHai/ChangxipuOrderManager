// ChangxipuAdminDoc.cpp : CChangxipuAdminDoc 类的实现
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


// CChangxipuAdminDoc 构造/析构

CChangxipuAdminDoc::CChangxipuAdminDoc()
{
	// TODO: 在此添加一次性构造代码

}

CChangxipuAdminDoc::~CChangxipuAdminDoc()
{
}

BOOL CChangxipuAdminDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CChangxipuAdminDoc 序列化

void CChangxipuAdminDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CChangxipuAdminDoc 诊断

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


// CChangxipuAdminDoc 命令
