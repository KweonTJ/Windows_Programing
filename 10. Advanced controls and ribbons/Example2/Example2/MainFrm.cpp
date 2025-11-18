// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Example2.h"

#include "MainFrm.h"
#include "Example2Doc.h"	
#include "Example2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_COMBO_OBJECT, &CMainFrame::OnComboObject)
	ON_COMMAND(ID_BUTTON_ERASER, &CMainFrame::OnButtonEraser)
	ON_COMMAND(ID_BUTTON_LINECOLOR, &CMainFrame::OnButtonLinecolor)
	ON_COMMAND(ID_BUTTON_FILLCOLOR, &CMainFrame::OnButtonFillcolor)
	ON_COMMAND(ID_SLIDER_ZOOM, &CMainFrame::OnSliderZoom)
	ON_COMMAND(ID_CHECK_POINTS, &CMainFrame::OnCheckPoints)
	ON_UPDATE_COMMAND_UI(ID_CHECK_POINTS, &CMainFrame::OnUpdateCheckPoints)
	ON_COMMAND(ID_EDIT_TEXT, &CMainFrame::OnEditText)
	ON_COMMAND(ID_SPIN_SIZE, &CMainFrame::OnSpinSize)
	ON_COMMAND(ID_BUTTON_TEXTCOLOR, &CMainFrame::OnButtonTextcolor)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 인쇄 미리 보기 모드를 닫습니다.
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

void CMainFrame::OnComboObject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonComboBox* pObject = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox,
		m_wndRibbonBar.FindByID(ID_COMBO_OBJECT));

	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_nObjectType = pObject->GetCurSel();
}

void CMainFrame::OnButtonEraser()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_nCount = 0;
	pView->Invalidate();
}

void CMainFrame::OnButtonLinecolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonColorButton* pColor =
        DYNAMIC_DOWNCAST(CMFCRibbonColorButton,
                         m_wndRibbonBar.FindByID(ID_BUTTON_LINECOLOR));
    CExample2View* pView = (CExample2View*)GetActiveView();
    pView->m_colorLine = pColor->GetColor();
    pView->Invalidate();
}

void CMainFrame::OnButtonFillcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonColorButton* pColor =
		DYNAMIC_DOWNCAST(CMFCRibbonColorButton,
			m_wndRibbonBar.FindByID(ID_BUTTON_FILLCOLOR));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_colorFill = pColor->GetColor();
	pView->Invalidate();
}

void CMainFrame::OnSliderZoom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonSlider* pZoom =
		DYNAMIC_DOWNCAST(CMFCRibbonSlider,
			m_wndRibbonBar.FindByID(ID_SLIDER_ZOOM));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_fZoom = (float)pZoom->GetPos() / 100.0f;
	pView->Invalidate();
}

void CMainFrame::OnCheckPoints()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonCheckBox* pViewPoint = DYNAMIC_DOWNCAST(
		CMFCRibbonCheckBox,
		m_wndRibbonBar.FindByID(ID_CHECK_POINTS));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_bViewPoints = !pView->m_bViewPoints;
	pView->Invalidate();
}

void CMainFrame::OnUpdateCheckPoints(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CExample2View* pView = (CExample2View*)GetActiveView();
	pCmdUI->SetCheck(pView->m_bViewPoints);
}

void CMainFrame::OnEditText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonEdit* pText = DYNAMIC_DOWNCAST(
		CMFCRibbonEdit,
		m_wndRibbonBar.FindByID(ID_EDIT_TEXT));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_strText = pText->GetEditText();
	pView->Invalidate();
}

void CMainFrame::OnSpinSize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonEdit* pSize = DYNAMIC_DOWNCAST(
		CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_SPIN_SIZE));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_lfFont.lfHeight = (int)_wtoi(pSize->GetEditText());
	pView->Invalidate();
}

void CMainFrame::OnButtonTextcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonColorButton* pColor =
		DYNAMIC_DOWNCAST(CMFCRibbonColorButton,
			m_wndRibbonBar.FindByID(ID_BUTTON_TEXTCOLOR));
	CExample2View* pView = (CExample2View*)GetActiveView();
	pView->m_colorText = pColor->GetColor();
	pView->Invalidate();
}
