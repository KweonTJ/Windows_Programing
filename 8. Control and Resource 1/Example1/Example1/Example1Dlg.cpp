
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
	, m_strDept(_T(""))
	, m_strID(_T(""))
	, m_strName(_T(""))
	, m_strSelectedItem(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_listStudent);
	DDX_Text(pDX, IDC_EDIT_DEPT, m_strDept);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SELECTED_ITEM, m_strSelectedItem);
}

BEGIN_MESSAGE_MAP(CExample1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CExample1Dlg::OnClickedButtonInsert)
//	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CExample1Dlg::OnClickedButtonDelete)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUDENT, &CExample1Dlg::OnItemchangedListStudent)
ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CExample1Dlg::OnClickedButtonModify)
ON_BN_CLICKED(IDC_BUTTON_DELETE, &CExample1Dlg::OnClickedButtonDelete)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CExample1Dlg::OnClickedButtonReset)
ON_CBN_SELCHANGE(IDC_COMBO_STYLE, &CExample1Dlg::OnSelchangeComboStyle)
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
	// List Control에 컬럼을 추가
	m_listStudent.InsertColumn(0, _T("순번"), LVCFMT_CENTER, 60);
	m_listStudent.InsertColumn(1, _T("학과"), LVCFMT_CENTER, 190);
	m_listStudent.InsertColumn(2, _T("학번"), LVCFMT_CENTER, 150);
	m_listStudent.InsertColumn(3, _T("이름"), LVCFMT_CENTER, 150);

	m_listStudent.SetExtendedStyle(m_listStudent.GetExtendedStyle() |
	LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	((CComboBox*)GetDlgItem(IDC_COMBO_STYLE))->SetCurSel(0);

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);


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


void CExample1Dlg::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_listStudent.GetItemCount();
	CString strCount;

	UpdateData(TRUE);
	if(!m_strDept.IsEmpty() && !m_strID.IsEmpty() && !m_strName.IsEmpty())
	{
		strCount.Format(_T("%d"), nCount + 1);
		m_listStudent.InsertItem(nCount, strCount);
		m_listStudent.SetItem(nCount, 1, LVIF_TEXT, m_strDept, 0, 0, 0, 0);
		m_listStudent.SetItem(nCount, 2, LVIF_TEXT, m_strID, 0, 0, 0, 0);
		m_listStudent.SetItem(nCount, 3, LVIF_TEXT, m_strName, 0, 0, 0, 0);

		m_strDept.Empty();
		m_strID.Empty();
		m_strName.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("학과, 학번, 이름을 입력하세요."));
	}
}


void CExample1Dlg::OnItemchangedListStudent(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

	m_strSelectedItem.Format(_T("%d"), m_nSelectedItem + 1);

	m_strDept = m_listStudent.GetItemText(m_nSelectedItem, 1);
	m_strID = m_listStudent.GetItemText(m_nSelectedItem, 2);
	m_strName = m_listStudent.GetItemText(m_nSelectedItem, 3);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	UpdateData(FALSE);
	*pResult = 0;
}

void CExample1Dlg::OnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strDept, strID, strName, strIndex;
	strDept = m_strDept;
	strID = m_strID;
	strName = m_strName;

	if (m_nSelectedItem >= 0)
	{
		if(!m_strDept.IsEmpty()&& !m_strID.IsEmpty() && !m_strName.IsEmpty())
		{
			strIndex.Format(_T("%d"), m_nSelectedItem + 1);
			m_listStudent.SetItem(m_nSelectedItem, 0, LVIF_TEXT, strIndex, 0, 0, 0, 0);
			m_listStudent.SetItem(m_nSelectedItem, 1, LVIF_TEXT, strDept, 0, 0, 0, 0);
			m_listStudent.SetItem(m_nSelectedItem, 2, LVIF_TEXT, strID, 0, 0, 0, 0);
			m_listStudent.SetItem(m_nSelectedItem, 3, LVIF_TEXT, strName, 0, 0, 0, 0);

			m_strDept.Empty();
			m_strID.Empty();
			m_strName.Empty();
			
			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			UpdateData(FALSE);
		}
		else
		{
			MessageBox(_T("모든 항목을 입력해 주세요."),_T("잠깐"),MB_OK);
		}
	}
	else
	{
		MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);	
	}
}

void CExample1Dlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0)
	{
		m_listStudent.DeleteItem(m_nSelectedItem);
		
		for(int i = m_nSelectedItem -1; i < m_listStudent.GetItemCount(); i++)
		{
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_listStudent.SetItemText(i, 0, strIndex);
		}
		m_strDept.Empty();
		m_strID.Empty();
		m_strName.Empty();
		m_strSelectedItem.Empty();
		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);
	}
}

void CExample1Dlg::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_strDept.Empty();
	m_strID.Empty();
	m_strName.Empty();
	UpdateData(FALSE);
}

void CExample1Dlg::OnSelchangeComboStyle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int numSel = ((CComboBox*)GetDlgItem(IDC_COMBO_STYLE))->GetCurSel();

	switch (numSel)
	{
	case 0:
		m_listStudent.SetView(LV_VIEW_DETAILS);
		break;
	case 1:
		m_listStudent.SetView(LV_VIEW_LIST);
		break;
	case 2:
		m_listStudent.SetView(LV_VIEW_SMALLICON);
		break;
	case 3:
		m_listStudent.SetView(LV_VIEW_ICON);
		break;
	}
//	SetWindowLong(m_listStudent.m_hWnd, GWL_STYLE, setStyle);
}
