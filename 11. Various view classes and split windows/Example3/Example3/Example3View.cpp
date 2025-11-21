
// Example3View.cpp: CExample3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example3.h"
#endif

#include "Example3Doc.h"
#include "Example3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExample3View

IMPLEMENT_DYNCREATE(CExample3View, CFormView)

BEGIN_MESSAGE_MAP(CExample3View, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CExample3View::OnClickedButtonSave)
END_MESSAGE_MAP()

// CExample3View 생성/소멸

CExample3View::CExample3View() noexcept
	: CFormView(IDD_EXAMPLE3_FORM)
	, m_strInput(_T(""))
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExample3View::~CExample3View()
{
}

void CExample3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
}

BOOL CExample3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CExample3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CExample3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExample3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExample3View 진단

#ifdef _DEBUG
void CExample3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CExample3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExample3Doc* CExample3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample3Doc)));
	return (CExample3Doc*)m_pDocument;
}
#endif //_DEBUG


// CExample3View 메시지 처리기

void CExample3View::OnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExample3Doc* pDoc = GetDocument();
	UpdateData(TRUE);
	pDoc->m_strSaveInput = m_strInput;
}
