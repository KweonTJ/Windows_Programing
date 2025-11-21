// CLeftViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example2.h"
#include "CLeftViewDlg.h"
#include "Example2Doc.h"
#include "Example2View.h"

// CLeftViewDlg

IMPLEMENT_DYNCREATE(CLeftViewDlg, CFormView)

CLeftViewDlg::CLeftViewDlg()
	: CFormView(IDD_FORMVIEW)
	, m_strNodeText(_T(""))
	, m_strSelectedNode(_T(""))
{

}

CLeftViewDlg::~CLeftViewDlg()
{
}

void CLeftViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NODE, m_strNodeText);
	DDX_Text(pDX, IDC_EDIT_SELECTD_NODE, m_strSelectedNode);
}

BEGIN_MESSAGE_MAP(CLeftViewDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CLeftViewDlg::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CLeftViewDlg::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CLeftViewDlg::OnClickedButtonDelete)
END_MESSAGE_MAP()


// CLeftViewDlg 진단

#ifdef _DEBUG
void CLeftViewDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftViewDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftViewDlg 메시지 처리기

void CLeftViewDlg::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExample2View* pView = (CExample2View*)this->GetNextWindow();
	UpdateData(TRUE);
	if (!m_strNodeText.IsEmpty())
	{
		pView->GetTreeCtrl().InsertItem(m_strNodeText, pView->m_hSelectedNode, TVI_LAST);
		pView->GetTreeCtrl().Expand(pView->m_hSelectedNode, TVE_EXPAND);
	}
	else
	{
		AfxMessageBox(_T("입력 노드의 텍스트를 입력하세요."));
	}
	m_strNodeText.Empty();
	UpdateData(FALSE);
}

void CLeftViewDlg::OnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExample2View* pView = (CExample2View*)this->GetNextWindow();
	UpdateData(TRUE);
	if (!m_strNodeText.IsEmpty())
	{
		if (pView->m_hSelectedNode != pView->m_hRoot)
		{
			pView->GetTreeCtrl().SetItemText(pView->m_hSelectedNode, m_strNodeText);
			m_strSelectedNode = m_strNodeText;
		}
		else
		{
			AfxMessageBox(_T("루트 노드는 수정해서는 안 됩니다."));
		}
	}
	else
	{
		AfxMessageBox(_T("루트 노드를 수정해서는 안 됩니다."));
	}
	m_strNodeText.Empty();
	UpdateData(FALSE);
}


void CLeftViewDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExample2View* pView = (CExample2View*)this->GetNextWindow();
	if (pView->m_hSelectedNode != pView->m_hRoot)
	{
		if (AfxMessageBox(_T("정말 삭제하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			pView->GetTreeCtrl().DeleteItem(pView->m_hSelectedNode);
		}
	}
	else
	{
		AfxMessageBox(_T("루트 노드는 삭제해서는 안 됩니다."));
	}
}
