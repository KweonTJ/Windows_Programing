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

// Example2View.cpp: CExample2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example2.h"
#endif

#include "Example2Doc.h"
#include "Example2View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExample2View

IMPLEMENT_DYNCREATE(CExample2View, CView)

BEGIN_MESSAGE_MAP(CExample2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExample2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CExample2View 생성/소멸

CExample2View::CExample2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nObjectType = -1;
	m_nCount = 0;

	afxGlobalData.fontRegular.GetLogFont(&m_lfFont);
	m_lfFont.lfHeight = 20;

	m_colorLine = RGB(0, 0, 0);
	m_colorFill = RGB(255, 255, 255);
	m_colorText = RGB(0, 0, 255);
	m_fZoom = 1.0f;
	m_bViewPoints = true;

}

CExample2View::~CExample2View()
{
}

BOOL CExample2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExample2View 그리기

void CExample2View::OnDraw(CDC* pDC)
{
	CExample2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rc;
	GetClientRect(&rc);

	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	CFont font, * pOldFont;

	pen.CreatePen(PS_SOLID, 2, m_colorLine);
	brush.CreateSolidBrush(m_colorFill);
	font.CreateFontIndirect(&m_lfFont);

	pOldPen = pDC->SelectObject(&pen);
	pOldBrush = pDC->SelectObject(&brush);
	pOldFont = pDC->SelectObject(&font);

	switch (m_nObjectType)
	{
	case 0:
		DrawEllipse(pDC);            // 타원 그리기
		break;

	case 1:
		DrawPolygon(pDC);            // 다각형 그리기
		break;
	}

	pDC->SetTextColor(m_colorText);
	pDC->DrawText(m_strText, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);

	pen.DeleteObject();
	brush.DeleteObject();
	font.DeleteObject();

}


// CExample2View 인쇄


void CExample2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExample2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExample2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExample2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CExample2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExample2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExample2View 진단

#ifdef _DEBUG
void CExample2View::AssertValid() const
{
	CView::AssertValid();
}

void CExample2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample2Doc* CExample2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample2Doc)));
	return (CExample2Doc*)m_pDocument;
}
#endif //_DEBUG


// CExample2View 메시지 처리기

void CExample2View::DrawEllipse(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	if (!m_nCount)
		return;

	int x1, y1, x2, y2;
	if (m_nCount < 2)
	{
		x1 = (int)((float)m_ptPoints[0].x * m_fZoom);
		y1 = (int)((float)m_ptPoints[0].y * m_fZoom);
		if (m_bViewPoints)
			pDC->Ellipse(x1 - 4, y1 - 4, x1 + 4, y1 + 4);
	}
	else
	{
		x1 = (int)((float)m_ptPoints[0].x * m_fZoom);
		y1 = (int)((float)m_ptPoints[0].y * m_fZoom);
		x2 = (int)((float)m_ptPoints[1].x * m_fZoom);
		y2 = (int)((float)m_ptPoints[1].y * m_fZoom);
		pDC->Ellipse(x1, y1, x2, y2);
		if (m_bViewPoints)
		{
			pDC->Ellipse(x1 - 4, y1 - 4, x1 + 4, y1 + 4);
			pDC->Ellipse(x2 - 4, y2 - 4, x2 + 4, y2 + 4);
		}
	}
}


void CExample2View::DrawPolygon(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	CPoint pPoints[20];
	for (int i = 0; i < m_nCount; i++)
	{
		pPoints[i].x = (int)((float)m_ptPoints[i].x * m_fZoom);
		pPoints[i].y = (int)((float)m_ptPoints[i].y * m_fZoom);
	}
	// 다각형 그리기
	if (m_bDrawing)
		pDC->Polyline(pPoints, m_nCount);
	else
		pDC->Polygon(pPoints, m_nCount);
	if (m_bViewPoints)
	{
		for (int i = 0; i < m_nCount; i++)
			pDC->Ellipse(pPoints[i].x - 4, pPoints[i].y - 4,
				pPoints[i].x + 4, pPoints[i].y + 4);
	}
}

void CExample2View::ResetZoom()
{
	// TODO: 여기에 구현 코드 추가.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonSlider* pZoom = DYNAMIC_DOWNCAST(CMFCRibbonSlider,
			pFrame->GetRibbonBar()->FindByID(ID_SLIDER_ZOOM));
	pZoom->SetPos(100);

	m_fZoom = 1.0f;
	Invalidate();
}

void CExample2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nObjectType == 0)
	{
		if (m_nCount == 0 || m_nCount >= 2)
		{
			ResetZoom();
			m_nCount = 0;
			m_bDrawing = true;
		}
		m_ptPoints[m_nCount++] = point;
		if (m_nCount == 2)
			m_bDrawing = false;

		Invalidate();
	}
	else if (m_nObjectType == 1)
	{
		if (!m_bDrawing)
		{
			ResetZoom();
			m_nCount = 0;
			m_bDrawing = true;
		}
		m_ptPoints[m_nCount++] = point;
		Invalidate();
	}

	m_ptPrev = point;
	CView::OnLButtonDown(nFlags, point);
}

void CExample2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nObjectType == 1)
	{
		if (m_bDrawing)
			m_bDrawing = false;
		Invalidate();
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CExample2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nCount < 1 || !m_bDrawing)
		return;

	CClientDC dc(this);
	switch (m_nObjectType)
	{
	case 0:
		DrawEllipse(&dc);
		break;
	case 1:
		DrawEllipse(&dc);
		break;
	}
	dc.SetROP2(R2_NOT);
	dc.MoveTo(m_ptPoints[m_nCount - 1]);
	dc.LineTo(m_ptPrev);

	dc.SetROP2(R2_COPYPEN);
	dc.MoveTo(m_ptPoints[m_nCount - 1]);
	dc.LineTo(point);

	m_ptPrev = point;
	CView::OnMouseMove(nFlags, point);
}
