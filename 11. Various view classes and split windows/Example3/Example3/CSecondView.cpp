// CSecondView.cpp: 구현 파일
//

#include "pch.h"
#include "Example3.h"
#include "CSecondView.h"
#include "Example3Doc.h"

// CSecondView

IMPLEMENT_DYNCREATE(CSecondView, CView)

CSecondView::CSecondView()
{

}

CSecondView::~CSecondView()
{
}

BEGIN_MESSAGE_MAP(CSecondView, CView)
END_MESSAGE_MAP()


// CSecondView 그리기

void CSecondView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CExample3Doc* pDoc2 = (CExample3Doc*)GetDocument();
	pDC->TextOut(1, 1, pDoc2->m_strSaveInput);
}


// CSecondView 진단

#ifdef _DEBUG
void CSecondView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSecondView 메시지 처리기
