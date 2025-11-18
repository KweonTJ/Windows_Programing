
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCVSLISTBOX_CARDLIST, m_listNamdCard);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID_CARD, m_pgCardInfo);
	DDX_Control(pDX, IDC_MFCFONTCOMBO_TEXT, m_fcbText);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_TEXT, m_cbtnText);
}

BEGIN_MESSAGE_MAP(CExample1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON_TEXT, &CExample1Dlg::OnClickedMfccolorbuttonText)
	ON_CBN_SELCHANGE(IDC_MFCFONTCOMBO_TEXT, &CExample1Dlg::OnSelchangeMfcfontcomboText)
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
	m_nCount = 0;
	m_nSelectedCard = 0;

	m_cbtnText.SetColor(RGB(0, 0, 0));

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);
	m_fcbText.SelectFont(lf.lfFaceName);

	m_listNamdCard.SetWindowText(_T("명함 목록"));

	InitializePropGrid(NameCard());

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExample1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CExample1Dlg::AddNameCard(CString strName)
{
	// TODO: 여기에 구현 코드 추가.
	NameCard card;
	card.strName = strName;

	m_pNameCards[m_nCount++] = card;
	DrawNameCard(card);
	InitializePropGrid(card);
}

void CExample1Dlg::SelectNameCard(int nIndex)
{
	// TODO: 여기에 구현 코드 추가.
	m_nSelectedCard = nIndex;
	DrawNameCard(m_pNameCards[nIndex]);
	InitializePropGrid(m_pNameCards[nIndex]);
}

void CExample1Dlg::DeleteNameCard(int nIndex)
{
	// TODO: 여기에 구현 코드 추가.
	if (nIndex != (m_nCount - 1))
	{
		memcpy(&m_pNameCards[nIndex], &m_pNameCards[nIndex + 1],
			sizeof(NameCard) * (m_nCount - nIndex + 1));
	}
	m_nCount--;
}

void CExample1Dlg::InitializePropGrid(NameCard card)
{
	// TODO: 여기에 구현 코드 추가.
	HDITEM item;
	item.cxy = 110;
	item.mask = HDI_WIDTH;
	m_pgCardInfo.GetHeaderCtrl().SetItem(0, &item);

	m_pgCardInfo.RemoveAll();
	m_pgCardInfo.EnableHeaderCtrl(FALSE);
	m_pgCardInfo.SetVSDotNetLook();
	m_pgCardInfo.EnableDescriptionArea();

	// 1. 개인 신상 정보
	CMFCPropertyGridProperty* pGroupInfo = new CMFCPropertyGridProperty(_T("명함 정보"));
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(_T("회 사"),
		card.strCompany, _T("회사 이름을 입력하세요."), 0));

	CMFCPropertyGridProperty* pTitle = new CMFCPropertyGridProperty(
		_T("직 책"), card.strTitle, _T("직책을 선택하세요."), 1);
	pTitle->AddOption(_T("대표"));
	pTitle->AddOption(_T("부장"));
	pTitle->AddOption(_T("과장"));
	pTitle->AddOption(_T("사원"));
	pTitle->AllowEdit(FALSE);
	pGroupInfo->AddSubItem(pTitle);

	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(_T("이 름"),
		card.strName, _T("이름을 입력하세요."), 2));
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(_T("연락처"),
		card.strContact, _T("연락처를 입력하세요."), 3));

	m_pgCardInfo.AddProperty(pGroupInfo);
	m_pgCardInfo.UpdateData(FALSE);
}

void CExample1Dlg::DrawNameCard(NameCard card)
{
	// TODO: 여기에 구현 코드 추가.
	CRect rc;
	CFont font, * pOldFont;
	CDC* pDC = GetDlgItem(IDC_STATIC_NAMECARD)->GetDC();
	GetDlgItem(IDC_STATIC_NAMECARD)->GetClientRect(&rc);

	//배경
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));

	LOGFONT lf;
	CMFCFontInfo* pInfo = m_fcbText.GetSelFont();
	afxGlobalData.fontRegular.GetLogFont(&lf);

	lf.lfCharSet = pInfo->m_nCharSet;
	lf.lfPitchAndFamily = pInfo->m_nPitchAndFamily;
	lstrcpyn(lf.lfFaceName, pInfo->m_strName, LF_FACESIZE);
	lf.lfHeight = 50;

	font.CreateFontIndirect(&lf);
	pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(m_cbtnText.GetColor());
	pDC->TextOut(15, 15, card.strCompany);  // 회사 이름

	CRect rcTitle(rc);
	rcTitle.right = rc.CenterPoint().x;
	pDC->DrawText(card.strTitle, &rcTitle, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	CRect rcName(rc);
	rcName.left = rc.CenterPoint().x;
	pDC->DrawText(card.strName, &rcName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	lf.lfCharSet = pInfo->m_nCharSet;
	lf.lfPitchAndFamily = pInfo->m_nPitchAndFamily;
	lstrcpyn(lf.lfFaceName, pInfo->m_strName, LF_FACESIZE);
	lf.lfHeight = 25;

	font.CreateFontIndirect(&lf);
	pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(m_cbtnText.GetColor());

	CString str;
	CRect rcContact(rc);

	rcContact.right = rcContact.right - 20;
	rcContact.bottom = rcContact.bottom - 20;
	str.Format(_T("연락처 : %s"), card.strContact);
	int nHeight = pDC->DrawText(str, &rcContact, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	font.DeleteObject();
}

LRESULT CExample1Dlg::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	// wParam- control id, lParam- a pointer to property that changed
	CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)lParam;
	switch (pProperty->GetData())
	{
	case 0:
		m_pNameCards[m_nSelectedCard].strCompany = pProperty->GetValue();
		break;
	case 1:
		m_pNameCards[m_nSelectedCard].strTitle = pProperty->GetValue();
		break;
	case 2:
		m_pNameCards[m_nSelectedCard].strName = pProperty->GetValue();
		break;
	case 3:
		m_pNameCards[m_nSelectedCard].strContact = pProperty->GetValue();
		break;
	}
	DrawNameCard(m_pNameCards[m_nSelectedCard]);
	return 0L;
}
void CExample1Dlg::OnClickedMfccolorbuttonText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DrawNameCard(m_pNameCards[m_nSelectedCard]);
}

void CExample1Dlg::OnSelchangeMfcfontcomboText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DrawNameCard(m_pNameCards[m_nSelectedCard]);
}
