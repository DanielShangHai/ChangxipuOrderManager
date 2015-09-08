#pragma once


// COrderInfoView view

class COrderInfoView : public CView
{
	DECLARE_DYNCREATE(COrderInfoView)

protected:
	COrderInfoView();           // protected constructor used by dynamic creation
	virtual ~COrderInfoView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


