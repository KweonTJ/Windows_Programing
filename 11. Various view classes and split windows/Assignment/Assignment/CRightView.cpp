// CRightView.cpp: 구현 파일
//

#include "pch.h"
#include "Assignment.h"
#include "CRightView.h"
#include "AssignmentView.h"
#include "AssignmentDoc.h"
#include "MainFrm.h"

// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{

}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
END_MESSAGE_MAP()


// CRightView 그리기

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
    CDocument* pBaseDoc = GetDocument();

    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    CAssignmentDoc* pDoc2 = (CAssignmentDoc*)pFrame->GetActiveDocument();

    if (pDoc2 == nullptr)
        return;

    if (pDoc2->m_nSelItem >= 0 && pDoc2->m_nSelItem <= 3)
    {
        CRect rectClient;
        GetClientRect(&rectClient);

        CPoint center = rectClient.CenterPoint();

        int nWidth, nHeight;

        nWidth = (int)((rectClient.Width() / 2.0) *
            (pDoc2->FigureData[pDoc2->m_nSelItem].hRatio / 100.0));

        nHeight = (int)((rectClient.Height() / 2.0) *
            (pDoc2->FigureData[pDoc2->m_nSelItem].vRatio / 100.0));

        CRect rect;
        rect.left = center.x - nWidth;
        rect.right = center.x + nWidth;
        rect.top = center.y - nHeight;
        rect.bottom = center.y + nHeight;

        CBrush brush(pDoc2->FigureData[pDoc2->m_nSelItem].color);
        CBrush* pOldBrush = pDC->SelectObject(&brush);

        if (pDoc2->FigureData[pDoc2->m_nSelItem].FigureKind == ELLIPSE)
        {
            pDC->Ellipse(rect);
        }
        else
        {
            pDC->Rectangle(rect);
        }

        pDC->SelectObject(pOldBrush);
    }

}

// CRightView 진단

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 메시지 처리기
