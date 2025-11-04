
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
	, m_strID(_T(""))
	, m_strYear(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEPT, m_treeDept);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_listStudent);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_CBString(pDX, IDC_COMBO_YEAR, m_strYear);
}

BEGIN_MESSAGE_MAP(CAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPT, &CAssignmentDlg::OnSelchangedTreeDept)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUDENT, &CAssignmentDlg::OnItemchangedListStudent)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CAssignmentDlg::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAssignmentDlg::OnClickedButtonDelete)
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
	m_hRoot = m_treeDept.InsertItem(_T("한국대학교"),TVI_ROOT, TVI_LAST);
	m_hComputer = m_treeDept.InsertItem(_T("컴퓨터공학과"), m_hRoot, TVI_LAST);
	m_hInfomation = m_treeDept.InsertItem(_T("정보통신공학과"), m_hRoot, TVI_LAST);

	m_treeDept.Expand(m_hRoot, TVE_EXPAND);

	m_listStudent.InsertColumn(0, _T("학번"), LVCFMT_CENTER, 150);
	m_listStudent.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 150);
	m_listStudent.InsertColumn(2, _T("학년"), LVCFMT_CENTER, 150);

	// ((CComboBox*)GetDlgItem(IDC_COMBO_YEAR))->SetCurSel(0);

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

void CAssignmentDlg::InsertListItem(int index)
{
	// TODO: 여기에 구현 코드 추가.
	int nCount = m_listStudent.GetItemCount();

	m_listStudent.InsertItem(nCount, m_StudentInfo[index].strID);
	m_listStudent.SetItem(nCount, 1, LVIF_TEXT, m_StudentInfo[index].strName, 0, 0, 0, 0);
	m_listStudent.SetItem(nCount, 2, LVIF_TEXT, m_StudentInfo[index].strYear, 0, 0, 0, 0);
}


void CAssignmentDlg::OnSelchangedTreeDept(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	m_listStudent.DeleteAllItems();
	m_nSelectedItem = -1;

	CString selText = m_treeDept.GetItemText(m_hSelectedNode);

	for (int i = 0; i<m_nCount; i++)
	{
		if (m_treeDept.GetItemText(m_hSelectedNode) == m_StudentInfo[i].strDept ||
			m_hSelectedNode == m_hRoot)
		{
			InsertListItem(i);
		}
	}

	*pResult = 0;
}

void CAssignmentDlg::OnItemchangedListStudent(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uChanged & LVIF_STATE) &&
		((pNMLV->uNewState ^ pNMLV->uOldState) & LVIS_SELECTED))
	{
		if (pNMLV->uNewState & LVIS_SELECTED)
			m_nSelectedItem = pNMLV->iItem;   // 현재 선택된 행 인덱스
		else
			m_nSelectedItem = -1;             // 선택 해제
	}
	*pResult = 0;
}

void CAssignmentDlg::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int nCount = m_listStudent.GetItemCount();
	if (m_hSelectedNode != m_hRoot)
	{
		if (!m_strID.IsEmpty() && !m_strName.IsEmpty() && !m_strYear.IsEmpty())
		{
			CString selDept = m_treeDept.GetItemText(m_hSelectedNode);

			for (int i = 0; i < m_nCount; i++)
			{
				if ((m_StudentInfo[i].strID == m_strID) &&
					(m_StudentInfo[i].strName == m_strName) &&
					(m_StudentInfo[i].strYear == m_strYear) &&
					(m_StudentInfo[i].strDept == selDept))
				{
					AfxMessageBox(_T("이미 존재하는 학생입니다."));
					return;
				}
			}

			m_StudentInfo[m_nCount].strID = m_strID;
			m_StudentInfo[m_nCount].strName = m_strName;
			m_StudentInfo[m_nCount].strYear = m_strYear;
			m_StudentInfo[m_nCount].strDept = selDept;

			InsertListItem(m_nCount);

			m_nCount++;

			m_strID.Empty();
			m_strName.Empty();
			m_strYear.Empty();

			UpdateData(FALSE);
		}
		else
		{
			AfxMessageBox(_T("모든 항목을 입력해 주세요."));
		}
	}
	else
	{
		AfxMessageBox(_T("학과 노드를 선택해 주세요."));
	}
}

void CAssignmentDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("정말로 삭제하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		int nIndex = -1;
		for (int i =0; i < m_nCount; i++)
		{
			if ((m_StudentInfo[i].strID==m_listStudent.GetItemText(m_nSelectedItem,0)) &&
				(m_StudentInfo[i].strName==m_listStudent.GetItemText(m_nSelectedItem,1)) &&
				(m_StudentInfo[i].strYear == m_listStudent.GetItemText(m_nSelectedItem, 2)))
			{
				nIndex = i;
				break;
			}
		}

		if (nIndex != -1)
		{
			// 아래 학생들을 한 칸씩 위로 이동
			for (int j = nIndex; j < m_nCount - 1; j++)
			{
				m_StudentInfo[j] = m_StudentInfo[j + 1];
			}

			// 3. 전체 학생 수 감소
			m_nCount--;

			// 4. List Control 초기화
			m_listStudent.DeleteAllItems();

			// 5. 현재 선택된 노드에 해당하는 학생만 다시 출력
			CString selDept = m_treeDept.GetItemText(m_hSelectedNode);

			for (int i = 0; i < m_nCount; i++)
			{
				if (m_hSelectedNode == m_hRoot || m_StudentInfo[i].strDept == selDept)
				{
					InsertListItem(i);
				}
			}
		}
	}
}

