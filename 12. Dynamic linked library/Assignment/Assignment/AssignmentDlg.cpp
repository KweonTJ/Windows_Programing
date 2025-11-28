
// AssignmentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Assignment.h"
#include "AssignmentDlg.h"
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


// CAssignmentDlg 대화 상자



CAssignmentDlg::CAssignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSIGNMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_NUM1, &CAssignmentDlg::OnBnClickedRadioNum1)
	ON_BN_CLICKED(IDC_RADIO_NUM2, &CAssignmentDlg::OnBnClickedRadioNum2)
	ON_BN_CLICKED(IDC_BUTTON_1, &CAssignmentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CAssignmentDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CAssignmentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CAssignmentDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CAssignmentDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CAssignmentDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CAssignmentDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CAssignmentDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CAssignmentDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CAssignmentDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAssignmentDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRACT, &CAssignmentDlg::OnBnClickedButtonSubtract)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CAssignmentDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CAssignmentDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CAssignmentDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CAssignmentDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CAssignmentDlg::OnBnClickedButtonEqual)
END_MESSAGE_MAP()


// CAssignmentDlg 메시지 처리기

BOOL CAssignmentDlg::OnInitDialog()
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

void CAssignmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAssignmentDlg::OnPaint()
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
HCURSOR CAssignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAssignmentDlg::MakeNumber(int nNumber)
{
	// TODO: 여기에 구현 코드 추가.
	UINT operand1, operand2;
	switch (m_nOperand)
	{
	case 1:
		operand1 = GetDlgItemInt(IDC_EDIT_NUM1, NULL, FALSE);
		if (operand1 < 10000)
			operand1 = operand1 * 10 + nNumber;
		else
			AfxMessageBox(_T("자릿수는 5자리까지만 가능합니다."));

		SetDlgItemInt(IDC_EDIT_NUM1, operand1, FALSE);
		break;
	case 2:
		operand2 = GetDlgItemInt(IDC_EDIT_NUM2, NULL, FALSE);
		if (operand2 < 10000)
			operand2 = operand2 * 10 + nNumber;
		else
			AfxMessageBox(_T("자릿수는 5자리까지만 가능합니다."));
		SetDlgItemInt(IDC_EDIT_NUM2, operand2, FALSE);
		break;
	default:
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
}

void CAssignmentDlg::OnBnClickedRadioNum1()
{
	m_nOperand = 1;
}

void CAssignmentDlg::OnBnClickedRadioNum2()
{
	m_nOperand = 2;
}

void CAssignmentDlg::OnBnClickedButton1()
{
	MakeNumber(1);
}

void CAssignmentDlg::OnBnClickedButton2()
{
	MakeNumber(2);
}

void CAssignmentDlg::OnBnClickedButton3()
{
	MakeNumber(3);
}

void CAssignmentDlg::OnBnClickedButton4()
{
	MakeNumber(4);
}

void CAssignmentDlg::OnBnClickedButton5()
{
	MakeNumber(5);
}

void CAssignmentDlg::OnBnClickedButton6()
{
	MakeNumber(6);
}

void CAssignmentDlg::OnBnClickedButton7()
{
	MakeNumber(7);
}

void CAssignmentDlg::OnBnClickedButton8()
{
	MakeNumber(8);
}

void CAssignmentDlg::OnBnClickedButton9()
{
	MakeNumber(9);
}

void CAssignmentDlg::OnBnClickedButton0()
{
	MakeNumber(0);
}

void CAssignmentDlg::OnBnClickedButtonAdd()
{
	m_chOperator = '+';
}

void CAssignmentDlg::OnBnClickedButtonSubtract()
{
	m_chOperator = '-';
}

void CAssignmentDlg::OnBnClickedButtonMultiply()
{
	m_chOperator = '*';
}

void CAssignmentDlg::OnBnClickedButtonDivide()
{
	m_chOperator = '/';
}

void CAssignmentDlg::OnBnClickedButtonBack()
{
	UINT operand = 0;
	int nEditID = (m_nOperand == 1) ? IDC_EDIT_NUM1 : IDC_EDIT_NUM2;

	operand = GetDlgItemInt(nEditID, NULL, FALSE);
	operand /= 10;

	SetDlgItemInt(nEditID, operand, FALSE);
}

void CAssignmentDlg::OnBnClickedButtonClear()
{
	((CButton*)GetDlgItem(IDC_RADIO_NUM1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_NUM2))->SetCheck(BST_UNCHECKED);
	m_nOperand = 0;
	m_chOperator = 0;

	SetDlgItemInt(IDC_EDIT_NUM1, 0, FALSE);
	SetDlgItemInt(IDC_EDIT_NUM2, 0, FALSE);
	SetDlgItemText(IDC_EDIT_RESULT, _T(""));
}

void CAssignmentDlg::OnBnClickedButtonEqual()
{
	CString strResult;
	int nNum1, nNum2, nResult;
	float fResult;

	nNum1 = GetDlgItemInt(IDC_EDIT_NUM1, NULL, FALSE);
	nNum2 = GetDlgItemInt(IDC_EDIT_NUM2, NULL, FALSE);

	switch (m_chOperator)
	{
	case '+':
		nResult = m_calculator.Add(nNum1, nNum2);
		strResult.Format(_T("%d"), nResult);
		break;
	case '-':
		nResult = m_calculator.Subtract(nNum1, nNum2);
		strResult.Format(_T("%d"), nResult);
		break;
	case '*':
		nResult = m_calculator.Multiply(nNum1, nNum2);
		strResult.Format(_T("%d"), nResult);
		break;
	case '/':
		if (nNum2 == 0)
		{
			AfxMessageBox(_T("0으로 나눌 수 없습니다."));
			return;
		}
		fResult = m_calculator.Divide(nNum1, nNum2);
		strResult.Format(_T("%.2f"), fResult);
		break;
	}
	SetDlgItemText(IDC_EDIT_RESULT, strResult);
}
