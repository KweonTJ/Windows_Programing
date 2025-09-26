﻿
// Practice2aView.cpp: CPractice2aView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice2a.h"
#endif

#include "Practice2aDoc.h"
#include "Practice2aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice2aView

IMPLEMENT_DYNCREATE(CPractice2aView, CView)

BEGIN_MESSAGE_MAP(CPractice2aView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPractice2aView 생성/소멸

CPractice2aView::CPractice2aView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice2aView::~CPractice2aView()
{
}

BOOL CPractice2aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice2aView 그리기

void CPractice2aView::OnDraw(CDC* /*pDC*/)
{
	CPractice2aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CPractice2aView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice2aView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice2aView 진단

#ifdef _DEBUG
void CPractice2aView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice2aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice2aDoc* CPractice2aView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice2aDoc)));
	return (CPractice2aDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice2aView 메시지 처리기
