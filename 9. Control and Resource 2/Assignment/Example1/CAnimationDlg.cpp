// CAnimationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example1.h"
#include "afxdialogex.h"
#include "CAnimationDlg.h"
#include "Example1Dlg.h"


// CAnimationDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnimationDlg, CDialogEx)

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANIMATION, pParent)
{

}

CAnimationDlg::~CAnimationDlg()
{
}

void CAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_ANIMATION, m_prgsAnimation);
	DDX_Control(pDX, IDC_SLIDER_ANIMATION, m_sliderAnimation);
}


BEGIN_MESSAGE_MAP(CAnimationDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_ANIMATION, &CAnimationDlg::OnClickedButtonAnimation)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAnimationDlg 메시지 처리기

BOOL CAnimationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

	m_prgsAnimation.SetRange(0, pMainDlg->m_dlgRatio.m_nHorizontal);
	m_sliderAnimation.SetRange(0, pMainDlg->m_dlgRatio.m_nHorizontal);

	m_prgsAnimation.SetPos(0);
	m_sliderAnimation.SetPos(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAnimationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar->GetSafeHwnd() == m_sliderAnimation.m_hWnd)
	{
		CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

		pMainDlg->m_dlgRatio.m_nCurHScale = m_sliderAnimation.GetPos();

		pMainDlg->m_dlgRatio.m_nCurVScale =
			(int)((float)pMainDlg->m_dlgRatio.m_nCurHScale *
				((float)pMainDlg->m_dlgRatio.m_nVertical /
					(float)pMainDlg->m_dlgRatio.m_nHorizontal));

		m_prgsAnimation.SetPos(pMainDlg->m_dlgRatio.m_nCurHScale);


		pMainDlg->UpdateDrawing();
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAnimationDlg::OnClickedButtonAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

	m_nAniHScale = 0;
	m_nAniVScale = 0;

	m_prgsAnimation.SetRange(0, pMainDlg->m_dlgRatio.m_nHorizontal);
	m_sliderAnimation.SetRange(0, pMainDlg->m_dlgRatio.m_nHorizontal);
	m_prgsAnimation.SetPos(0);
	m_sliderAnimation.SetPos(0);

	SetTimer(1, 30, NULL);

	GetDlgItem(IDC_BUTTON_ANIMATION)->EnableWindow(FALSE);
}

void CAnimationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent != 1) { CDialogEx::OnTimer(nIDEvent); return; }

	CExample1Dlg* pMainDlg = (CExample1Dlg*)AfxGetMainWnd();

	if (m_nAniHScale != pMainDlg->m_dlgRatio.m_nHorizontal)
	{
		++m_nAniHScale;

		m_nAniVScale = (int)((float)m_nAniHScale *
			((float)pMainDlg->m_dlgRatio.m_nVertical /
				(float)pMainDlg->m_dlgRatio.m_nHorizontal));

		pMainDlg->m_dlgRatio.m_nCurHScale = m_nAniHScale;
		pMainDlg->m_dlgRatio.m_nCurVScale = m_nAniVScale;

		m_prgsAnimation.SetPos(pMainDlg->m_dlgRatio.m_nCurHScale);
		m_sliderAnimation.SetPos(pMainDlg->m_dlgRatio.m_nCurHScale);
	}
	else
	{
		KillTimer(1);
		if (auto* pBtn = GetDlgItem(IDC_BUTTON_ANIMATION))
			pBtn->EnableWindow(TRUE);
	}

	pMainDlg->UpdateDrawing();

	CDialogEx::OnTimer(nIDEvent);
}
