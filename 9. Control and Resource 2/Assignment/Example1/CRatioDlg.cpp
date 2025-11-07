// CRatioDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example1.h"
#include "afxdialogex.h"
#include "CRatioDlg.h"
#include "Example1Dlg.h"


// CRatioDlg 대화 상자

IMPLEMENT_DYNAMIC(CRatioDlg, CDialogEx)

CRatioDlg::CRatioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RATIO, pParent)
	, m_nHorizontal(0)
	, m_nVertical(0)
{

}

CRatioDlg::~CRatioDlg()
{
}

void CRatioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_HORIZONTAL, m_sliderHorizontal);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL, m_sliderVertical);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_nHorizontal);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_nVertical);
}


BEGIN_MESSAGE_MAP(CRatioDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_SAME_RATIO, &CRatioDlg::OnClickedCheckSameRatio)
END_MESSAGE_MAP()


// CRatioDlg 메시지 처리기

BOOL CRatioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bSameRatio = TRUE;
	((CButton*)GetDlgItem(IDC_CHECK_SAME_RATIO))->SetCheck(TRUE);

	m_sliderHorizontal.SetRange(0, 100);
	m_sliderVertical.SetRange(0, 100);
	m_sliderHorizontal.SetPos(50);
	m_sliderVertical.SetPos(50);

	m_nHorizontal = 50;
	m_nVertical = 50;
	m_nCurHScale = 50;
	m_nCurVScale = 50;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRatioDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

	m_nCurHScale = m_sliderHorizontal.GetPos();
	m_nCurVScale = m_sliderVertical.GetPos();
	if (pScrollBar->GetSafeHwnd() == m_sliderHorizontal.m_hWnd)
	{
		if (m_bSameRatio == TRUE)
		{
			m_sliderVertical.SetPos(m_nCurHScale);
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_sliderVertical.m_hWnd)
	{
		if (m_bSameRatio == TRUE)
		{
			m_sliderHorizontal.SetPos(m_nCurVScale);
		}
	}
	else
		return;
	m_nHorizontal = m_nCurHScale;
	m_nVertical = m_nCurVScale;
	UpdateData(FALSE);
	pMainDlg->UpdateDrawing();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRatioDlg::OnClickedCheckSameRatio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();
	m_bSameRatio = !m_bSameRatio;
	if (m_bSameRatio)
	{
		if (m_nCurHScale > m_nCurVScale)
		{
			m_nHorizontal = m_sliderHorizontal.GetPos();
			m_nVertical = m_nHorizontal;
		}
		else
		{
			m_nVertical = m_sliderVertical.GetPos();
			m_nHorizontal = m_nVertical;
		}
		m_nCurHScale = m_nHorizontal;
		m_nCurVScale = m_nVertical;
		m_sliderHorizontal.SetPos(m_nCurHScale);
		m_sliderVertical.SetPos(m_nCurVScale);
		UpdateData(FALSE);
	}
	pMainDlg->UpdateDrawing();
}
