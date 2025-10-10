
// AssignmentView.cpp: CAssignmentView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Assignment.h"
#endif

#include "AssignmentDoc.h"
#include "AssignmentView.h"
#include "CInputDlg.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssignmentView

IMPLEMENT_DYNCREATE(CAssignmentView, CView)

BEGIN_MESSAGE_MAP(CAssignmentView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CAssignmentView 생성/소멸

CAssignmentView::CAssignmentView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAssignmentView::~CAssignmentView()
{
}

BOOL CAssignmentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAssignmentView 그리기

void CAssignmentView::OnDraw(CDC* pDC)
{
	CAssignmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 색상 설정
	switch (pDoc->m_nDocColor)
	{
	case 0: pDC->SetTextColor(RGB(0, 0, 0)); break;
	case 1: pDC->SetTextColor(RGB(255, 0, 0)); break;
	case 2: pDC->SetTextColor(RGB(0, 255, 0)); break;
	case 3: pDC->SetTextColor(RGB(0, 0, 255)); break;
	default: pDC->SetTextColor(RGB(0, 0, 0)); break;
	}

	pDC->TextOut(pDoc->m_nDocX, pDoc->m_nDocY, pDoc->m_strDocText);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAssignmentView 인쇄

BOOL CAssignmentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAssignmentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAssignmentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAssignmentView 진단

#ifdef _DEBUG
void CAssignmentView::AssertValid() const
{
	CView::AssertValid();
}

void CAssignmentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAssignmentDoc* CAssignmentView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssignmentDoc)));
	return (CAssignmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CAssignmentView 메시지 처리기

void CAssignmentView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CInputDlg* pInput = new CInputDlg;

	if (pInput->DoModal() == IDOK)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CAssignmentDoc* pDoc = (CAssignmentDoc*)pFrame->GetActiveDocument();

		UpdateData(TRUE);
		pDoc->m_nDocX = pInput->m_nX;
		pDoc->m_nDocY = pInput->m_nY;
		pDoc->m_nDocColor = pInput->m_nDocColor;
		pDoc->m_strDocText = pInput->m_strText;
		Invalidate();
	}

	CView::OnRButtonDown(nFlags, point);
}
