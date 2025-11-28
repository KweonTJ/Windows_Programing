
// Example1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Example1.h"
#include "Example1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// extern "C" __declspec(dllimport) void Calender(int year, int month, int* Days);

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


// CExample1Dlg 대화 상자



CExample1Dlg::CExample1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMPLE1_DIALOG, pParent)
	, m_nYear(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_nYear);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_nYear);
	DDX_Control(pDX, IDC_COMBO_MONTH, m_cbMonth);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_spinYear);
}

BEGIN_MESSAGE_MAP(CExample1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_MONTH, &CExample1Dlg::OnSelchangeComboMonth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_YEAR, &CExample1Dlg::OnDeltaposSpinYear)
END_MESSAGE_MAP()


// CExample1Dlg 메시지 처리기

BOOL CExample1Dlg::OnInitDialog()
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
	CTime time = CTime::GetCurrentTime();
	m_nYear = time.GetYear();
	m_nMonth = time.GetMonth() - 1;

	m_cbMonth.SetCurSel(m_nMonth);
	m_spinYear.SetRange(1583, 4040);
	m_spinYear.SetPos(m_nYear);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExample1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExample1Dlg::OnPaint()
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
		int m_nDays[6][7] = { 0 };
		int i, j, x, y;

		x = 60;
		y = 150;

		CString m_Weekday[7] = { _T("Sun"),_T("Mon"),_T("Tue"),_T("Wed"),_T("Thu"),_T("Fri"),_T("Sat") };
		CString m_Number;

		CPaintDC dc(this);
		dc.SetBkColor(RGB(240, 238, 228));

		for (i = 0; i < 7; i++)
		{
			dc.TextOutW(x + i * 50, y - 30, m_Weekday[i]);
			x += 40;
		}
		// Calender(m_nYear, m_nMonth, &m_nDays[0][0]);

		HINSTANCE hDLL;
		hDLL = LoadLibrary(_T("CalenderDLL.dll"));

		typedef int(*CalenderFunc)(int year, int month, int* Days);

		CalenderFunc lpCalender;
		lpCalender = (CalenderFunc)GetProcAddress(hDLL, "Calender");
		lpCalender(m_nYear, m_nMonth, &m_nDays[0][0]);

		for (i = 0; i < 6; i++)
		{
			x = 60;
			for (j = 0; j < 7; j++)
			{
				if (m_nDays[i][j] != 0)
				{
					m_Number.Format(_T("%d"), m_nDays[i][j]);
					dc.TextOutW(x + j * 50, y + i * 30, m_Number);
				}
				x += 40;
			}
			y += 30;
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExample1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CExample1Dlg::OnSelchangeComboMonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItem = m_cbMonth.GetCurSel();
	m_nMonth = nItem;
	Invalidate();
}

void CExample1Dlg::OnDeltaposSpinYear(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nYear += pNMUpDown->iDelta;
	if(m_nYear < 1583)
		m_nYear = 1583;
	else if (m_nYear > 4040)
		m_nYear = 4040;
	Invalidate();
	*pResult = 0;
}
