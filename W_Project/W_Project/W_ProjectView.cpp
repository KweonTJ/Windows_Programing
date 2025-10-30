
// W_ProjectView.cpp: CWProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "W_Project.h"
#endif

#include "W_ProjectDoc.h"
#include "W_ProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWProjectView

IMPLEMENT_DYNCREATE(CWProjectView, CView)

BEGIN_MESSAGE_MAP(CWProjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CWProjectView::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CWProjectView::OnEllipse)
	ON_COMMAND(ID_RECTANGLE, &CWProjectView::OnRectangle)
	ON_COMMAND(ID_DIAMOND, &CWProjectView::OnDiamond)
	ON_COMMAND(ID_RIGHT_TRIANGLE, &CWProjectView::OnRightTriangle)
	ON_COMMAND(ID_ISO_TRIANGLE, &CWProjectView::OnIsoTriangle)
	ON_COMMAND(ID_TEXT, &CWProjectView::OnText)
	ON_COMMAND(ID_COLOR1, &CWProjectView::OnColor1)
	ON_COMMAND(ID_COLOR2, &CWProjectView::OnColor2)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CWProjectView 생성/소멸

CWProjectView::CWProjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_colorBrush = RGB(255, 255, 255);
	m_colorPen = RGB(0, 0, 0);
	m_nDrawMode = MODE_LINE;	// 기본 도형 모드: 선
	m_bLButtonDown = false;
}

CWProjectView::~CWProjectView()
{
}

BOOL CWProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWProjectView 그리기

void CWProjectView::OnDraw(CDC* pDC)
{
	CWProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Gdiplus::Graphics g(pDC->m_hDC);
	g.SetSmoothingMode(SmoothingModeAntiAlias);	

	for (POSITION pos = pDoc->m_list.GetHeadPosition(); pos; )
	{
		const CMyShape& s = pDoc->m_list.GetNext(pos);
		Color penCol(255, GetRValue(s.pen), GetGValue(s.pen), GetBValue(s.pen));
		Color brCol(255, GetRValue(s.brush), GetGValue(s.brush), GetBValue(s.brush));
		Pen pen(penCol, s.penWidth);
		SolidBrush brush(brCol);

		const int L = s.rc.left, T = s.rc.top, R = s.rc.right, B = s.rc.bottom;
		Rect rect(L, T, R - L, B - T);

		switch (s.type)		// GDI+ 코드를 활용한 도형 그리기 코드
		{
		case ST_LINE:       
			g.DrawLine(&pen, s.rc.left, s.rc.top, s.rc.right, s.rc.bottom); 
			break;
		case ST_ELLIPSE:     
			g.FillEllipse(&brush, rect); g.DrawEllipse(&pen, rect); 
			break;
		case ST_RECTANGLE:   
			g.FillRectangle(&brush, rect); g.DrawRectangle(&pen, rect);
			break;
		case ST_DIAMOND: 
		{
			Point pts[4] = { {(L + R) / 2,T},{R,(T + B) / 2},{(L + R) / 2,B},{L,(T + B) / 2} };
			g.FillPolygon(&brush, pts, 4); g.DrawPolygon(&pen, pts, 4); break;
		}
		case ST_ISO_TRIANGLE: 
		{
			Point pts[3] = { {(L + R) / 2,T},{R,B},{L,B} };
			g.FillPolygon(&brush, pts, 3); g.DrawPolygon(&pen, pts, 3); break;
		}
		case ST_RT_TRIANGLE: 
		{
			Point pts[3] = { {L,T},{L,B},{R,B} };
			g.FillPolygon(&brush, pts, 3); g.DrawPolygon(&pen, pts, 3); break;
		}
		case ST_TEXT: // gdi+의 font의 경우, 식별자가 모호해, gdi의  시스템 폰트 활용.
		{
			/*Font font(L"Malgun Gothic", 20, FontStyleRegular, UnitPixel);*/
			CFont sysFont;
			sysFont.CreateStockObject(DEFAULT_GUI_FONT);
			CFont* pOldFont = pDC->SelectObject(&sysFont);

			COLORREF oldColor = pDC->SetTextColor(s.pen);
			int oldBk = pDC->SetBkMode(TRANSPARENT);

		#ifdef _UNICODE
			// CString은 TCHAR 기반이므로 유니코드면 TextOutW 매크로가 자동 적용
			pDC->TextOut(s.textPt.x, s.textPt.y, s.text);
		#else
			pDC->TextOut(s.textPt.x, s.textPt.y, s.text);
		#endif

			// 3) 원복
			pDC->SetBkMode(oldBk);
			pDC->SetTextColor(oldColor);
			pDC->SelectObject(pOldFont);
			break;
		}
		}
	}
}


// CWProjectView 인쇄


void CWProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CWProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	if (m_bRButtonDown) 
	{
		m_bRButtonDown = false;
		ReleaseCapture();

		// color2로 채우기 확정
		CClientDC dc(this);
		Graphics g(dc);
		g.SetSmoothingMode(SmoothingModeAntiAlias);

		// 화면 갱신(미리보기 잔상 제거)
		Invalidate(FALSE);
	}
	OnContextMenu(this, point);
}

void CWProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}		// 예제 7번에 나온 팝업창 닫기


// CWProjectView 진단

#ifdef _DEBUG
void CWProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CWProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWProjectDoc* CWProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWProjectDoc)));
	return (CWProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CWProjectView 메시지 처리기

void CWProjectView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_LINE;		// 각 함수에 따른 그리기 모드 설정
}

void CWProjectView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_ELLIPSE;
}

void CWProjectView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_RECTANGLE;
}

void CWProjectView::OnDiamond()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_DIAMOND;
}

void CWProjectView::OnRightTriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_RIGHT_TRIANGLE;
}

void CWProjectView::OnIsoTriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_ISO_TRIANGLE;
}

void CWProjectView::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = MODE_TEXT;
}

void CWProjectView::OnColor1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// AfxMessageBox(_T("왼쪽 마우스 클릭, 색상 1로 변경."));		// 색상 1 선택
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		GetDocument()->m_Pcolor = colorDlg.GetColor();
	}
}

void CWProjectView::OnColor2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// AfxMessageBox(_T("오른쪽 마우스 클릭, 색상 2로 변경."));	// 색상 2 선택
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		GetDocument()->m_Bcolor = colorDlg.GetColor();
	}
}

void CWProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// OnColor1(); // 왼쪽 버튼 클릭 시 색상 1 선택이지만, 계속 동작해 그림 못 그림
	SetCapture();
	m_bLButtonDown = true;
	m_ptPrev = m_ptStart = point;
	SetCursor(AfxGetApp()->LoadCursorW(IDC_CROSS));

	if (m_nDrawMode == MODE_TEXT)	// 텍스트 모드 (도형&객체가 아닌, 텍스트이기에 추가적인 모드로 처리)
	{ // 텍스트 위치 지정
		m_textPt = point;
		m_bTyping = true;
		m_textBuffer.Empty();
		CreateSolidCaret(2, 20);
		SetCaretPos(point);
		ShowCaret();
	}

	CView::OnLButtonDown(nFlags, point);
}

void CWProjectView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// OnColor2();
	m_bRButtonDown = true;
	m_ptPrev = m_ptStart = point;
	SetCapture();
	SetCursor(AfxGetApp()->LoadCursorW(IDC_CROSS));

	CView::OnRButtonDown(nFlags, point);
}

void CWProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	Graphics graphics(dc);

	Gdiplus::Color clr;
	clr.SetFromCOLORREF(RGB(255, 255, 255));		// 기본 도형 배경색: 흰색

	if (nFlags == MK_LBUTTON)
	{
		m_ptPrev = point;
		SetCursor(AfxGetApp()->LoadCursorW(IDC_CROSS));
		m_ptPrev = point;
	}
	if (nFlags == MK_RBUTTON)
	{
		
	}

	CView::OnMouseMove(nFlags, point);
}

void CWProjectView::OnLButtonUp(UINT nFlags, CPoint point)		// 왼쪽 버튼이 떼어졌을 때 도형 완성
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown)
	{
		ReleaseCapture();
		m_bLButtonDown = false;

		CWProjectDoc* pDoc = GetDocument();
		const COLORREF pen = pDoc->m_Pcolor;
		const COLORREF brush = pDoc->m_Bcolor;
		const float width = pDoc->m_PenWidth;

		switch (m_nDrawMode)
		{
		case MODE_LINE:
			pDoc->m_list.AddTail(CMyShape::MakeLine(m_ptStart, point, pen, width));
			break;
		case MODE_ELLIPSE:
			pDoc->m_list.AddTail(CMyShape::MakeRectLike(ST_ELLIPSE, m_ptStart, point, pen, brush, width));
			break;
		case MODE_RECTANGLE:
			pDoc->m_list.AddTail(CMyShape::MakeRectLike(ST_RECTANGLE, m_ptStart, point, pen, brush, width));
			break;
		case MODE_DIAMOND:
			pDoc->m_list.AddTail(CMyShape::MakeRectLike(ST_DIAMOND, m_ptStart, point, pen, brush, width));
			break;
		case MODE_ISO_TRIANGLE:
			pDoc->m_list.AddTail(CMyShape::MakeRectLike(ST_ISO_TRIANGLE, m_ptStart, point, pen, brush, width));
			break;
		case MODE_RIGHT_TRIANGLE:
			pDoc->m_list.AddTail(CMyShape::MakeRectLike(ST_RT_TRIANGLE, m_ptStart, point, pen, brush, width));
			break;
		default:
			break;
		}
		pDoc->SetModifiedFlag(); // 문서 수정됨 표시
		Invalidate();	// 화면 갱신
	}

	CView::OnLButtonUp(nFlags, point);
}

// keyboard 문자 처리
void CWProjectView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_bTyping)		// 플래그 변수 사용, 일반 모드, 텍스트 모드 구분
	{
		CView::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	if (nChar == VK_RETURN)
	{
		HideCaret();
		DestroyCaret();
		m_bTyping = false;
		if (!m_textBuffer.IsEmpty())
		{
			CWProjectDoc* pDoc = GetDocument();
			const COLORREF pen = pDoc->m_Pcolor;
			const float width = pDoc->m_PenWidth;
			pDoc->m_list.AddTail(CMyShape::MakeText(m_textBuffer, m_textPt, pDoc->m_Pcolor));
			pDoc->SetModifiedFlag(); // 문서 수정됨 표시
			Invalidate();	// 화면 갱신
		}
		return;
	}		// 텍스트 입력 최종 확정 및 종료

	if (nChar == VK_ESCAPE) 
	{
		HideCaret(); DestroyCaret();
		m_bTyping = false; m_textBuffer.Empty();
		Invalidate(FALSE); return;
	}		// 텍스트 입력 취소 및 입력 모드 종료

	if (nChar == VK_BACK) 
	{
		if (!m_textBuffer.IsEmpty()) 
			m_textBuffer.Delete(m_textBuffer.GetLength() - 1, 1);
	}
	else 
	{
		m_textBuffer.AppendChar((TCHAR)nChar);
	}
	// m_textBuffer에 저장된 문자열의 마지막 글자 하나 삭제
	CView::OnChar(nChar, nRepCnt, nFlags);
}
