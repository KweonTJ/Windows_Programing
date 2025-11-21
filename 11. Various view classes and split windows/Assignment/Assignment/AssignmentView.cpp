
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
#include "CRightView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssignmentView

IMPLEMENT_DYNCREATE(CAssignmentView, CListView)

BEGIN_MESSAGE_MAP(CAssignmentView, CListView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CAssignmentView::OnLvnItemchanged)
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

	return CListView::PreCreateWindow(cs);
}


void CAssignmentView::OnDraw(CDC* /*pDC*/)
{
	CAssignmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


void CAssignmentView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& ListCtrl = GetListCtrl();
	ListCtrl.ModifyStyle(0, LVS_REPORT);
	ListCtrl.SetExtendedStyle(ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	ListCtrl.InsertColumn(0, _T("도형 종류"), LVCFMT_CENTER, 110);
	ListCtrl.InsertColumn(1, _T("도형 색상"), LVCFMT_CENTER, 110);
	ListCtrl.InsertColumn(2, _T("도형 비율"), LVCFMT_CENTER, 110);

	ListCtrl.InsertItem(0, _T("원"));
	ListCtrl.SetItem(0, 1, LVIF_TEXT, _T("빨간색"), 0, 0, 0, 0);
	ListCtrl.SetItem(0, 2, LVFIF_TEXT, _T("60% - 60%"), 0, 0, 0, 0);

	ListCtrl.InsertItem(0, _T("사각형"));
	ListCtrl.SetItem(0, 1, LVIF_TEXT, _T("파란색"), 0, 0, 0, 0);
	ListCtrl.SetItem(0, 2, LVFIF_TEXT, _T("60% - 60%"), 0, 0, 0, 0);

	ListCtrl.InsertItem(0, _T("원"));
	ListCtrl.SetItem(0, 1, LVIF_TEXT, _T("초록색"), 0, 0, 0, 0);
	ListCtrl.SetItem(0, 2, LVFIF_TEXT, _T("60% - 30%"), 0, 0, 0, 0);

	ListCtrl.InsertItem(0, _T("사각형"));
	ListCtrl.SetItem(0, 1, LVIF_TEXT, _T("노란색"), 0, 0, 0, 0);
	ListCtrl.SetItem(0, 2, LVFIF_TEXT, _T("30% - 60%"), 0, 0, 0, 0);
	// TODO: GetListCtrl()을 호출하여 해당 list 컨트롤을 직접 액세스함으로써
	//  ListView를 항목으로 채울 수 있습니다.
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
	CListView::AssertValid();
}

void CAssignmentView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CAssignmentDoc* CAssignmentView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssignmentDoc)));
	return (CAssignmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CAssignmentView 메시지 처리기

int CAssignmentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	lpCreateStruct->style |= LVS_REPORT | LVS_SHOWSELALWAYS;

	return 0;
}

void CAssignmentView::OnLvnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel = pNMLV->iItem;

	if (nSel >= 0)
    {
        CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

        CAssignmentDoc* pDoc = (CAssignmentDoc*)pFrame->GetActiveDocument();

        if (pDoc != nullptr)
        {
            pDoc->m_nSelItem = nSel;
            pDoc->UpdateAllViews(NULL);
        }
    }

	*pResult = 0;
}
