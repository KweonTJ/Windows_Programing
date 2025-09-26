
// ExampleView.cpp: CExampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example.h"
#endif

#include "ExampleDoc.h"
#include "ExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExampleView

IMPLEMENT_DYNCREATE(CExampleView, CView)

BEGIN_MESSAGE_MAP(CExampleView, CView)
ON_WM_SIZE()
ON_WM_KEYDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CExampleView 생성/소멸

CExampleView::CExampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExampleView::~CExampleView()
{
}

BOOL CExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExampleView 그리기

void CExampleView::OnDraw(CDC* pDC)
{
	CExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	// 윈도우 크기 문자열을 좌측 상단 (10, 10)에 출력
	pDC->TextOut(10, 10, m_strWindowSize);
	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->TextOut(m_ptMouseMove.x + 10, m_ptMouseMove.y, m_strMouseMove);
}


// CExampleView 진단

#ifdef _DEBUG
void CExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExampleDoc* CExampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExampleDoc)));
	return (CExampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CExampleView 메시지 처리기

void CExampleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_strWindowSize.Format(_T("윈도우 크기는 넓이 %d, 높이 %d 입니다."), cx, cy);
	// 화면 갱신
	Invalidate();
}

void CExampleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("키보드를 눌렀습니다.");
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CExampleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag == TRUE)
	{
		m_strOutput = _T("마우스를 드래그하고 있습니다.");
	}
	else
	{
		m_strOutput = _T("마우스를 이동 중 입니다.");
	}
	m_ptMouseMove = point;
	m_strMouseMove.Format(_T("X : % d Y : % d"), point.x, point.y);
	Invalidate();

	CView::OnMouseMove(nFlags, point);
}

void CExampleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrag = TRUE;
	m_strOutput = _T("왼쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

void CExampleView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("오른쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}

void CExampleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrag = FALSE;

	CView::OnLButtonUp(nFlags, point);
}
