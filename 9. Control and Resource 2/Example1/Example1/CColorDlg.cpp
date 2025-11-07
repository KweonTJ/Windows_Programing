// CColorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example1.h"
#include "afxdialogex.h"
#include "CColorDlg.h"
#include "Example1Dlg.h"


// CColorDlg 대화 상자

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COLOR, pParent)
	, m_nRed(0)
	, m_nGreen(0)
	, m_nBlue(0)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_RED, m_sliderRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_sliderGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_sliderBlue);
	DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_nGreen);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_nBlue);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CColorDlg 메시지 처리기

BOOL CColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_colorObject = RGB(255, 0, 0);
	m_sliderRed.SetRange(0, 255);
	m_sliderGreen.SetRange(0, 255);
	m_sliderBlue.SetRange(0, 255);
	m_sliderRed.SetPos(255);
	m_sliderGreen.SetPos(0);
	m_sliderBlue.SetPos(0);
	m_nRed = 255;
	m_nGreen = 0;
	m_nBlue = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CColorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

	if (pScrollBar->GetSafeHwnd() == m_sliderRed.m_hWnd)
		m_nRed = m_sliderRed.GetPos();
	else if (pScrollBar->GetSafeHwnd() == m_sliderGreen.m_hWnd)
		m_nGreen = m_sliderGreen.GetPos();
	else if (pScrollBar->GetSafeHwnd() == m_sliderBlue.m_hWnd)
		m_nBlue = m_sliderBlue.GetPos();
	else
		return;
	m_colorObject = RGB(m_nRed, m_nGreen, m_nBlue);
	UpdateData(FALSE);
	pMainDlg->UpdateDrawing();;
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
