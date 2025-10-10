// CInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Assignment.h"
#include "afxdialogex.h"
#include "CInputDlg.h"


// CInputDlg 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT, pParent)
	, m_strText(_T(""))
	, m_nX(0)
	, m_nY(0)
{
	m_nX = 30;
	m_nY = 30;
}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_cbColor);
	DDX_CBIndex(pDX, IDC_COMBO_COLOR, m_nDocColor);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
END_MESSAGE_MAP()


// CInputDlg 메시지 처리기

BOOL CInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_COLOR);

	if (pCombo)
	{
		pCombo->ResetContent(); // 기존 항목 제거
		pCombo->AddString(_T("BLACK"));
		pCombo->AddString(_T("RED"));
		pCombo->AddString(_T("GREEN"));
		pCombo->AddString(_T("BLUE"));
		pCombo->SetCurSel(0);   // 첫 번째 선택
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
