
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
	, m_strName(_T(""))
	, m_strContact(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMBERS, m_listMembers);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID_MEMBER, m_proMember);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_CONTANT, m_strContact);
}

BEGIN_MESSAGE_MAP(CAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAssignmentDlg::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAssignmentDlg::OnClickedButtonDelete)
	ON_COMMAND(IDC_RADIO_MALE, &CAssignmentDlg::OnRadioMale)
	ON_COMMAND(IDC_RADIO_FEMALE, &CAssignmentDlg::OnRadioFemale)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MEMBERS, &CAssignmentDlg::OnItemchangedListMembers)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CAssignmentDlg::OnPropertyChanged)
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
	m_bSex = TRUE;
	m_nSelectedMember = -1;

	m_listMembers.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 60);
	m_listMembers.InsertColumn(1, _T("이름"), LVCFMT_LEFT, 100);
	m_listMembers.InsertColumn(2, _T("성별"), LVCFMT_LEFT, 80);
	m_listMembers.InsertColumn(3, _T("연락처"), LVCFMT_LEFT, 180);

	DWORD dwStyle = m_listMembers.GetExtendedStyle();
	m_listMembers.SetExtendedStyle(dwStyle |
		LVS_EX_GRIDLINES |
		LVS_EX_FULLROWSELECT);


	CheckRadioButton(IDC_RADIO_MALE, IDC_RADIO_FEMALE, IDC_RADIO_MALE);

	UpdatePropGrid(_T(""), m_bSex, _T(""));

	return TRUE;  
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


void CAssignmentDlg::UpdatePropGrid(CString strName, bool bSex, CString strContact)
{
	HDITEM item;
	item.cxy = 150;        
	item.mask = HDI_WIDTH;
	m_proMember.GetHeaderCtrl().SetItem(0, &item);

	m_proMember.RemoveAll();

	m_proMember.EnableHeaderCtrl(FALSE);
	m_proMember.EnableDescriptionArea();
	m_proMember.SetVSDotNetLook(TRUE);
	m_proMember.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroupInfo =
		new CMFCPropertyGridProperty(_T("회원 정보"));

	CMFCPropertyGridProperty* pNameProp =
		new CMFCPropertyGridProperty(
			_T("이름"),
			(_variant_t)strName,
			_T("회원의 이름입니다.")
		);
	pNameProp->SetData(0);
	pGroupInfo->AddSubItem(pNameProp);

	CString strSex = bSex ? _T("남자") : _T("여자");
	CMFCPropertyGridProperty* pSexProp =
		new CMFCPropertyGridProperty(
			_T("성별"),
			(_variant_t)strSex,
			_T("회원의 성별입니다.")
		);
	pSexProp->AddOption(_T("남자"));
	pSexProp->AddOption(_T("여자"));
	pSexProp->AllowEdit(FALSE);
	pSexProp->SetData(1);
	pGroupInfo->AddSubItem(pSexProp);

	CMFCPropertyGridProperty* pContactProp =
		new CMFCPropertyGridProperty(
			_T("연락처"),
			(_variant_t)strContact,
			_T("회원의 연락처입니다.")
		);
	pContactProp->SetData(2);
	pGroupInfo->AddSubItem(pContactProp);

	m_proMember.AddProperty(pGroupInfo);

	CMFCPropertyGridProperty* pGroupView =
		new CMFCPropertyGridProperty(_T("보기"));

	CMFCPropertyGridProperty* pViewMode =
		new CMFCPropertyGridProperty(
			_T("리스트 뷰"),
			(_variant_t)_T("자세히"),
			_T("리스트 뷰 모드를 선택합니다.")
		);
	pViewMode->AddOption(_T("자세히"));
	pViewMode->AddOption(_T("목록"));
	pViewMode->AddOption(_T("큰 아이콘"));
	pViewMode->AllowEdit(FALSE);
	pViewMode->SetData(3);
	pGroupView->AddSubItem(pViewMode);

	m_proMember.AddProperty(pGroupView);

	m_proMember.AdjustLayout();
}

void CAssignmentDlg::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);   

	int nCount = m_listMembers.GetItemCount();

	m_bSex = (IsDlgButtonChecked(IDC_RADIO_MALE) == BST_CHECKED);

	if (!m_strName.IsEmpty() && !m_strContact.IsEmpty())
	{
		CString strNo;
		strNo.Format(_T("%d"), nCount + 1); 

		CString strSex = m_bSex ? _T("남자") : _T("여자");

		int nItem = m_listMembers.InsertItem(nCount, strNo);  
		m_listMembers.SetItemText(nItem, 1, m_strName);       
		m_listMembers.SetItemText(nItem, 2, strSex);          
		m_listMembers.SetItemText(nItem, 3, m_strContact);    

		m_nSelectedMember = nItem;
		m_listMembers.SetItemState(nItem,
			LVIS_SELECTED | LVIS_FOCUSED,
			LVIS_SELECTED | LVIS_FOCUSED);

		UpdatePropGrid(m_strName, m_bSex, m_strContact);

		m_strName.Empty();
		m_strContact.Empty();
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("모든 항목을 입력해 주세요."), _T("잠깐만"), MB_OK | MB_ICONEXCLAMATION);
	}
}

void CAssignmentDlg::OnItemchangedListMembers(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uChanged & LVIF_STATE) &&
		(pNMLV->uNewState & LVIS_SELECTED))
	{
		m_nSelectedMember = pNMLV->iItem;

		CString strName = m_listMembers.GetItemText(m_nSelectedMember, 1);
		CString strSex = m_listMembers.GetItemText(m_nSelectedMember, 2);
		CString strContact = m_listMembers.GetItemText(m_nSelectedMember, 3);

		bool bSex = (strSex == _T("남자"));

		UpdatePropGrid(strName, bSex, strContact);
	}

	*pResult = 0;
}

void CAssignmentDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedMember >= 0)
	{
		if (AfxMessageBox(_T("정말로 삭제하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			int nDeleteIndex = m_nSelectedMember;
			int nCount = m_listMembers.GetItemCount();

			m_listMembers.DeleteItem(nDeleteIndex);

			for (int i = nDeleteIndex; i < nCount - 1; ++i)
			{
				CString strNo;
				strNo.Format(_T("%d"), i + 1);
				m_listMembers.SetItemText(i, 0, strNo);
			}

			UpdatePropGrid(_T(""), TRUE, _T(""));

			m_nSelectedMember = -1;
		}
	}
	else
	{
		MessageBox(_T("아이템을 선택하지 않았습니다."),
			_T("알림"), MB_OK | MB_ICONEXCLAMATION);
	}
}

void CAssignmentDlg::OnRadioMale()
{
	m_bSex = TRUE;
}

void CAssignmentDlg::OnRadioFemale()
{
	m_bSex = FALSE;
}

LRESULT CAssignmentDlg::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CString strName, strContact, strSex;
	CMFCPropertyGridProperty* pProperty =
		(CMFCPropertyGridProperty*)lParam;

	if (m_nSelectedMember >= 0)
	{
		switch ((int)pProperty->GetData())
		{
		case 0:    
			strName = (LPCTSTR)(_bstr_t)pProperty->GetValue();
			m_listMembers.SetItemText(m_nSelectedMember, 1, strName);
			break;

		case 1:    
			strSex = (LPCTSTR)(_bstr_t)pProperty->GetValue();
			m_listMembers.SetItemText(m_nSelectedMember, 2, strSex);
			m_bSex = (strSex == _T("남자"));
			break;

		case 2:  
			strContact = (LPCTSTR)(_bstr_t)pProperty->GetValue();
			m_listMembers.SetItemText(m_nSelectedMember, 3, strContact);
			break;

		case 3:  
		{
			CString strView = (LPCTSTR)(_bstr_t)pProperty->GetValue();

			if (strView == _T("자세히"))
			{
				m_listMembers.SetView(LVS_REPORT);
			}
			else if (strView == _T("목록"))
			{
				m_listMembers.SetView(LVS_LIST);
			}
			else
			{
				m_listMembers.SetView(LVS_ICON);
			}
			break;
		}

		default:
			break;
		}
	}
	else
	{
		MessageBox(_T("아이템을 선택하지 않았습니다."),
			_T("잠깐"), MB_OK);
	}

	return 0L;
}
