
// Example2View.cpp: CExample2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example2.h"
#endif

#include "Example2Doc.h"
#include "Example2View.h"
#include "CLeftViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExample2View

IMPLEMENT_DYNCREATE(CExample2View, CTreeView)

BEGIN_MESSAGE_MAP(CExample2View, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CExample2View::OnTvnSelchanged)
END_MESSAGE_MAP()

// CExample2View 생성/소멸

CExample2View::CExample2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExample2View::~CExample2View()
{
}

BOOL CExample2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CTreeView::PreCreateWindow(cs);
}

void CExample2View::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& TreeCtrl = GetTreeCtrl();

	m_hRoot = TreeCtrl.InsertItem(_T("루트노드"), 0, TVI_LAST);
	TreeCtrl.ModifyStyle(0, TVS_LINESATROOT | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS);
	m_hSelectedNode = m_hRoot;

	CLeftViewDlg* pDlg = (CLeftViewDlg*)this->GetNextWindow(GW_HWNDPREV);
	pDlg->m_strSelectedNode = TreeCtrl.GetItemText(m_hSelectedNode);
	pDlg->UpdateData(FALSE);
}

void CExample2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExample2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExample2View 진단

#ifdef _DEBUG
void CExample2View::AssertValid() const
{
	CTreeView::AssertValid();
}

void CExample2View::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CExample2Doc* CExample2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample2Doc)));
	return (CExample2Doc*)m_pDocument;
}
#endif //_DEBUG


// CExample2View 메시지 처리기

void CExample2View::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	CLeftViewDlg* pDlg = (CLeftViewDlg*)this->GetNextWindow(GW_HWNDPREV);
	pDlg->m_strSelectedNode = GetTreeCtrl().GetItemText(m_hSelectedNode);
	pDlg->UpdateData(FALSE);
}
