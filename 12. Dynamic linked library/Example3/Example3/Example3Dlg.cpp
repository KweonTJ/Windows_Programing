
// Example3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Example3.h"
#include "Example3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExample3Dlg 대화 상자



CExample3Dlg::CExample3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMPLE3_DIALOG, pParent)
	, m_strHeight(_T(""))
	, m_strResult(_T(""))
	, m_strWeight(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_strHeight);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_strWeight);
}

BEGIN_MESSAGE_MAP(CExample3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_RADIO_MALE, &CExample3Dlg::OnRadioMale)
	ON_COMMAND(IDC_RADIO2_FEMALE, &CExample3Dlg::OnRadio2Female)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CExample3Dlg::OnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CExample3Dlg::OnClickedButtonReset)
END_MESSAGE_MAP()


// CExample3Dlg 메시지 처리기

BOOL CExample3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExample3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExample3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExample3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CExample3Dlg::OnRadioMale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_chGender = 'M';
}

void CExample3Dlg::OnRadio2Female()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_chGender = 'F';
}

void CExample3Dlg::OnClickedButtonCalculate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString result1, result2;
	double height, weight, std_weight, bmi;

	UpdateData(TRUE);
	height = _wtof(m_strHeight);
	weight = _wtof(m_strWeight);

	bmi = m_calcBMI.CalculateBMI(height, weight);
	std_weight = m_calcBMI.CalculateStdWeight(m_chGender, height, weight);

	result1.Format(_T("당신의 비만도는 %.2f이고, %s 입니다."), bmi, m_calcBMI.DetermineObesity());
	if (bmi < 18.5)
	{
		result2.Format(_T("당신의 표준 체중은 %.1fkg 이므로 %.1fkg 증량이 필요합니다."), std_weight, std_weight - weight);
	}
	else if (bmi < 23.0)
	{
		result2.Format(_T("당신의 표준 체중은 %.1fkg 이고 현재 정상체중입니다."), std_weight);
	}
	else
	{
		result2.Format(_T("당신의 표준 체중은 %.1fkg 이므로 %.1fkg 감량이 필요합니다."), std_weight, weight - std_weight);
	}
	m_strResult = result1 + _T("\r\n") + result2;
	UpdateData(FALSE);
}

void CExample3Dlg::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_MALE))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO2_FEMALE))->SetCheck(FALSE);
	m_strHeight.Empty();
	m_strWeight.Empty();
	m_strResult.Empty();
	UpdateData(FALSE);
}
