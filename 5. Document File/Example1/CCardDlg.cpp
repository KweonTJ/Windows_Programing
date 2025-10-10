// CCardDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example1.h"
#include "afxdialogex.h"
#include "CCardDlg.h"


// CCardDlg 대화 상자

IMPLEMENT_DYNAMIC(CCardDlg, CDialogEx)

CCardDlg::CCardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CARD, pParent)
	, m_strDept(_T(""))
	, m_strName(_T(""))
{

}

CCardDlg::~CCardDlg()
{
}

void CCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_DEPT, m_strDept);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CCardDlg, CDialogEx)
	ON_COMMAND(IDC_RADIO_FEMALE, &CCardDlg::OnRadioFemale)
	ON_COMMAND(IDC_RADIO_MALE, &CCardDlg::OnRadioMale)
	ON_BN_CLICKED(IDC_CHECK_FISHING, &CCardDlg::OnClickedCheckFishing)
	ON_BN_CLICKED(IDC_CHECK_READING, &CCardDlg::OnClickedCheckReading)
	ON_BN_CLICKED(IDC_CHECK_SPORTS, &CCardDlg::OnClickedCheckSports)
END_MESSAGE_MAP()


// CCardDlg 메시지 처리기

BOOL CCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bSex = true;
	m_bHobby[0] = m_bHobby[1] = m_bHobby[2] = false;
	((CButton*)GetDlgItem(IDC_RADIO_MALE))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCardDlg::OnRadioFemale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bSex = false;
}

void CCardDlg::OnRadioMale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bSex = true;
}

void CCardDlg::OnClickedCheckFishing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bHobby[2] = !m_bHobby[2];
}

void CCardDlg::OnClickedCheckReading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bHobby[0] = !m_bHobby[0];
}

void CCardDlg::OnClickedCheckSports()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bHobby[1] = !m_bHobby[1];
}
