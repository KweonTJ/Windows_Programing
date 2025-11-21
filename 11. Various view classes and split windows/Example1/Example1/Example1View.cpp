
// Example1View.cpp: CExample1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example1.h"
#endif

#include "Example1Doc.h"
#include "Example1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExample1View

IMPLEMENT_DYNCREATE(CExample1View, CFormView)

BEGIN_MESSAGE_MAP(CExample1View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExample1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CExample1View::OnClickedButtonOutput)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CExample1View::OnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CExample1View::OnClickedButtonReset)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_RED, &CExample1View::OnChangeEditRed)
	ON_EN_CHANGE(IDC_EDIT_GREEN, &CExample1View::OnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_BLUE, &CExample1View::OnChangeEditBlue)
END_MESSAGE_MAP()

// CExample1View 생성/소멸

CExample1View::CExample1View() noexcept
	: CFormView(IDD_EXAMPLE1_FORM)
	, m_strText(_T(""))
	, m_nGreen(0)
	, m_nRed(0)
	, m_nBlue(0)
	, m_nX(0)
	, m_nY(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_colorText = RGB(0, 0, 0);
	m_nX = 30;
	m_nY = 400;
}

CExample1View::~CExample1View()
{
}

void CExample1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	//  DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_nGreen);
	DDV_MinMaxInt(pDX, m_nGreen, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDV_MinMaxInt(pDX, m_nRed, 0, 255);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_nBlue);
	DDV_MinMaxInt(pDX, m_nBlue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	DDX_Control(pDX, IDC_SLIDER_Y, m_sliderY);
	DDX_Control(pDX, IDC_SLIDER_X, m_sliderX);
}

BOOL CExample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CExample1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_sliderX.SetRange(30, 550);
	m_sliderY.SetRange(320, 650);
	m_sliderX.SetPos(30);
	m_sliderY.SetPos(400);
}


// CExample1View 인쇄


void CExample1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CExample1View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}

void CExample1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExample1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExample1View 진단

#ifdef _DEBUG
void CExample1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CExample1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExample1Doc* CExample1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample1Doc)));
	return (CExample1Doc*)m_pDocument;
}
#endif //_DEBUG


// CExample1View 메시지 처리기

void CExample1View::OnClickedButtonOutput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_colorText = RGB(m_nRed, m_nGreen, m_nBlue);
	if (m_nRed > 255 || m_nRed < 0 || m_nGreen > 255 || m_nGreen < 0 ||
		m_nBlue > 255 || m_nBlue < 0)
	{
		AfxMessageBox(_T("잘못된 색상입니다."));
	}
	else
	{
		Invalidate();
	}
}

void CExample1View::OnClickedButtonColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		m_colorText = colorDlg.GetColor();
	}
	m_nRed = GetRValue(m_colorText);
	m_nGreen = GetGValue(m_colorText);
	m_nBlue = GetBValue(m_colorText);

	UpdateData(FALSE);
	Invalidate();
}

void CExample1View::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_strText.Empty();
	m_nRed = 0;
	m_nGreen = 0;
	m_nBlue = 0;
	m_nX = 30;
	m_nY = 400;
	m_sliderX.SetPos(30);
	m_sliderY.SetPos(400);
	UpdateData(FALSE);
	Invalidate();
}

void CExample1View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar->GetSafeHwnd() == m_sliderX.m_hWnd)
		m_nX = m_sliderX.GetPos();
	else if (pScrollBar->GetSafeHwnd() == m_sliderY.m_hWnd)
		m_nY = m_sliderY.GetPos();
	else
		return;

	UpdateData(FALSE);
	Invalidate();
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CExample1View::OnChangeEditRed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_colorText = RGB(m_nRed, m_nGreen, m_nBlue);
	Invalidate();
}

void CExample1View::OnChangeEditGreen()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_colorText = RGB(m_nRed, m_nGreen, m_nBlue);
	Invalidate();
}

void CExample1View::OnChangeEditBlue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_colorText = RGB(m_nRed, m_nGreen, m_nBlue);
	Invalidate();
}

void CExample1View::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC->SetTextColor(m_colorText);
	pDC->TextOut(m_nX, m_nY, m_strText);
}
